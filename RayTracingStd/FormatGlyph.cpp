#pragma warning(disable:4530)

#include <string>
#include "TraceService.h"
#include "stdafx.h"
#include "FormatGlyph.h"
#include "FontFile.h"

unsigned short CFormatGlyph::ProcessFormat0Glyph(CFontFileInfo &ffile, unsigned int search_char)
{
  char temp_index;

  ffile.fp.Seek((long)search_char, CFile::current) ;
  
  if (!ffile.fp.Read ((char *)(&temp_index), 1)) /* Each index is 1 byte */
  {
    _TRACE_ERROR(_STR("Cannot read TrueType font file at line %d, %s",
          __LINE__, __FILE__));
  }
  
  return (unsigned short)(temp_index);
}


unsigned short CFormatGlyph::ProcessFormat4Glyph(CFontFileInfo &ffile, unsigned int search_char)
{
  int i;
  unsigned int glyph_index = 0;  /* Set the glyph index to "not present" */

  /*
   * If this is the first time we are here, read all of the segment headers,
   * and save them for later calls to this function, rather than seeking and
   * mallocing for each character
   */
  if (ffile.segCount == 0)
  {
    USHORT temp16;

    ffile.segCount = CFontFile::readUSHORT(ffile.fp) >> 1;
    ffile.searchRange = CFontFile::readUSHORT(ffile.fp);
    ffile.entrySelector = CFontFile::readUSHORT(ffile.fp);
    ffile.rangeShift = CFontFile::readUSHORT(ffile.fp);

    /* Now allocate and read in the segment arrays */
  
    ffile.endCount = (USHORT *)malloc(ffile.segCount * sizeof(USHORT));
    ffile.startCount = (USHORT *)malloc(ffile.segCount * sizeof(USHORT));
    ffile.idDelta = (USHORT *)malloc(ffile.segCount * sizeof(USHORT));
    ffile.idRangeOffset = (USHORT *)malloc(ffile.segCount * sizeof(USHORT));

    for (i = 0; i < ffile.segCount; i++)
    {
      ffile.endCount[i] = CFontFile::readUSHORT(ffile.fp);
    }
  
    temp16 = CFontFile::readUSHORT(ffile.fp);  /* Skip over 'reservedPad' */
  
    for (i = 0; i < ffile.segCount; i++)
    {
      ffile.startCount[i] = CFontFile::readUSHORT(ffile.fp);
    }
  
    for (i = 0; i < ffile.segCount; i++)
    {
      ffile.idDelta[i] = CFontFile::readUSHORT(ffile.fp);
    }

    /* location of start of idRangeOffset */
    ffile.glyphIDoffset = ffile.fp.GetPosition () ;

    for (i = 0; i < ffile.segCount; i++)
    {
      ffile.idRangeOffset[i] = CFontFile::readUSHORT(ffile.fp);
    }
  }
  
  /* Search the segments for our character */
  
glyph_search:
  for (i = 0; i < ffile.segCount; i++)
  {
    if (search_char <= ffile.endCount[i])
    {
      if (search_char >= ffile.startCount[i])
      {
        /* Found correct range for this character */
  
        if (ffile.idRangeOffset[i] == 0)
        {
          glyph_index = search_char + ffile.idDelta[i];
        }
        else
        {
          /*
           * Alternate encoding of glyph indices, relies on a quite unusual way
           * of storing the offsets.  We need the *2s because we are talking
           * about addresses of shorts and not bytes.
           *
           * (glyphIDoffset + i*2 + idRangeOffset[i]) == &idRangeOffset[i]
           */
          ffile.fp.Seek(ffile.glyphIDoffset + 2*i + ffile.idRangeOffset[i]+
			  2*(search_char - ffile.startCount[i]),CFile::begin);
          
          glyph_index = CFontFile::readUSHORT(ffile.fp);
          
          if (glyph_index != 0)
            glyph_index = glyph_index + ffile.idDelta[i];
        }
      }
      break;
    }
  }

  /*
   * If we haven't found the character yet, and this is the first time to
   * search the tables, try looking in the Unicode user space, since this
   * is the location Microsoft recommends for symbol characters like those
   * in wingdings and dingbats.
   */
  if (glyph_index == 0 && search_char < 0x100)
  {
    search_char += 0xF000;

    goto glyph_search;
  }

  /* Deallocate the memory we used for the segment arrays */
  
  return glyph_index;
}



unsigned short CFormatGlyph::ProcessFormat6Glyph(CFontFileInfo &ffile, unsigned int search_char)
{
  USHORT firstCode, entryCount;
  BYTE glyph_index;

  firstCode = CFontFile::readUSHORT(ffile.fp);
  entryCount = CFontFile::readUSHORT(ffile.fp);
  
  if (search_char >= firstCode && search_char < firstCode + entryCount)
  {
	ffile.fp.Seek((long)(search_char - firstCode), CFile::current) ;
    glyph_index = CFontFile::readUSHORT(ffile.fp);
  }
  else
    glyph_index = 0;
  
  return glyph_index;
}


void CFormatGlyph::ExtractGlyphOutline(CFontFileInfo &ffile,
									   unsigned int glyph_index, 
									   unsigned int c,
									   CGlyphOutline &ttglyph)
{
  int i;
  USHORT n;
  SHORT nc;

  ttglyph.myMetrics = glyph_index;

  /* Have to treat space characters differently */
  if (c != ' ')
  {
	  ffile.fp.Seek(ffile.glyf_table_offset+ffile.loca_table[glyph_index],CFile::begin);

    ttglyph.header.numContours = CFontFile::readSHORT(ffile.fp);
    ttglyph.header.xMin = CFontFile::readSHORT(ffile.fp);   /* These may be  */
    ttglyph.header.yMin = CFontFile::readSHORT(ffile.fp);   /* unreliable in */
    ttglyph.header.xMax = CFontFile::readSHORT(ffile.fp);   /* some fonts.   */
    ttglyph.header.yMax = CFontFile::readSHORT(ffile.fp);
  }
  
  nc = ttglyph.header.numContours;
  
  /*
   * A positive number of contours means a regular glyph, with possibly
   * several separate line segments making up the outline.
   */
  if (nc > 0)
  {
    short coord;
    BYTE flag, repeat_count;
    USHORT temp16;

    /* Grab the contour endpoints */
  
    //ttglyph.endPoints = (USHORT *)POV_MALLOC(nc * sizeof(USHORT), "ttf");
	ttglyph.endPoints = new unsigned short[nc];
  
    for (i = 0; i < nc; i++)
    {
      ttglyph.endPoints[i] = CFontFile::readUSHORT(ffile.fp);
    }

    /* Skip over the instructions */
    temp16 = CFontFile::readUSHORT(ffile.fp);
    ffile.fp.Seek(temp16, CFile::current);

    /* Determine the number of points making up this glyph */
    
    n = ttglyph.numPoints = ttglyph.endPoints[nc - 1] + 1;

    /* Read the flags */
    
    ttglyph.flags = new char[n];
    
    for (i = 0; i < ttglyph.numPoints; i++)
    {
      if (!ffile.fp.Read((char *)(&ttglyph.flags[i]), sizeof(BYTE)))
      {
        _TRACE_ERROR(_STR("Cannot read TrueType font file at line %d, %s",
              __LINE__, __FILE__));
      }
      
      if (ttglyph.flags[i] & REPEAT_FLAGS)
      {
        if (!ffile.fp.Read((char *)(&repeat_count), sizeof(BYTE)))
        {
          _TRACE_ERROR(_STR("Cannot read TrueType font file at line %d, %s",
                __LINE__, __FILE__));
        }
        for (; repeat_count > 0; repeat_count--, i++)
        {
          if (i<n)      /* hack around a bug that is trying to write too many flags */
            ttglyph.flags[i + 1] = ttglyph.flags[i];
        }
      }
    }

    /* Read the coordinate vectors */
    
    ttglyph.x = new double[n];
    ttglyph.y = new double[n];

    coord = 0;
    
    for (i = 0; i < ttglyph.numPoints; i++)
    {
      /* Read each x coordinate */
      
      flag = ttglyph.flags[i];
      
      if (flag & XSHORT)
      {
        BYTE temp8;

        if (!ffile.fp.Read((char *)(&temp8), 1))
        {
          _TRACE_ERROR(_STR("Cannot read TrueType font file at line %d, %s",
                __LINE__, __FILE__));
        }
        
        if (flag & SHORT_X_IS_POS)
          coord += temp8;
        else
          coord -= temp8;
      }
      else if (!(flag & NEXT_X_IS_ZERO))
      {
        coord += CFontFile::readSHORT(ffile.fp);
      }
      
      /* Find our own maximum and minimum x coordinates */
      if (coord > ttglyph.header.xMax)
        ttglyph.header.xMax = coord;
      if (coord < ttglyph.header.xMin)
        ttglyph.header.xMin = coord;

      ttglyph.x[i] = (double)coord / (double)ffile.unitsPerEm;
    }

    coord = 0;
    
    for (i = 0; i < ttglyph.numPoints; i++)
    {
      /* Read each y coordinate */
      
      flag = ttglyph.flags[i];
      
      if (flag & YSHORT)
      {
        BYTE temp8;

        if (!ffile.fp.Read((char *)(&temp8), 1))
        {
          _TRACE_ERROR(_STR("Cannot read TrueType font file at line %d, %s",
                __LINE__, __FILE__));
        }
        
        if (flag & SHORT_Y_IS_POS)
          coord += temp8;
        else
          coord -= temp8;
      }
      else if (!(flag & NEXT_Y_IS_ZERO))
      {
        coord += CFontFile::readSHORT(ffile.fp);
      }
      
      /* Find out our own maximum and minimum y coordinates */
      if (coord > ttglyph.header.yMax)
        ttglyph.header.yMax = coord;
      if (coord < ttglyph.header.yMin)
        ttglyph.header.yMin = coord;

      ttglyph.y[i] = (double)coord / (double)ffile.unitsPerEm;
    }
  }
  /*
   * A negative number for numContours means that this glyph is
   * made up of several separate glyphs.
   */
  else if (nc < 0)
  {
    USHORT flags;

    ttglyph.header.numContours = 0;
    ttglyph.numPoints = 0;

    do
    {
      CGlyphOutline sub_ttglyph;
      unsigned int sub_glyph_index;
      long   current_pos;
      SHORT arg1, arg2;
      double xoff = 0, yoff = 0;
      double xscale = 1, yscale = 1;
      double scale01 = 0, scale10 = 0;
      USHORT n2;
      SHORT nc2;

      flags = CFontFile::readUSHORT(ffile.fp);
      sub_glyph_index = CFontFile::readUSHORT(ffile.fp);

   
      if (flags & ARG_1_AND_2_ARE_WORDS)
      {
        arg1 = CFontFile::readSHORT(ffile.fp);
        arg2 = CFontFile::readSHORT(ffile.fp);
      }
      else
      {
        arg1 = CFontFile::readUSHORT(ffile.fp);
        arg2 = arg1 & 0xFF;
        arg1 = (arg1 >> 8) & 0xFF;
      }


      if (flags & WE_HAVE_A_SCALE)
      {
        xscale = yscale = (double)CFontFile::readSHORT(ffile.fp)/0x4000;
      }
      else if (flags & WE_HAVE_AN_X_AND_Y_SCALE)
      {
        xscale = (double)CFontFile::readSHORT(ffile.fp)/0x4000;
        yscale = (double)CFontFile::readSHORT(ffile.fp)/0x4000;
      }
      else if (flags & WE_HAVE_A_TWO_BY_TWO)
      {
        xscale  = (double)CFontFile::readSHORT(ffile.fp)/0x4000;
        scale01 = (double)CFontFile::readSHORT(ffile.fp)/0x4000;
        scale10 = (double)CFontFile::readSHORT(ffile.fp)/0x4000;
        yscale  = (double)CFontFile::readSHORT(ffile.fp)/0x4000;
      }

      if (flags & ARGS_ARE_XY_VALUES)
      {
        xoff = (double)arg1 / ffile.unitsPerEm;
        yoff = (double)arg2 / ffile.unitsPerEm;
      }
      else  /* until I understand how this method works... */
      {
        _TRACE_WARNING(_STR("Cannot handle part of glyph %d (0x%X).", c, c));
        continue;
      }

      if (flags & USE_MY_METRICS)
      {
        ttglyph.myMetrics = sub_glyph_index;
      }

      current_pos = ffile.fp.GetPosition() ;
      ExtractGlyphOutline(ffile, sub_glyph_index, c,sub_ttglyph);
      ffile.fp.Seek(current_pos,CFile::begin) ;

      if ((nc2 = sub_ttglyph.header.numContours) == 0)
        continue;

      nc = ttglyph.header.numContours;
      n = ttglyph.numPoints;
      n2 = sub_ttglyph.numPoints;

	  if(ttglyph.endPoints!=NULL) delete[] ttglyph.endPoints;
	  if(ttglyph.flags!=NULL) delete[] ttglyph.flags;
	  if(ttglyph.x!=NULL) delete[] ttglyph.x;
	  if(ttglyph.y!=NULL) delete[] ttglyph.y;
	  
      ttglyph.endPoints = new unsigned short[nc+nc2];
      ttglyph.flags = new char[n+n2];
      ttglyph.x = new double[n+n2];
      ttglyph.y = new double[n+n2];

      /* Add the sub glyph info to the end of the current glyph */

      ttglyph.header.numContours += nc2;
      ttglyph.numPoints += n2;

      for (i = 0; i < nc2; i++)
      {
        ttglyph.endPoints[i + nc] = sub_ttglyph.endPoints[i] + n;
      }

      for (i = 0; i < n2; i++)
      {
        ttglyph.flags[i + n] = sub_ttglyph.flags[i];
        ttglyph.x[i + n] = xscale * sub_ttglyph.x[i] +
                            scale01 * sub_ttglyph.y[i] + xoff;
        ttglyph.y[i + n] = scale10 * sub_ttglyph.x[i] +
                            yscale * sub_ttglyph.y[i] + yoff;

        if (ttglyph.x[i + n] < ttglyph.header.xMin)
          ttglyph.header.xMin = ttglyph.x[i + n];

        if (ttglyph.x[i + n] > ttglyph.header.xMax)
          ttglyph.header.xMax = ttglyph.x[i + n];

        if (ttglyph.y[i + n] < ttglyph.header.yMin)
          ttglyph.header.yMin = ttglyph.y[i + n];

        if (ttglyph.y[i + n] > ttglyph.header.yMax)
          ttglyph.header.yMax = ttglyph.y[i + n];
      }

    } while (flags & MORE_COMPONENTS);
  }
}


void CFormatGlyph::ConvertOutlineToGlyph(CFontFileInfo &ffile, CGlyphOutline &ttglyph,CGlyph &glyph)
{
  double *temp_x, *temp_y;
  char *temp_f;
  USHORT i, j, last_j;

  /* Create storage for this glyph */

  if (ttglyph.header.numContours > 0)
  {
    glyph.contours = new CContour[ttglyph.header.numContours];
  }
  else
  {
    glyph.contours = NULL;
  }

  /* Copy sizing information about this glyph */
  
  memcpy(&glyph.header, &ttglyph.header, sizeof(CGlyphHeader));

  /* Keep track of the size for this glyph */
  
  glyph.unitsPerEm = ffile.unitsPerEm;

  /* Now copy the vertex information into the contours */
  
  for (i = 0, last_j = 0; i < (USHORT) ttglyph.header.numContours; i++)
  {
    /* Figure out number of points in contour */
  
    j = ttglyph.endPoints[i] - last_j + 1;

    /* Copy the coordinate information into the glyph */
  
    temp_x = new double[j+1];
    temp_y = new double[j+1];

    temp_f = new char[j+1];
    memcpy(temp_x, &ttglyph.x[last_j], j * sizeof(double));
    memcpy(temp_y, &ttglyph.y[last_j], j * sizeof(double));

    memcpy(temp_f, &ttglyph.flags[last_j], j * sizeof(char));
    temp_x[j] = ttglyph.x[last_j];
    temp_y[j] = ttglyph.y[last_j];
    temp_f[j] = ttglyph.flags[last_j];

    /* Figure out if this is an inside or outside contour */
    
    glyph.contours[i].inside_flag = 0;

    /* Plug in the reset of the contour components into the glyph */
    
    glyph.contours[i].count = j;
    glyph.contours[i].x = temp_x;
    glyph.contours[i].y = temp_y;
    glyph.contours[i].flags = temp_f;

    /*
     * Set last_j to point to the beginning of the next contour's coordinate
     * information
     */
    
    last_j = ttglyph.endPoints[i] + 1;
  }
}