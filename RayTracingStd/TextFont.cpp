//Based on POYRAY files
#include "stdafx.h"		//pour system directory
#include "TextFont.h"
#include "TraceService.h"
#include "FontFile.h"
#include "resource.h"

static char tag_CharToIndexMap[] = "cmap"; /* 0x636d6170; */
static char tag_FontHeader[]     = "head"; /* 0x68656164; */
static char tag_GlyphData[]      = "glyf"; /* 0x676c7966; */
static char tag_IndexToLoc[]     = "loca"; /* 0x6c6f6361; */
static char tag_Kerning[]        = "kern"; /* 0x6b65726e; */
static char tag_MaxProfile[]     = "maxp"; /* 0x6d617870; */
static char tag_HorizHeader[]    = "hhea"; /* 0x68686561; */
static char tag_HorizMetric[]    = "hmtx"; /* 0x686d7478; */
static char tag_TTCFontFile[]    = "ttcf"; /* */

CTextFont::CTextFont(const std::string &fontfilename)
{
	m_bExistFont=ProcessFontFile(fontfilename);
}

CTextFont::~CTextFont()
{
	m_FontFileInfo=CFontFileInfo(); //création nouvelle fonte bidon pour éviter double destruction
	//car cette fonte va être également détruite dans la liste
}


int CTextFont::compare_tag4(char *ttf_tag, char *known_tag)
{
   return (ttf_tag[0] == known_tag[0] && ttf_tag[1] == known_tag[1] &&
           ttf_tag[2] == known_tag[2] && ttf_tag[3] == known_tag[3]);
}


bool	CTextFont::ProcessFontFile(const std::string &fontfilename)
{
  long head_table_offset = 0;
  long loca_table_offset = 0;
  long maxp_table_offset = 0;
  long kern_table_offset = 0;
  long hhea_table_offset = 0;
  long hmtx_table_offset = 0;
  char temp_tag[4];
  C_sfnt_OffsetTable OffsetTable;

  /* Open the font file */
  
  if(!OpenFontFile(fontfilename,m_FontFileInfo))
  {
	  CString str;
	  str.LoadString(IDS_ERROR_FONTFILE);
	  AfxMessageBox(str);
	  return false;
  }


  /*
   * Read the initial directory header on the TTF.  The numTables variable
   * tells us how many tables are present in this file.
   */
  if (!m_FontFileInfo.fp.Read((char *)(&temp_tag), sizeof(BYTE) * 4))
  {
    //Error("Cannot read TrueType font file table tag");
  }
  if (compare_tag4(temp_tag, tag_TTCFontFile))
  {
    CFontFile::readSHORT(m_FontFileInfo.fp); // header version - ignored [trf]
    CFontFile::readULONG(m_FontFileInfo.fp); // directory count - ignored [trf]
    // go to first font data block listed in the directory table entry [trf]
    m_FontFileInfo.fp.Seek(CFontFile::readULONG(m_FontFileInfo.fp), CFile::begin);
  }
  else
  {
    // if it is no TTC style file, it is a regular TTF style file
    m_FontFileInfo.fp.Seek(0, CFile::begin);
  }

  OffsetTable.version = CFontFile::readLONG(m_FontFileInfo.fp);
  OffsetTable.numTables = CFontFile::readUSHORT(m_FontFileInfo.fp);
  OffsetTable.searchRange = CFontFile::readUSHORT(m_FontFileInfo.fp);
  OffsetTable.entrySelector = CFontFile::readUSHORT(m_FontFileInfo.fp);
  OffsetTable.rangeShift = CFontFile::readUSHORT(m_FontFileInfo.fp);


  /* Process general font information and save it. */
  
  for (int i = 0; i < OffsetTable.numTables && i < 40; i++)
  {
	C_sfnt_TableDirectory Table;

	if (!m_FontFileInfo.fp.Read((char *)(&Table.tag), sizeof(BYTE) * 4))
    {
      //Error("Cannot read TrueType font file table tag");
    }

    Table.checkSum = CFontFile::readULONG(m_FontFileInfo.fp);
    Table.offset   = CFontFile::readULONG(m_FontFileInfo.fp);
    Table.length   = CFontFile::readULONG(m_FontFileInfo.fp);


    if (compare_tag4(Table.tag, tag_CharToIndexMap))
      m_FontFileInfo.cmap_table_offset = Table.offset;
    else if (compare_tag4(Table.tag, tag_GlyphData))
      m_FontFileInfo.glyf_table_offset = Table.offset;
    else if (compare_tag4(Table.tag, tag_FontHeader))
      head_table_offset = Table.offset;
    else if (compare_tag4(Table.tag, tag_IndexToLoc))
      loca_table_offset = Table.offset;
    else if (compare_tag4(Table.tag, tag_MaxProfile))
      maxp_table_offset = Table.offset;
    else if (compare_tag4(Table.tag, tag_Kerning))
      kern_table_offset = Table.offset;
    else if (compare_tag4(Table.tag, tag_HorizHeader))
      hhea_table_offset = Table.offset;
    else if (compare_tag4(Table.tag, tag_HorizMetric))
      hmtx_table_offset = Table.offset;
  }

    ProcessHeadTable(m_FontFileInfo, head_table_offset);  /* Need indexToLocFormat */

    ProcessMaxpTable(m_FontFileInfo, maxp_table_offset);  /* Need numGlyphs */

    ProcessLocaTable(m_FontFileInfo, loca_table_offset);  /* Now we can do loca_table */

    ProcessHheaTable(m_FontFileInfo, hhea_table_offset);  /* Need numberOfHMetrics */

    ProcessHmtxTable(m_FontFileInfo, hmtx_table_offset);  /* Now we can read HMetrics */

	if (kern_table_offset != 0)
      ProcessKernTable(m_FontFileInfo, kern_table_offset);

	return true;
  
}

#define MAX_CHAR_KEYS	255

bool CTextFont::OpenFontFile(const std::string &filename,CFontFileInfo &FileInfo)
{
  /* int i; */ /* tw, mtg */
  char b[FILE_NAME_LENGTH];

  /* First look to see if we have already opened this font */
  std::vector<CFontFileInfo>::iterator i;
  for(i=m_ListFontFileInfo.begin();
	  i!=m_ListFontFileInfo.end();i++)
	  {
		  CFontFileInfo &FileInfo=(*i);
		  if(filename.compare(FileInfo.filename)==0)
			  break;
	  }

  if(i!=m_ListFontFileInfo.end())
  {
	FileInfo=*i;
	if(!FileInfo.fp.Open(FileInfo.filename.c_str(),CFile::modeRead)) return false;
  }
  else
  {
	char sKeyValue[MAX_CHAR_KEYS];
	GetWindowsDirectory(sKeyValue,MAX_CHAR_KEYS);
	
	CString str;
	str.Format("%s\\fonts\\%s",sKeyValue,filename.c_str());
  	if(!FileInfo.fp.Open(str,CFile::modeRead)) return false;
  
    FileInfo.filename = b;
    
    /*
     * For Microsoft encodings 3, 1 is for Unicode
     *                         3, 0 is for Non-Unicode (ie symbols),
     * For Macintosh encodings 1, 0 is for Roman character set.
     */
 // ASCII
	// first choice
	FileInfo.platformID[0] = 1;
	FileInfo.specificID[0] = 0;
	// second choice
	FileInfo.platformID[1] = 3;
	FileInfo.specificID[1] = 1;
	// third choice
	FileInfo.platformID[2] = 3;
	FileInfo.specificID[2] = 0;
	// fourth choice (not used right now)
	FileInfo.platformID[3] = 0;
	FileInfo.specificID[3] = 0;

	// UTF8
	 // System Specific
/*			// first choice
			fontlist->platformID[0] = 3;
			fontlist->specificID[0] = 1;
			// second choice
			fontlist->platformID[1] = 1;
			fontlist->specificID[1] = 0;
			// third choice
			fontlist->platformID[2] = 3;
			fontlist->specificID[2] = 0;
			// fourth choice (not used right now)
			fontlist->platformID[3] = 0;
			fontlist->specificID[3] = 0;*/

	m_ListFontFileInfo.push_back(FileInfo);

  }

  return true;

}


void CTextFont::ProcessHeadTable(CFontFileInfo &ffile, long head_table_offset)
{
  C_sfnt_FontHeader fontHeader;

  /* Read head table */
  ffile.fp.Seek(head_table_offset,CFile::begin) ;

  fontHeader.version = CFontFile::readLONG(ffile.fp);
  fontHeader.fontRevision = CFontFile::readLONG(ffile.fp);
  fontHeader.checkSumAdjustment = CFontFile::readULONG(ffile.fp);
  fontHeader.magicNumber = CFontFile::readULONG(ffile.fp);   /* should be 0x5F0F3CF5 */
  fontHeader.flags = CFontFile::readUSHORT(ffile.fp);
  fontHeader.unitsPerEm = CFontFile::readUSHORT(ffile.fp);
  fontHeader.created.bc = CFontFile::readULONG(ffile.fp);
  fontHeader.created.ad = CFontFile::readULONG(ffile.fp);
  fontHeader.modified.bc = CFontFile::readULONG(ffile.fp);
  fontHeader.modified.ad = CFontFile::readULONG(ffile.fp);
  fontHeader.xMin = CFontFile::readSHORT(ffile.fp);
  fontHeader.yMin = CFontFile::readSHORT(ffile.fp);
  fontHeader.xMax = CFontFile::readSHORT(ffile.fp);
  fontHeader.yMax = CFontFile::readSHORT(ffile.fp);
  fontHeader.macStyle = CFontFile::readUSHORT(ffile.fp);
  fontHeader.lowestRecPPEM = CFontFile::readUSHORT(ffile.fp);
  fontHeader.fontDirectionHint = CFontFile::readSHORT(ffile.fp);
  fontHeader.indexToLocFormat = CFontFile::readSHORT(ffile.fp);
  fontHeader.glyphDataFormat = CFontFile::readSHORT(ffile.fp);
  
  if (fontHeader.magicNumber != 0x5F0F3CF5)
  {
	_TRACE_ERROR("Error MagicNumber");
    //Error("Error reading TrueType font %s.  Bad magic number (0x%8X)",
    //      ffile->filename, fontHeader.magicNumber);
  }

  ffile.indexToLocFormat = fontHeader.indexToLocFormat;
  ffile.unitsPerEm = fontHeader.unitsPerEm;
}

void CTextFont::ProcessMaxpTable(CFontFileInfo &ffile, long maxp_table_offset)
{
  /* seekg to the maxp table, skipping the 4 byte version number */
  ffile.fp.Seek(maxp_table_offset + 4,CFile::begin) ;
  
  ffile.numGlyphs = CFontFile::readUSHORT(ffile.fp);
}

void CTextFont::ProcessLocaTable(CFontFileInfo &ffile, long loca_table_offset)
{
  int i;

  /* Move to location of table in file */
  ffile.fp.Seek(loca_table_offset,CFile::begin) ;

  ffile.loca_table = (unsigned long*) malloc((ffile.numGlyphs+1) * sizeof(ULONG));

  /* Now read and save the location table */
  if (ffile.indexToLocFormat == 0)                  /* short version */
  {
    for (i = 0; i < ffile.numGlyphs; i++)
    {
      ffile.loca_table[i] = ((ULONG)CFontFile::readUSHORT(ffile.fp)) << 1;
    }
  }
  else                                               /* long version */
  {
    for (i = 0; i < ffile.numGlyphs; i++)
    {
      ffile.loca_table[i] = CFontFile::readULONG(ffile.fp);
    }
  }
}


/*
 * This routine determines the total number of horizontal metrics.
 */
void CTextFont::ProcessHheaTable(CFontFileInfo &ffile, long hhea_table_offset)
{
  /* seekg to the hhea table, skipping all that stuff we don't need */
	ffile.fp.Seek(hhea_table_offset + 34,CFile::begin) ;
	ffile.numberOfHMetrics = CFontFile::readUSHORT(ffile.fp);
}


void CTextFont::ProcessHmtxTable (CFontFileInfo &ffile, long hmtx_table_offset)
{
  int i;
  CLongHorMetric *metric;
  USHORT lastAW = 0;     /* Just to quiet warnings. */

  ffile.fp.Seek (hmtx_table_offset,CFile::begin) ;

  ffile.hmtx_table = (CLongHorMetric *) malloc (ffile.numGlyphs*sizeof(CLongHorMetric));

  /*
   * Read in the total glyph width, and the left side offset.  There is
   * guaranteed to be at least one longHorMetric entry in this table to
   * set the advanceWidth for the subsequent lsb entries.
   */
  for (i=0, metric=ffile.hmtx_table; i < ffile.numberOfHMetrics; i++,metric++)
  {
    lastAW = metric->advanceWidth = CFontFile::readUSHORT(ffile.fp);
    metric->lsb = CFontFile::readSHORT(ffile.fp);
  }

  /* Read in the remaining left offsets */
  for (; i < ffile.numGlyphs; i++, metric++)
  {
    metric->advanceWidth = lastAW;
    metric->lsb = CFontFile::readSHORT(ffile.fp);
  }
}


/* Read the kerning information for a glyph */
void CTextFont::ProcessKernTable(CFontFileInfo &ffile, long kern_table_offset)
{
  int i, j;
  USHORT temp16;
  USHORT length;
  CKernTables *kern_table;

  kern_table = &ffile.kerning_tables;

  /* Move to the beginning of the kerning table, skipping the 2 byte version */
  ffile.fp.Seek(kern_table_offset + 2,CFile::begin) ;

  /* Read in the number of kerning tables */

  kern_table->nTables = CFontFile::readUSHORT(ffile.fp);
  kern_table->tables = NULL;      /*<==[esp] added (in case nTables is zero)*/
  
  /* Don't do any more work if there isn't kerning info */
  
  if (kern_table->nTables == 0)
    return;

  kern_table->tables = (CKernStruct *)malloc(kern_table->nTables * sizeof(CKernStruct));
  
  for (i = 0; i < kern_table->nTables; i++)
  {
    /* Read in a subtable */
    
    temp16 = CFontFile::readUSHORT(ffile.fp);                      /* Subtable version */
    length = CFontFile::readUSHORT(ffile.fp);                       /* Subtable length */
    kern_table->tables[i].coverage = CFontFile::readUSHORT(ffile.fp); /* Coverage bits */
   
    kern_table->tables[i].kern_pairs = NULL;   /*<==[esp] added*/
    kern_table->tables[i].nPairs = 0;          /*<==[esp] added*/

    if ((kern_table->tables[i].coverage >> 8) == 0)
    {
      /* Can only handle format 0 kerning subtables */
      kern_table->tables[i].nPairs = CFontFile::readUSHORT(ffile.fp);

      temp16 = CFontFile::readUSHORT(ffile.fp);     /* searchRange */
      temp16 = CFontFile::readUSHORT(ffile.fp);     /* entrySelector */
      temp16 = CFontFile::readUSHORT(ffile.fp);     /* rangeShift */
      
      kern_table->tables[i].kern_pairs =
      (CKernData *)malloc(kern_table->tables[i].nPairs * sizeof(CKernData));

      for (j = 0; j < kern_table->tables[i].nPairs; j++)
      {
        /* Read in a kerning pair */
        kern_table->tables[i].kern_pairs[j].left = CFontFile::readUSHORT(ffile.fp);
        kern_table->tables[i].kern_pairs[j].right = CFontFile::readUSHORT(ffile.fp);
        kern_table->tables[i].kern_pairs[j].value = CFontFile::readSHORT(ffile.fp);

      }
    }
    else
    {      /*
       * seekg to the end of this table, excluding the length of the version,
       * length, and coverage USHORTs, which we have already read.
       */
      ffile.fp.Seek((long)(length - 6), CFile::current) ;
      kern_table->tables[i].nPairs = 0;
    }
  }
}
