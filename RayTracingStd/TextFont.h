#ifndef _TEXTFONT
#define _TEXTFONT

#pragma warning(disable:4530)

#include <string>
#include <vector>
#include "TextFontStruct.h"


class	CTextFont
{
public:
	CTextFont();
	CTextFont(const std::string &filename);
	virtual ~CTextFont();

private:
	std::vector<CFontFileInfo>	m_ListFontFileInfo;	//première fonte
	CFontFileInfo				m_FontFileInfo;		//fonte courante
	bool						m_bExistFont;

private:
	int		compare_tag4(char *ttf_tag, char *known_tag);

	bool	ProcessFontFile(const std::string &fontfilename);
	bool	OpenFontFile(const std::string &filename,CFontFileInfo &FileInfo);

	void	ProcessHeadTable(CFontFileInfo &ffile, long head_table_offset);
	void	ProcessMaxpTable(CFontFileInfo &ffile, long maxp_table_offset);
	void	ProcessLocaTable(CFontFileInfo &ffile, long loca_table_offset);
	void	ProcessHheaTable(CFontFileInfo &ffile, long hhea_table_offset);
	void	ProcessHmtxTable(CFontFileInfo &ffile, long hmtx_table_offset);
	void	ProcessKernTable(CFontFileInfo &ffile, long kern_table_offset);


public:
	inline	bool		   GetExistFont()	{return m_bExistFont;}
	inline	unsigned short GetUnitsPerEm()	{return m_FontFileInfo.unitsPerEm;}
	inline	CFontFileInfo&	GetCurrentFont() {return m_FontFileInfo;}
};

#endif