//////////////////////////////////////////////////////////////////////
// winostream.cpp:	implementation of class winostream
// author:			g. makulik
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winostream.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

winostream::winostream	( CWnd *	pWnd_
						, int		nBufSize_
						)
	: ostream(new winstrbuf(pWnd_, nBufSize_))
{
	// I am pretty sure that it's OK to use a reinterpret_cast
	// here, since we've created this object just two lines before.
	// Though someone might have the idea to reimplement ostream::rdbuf()
	// in a completely unexpected manner.
	m_pWinstrbuf = reinterpret_cast<winstrbuf*>(rdbuf());
}

winostream::~winostream	()
{
	// Tidy up memory
	delete m_pWinstrbuf;
}

// operator<< for manipulator functions ('endl' style)
//////////////////////////////////////////////////////////////////////
winostream &	winostream::operator<<	( winostream &(*fmanip)(winostream &)
										)
{
	// simply call the manipulator function (should return *this as well)
	return fmanip(*this);
}


//taken from your print_all_matrix()
std::ostream& operator<<(std::ostream& os, Matrix& A)
{
  int i,j;
  os << A.nrows() << "x" << A.ncols() << std::endl;
  os << "[" << std::endl;
  for (i=0; i < A.nrows(); ++i) {
    os << "  [";
    for (j=0; j < A.ncols(); ++j) {
      os << A(i,j);
      if (j < A.ncols() - 1)
	os << ",";
    }
    os << "]";
    if (i < A.nrows() - 1)
      os << "," << std::endl;
    else
      os << std::endl;
  }
  os << "]" << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, CColor& color)
{
	os << "Red : " << color.GetRed() << 
	" - Green : " << color.GetGreen() <<
	" - Blue : " << color.GetBlue();

	return os;
}

//taken from your print_all_matrix()
std::ostream& operator<<(std::ostream& os, Vector& A)
{
	os << "X : " << A[0] << 
	" - Y : " << A[1] <<
	" - Z : " << A[2];

	return os;

}