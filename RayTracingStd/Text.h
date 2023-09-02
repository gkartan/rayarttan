/////Etat classe : EN COURS
#ifndef _TEXTDEFINE
#define _TEXTDEFINE

#include "Vector.h"
#include "BaseGeometry.h"
#include <string>
#include "TextFont.h"
#include "TextChar.h"
#include "Box.h"

class CText : public CBaseGeometry
{
// Construction
public:
	CText();
	CText(const std::string& font,const std::string &text);

//Attributes
private:
	std::string		m_FontName;
	std::string		m_Text;
	CVector			m_Offset;
	CVector			m_FinalOffset;
	CBox			m_BoundingBox;

	std::vector<CTextChar*>	m_ListText;

private:
	void	CreateObjectText(const std::string& font,const std::string &text);

	/////////Initialize
public:
	void	SetFont(const std::string &str) {m_FontName=str;}
	void	SetStr(const std::string &str) {m_Text=str;}
	void	Init();
	void	Center();	//centre la texte sur (0,0,0)
	void	ComputeBoundingBox();

protected:
	virtual void	ForceEqual(CBaseGeometry&);

public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type
	virtual CBaseGeometry* GetBoundSphere()	{return m_BoundingBox.GetBoundSphere();};

	virtual	void	Scale(const CVector&);
	virtual	void	Rotate(const CVector&);
	virtual	void	Translate(const CVector&);
public:
	CText&	operator=(CText&);

//operations
public:
	virtual	bool	Intersection(CRay&);
	virtual bool	AddIntersect(CRay&,double Distance);

protected:
	virtual CVector	Normal(const CCoord &coord);

// Implementation
public:
	virtual ~CText();

//Gestion stream
public:
	virtual	void	GetOutputStream(ostream&);
};


#endif