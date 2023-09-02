#include <string>
#include "rand.h"


#define NBOPERATIONSMAX	20
#define EXPONENTMAX		20

class CRandomFractal
{
public:
	inline static  std::string Generate();
	inline static  std::string GenerateType();

private:
	inline	static std::string GenerateOperations();
	inline	static std::string GenerateArguments();
};


std::string CRandomFractal::Generate()
{
	std::string str;
	long	NbOperations=0;

	initrand();

	NbOperations=drand48()*NBOPERATIONSMAX;
	for(long i=0;i<NbOperations;i++)
	{
		if(i!=0)
			str+=GenerateOperations();
		str+=std::string("(");
		str+=GenerateArguments();
		str+=GenerateOperations();
		str+=GenerateArguments();
		str+=std::string(")");
	}

	return str;
}


std::string CRandomFractal::GenerateOperations()
{
	long theOperation=drand48()*4;

	switch(theOperation)
	{
		case 0:
			return std::string("+");
		case 1:
			return std::string("-");
		case 2:
			return std::string("*");
		case 3:
			return std::string("/");
	}
}


std::string CRandomFractal::GenerateArguments()
{
	long theArgument=drand48()*21;

	switch(theArgument)
	{
		case 0:
		case 13:
		case 14:
		case 15:	//on augmente la proba de ces 2 arguments
			return std::string("Z");
		case 1:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
			{
				long Power=drand48()*EXPONENTMAX;
				std::string str("Z^");
				char buffer[255];
				sprintf(buffer,"%d",Power);
				str+=std::string(buffer);
				return str;
			}
		case 2:
			return std::string("sin(z)");
		case 3:
			return std::string("cos(z)");
		case 4:
			return std::string("exp(z)");
		case 5:
			return std::string("tan(z)");
		case 6:
			return std::string("cotan(z)");
		case 7:
			return std::string("log(z)");
		case 8:
			return std::string("asin(z)");
		case 9:
			return std::string("acos(z)");
		case 10:
			return std::string("atan(z)");
		case 11:
			return std::string("acotan(z)");
		case 12:
			return std::string("sqrt(z)");

	}
}

std::string CRandomFractal::GenerateType()
{
	long	theType=0;

	theType=drand48()*18;

	switch(theType)
	{
		case 0:
			return std::string("quaternion");
		case 1:
			return std::string("hypercomplex");
		case 2:
			return std::string("algebra01");
		case 3:
			return std::string("algebra02");
		case 4:
			return std::string("algebra03");
		case 5:
			return std::string("algebra04");
		case 6:
			return std::string("algebra05");
		case 7:
			return std::string("algebra06");
		case 8:
			return std::string("algebra07");
		case 9:
			return std::string("algebra08");
		case 10:
			return std::string("algebra09");
		case 11:
			return std::string("algebra10");
		case 12:
			return std::string("algebra11");
		case 13:
			return std::string("algebra12");
		case 14:
			return std::string("algebra13");
		case 15:
			return std::string("algebra14");
		case 16:
			return std::string("algebra15");
		case 17:
			return std::string("algebra16");

	}

}