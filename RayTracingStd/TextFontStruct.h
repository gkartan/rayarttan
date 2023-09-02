#ifndef _TEXTFONTSTRUCT
#define _TEXTFONTSTRUCT

#include "stdafx.h"		///utilisé pour CFile entre autres


#define FILE_NAME_LENGTH	255


/* For decoding kern coverage bit flags */
#define KERN_HORIZONTAL     0x01
#define KERN_MINIMUM        0x02
#define KERN_CROSS_STREAM   0x04
#define KERN_OVERRIDE       0x08

/* For decoding glyph coordinate bit flags */
#define ONCURVE             0x01
#define XSHORT              0x02
#define YSHORT              0x04
#define REPEAT_FLAGS        0x08  /* repeat flag n times */
#define SHORT_X_IS_POS      0x10  /* the short vector is positive */
#define NEXT_X_IS_ZERO      0x10  /* the relative x coordinate is zero */
#define SHORT_Y_IS_POS      0x20  /* the short vector is positive */
#define NEXT_Y_IS_ZERO      0x20  /* the relative y coordinate is zero */

/* For decoding multi-component glyph bit flags */
#define ARG_1_AND_2_ARE_WORDS     0x0001
#define ARGS_ARE_XY_VALUES        0x0002
#define ROUND_XY_TO_GRID          0x0004
#define WE_HAVE_A_SCALE           0x0008
/*      RESERVED                  0x0010 */
#define MORE_COMPONENTS           0x0020
#define WE_HAVE_AN_X_AND_Y_SCALE  0x0040
#define WE_HAVE_A_TWO_BY_TWO      0x0080
#define WE_HAVE_INSTRUCTIONS      0x0100
#define USE_MY_METRICS            0x0200

class CGlyphHeader
{
public:
  short numContours;
  short xMin;
  short yMin;
  short xMax;
  short yMax;
};

class CGlyphOutline
{
public:
  CGlyphOutline()
  {
	  flags=NULL;
	  x=y=NULL;
  }

  virtual ~CGlyphOutline()
  {
	  if(x) delete[](x);
	  if(y) delete[](y);
	  if(flags) delete[](flags);
  }
  CGlyphHeader header;
  unsigned short numPoints;
  unsigned short *endPoints;
  char *flags;
  double *x, *y;
  unsigned short myMetrics;
};

class CContour
{
public:
  CContour()
  {
	  flags=NULL;
	  x=y=NULL;
  }
  virtual ~CContour()
  {
	  if(x) delete[](x);
	  if(y) delete[](y);
	  if(flags) delete[](flags);
  }

  char inside_flag;             /* 1 if this an inside contour, 0 if outside */
  unsigned short count;                 /* Number of points in the contour */
  char *flags;                  /* On/off curve flags */
  double *x, *y;                   /* Coordinates of control vertices */
};

class CGlyph;
class CGlyph
{
public:
  CGlyph()
  {
	  contours=NULL;
	  next=NULL;
  }
  virtual ~CGlyph()
  {
	  if(contours) delete[](contours);
	  if(next) delete[](next);
  }

  CGlyphHeader header;           /* Count and sizing information about this
                                 * glyph */
  unsigned short glyph_index;           /* Internal glyph index for this character */
  CContour *contours;					/* Array of outline contours */
  unsigned short unitsPerEm;            /* Max units character */
  CGlyph   *next;						/* Next cached glyph */
  unsigned short c;                     /* Character code */
  unsigned short myMetrics;             /* Which glyph index this is for metrics */
};

class CKernData
{
public:
  unsigned short left, right;           /* Glyph index of left/right to kern */
  short			value;                  /* Delta in FUnits to apply in between */
};

class CKernStruct
{
public:
  CKernStruct()
  {
	kern_pairs=NULL;
  }
  virtual ~CKernStruct()
  {
	  if(kern_pairs) delete[] kern_pairs;
  }
  unsigned short coverage;              /* Coverage bit field of this subtable */
  unsigned short nPairs;                /* # of kerning pairs in this table */
  CKernData *kern_pairs;				 /* Array of kerning values */
};


class CKernTables
{
public:
  CKernTables()
  {
	nTables=0;
	tables=NULL;
  }
  virtual ~CKernTables()
  {
	  if(tables) delete[] tables;
  }
  unsigned short nTables;               /* # of subtables in the kerning table */
  CKernStruct *tables;
};

class CLongHorMetric
{
public:
  unsigned short advanceWidth;          /* Total width of a glyph in FUnits */
  short			 lsb;                    /* FUnits to the left of the glyph */
};


class	CFontFileInfo
{
public:
	CFontFileInfo() 
	{
		loca_table=NULL;
		glyphs=NULL;
		hmtx_table=NULL;
		startCount=NULL;
		endCount=NULL;
		idDelta=NULL;
		idRangeOffset=NULL;
	};
	virtual ~CFontFileInfo()
	{
		if(loca_table) delete[] loca_table;
		if(glyphs) delete[] glyphs;
		if(hmtx_table) delete[] hmtx_table;
		if(startCount) delete[] startCount;
		if(endCount) delete[] endCount;
		if(idDelta) delete[] idDelta;
		if(idRangeOffset) delete[] idRangeOffset;
	}

	CFontFileInfo(const CFontFileInfo &Param) {*this=Param;}

	std::string		filename;
	CFile			fp;
	unsigned short	platformID[4];             /* Character encoding search order */
	unsigned short	specificID[4];
	unsigned long	cmap_table_offset;          /* File locations for these tables */
	unsigned long	glyf_table_offset;
	unsigned short	numGlyphs;                 /* How many symbols in this file */
	unsigned short	unitsPerEm;                /* The "resoultion" of this font */
	short			indexToLocFormat;           /* 0 - short format, 1 - long format */
	unsigned long	*loca_table;                /* Mapping from characters to glyphs */
	CGlyph			*glyphs;                  /* Cached info for this font */
	CKernTables		kerning_tables;        /* Kerning info for this font */
	unsigned short	numberOfHMetrics;          /* The number of explicit spacings */
	CLongHorMetric	*hmtx_table;        /* Horizontal spacing info */
	unsigned long	glyphIDoffset;              /* Offset for Type 4 encoding tables */
	unsigned short  segCount;
	unsigned short  searchRange;	/* Counts for Type 4 encoding tables */
	unsigned short  entrySelector;
	unsigned short  rangeShift;
	unsigned short  *startCount;
	unsigned short  *endCount;		/* Type 4 (MS) encoding tables */
	unsigned short  *idDelta;
	unsigned short  *idRangeOffset;

	CFontFileInfo&	operator=(const CFontFileInfo &Param)
	{
		filename=Param.filename;
		//fp=Param.fp;
		memcpy(platformID,Param.platformID,4*sizeof(short)); 
		memcpy(specificID,Param.specificID,4*sizeof(short));            
		cmap_table_offset=Param.cmap_table_offset;          
		glyf_table_offset=Param.glyf_table_offset;
		numGlyphs=Param.numGlyphs;                
		unitsPerEm=Param.unitsPerEm;              
		indexToLocFormat=Param.indexToLocFormat;         
		loca_table=Param.loca_table;            
		glyphs=Param.glyphs;                
		kerning_tables=Param.kerning_tables;     
		numberOfHMetrics=Param.numberOfHMetrics;         
		hmtx_table=Param.hmtx_table;        
		glyphIDoffset=Param.glyphIDoffset;            
		segCount=Param.segCount;
		searchRange=Param.searchRange;
		entrySelector=Param.entrySelector;
		rangeShift=Param.rangeShift;
		startCount=Param.startCount;
		endCount=Param.endCount;		
		idDelta=Param.idDelta;
		idRangeOffset=Param.idRangeOffset;

		return(*this);
	}
};


class C_sfnt_OffsetTable
{
public:
  unsigned short version;                /* 0x10000 (1.0) */
  unsigned short numTables;             /* number of tables */
  unsigned short searchRange;           /* (max2 <= numTables)*16 */
  unsigned short entrySelector;         /* log2 (max2 <= numTables) */
  unsigned short rangeShift;            /* numTables*16-searchRange */
};

class C_sfnt_TableDirectory
{
public:
  char			tag[4];
  unsigned long checkSum;
  unsigned long offset;
  unsigned long length;
};

class CLongDateTime
{
public:
  unsigned long bc;
  unsigned long ad;
};

class C_sfnt_FontHeader
{
public:
  long version;                /* for this table, set to 1.0 */
  long fontRevision;           /* For Font Manufacturer */
  unsigned long checkSumAdjustment;
  unsigned long magicNumber;            /* signature, must be 0x5F0F3CF5 == MAGIC */
  unsigned short flags;
  unsigned short unitsPerEm;            /* How many in Font Units per EM */

  CLongDateTime created;
  CLongDateTime modified;

  short xMin;                   /* Font wide bounding box in ideal space */
  short yMin;                   /* Baselines and metrics are NOT worked */
  short xMax;                   /* into these numbers) */
  short yMax;

  unsigned short macStyle;              /* macintosh style word */
  unsigned short lowestRecPPEM;         /* lowest recommended pixels per Em */

  short fontDirectionHint;
  short indexToLocFormat;       /* 0 - short offsets, 1 - long offsets */
  short glyphDataFormat;
};

class C_sfnt_platformEntry
{
public:
  unsigned short platformID;
  unsigned short specificID;
  unsigned long offset;
};

class C_sfnt_mappingTable
{
public:
  unsigned short  format;
  unsigned short  length;
  unsigned short  version;
};

#endif
