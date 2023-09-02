//////////////////////////////////////////////////////////////////////
// winostream.h:	interface of class winostream
// author:			g. makulik
// purpose:			implementing std::ostream for text output on
//					a MFC-CWnd. This is primarily intended to use
//					with CStatic/CEdit controls.
//
//////////////////////////////////////////////////////////////////////

#if !defined(WINOSTREAM_H)
#define WINOSTREAM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>

#include <mtl\matrix.h>
#include "Color.h"

typedef  CColor Type;
typedef mtl::matrix<Type>::type Matrix;

typedef mtl::dense1D<double> Vector;	///Utilisation du vecteur de la mtl
								///au lieu de celui de la stl

std::ostream& operator<<(std::ostream&, Matrix&);
std::ostream& operator<<(std::ostream& os, CColor& color);
std::ostream& operator<<(std::ostream& os, Vector& A);


#include "winstrbuf.h"

class winostream : public ostream
{
public:
						winostream	( CWnd *	pWnd_
									, int		nBufSize_ = 0
									);
	virtual				~winostream	();

	// It's not essential to reimplement all the operator<< overloads
	// of ostream. But this will be useful if you like to implement
	// special manipulator methods and their global pendants in the
	// same style as 'endl' or 'flush'.
	winostream &		operator<<	( winostream &(*fmanip)(winostream &)
									);
	winostream &		operator<<	( ostream &(*fmanip)(ostream &)
									)
							{ fmanip(*this); return *this; };
	winostream &		operator<<	( ios &(*fmanip)(ios &)
									)
							{ fmanip(static_cast<ios>(*this)); return *this; };
	winostream &		operator<<	( ios_base &(*fmanip)(ios_base &)
									)
							{ fmanip(static_cast<ios_base>(*this)); return *this; };
	winostream &		operator<<	( bool		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( short		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( unsigned short	x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( int		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( unsigned int		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( long		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( unsigned long		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( float		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( double	x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( long double		x
									)
							{ ostream::operator <<(x); return *this; };
	winostream &		operator<<	( streambuf *		x
									)
							{ ostream::operator <<(x); return *this; };
	// declare special winostream manipulators here
	//===========================================================================
	winostream &		operator=	( ostream&		x
									)
							{ ostream::operator =(x); return *this;};

protected:
	virtual CWnd *		getwnd		()
							{ return m_pWinstrbuf->getwnd(); };
private:
	winstrbuf *			m_pWinstrbuf;
};

// this is global to work with any global conversion of char *
// like std::operator<<(std::ostream&,const std::string &).
inline
winostream &		operator<<		( winostream &		wos_
									, char *			x
									)
						{ 
							static_cast<ostream>(wos_) << x; return wos_; 
						};

// declare global special winostream manipulators ('endl' style)
//===========================================================================

#endif // !defined(WINOSTREAM_H)
