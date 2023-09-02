#include "stdafx.h"
#include "FontFile.h"

short CFontFile::readSHORT(CFile &infile)
{
  int i0, i1 = 0; /* To quiet warnings */

  infile.Read(&i0,1);
  infile.Read(&i1,1);

  if (i0 & 0x80) /* Subtract 1 after value is negated to avoid overflow [AED] */
    return -(((255 - i0) << 8) | (255 - i1)) - 1;
  else
    return (i0 << 8) | i1;
}

unsigned short CFontFile::readUSHORT(CFile &infile)
{
  int i0, i1 = 0; /* To quiet warnings */

  infile.Read(&i0,1);
  infile.Read(&i1,1);

  return (USHORT)((((USHORT)i0) << 8) | ((USHORT)i1));
}

long CFontFile::readLONG(CFile &infile)
{
  long i0, i1 = 0, i2 = 0, i3 = 0; /* To quiet warnings */

  infile.Read(&i0,1);
  infile.Read(&i1,1);
  infile.Read(&i2,1);
  infile.Read(&i3,1);

  if (i0 & 0x80) /* Subtract 1 after value is negated to avoid overflow [AED] */
    return -(((255 - i0) << 24) | ((255 - i1) << 16) |
             ((255 - i2) << 8)  |  (255 - i3)) - 1;
  else
    return (i0 << 24) | (i1 << 16) | (i2 << 8) | i3;
}

unsigned long CFontFile::readULONG(CFile &infile)
{
  int i0, i1 = 0, i2 = 0, i3 = 0;  /* To quiet warnings */

  infile.Read(&i0,1);
  infile.Read(&i1,1);
  infile.Read(&i2,1);
  infile.Read(&i3,1);

  return (ULONG) ((((ULONG) i0) << 24) | (((ULONG) i1) << 16) |
                  (((ULONG) i2) << 8)  |  ((ULONG) i3));
}

