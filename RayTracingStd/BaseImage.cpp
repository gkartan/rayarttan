#include "stdio.h"
#include "Color.h"
#include "BaseImage.h"
#include "wx/bitmap.h"
#include "wx/string.h"

CBaseImage::CBaseImage()
{
	wxInitAllImageHandlers();
	m_Type=IMAGE_TYPE_TIFF;
	m_NbLineRendered=0;
	m_Width=800; 
	m_Height=600; 
	m_Map.Create(m_Width,m_Height);

}

CBaseImage::~CBaseImage()
{
	m_Map.Destroy();
}


void CBaseImage::SetSize(long W,long H)
{
	m_Width=W; 
	m_Height=H; 

	m_Map.Create(W,H);
}

void  CBaseImage::Clear()
{
	m_Map.Destroy();
}


void	CBaseImage::SetAdaptativeSampling()
{
	SetSize(m_Width+1,m_Height+1);
}

void	CBaseImage::SetLine(long Y,std::list<BaseColorChar> &Line)
{
	m_NbLineRendered++;//une ligne de rendu supplémentaire

	long CurX=0;

	for(std::list<BaseColorChar>::iterator i=Line.begin();
		i!=Line.end();i++)
	{
		SetColor(CurX,Y,*i);

		CurX++;
	}

}

bool CBaseImage::SaveFile(std::string &str,std::string &output)
{
	wxBitmap	bmp;
	bmp.InitStandardHandlers();
	bmp=m_Map.ConvertToBitmap();

	switch(m_Type)
	{
		case IMAGE_TYPE_TIFF:
			{
				wxString strFormat;
				strFormat=strFormat.Format("%s.tif",str.c_str());
				output=strFormat.c_str();
				return bmp.SaveFile(strFormat,wxBITMAP_TYPE_TIF);
			}
			break;
		default:
			{
				wxString strFormat;
				strFormat=strFormat.Format("%s.tif",str.c_str());
				output=strFormat.c_str();
				return bmp.SaveFile(strFormat,wxBITMAP_TYPE_TIF);
			}
			break;
	}
}

bool CBaseImage::SaveFile(std::string &str)
{
	std::string pipo;
	return(SaveFile(str,pipo));
}

bool CBaseImage::LoadFile(std::string &str)
{
	return(m_Map.LoadFile(wxString(str.c_str())));
}


unsigned char*	CBaseImage::GetArray()
{
	return(m_Map.GetData());
}




ostream&	operator<<(ostream& o,const CBaseImage& c)
{
	o	<<	"image {\n";
	o	<<	"\twidth " << c.GetWidth()	<<	"\n";
	o	<<	"\theight " << c.GetHeight()	<<	"\n";
	o	<<	"}\n";

	return o;
}
 