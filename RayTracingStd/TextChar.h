#include "Vector.h"
#include "BaseGeometry.h"
#include "TextFontStruct.h"
#include "TextFont.h"
#include "Box.h"

typedef enum GLYPH_SIDE_ENUM
{
	GLYPH_SIDE_0=0,
	GLYPH_SIDE_1=1
};

class	CTextChar  : public CBaseGeometry
{
public:
	CTextChar();
	virtual ~CTextChar();

	void	AddRef();
	void	Release();

	void	ProcessCharacter(unsigned char caract,CTextFont &font,unsigned int &glyph_index);
	inline  CGlyph&		GetGlyph()	{return m_Glyph;}

	void	ComputeBoundingBox(CCoord&,CCoord&);

private:
	unsigned short ProcessCharMap(CFontFileInfo &ffile, unsigned int search_char);
	void		   ExtractGlyphInfo(CFontFileInfo &ffile, 
									unsigned int glyph_index, 
									unsigned int c,
									CGlyph& glyph);
	int				solve_quad(double *x, double *y, double mindist, double maxdist);
	void			GetZeroOneHits(CGlyph &glyph, CRay& Ray, double glyph_depth, double &t0, double &t1);
	int				Inside_Glyph(double x, double y, CGlyph &glyph);

	CGlyph	m_Glyph;
	double  m_Depth;
	long	m_NbRef;
///virtual members
protected:
	virtual void	ForceEqual(CBaseGeometry&);

public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type
	virtual CBaseGeometry* GetBoundSphere()	{return NULL;};

public:
	CTextChar&	operator=(const CTextChar&);

//operations
public:
	virtual	bool	Intersection(CRay&);
	virtual bool	AddIntersect(CRay&,double Distance);
			bool	AddIntersect(CRay &Ray,double Distance,GLYPH_SIDE_ENUM Side);
			bool	AddIntersect(CRay &Ray,double Distance,CVector&);

protected:
	virtual CVector	Normal(const CCoord &coord);
	CVector	Normal(GLYPH_SIDE_ENUM);

//Gestion stream
public:
	virtual	void	GetOutputStream(ostream&);
};