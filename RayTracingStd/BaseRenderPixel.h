/////Etat classe : VALIDE



class CBaseRenderPixel
{
// Construction
public:
	CBaseRenderPixel();
	CBaseRenderPixel(long x,long y);

// Attributes
protected:
	long	m_lCoordX;
	long	m_lCoordY;
	CColor	m_Color;

// Operations
protected:
	void	Compute(CRay&);

public:

// Implementation
public:
	virtual ~CBaseRenderPixel();

	// Generated message map functions
protected:
};

