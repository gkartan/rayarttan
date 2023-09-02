-------------------------------------------------------------
James Grenning      High Point Software Technology Company
Design Consulting   10 High Point Drive  (847) 438-9942
Project Management  Hawthorn Woods, IL
OO Training         60047
jgrenning@HighPointSoftware.com     www.HighPointSoftware.com
--------------------------------------------------------------

#include "mtl/matrix.h"
#include "mtl/mtl.h"
#include "mtl/utils.h"
#include <iostream>




//---------------------------------- Test Case ------------------------------------
void MatrixOutputTest()
{
    char* outputFile = "MatrixOutputTest.txt";

    TestOutput = new std::fstream(outputFile, std::ios::out | std::ios::trunc);

    Matrix m3(3,3);
    Matrix m10(10,10);

	Fixed cell = 0;
	Fixed incr(.25);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			m10(i,j) = (cell += incr);

	(*TestOutput) << m3 << std::endl << std::endl << m10;

    delete TestOutput;

}



