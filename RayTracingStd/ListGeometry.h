/////Etat classe : VALIDE
#pragma warning(disable : 4530)

#include <iostream>
#include <vector>
#include "BaseGeometry.h"


class CListGeometry
{
// Construction
public:
	CListGeometry();

// Attributes
protected:

// Operations
protected:
	std::vector<CBaseGeometry>	m_ListObjects;


// Implementation
public:
	virtual ~CListGeometry();

	// Generated message map functions
protected:
};

