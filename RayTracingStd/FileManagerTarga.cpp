#include <stdio.h>
#include "BaseFileManager.h"
#include "FileManagerTarga.h"


CFileManagerTarga::CFileManagerTarga()
{
}

CFileManagerTarga::~CFileManagerTarga()
{
}


int CFileManagerTarga::Open()
{
  unsigned char tgaheader[18];

  Targa_Line_Number = 0;
  
  switch (mode)
  {
    case READ_MODE:

      /* We can't resume from stdout. */
      if (opts.Options & TO_STDOUT ||
          (m_phandle = fopen(m_name, READ_BINFILE_STRING)) == NULL)
      {
        Status_Info("\n");
        return(0);
      }

      /* Read targa header information. */

      if (fread(tgaheader, 18, 1, handle->file) != 1)
      {
        return(0);
      }

      /* Decipher the header information */

      switch (tgaheader[2])
      {
        case 2  : opts.OutputFormat = 'T'; break;
        case 10 : opts.OutputFormat = 'C'; break;
        default : return(0);
      }

      switch (tgaheader[16])
      {
        case 24 : break;
        case 32 : opts.Options |= OUTPUT_ALPHA; break;
        default : return(0);
      }

      /* First_Column set to x offset.  Bytes 8, 9 */
      opts.First_Column = tgaheader[8] + (tgaheader[9] << 8);

      /* First line set to y offset.  Bytes 10, 11 */
      opts.First_Line = Targa_Line_Number = tgaheader[10] + (tgaheader[11]<<8);

      handle->width  = *width  = tgaheader[12] + (tgaheader[13] << 8);
      handle->height = *height = tgaheader[14] + (tgaheader[15] << 8);

      handle->buffer_size = buffer_size;
  
      Status_Info("\nResuming interrupted trace from %s",handle->filename);

      break;

    case WRITE_MODE:

      if (opts.Options & TO_STDOUT)
      {
        buffer_size = 0;
        handle->file = stdout;
      }
      else if ((handle->file = fopen (name, WRITE_BINFILE_STRING)) == NULL)
      {
        return(0);
      }

      if (buffer_size != 0)
      {
        handle->buffer = (char *)POV_MALLOC((size_t)buffer_size, "TGA file buffer");
        setvbuf (handle->file, handle->buffer, _IOFBF, buffer_size);
      }

      /* Output TGA file header info */
      putc(0, handle->file);  /* Byte 0 - Length of Image ID field */

      putc(0, handle->file);  /* Byte 1 - Color map type (0 is no color map) */

      switch(opts.OutputFormat)  /* Byte 2 - TGA file type */
      {
        case 't': /* Uncompressed True-Color Image */
        case 'T': 
        case 's': 
        case 'S': putc(2, handle->file); break;

        case 'c': /* Run-length compressed True-Color Image */
        case 'C': putc(10, handle->file); break;
      }

      putc(0, handle->file);  /* Byte 3 - Index of first color map entry LSB */
      putc(0, handle->file);  /* Byte 4 - Index of first color map entry MSB */

      putc(0, handle->file);  /* Byte 5 - Color map length LSB */
      putc(0, handle->file);  /* Byte 6 - Color map legth MSB */

      putc(0, handle->file);  /* Byte 7 - Color map size */

      /* x origin set to "First_Column"  Bytes 8, 9 */

      putc(opts.First_Column % 256, handle->file);
      putc(opts.First_Column / 256, handle->file);

      /* y origin set to "First_Line"    Bytes 10, 11 */

      putc(opts.First_Line % 256, handle->file);
      putc(opts.First_Line / 256, handle->file);

      /* write width and height  Bytes 12 - 15 */

      putc(*width % 256, handle->file);
      putc(*width / 256, handle->file);
      putc(*height % 256, handle->file);
      putc(*height / 256, handle->file);

      /* We write 24 or 32 bits/pixel (16 million colors and alpha channel)
       * and also store the orientation and Alpha channel depth.  Bytes 16, 17.
       */
      if (opts.Options & OUTPUT_ALPHA)
      {
        putc(32, handle->file);    /* 32 bits/pixel (BGRA) */
        putc(0x28, handle->file);  /* Data starts at top left, 8 bits Alpha */
      }
      else
      {
        putc(24, handle->file);    /* 24 bits/pixel (BGR) */
        putc(0x20, handle->file);  /* Data starts at top left, 0 bits Alpha */
      }

      /* TGA file Image ID field data would go here (up to 255 chars) */

      handle->width = *width;
      handle->height = *height;

      handle->buffer_size = buffer_size;

      break;

    case APPEND_MODE:

      if (opts.Options & TO_STDOUT)
      {
        buffer_size = 0;
        handle->file = stdout;
      }
      else if ((handle->file = fopen (name, APPEND_BINFILE_STRING)) == NULL)
      {
        return(0);
      }
      else if (buffer_size != 0)
      {
        handle->buffer = (char *)POV_MALLOC((size_t)buffer_size, "TGA file buffer");
        setvbuf (handle->file, handle->buffer, _IOFBF, buffer_size);
      }

      break;
  }

  return(1);
}


void CFileManagerTarga::WritePixel(CColor &Color)
{
  unsigned int gray;

  if (opts.Options & HF_GRAY_16)
  {
    /* Ouput heightfield in POV red/green format */
    gray = ((0.30 * r) + (0.59 * g) + (0.11 * b)) * 65535;

    if ((putc(0 , handle->file) == EOF) ||
        (putc(gray & 0xFF, handle->file) == EOF) ||
        (putc((gray >> 8) & 0xFF, handle->file) == EOF))
    {
      Error("Error writing TGA output data to %s.\n",handle->filename);
    }
  }
  else
  {
    /* Normal 24/32 bit pixel coloring */

    if ((putc((int) floor(b * 255.0), handle->file) == EOF) ||
        (putc((int) floor(g * 255.0), handle->file) == EOF) ||
        (putc((int) floor(r * 255.0), handle->file) == EOF))
    {
      Error("Error writing TGA output data to %s.\n",handle->filename);
    }

    if (opts.Options & OUTPUT_ALPHA)
    {
      if (putc((int) floor((1.0 - f) * 255.0), handle->file) == EOF)
      {
        Error("Error writing TGA output data to %s.\n",handle->filename);
      }
    }
  }
}


void CFileManagerTarga::Write(COLOUR *line_data, int line_number)
{
  register int x;
  int ptype, cnt, llen, startx;
  boolean writenow;
  pix curpix, nexpix;

  switch (opts.OutputFormat)
  {
    case 't':
    case 'T':
    case 's':
    case 'S':

      for (x = 0; x < handle->width; x++)
      {
        Write_Targa_Pixel (handle, line_data[x][BLUE], line_data[x][GREEN], line_data[x][RED], line_data[x][TRANSM]);
      }

      break;

    case 'c':
    case 'C':

      llen = handle->width;

      startx = 0;

      cnt = 1;

      curpix.blue   = line_data[startx][BLUE];
      curpix.green  = line_data[startx][GREEN];
      curpix.red    = line_data[startx][RED];
      curpix.transm = line_data[startx][TRANSM];

      ptype = 0;

      writenow = FALSE;

      for (;;)
      {
        nexpix.blue   = line_data[startx+cnt][BLUE];
        nexpix.green  = line_data[startx+cnt][GREEN];
        nexpix.red    = line_data[startx+cnt][RED];
        nexpix.transm = line_data[startx+cnt][TRANSM];

        if ((nexpix.red == curpix.red) && (nexpix.blue == curpix.blue) &&
            (nexpix.green == curpix.green) && (nexpix.transm == curpix.transm))
        {
          if (ptype == 0)
          {
            cnt++;

            if ((cnt >= 128) || ((startx + cnt) >= llen))
            {
              writenow = TRUE;
            }
          }
          else
          {
            cnt--;

            writenow = TRUE;
          }
        }
        else
        {
          if ((ptype == 1) || (cnt <= 1))
          {
            ptype = 1;

            curpix = nexpix;

            cnt++;

            if ((cnt >= 128) || ((startx + cnt) >= llen))
            {
              writenow = TRUE;
            }
          }
          else
          {
            writenow = TRUE;
          }
        }

        if (writenow)
        {
          /* This test SHOULD be unnecessary!  However, it isn't!  [CWM] */

          if (startx + cnt > llen)
          {
            cnt = llen - startx;
          }

          if (ptype == 0)
          {
            putc((int) ((cnt - 1) | 0x80), handle->file);

            Write_Targa_Pixel (handle, curpix.blue, curpix.green, curpix.red, curpix.transm);

            curpix = nexpix;
          }
          else
          {
            putc((int) cnt - 1, handle->file);

            for (x = 0; x < cnt; x++)
            {
               Write_Targa_Pixel (handle,
                 line_data[startx+x][BLUE], line_data[startx+x][GREEN],
                 line_data[startx+x][RED], line_data[startx+x][TRANSM]);
            }
          }
          startx = startx + cnt;

          writenow = FALSE;

          ptype = 0;

          cnt = 1;

          if (startx >= llen)
          {
             break; /* Exit while */
          }
        }
      }

      break; /* End of case */
  }

  if (handle->buffer_size == 0)
  {
    /* Close and reopen file (if not stdout) for integrity in case we crash */

    fflush(handle->file);

    if (!(opts.Options & TO_STDOUT))
    {
      handle->file = freopen(handle->filename, APPEND_BINFILE_STRING, handle->file);
    }
  }
}