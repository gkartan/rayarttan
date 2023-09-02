#include "TextFontStruct.h"

class CFormatGlyph
{
public:
	static unsigned short ProcessFormat0Glyph(CFontFileInfo &ffile, unsigned int search_char);
	static unsigned short ProcessFormat4Glyph(CFontFileInfo &ffile, unsigned int search_char);
	static unsigned short ProcessFormat6Glyph(CFontFileInfo &ffile, unsigned int search_char);
	static void  ExtractGlyphOutline(CFontFileInfo &ffile,
												unsigned int glyph_index, 
												unsigned int c,
												CGlyphOutline &ttglyph);
	static void	 ConvertOutlineToGlyph(CFontFileInfo &ffile, CGlyphOutline &ttglyph,CGlyph &glyph);
};