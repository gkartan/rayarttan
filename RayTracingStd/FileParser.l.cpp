#include <clex.h>

#line 1 "FileParser.l"

/*	Parser servant à compiler les fichiers d'entrée pour les traduire en
 *  structure de données
 */
#include "TraceService.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include "Color.h"
#include "ParserUnDef.h"
#include "CommonMatiere.h"

class CBaseGeometry;
class CFileLexer;
class CBaseCamera;
class CRenderStructure;
class CBaseLight;
class CBaseMatiere;
class CTextureElement;
#include "FileParser.h"

#line 27 "FileParser.l.cpp"
// repeated because of possible precompiled header
#include <clex.h>

#include "FileParser.l.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYLEXNAME::YYLEXNAME()
{
	yytables();
}

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif

// backwards compatability with lex
#ifdef input
int YYLEXNAME::yyinput()
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
void YYLEXNAME::yyoutput(int ch)
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
void YYLEXNAME::yyunput(int ch)
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		// <warning: unreachable code> off
#endif
#endif

int YYLEXNAME::yyaction(int action)
{
	yyreturnflg = 1;
	switch (action) {
	case 1:
		{
#line 52 "FileParser.l"
return DASH_TOKEN;
#line 90 "FileParser.l.cpp"
		}
		break;
	case 2:
		{
#line 53 "FileParser.l"
return PLUS_TOKEN;
#line 97 "FileParser.l.cpp"
		}
		break;
	case 3:
		{
#line 55 "FileParser.l"
return FLOAT_TOKEN;
#line 104 "FileParser.l.cpp"
		}
		break;
	case 4:
		{
#line 56 "FileParser.l"
return FLOAT_TOKEN;
#line 111 "FileParser.l.cpp"
		}
		break;
	case 5:
		{
#line 58 "FileParser.l"
return LEFT_CURLY_TOKEN;
#line 118 "FileParser.l.cpp"
		}
		break;
	case 6:
		{
#line 59 "FileParser.l"
return RIGHT_CURLY_TOKEN;
#line 125 "FileParser.l.cpp"
		}
		break;
	case 7:
		{
#line 61 "FileParser.l"
return LEFT_PAREN_TOKEN;
#line 132 "FileParser.l.cpp"
		}
		break;
	case 8:
		{
#line 62 "FileParser.l"
return RIGHT_PAREN_TOKEN;
#line 139 "FileParser.l.cpp"
		}
		break;
	case 9:
		{
#line 64 "FileParser.l"
return LEFT_SQUARE_TOKEN;
#line 146 "FileParser.l.cpp"
		}
		break;
	case 10:
		{
#line 65 "FileParser.l"
return RIGHT_SQUARE_TOKEN;
#line 153 "FileParser.l.cpp"
		}
		break;
	case 11:
		{
#line 67 "FileParser.l"
return LEFT_ANGLE_TOKEN;
#line 160 "FileParser.l.cpp"
		}
		break;
	case 12:
		{
#line 68 "FileParser.l"
return RIGHT_ANGLE_TOKEN;
#line 167 "FileParser.l.cpp"
		}
		break;
	case 13:
		{
#line 70 "FileParser.l"
return BAR_TOKEN;
#line 174 "FileParser.l.cpp"
		}
		break;
	case 14:
		{
#line 71 "FileParser.l"
return TILDE_TOKEN;
#line 181 "FileParser.l.cpp"
		}
		break;
	case 15:
		{
#line 72 "FileParser.l"
return EXCLAMATION_TOKEN;
#line 188 "FileParser.l.cpp"
		}
		break;
	case 16:
		{
#line 73 "FileParser.l"
return AT_TOKEN;
#line 195 "FileParser.l.cpp"
		}
		break;
	case 17:
		{
#line 74 "FileParser.l"
return DOLLAR_TOKEN;
#line 202 "FileParser.l.cpp"
		}
		break;
	case 18:
		{
#line 75 "FileParser.l"
return PERCENT_TOKEN;
#line 209 "FileParser.l.cpp"
		}
		break;
	case 19:
		{
#line 76 "FileParser.l"
return HAT_TOKEN;
#line 216 "FileParser.l.cpp"
		}
		break;
	case 20:
		{
#line 77 "FileParser.l"
return AMPERSAND_TOKEN;
#line 223 "FileParser.l.cpp"
		}
		break;
	case 21:
		{
#line 78 "FileParser.l"
return STAR_TOKEN;
#line 230 "FileParser.l.cpp"
		}
		break;
	case 22:
		{
#line 79 "FileParser.l"
return COMMA_TOKEN;
#line 237 "FileParser.l.cpp"
		}
		break;
	case 23:
		{
#line 80 "FileParser.l"
return SEMI_COLON_TOKEN;
#line 244 "FileParser.l.cpp"
		}
		break;
	case 24:
		{
#line 81 "FileParser.l"
return COLON_TOKEN;
#line 251 "FileParser.l.cpp"
		}
		break;
	case 25:
		{
#line 82 "FileParser.l"
return BACK_QUOTE_TOKEN;
#line 258 "FileParser.l.cpp"
		}
		break;
	case 26:
		{
#line 83 "FileParser.l"
return EQUALS_TOKEN;
#line 265 "FileParser.l.cpp"
		}
		break;
	case 27:
		{
#line 84 "FileParser.l"
return QUESTION_TOKEN;
#line 272 "FileParser.l.cpp"
		}
		break;
	case 28:
		{
#line 85 "FileParser.l"
return SLASH_TOKEN;
#line 279 "FileParser.l.cpp"
		}
		break;
	case 29:
		{
#line 86 "FileParser.l"
return BACK_SLASH_TOKEN;
#line 286 "FileParser.l.cpp"
		}
		break;
	case 30:
		{
#line 88 "FileParser.l"
return REL_NE_TOKEN;
#line 293 "FileParser.l.cpp"
		}
		break;
	case 31:
		{
#line 89 "FileParser.l"
return REL_LE_TOKEN;
#line 300 "FileParser.l.cpp"
		}
		break;
	case 32:
		{
#line 90 "FileParser.l"
return REL_GE_TOKEN;
#line 307 "FileParser.l.cpp"
		}
		break;
	case 33:
		{
#line 92 "FileParser.l"

#line 314 "FileParser.l.cpp"
		}
		break;
	case 34:
		{
#line 93 "FileParser.l"

			   int c;
			   for (;;)
			   {
				while ((c=input())!='*' && c!=EOF) ;
				if (c=='*')
				{
					while ((c=input())=='*') ;
					if (c=='/') break;
				}
				if (c==EOF)
				{
					//Error("EOF in comment");
					break;
				}
			   }
			
#line 337 "FileParser.l.cpp"
		}
		break;
#line 110 "FileParser.l"
            
#line 342 "FileParser.l.cpp"
	case 35:
		{
#line 112 "FileParser.l"
return STRING_LITERAL_TOKEN;
#line 347 "FileParser.l.cpp"
		}
		break;
	case 36:
		{
#line 114 "FileParser.l"
 return CAMERA_TOKEN;		
#line 354 "FileParser.l.cpp"
		}
		break;
	case 37:
		{
#line 115 "FileParser.l"
 return FRACTAL_TOKEN;		
#line 361 "FileParser.l.cpp"
		}
		break;
	case 38:
		{
#line 116 "FileParser.l"
 return PLANE_TOKEN;		
#line 368 "FileParser.l.cpp"
		}
		break;
	case 39:
		{
#line 117 "FileParser.l"
 return ORTHOGRAPHIC_TOKEN;
#line 375 "FileParser.l.cpp"
		}
		break;
	case 40:
		{
#line 118 "FileParser.l"
 return PERSPECTIVE_TOKEN; 
#line 382 "FileParser.l.cpp"
		}
		break;
	case 41:
		{
#line 119 "FileParser.l"
 return SPHERIC_TOKEN;		
#line 389 "FileParser.l.cpp"
		}
		break;
	case 42:
		{
#line 120 "FileParser.l"
 return SUPERELLIPSOID_TOKEN;
#line 396 "FileParser.l.cpp"
		}
		break;
	case 43:
		{
#line 121 "FileParser.l"
 return LOCATION_TOKEN;	
#line 403 "FileParser.l.cpp"
		}
		break;
	case 44:
		{
#line 122 "FileParser.l"
 return UP_TOKEN;			
#line 410 "FileParser.l.cpp"
		}
		break;
	case 45:
		{
#line 123 "FileParser.l"
 return DIRECTION_TOKEN;	
#line 417 "FileParser.l.cpp"
		}
		break;
	case 46:
		{
#line 124 "FileParser.l"
 return LOOK_AT_TOKEN;		
#line 424 "FileParser.l.cpp"
		}
		break;
	case 47:
		{
#line 125 "FileParser.l"
 return QUATERNION_TOKEN;	
#line 431 "FileParser.l.cpp"
		}
		break;
	case 48:
		{
#line 126 "FileParser.l"
 return HYPERCOMPLEX_TOKEN;	  
#line 438 "FileParser.l.cpp"
		}
		break;
	case 49:
		{
#line 127 "FileParser.l"
 return HYPERCOMPLEXEXOT01_TOKEN;
#line 445 "FileParser.l.cpp"
		}
		break;
	case 50:
		{
#line 128 "FileParser.l"
 return HYPERCOMPLEXEXOT02_TOKEN;
#line 452 "FileParser.l.cpp"
		}
		break;
	case 51:
		{
#line 129 "FileParser.l"
 return HYPERCOMPLEXEXOT03_TOKEN;
#line 459 "FileParser.l.cpp"
		}
		break;
	case 52:
		{
#line 130 "FileParser.l"
 return HYPERCOMPLEXEXOT04_TOKEN;
#line 466 "FileParser.l.cpp"
		}
		break;
	case 53:
		{
#line 131 "FileParser.l"
 return HYPERCOMPLEXEXOT05_TOKEN;
#line 473 "FileParser.l.cpp"
		}
		break;
	case 54:
		{
#line 132 "FileParser.l"
 return HYPERCOMPLEXEXOT06_TOKEN;
#line 480 "FileParser.l.cpp"
		}
		break;
	case 55:
		{
#line 133 "FileParser.l"
 return HYPERCOMPLEXEXOT07_TOKEN;
#line 487 "FileParser.l.cpp"
		}
		break;
	case 56:
		{
#line 134 "FileParser.l"
 return HYPERCOMPLEXEXOT08_TOKEN;
#line 494 "FileParser.l.cpp"
		}
		break;
	case 57:
		{
#line 135 "FileParser.l"
 return HYPERCOMPLEXEXOT09_TOKEN;
#line 501 "FileParser.l.cpp"
		}
		break;
	case 58:
		{
#line 136 "FileParser.l"
 return HYPERCOMPLEXEXOT10_TOKEN;
#line 508 "FileParser.l.cpp"
		}
		break;
	case 59:
		{
#line 137 "FileParser.l"
 return HYPERCOMPLEXEXOT11_TOKEN;
#line 515 "FileParser.l.cpp"
		}
		break;
	case 60:
		{
#line 138 "FileParser.l"
 return HYPERCOMPLEXEXOT12_TOKEN;
#line 522 "FileParser.l.cpp"
		}
		break;
	case 61:
		{
#line 139 "FileParser.l"
 return HYPERCOMPLEXEXOT13_TOKEN;
#line 529 "FileParser.l.cpp"
		}
		break;
	case 62:
		{
#line 140 "FileParser.l"
 return HYPERCOMPLEXEXOT14_TOKEN;
#line 536 "FileParser.l.cpp"
		}
		break;
	case 63:
		{
#line 141 "FileParser.l"
 return HYPERCOMPLEXEXOT15_TOKEN;
#line 543 "FileParser.l.cpp"
		}
		break;
	case 64:
		{
#line 142 "FileParser.l"
 return HYPERCOMPLEXEXOT16_TOKEN;
#line 550 "FileParser.l.cpp"
		}
		break;
	case 65:
		{
#line 143 "FileParser.l"
 return MAX_ITERATION_TOKEN;
#line 557 "FileParser.l.cpp"
		}
		break;
	case 66:
		{
#line 144 "FileParser.l"
 return BAILOUT_TOKEN;		
#line 564 "FileParser.l.cpp"
		}
		break;
	case 67:
		{
#line 145 "FileParser.l"
 return PRECISION_TOKEN;	
#line 571 "FileParser.l.cpp"
		}
		break;
	case 68:
		{
#line 146 "FileParser.l"
 return ANGLE_TOKEN;		
#line 578 "FileParser.l.cpp"
		}
		break;
	case 69:
		{
#line 147 "FileParser.l"
 return AMBIENT_TOKEN;		
#line 585 "FileParser.l.cpp"
		}
		break;
	case 70:
		{
#line 148 "FileParser.l"
 return POINTLIGHT_TOKEN;	
#line 592 "FileParser.l.cpp"
		}
		break;
	case 71:
		{
#line 149 "FileParser.l"
 return LIGHT_SOURCE_TOKEN;
#line 599 "FileParser.l.cpp"
		}
		break;
	case 72:
		{
#line 150 "FileParser.l"
 return DECLARE_TOKEN;		
#line 606 "FileParser.l.cpp"
		}
		break;
	case 73:
		{
#line 151 "FileParser.l"
 return DIFFUSE_TOKEN;		
#line 613 "FileParser.l.cpp"
		}
		break;
	case 74:
		{
#line 152 "FileParser.l"
 return SPECULAR_TOKEN;	
#line 620 "FileParser.l.cpp"
		}
		break;
	case 75:
		{
#line 153 "FileParser.l"
 return TRANSPARENT_TOKEN;	
#line 627 "FileParser.l.cpp"
		}
		break;
	case 76:
		{
#line 154 "FileParser.l"
 return COLOR_MAP_TOKEN;	
#line 634 "FileParser.l.cpp"
		}
		break;
	case 77:
		{
#line 155 "FileParser.l"
 return TEXTURE_TOKEN;		
#line 641 "FileParser.l.cpp"
		}
		break;
	case 78:
		{
#line 156 "FileParser.l"
 return GRANITE_TOKEN;		
#line 648 "FileParser.l.cpp"
		}
		break;
	case 79:
		{
#line 157 "FileParser.l"
 return SPOTTED_TOKEN;		
#line 655 "FileParser.l.cpp"
		}
		break;
	case 80:
		{
#line 158 "FileParser.l"
 return GRADIENT_TOKEN;	
#line 662 "FileParser.l.cpp"
		}
		break;
	case 81:
		{
#line 159 "FileParser.l"
 return FINISH_TOKEN;		
#line 669 "FileParser.l.cpp"
		}
		break;
	case 82:
		{
#line 160 "FileParser.l"
 return PIGMENT_TOKEN;		
#line 676 "FileParser.l.cpp"
		}
		break;
	case 83:
		{
#line 161 "FileParser.l"
 return WIDTH_TOKEN;		
#line 683 "FileParser.l.cpp"
		}
		break;
	case 84:
		{
#line 162 "FileParser.l"
 return HEIGHT_TOKEN;		
#line 690 "FileParser.l.cpp"
		}
		break;
	case 85:
		{
#line 163 "FileParser.l"
 return CONSTANT_TOKEN;	
#line 697 "FileParser.l.cpp"
		}
		break;
	case 86:
		{
#line 164 "FileParser.l"
 return FOCUS_TOKEN;		
#line 704 "FileParser.l.cpp"
		}
		break;
	case 87:
		{
#line 165 "FileParser.l"
 return DISPLAY_TOKEN;		
#line 711 "FileParser.l.cpp"
		}
		break;
	case 88:
		{
#line 166 "FileParser.l"
 return ALGORITHM_TOKEN;	
#line 718 "FileParser.l.cpp"
		}
		break;
	case 89:
		{
#line 167 "FileParser.l"
 return DEFAULT_TOKEN;		
#line 725 "FileParser.l.cpp"
		}
		break;
	case 90:
		{
#line 168 "FileParser.l"
 return ANTIALIAS_TOKEN;	
#line 732 "FileParser.l.cpp"
		}
		break;
	case 91:
		{
#line 169 "FileParser.l"
 return THRESHOLD_TOKEN;	
#line 739 "FileParser.l.cpp"
		}
		break;
	case 92:
		{
#line 170 "FileParser.l"
 return DEPTH_TOKEN;		
#line 746 "FileParser.l.cpp"
		}
		break;
	case 93:
		{
#line 171 "FileParser.l"
 return WIDTH_TOKEN;		
#line 753 "FileParser.l.cpp"
		}
		break;
	case 94:
		{
#line 172 "FileParser.l"
 return HEIGHT_TOKEN;		
#line 760 "FileParser.l.cpp"
		}
		break;
	case 95:
		{
#line 173 "FileParser.l"
 return ROTATE_TOKEN;		
#line 767 "FileParser.l.cpp"
		}
		break;
	case 96:
		{
#line 174 "FileParser.l"
 return SCALE_TOKEN;		
#line 774 "FileParser.l.cpp"
		}
		break;
	case 97:
		{
#line 175 "FileParser.l"
 return TRANSLATE_TOKEN;	
#line 781 "FileParser.l.cpp"
		}
		break;
	case 98:
		{
#line 176 "FileParser.l"
 return EPSILON_TOKEN;		
#line 788 "FileParser.l.cpp"
		}
		break;
	case 99:
		{
#line 177 "FileParser.l"
 return REFLECTION_TOKEN;	
#line 795 "FileParser.l.cpp"
		}
		break;
	case 100:
		{
#line 178 "FileParser.l"
 return IMAGE_TOKEN;		
#line 802 "FileParser.l.cpp"
		}
		break;
	case 101:
		{
#line 179 "FileParser.l"
 return COLOR_TOKEN;		
#line 809 "FileParser.l.cpp"
		}
		break;
	case 102:
		{
#line 180 "FileParser.l"
 return PHONG_SIZE_TOKEN;	
#line 816 "FileParser.l.cpp"
		}
		break;
	case 103:
		{
#line 181 "FileParser.l"
 return DERIVATIVE_TOKEN;	
#line 823 "FileParser.l.cpp"
		}
		break;
	case 104:
		{
#line 182 "FileParser.l"
 return SPHERE_TOKEN;		
#line 830 "FileParser.l.cpp"
		}
		break;
	case 105:
		{
#line 183 "FileParser.l"
 return INTERIOR_TOKEN;	
#line 837 "FileParser.l.cpp"
		}
		break;
	case 106:
		{
#line 184 "FileParser.l"
 return IOR_TOKEN;			
#line 844 "FileParser.l.cpp"
		}
		break;
	case 107:
		{
#line 185 "FileParser.l"
 return DISPERSION_TOKEN;	
#line 851 "FileParser.l.cpp"
		}
		break;
	case 108:
		{
#line 186 "FileParser.l"
 return PHOTONS_TOKEN;		
#line 858 "FileParser.l.cpp"
		}
		break;
	case 109:
		{
#line 187 "FileParser.l"
 return COUNT_TOKEN;		
#line 865 "FileParser.l.cpp"
		}
		break;
	case 110:
		{
#line 188 "FileParser.l"
 return DISPERSION_SAMPLES_TOKEN;	
#line 872 "FileParser.l.cpp"
		}
		break;
	case 111:
		{
#line 189 "FileParser.l"
 return INTENSITY_TOKEN;	
#line 879 "FileParser.l.cpp"
		}
		break;
	case 112:
		{
#line 190 "FileParser.l"
 return PROBABILITY_REFLECTION_TOKEN;
#line 886 "FileParser.l.cpp"
		}
		break;
	case 113:
		{
#line 191 "FileParser.l"
 return CYLINDER_TOKEN;
#line 893 "FileParser.l.cpp"
		}
		break;
	case 114:
		{
#line 192 "FileParser.l"
 return CONE_TOKEN;
#line 900 "FileParser.l.cpp"
		}
		break;
	case 115:
		{
#line 193 "FileParser.l"
 return TEXT_TOKEN;
#line 907 "FileParser.l.cpp"
		}
		break;
	case 116:
		{
#line 194 "FileParser.l"
 return TTF_TOKEN;
#line 914 "FileParser.l.cpp"
		}
		break;
	case 117:
		{
#line 195 "FileParser.l"
 ; 
#line 921 "FileParser.l.cpp"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = 0;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		// <warning: unreachable code> to the old state
#endif
#endif
#line 197 "FileParser.l"


void   CFileLexer::Create(CFileParser *Parser)
{
	yycreate(Parser);
	m_pParser=Parser;
}
#line 945 "FileParser.l.cpp"

void YYLEXNAME::yytables()
{
	yystext_size = YYTEXT_SIZE;
	yysunput_size = YYUNPUT_SIZE;

	static const yymatch_t YYNEARFAR YYBASED_CODE match[] = {
		0
	};
	yymatch = match;

	yytransitionmax = 554;
	static const yytransition_t YYNEARFAR YYBASED_CODE transition[] = {
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 1 },
		{ 0, 59 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 106 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 16, 1 },
		{ 31, 1 },
		{ 45, 1 },
		{ 18, 1 },
		{ 19, 1 },
		{ 21, 1 },
		{ 106, 106 },
		{ 8, 1 },
		{ 9, 1 },
		{ 22, 1 },
		{ 4, 1 },
		{ 23, 1 },
		{ 3, 1 },
		{ 61, 31 },
		{ 29, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 5, 1 },
		{ 25, 1 },
		{ 24, 1 },
		{ 12, 1 },
		{ 27, 1 },
		{ 13, 1 },
		{ 28, 1 },
		{ 17, 1 },
		{ 53, 5 },
		{ 58, 17 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 5, 5 },
		{ 104, 54 },
		{ 57, 16 },
		{ 104, 54 },
		{ 415, 380 },
		{ 416, 380 },
		{ 417, 380 },
		{ 418, 380 },
		{ 419, 380 },
		{ 420, 380 },
		{ 421, 380 },
		{ 55, 12 },
		{ 54, 5 },
		{ 56, 13 },
		{ 0, 0 },
		{ 10, 1 },
		{ 30, 1 },
		{ 11, 1 },
		{ 20, 1 },
		{ 269, 214 },
		{ 26, 1 },
		{ 42, 1 },
		{ 44, 1 },
		{ 32, 1 },
		{ 39, 1 },
		{ 50, 1 },
		{ 33, 1 },
		{ 47, 1 },
		{ 41, 1 },
		{ 51, 1 },
		{ 336, 290 },
		{ 183, 129 },
		{ 37, 1 },
		{ 43, 1 },
		{ 217, 164 },
		{ 35, 1 },
		{ 34, 1 },
		{ 40, 1 },
		{ 49, 1 },
		{ 36, 1 },
		{ 46, 1 },
		{ 38, 1 },
		{ 62, 32 },
		{ 48, 1 },
		{ 54, 5 },
		{ 85, 41 },
		{ 397, 368 },
		{ 6, 1 },
		{ 14, 1 },
		{ 7, 1 },
		{ 15, 1 },
		{ 69, 34 },
		{ 338, 292 },
		{ 429, 391 },
		{ 73, 34 },
		{ 72, 34 },
		{ 63, 32 },
		{ 93, 46 },
		{ 68, 34 },
		{ 445, 431 },
		{ 94, 46 },
		{ 71, 34 },
		{ 77, 36 },
		{ 144, 89 },
		{ 70, 34 },
		{ 84, 41 },
		{ 64, 32 },
		{ 108, 63 },
		{ 148, 93 },
		{ 109, 63 },
		{ 92, 46 },
		{ 458, 450 },
		{ 95, 46 },
		{ 132, 81 },
		{ 403, 376 },
		{ 75, 36 },
		{ 110, 63 },
		{ 244, 190 },
		{ 430, 393 },
		{ 134, 82 },
		{ 76, 36 },
		{ 66, 33 },
		{ 141, 87 },
		{ 83, 40 },
		{ 231, 178 },
		{ 131, 81 },
		{ 133, 81 },
		{ 67, 33 },
		{ 174, 121 },
		{ 135, 82 },
		{ 65, 33 },
		{ 136, 82 },
		{ 400, 373 },
		{ 239, 186 },
		{ 175, 121 },
		{ 142, 87 },
		{ 242, 188 },
		{ 167, 114 },
		{ 257, 203 },
		{ 304, 254 },
		{ 162, 109 },
		{ 235, 182 },
		{ 237, 184 },
		{ 153, 98 },
		{ 157, 102 },
		{ 179, 125 },
		{ 189, 135 },
		{ 262, 208 },
		{ 290, 238 },
		{ 298, 247 },
		{ 303, 253 },
		{ 191, 137 },
		{ 310, 259 },
		{ 325, 278 },
		{ 161, 109 },
		{ 334, 288 },
		{ 203, 148 },
		{ 340, 294 },
		{ 341, 295 },
		{ 345, 300 },
		{ 347, 302 },
		{ 349, 304 },
		{ 357, 313 },
		{ 362, 318 },
		{ 364, 321 },
		{ 386, 352 },
		{ 388, 356 },
		{ 391, 360 },
		{ 207, 152 },
		{ 215, 161 },
		{ 216, 163 },
		{ 218, 165 },
		{ 225, 172 },
		{ 431, 395 },
		{ 432, 396 },
		{ 441, 424 },
		{ 122, 74 },
		{ 452, 442 },
		{ 232, 179 },
		{ 475, 473 },
		{ 267, 212 },
		{ 258, 204 },
		{ 326, 279 },
		{ 327, 280 },
		{ 266, 212 },
		{ 101, 51 },
		{ 102, 51 },
		{ 103, 51 },
		{ 335, 289 },
		{ 219, 166 },
		{ 423, 382 },
		{ 339, 293 },
		{ 275, 223 },
		{ 220, 167 },
		{ 291, 239 },
		{ 124, 75 },
		{ 155, 100 },
		{ 447, 435 },
		{ 123, 75 },
		{ 256, 202 },
		{ 457, 449 },
		{ 169, 116 },
		{ 474, 472 },
		{ 316, 267 },
		{ 370, 330 },
		{ 125, 75 },
		{ 383, 348 },
		{ 385, 351 },
		{ 116, 69 },
		{ 230, 177 },
		{ 390, 359 },
		{ 213, 159 },
		{ 214, 160 },
		{ 328, 281 },
		{ 233, 180 },
		{ 86, 42 },
		{ 88, 42 },
		{ 87, 42 },
		{ 74, 35 },
		{ 158, 103 },
		{ 293, 241 },
		{ 296, 245 },
		{ 436, 400 },
		{ 96, 47 },
		{ 299, 248 },
		{ 149, 94 },
		{ 350, 305 },
		{ 246, 192 },
		{ 308, 257 },
		{ 460, 453 },
		{ 363, 319 },
		{ 249, 195 },
		{ 307, 256 },
		{ 128, 78 },
		{ 117, 70 },
		{ 79, 37 },
		{ 306, 256 },
		{ 194, 140 },
		{ 99, 49 },
		{ 398, 369 },
		{ 187, 133 },
		{ 78, 37 },
		{ 80, 38 },
		{ 405, 378 },
		{ 118, 70 },
		{ 129, 78 },
		{ 126, 76 },
		{ 195, 140 },
		{ 98, 49 },
		{ 222, 169 },
		{ 138, 84 },
		{ 392, 361 },
		{ 468, 466 },
		{ 100, 50 },
		{ 435, 399 },
		{ 206, 151 },
		{ 314, 264 },
		{ 121, 73 },
		{ 228, 175 },
		{ 354, 309 },
		{ 254, 200 },
		{ 359, 315 },
		{ 229, 176 },
		{ 160, 108 },
		{ 343, 297 },
		{ 205, 151 },
		{ 365, 322 },
		{ 455, 447 },
		{ 402, 375 },
		{ 333, 287 },
		{ 459, 451 },
		{ 404, 377 },
		{ 373, 335 },
		{ 374, 336 },
		{ 428, 389 },
		{ 477, 476 },
		{ 318, 270 },
		{ 394, 365 },
		{ 437, 402 },
		{ 439, 404 },
		{ 113, 66 },
		{ 442, 425 },
		{ 443, 428 },
		{ 342, 296 },
		{ 302, 252 },
		{ 401, 374 },
		{ 278, 226 },
		{ 372, 333 },
		{ 280, 228 },
		{ 168, 115 },
		{ 202, 147 },
		{ 463, 459 },
		{ 163, 110 },
		{ 356, 311 },
		{ 172, 119 },
		{ 358, 314 },
		{ 478, 477 },
		{ 241, 187 },
		{ 466, 462 },
		{ 173, 120 },
		{ 378, 343 },
		{ 422, 381 },
		{ 107, 62 },
		{ 317, 269 },
		{ 240, 187 },
		{ 284, 231 },
		{ 332, 286 },
		{ 196, 141 },
		{ 200, 145 },
		{ 264, 210 },
		{ 294, 242 },
		{ 387, 354 },
		{ 209, 154 },
		{ 255, 201 },
		{ 277, 225 },
		{ 320, 272 },
		{ 301, 251 },
		{ 366, 323 },
		{ 469, 467 },
		{ 470, 468 },
		{ 111, 64 },
		{ 371, 332 },
		{ 440, 405 },
		{ 181, 127 },
		{ 283, 230 },
		{ 253, 199 },
		{ 97, 48 },
		{ 119, 71 },
		{ 282, 230 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 105, 105 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 53, 53 },
		{ 82, 39 },
		{ 287, 235 },
		{ 375, 339 },
		{ 376, 341 },
		{ 81, 39 },
		{ 377, 342 },
		{ 315, 266 },
		{ 164, 111 },
		{ 190, 136 },
		{ 346, 301 },
		{ 166, 113 },
		{ 259, 205 },
		{ 389, 357 },
		{ 446, 434 },
		{ 322, 275 },
		{ 451, 441 },
		{ 323, 276 },
		{ 324, 277 },
		{ 393, 364 },
		{ 260, 206 },
		{ 395, 366 },
		{ 145, 90 },
		{ 461, 455 },
		{ 223, 170 },
		{ 399, 371 },
		{ 360, 316 },
		{ 300, 249 },
		{ 210, 155 },
		{ 139, 85 },
		{ 197, 142 },
		{ 476, 475 },
		{ 198, 143 },
		{ 368, 326 },
		{ 434, 398 },
		{ 184, 130 },
		{ 396, 367 },
		{ 309, 258 },
		{ 176, 122 },
		{ 247, 193 },
		{ 381, 345 },
		{ 273, 219 },
		{ 243, 189 },
		{ 261, 207 },
		{ 227, 174 },
		{ 367, 324 },
		{ 130, 79 },
		{ 140, 86 },
		{ 120, 72 },
		{ 281, 229 },
		{ 211, 156 },
		{ 193, 139 },
		{ 186, 132 },
		{ 154, 99 },
		{ 150, 95 },
		{ 467, 464 },
		{ 355, 310 },
		{ 265, 211 },
		{ 159, 107 },
		{ 438, 403 },
		{ 250, 196 },
		{ 274, 222 },
		{ 252, 198 },
		{ 234, 181 },
		{ 204, 149 },
		{ 444, 430 },
		{ 177, 123 },
		{ 226, 173 },
		{ 146, 91 },
		{ 450, 440 },
		{ 337, 291 },
		{ 185, 131 },
		{ 311, 260 },
		{ 456, 448 },
		{ 312, 262 },
		{ 285, 232 },
		{ 286, 233 },
		{ 192, 138 },
		{ 180, 126 },
		{ 245, 191 },
		{ 464, 460 },
		{ 319, 271 },
		{ 425, 385 },
		{ 426, 386 },
		{ 348, 303 },
		{ 212, 157 },
		{ 471, 469 },
		{ 472, 470 },
		{ 263, 209 },
		{ 384, 350 },
		{ 353, 308 },
		{ 433, 397 },
		{ 221, 168 },
		{ 271, 217 },
		{ 91, 45 },
		{ 427, 387 },
		{ 152, 97 },
		{ 331, 285 },
		{ 465, 461 },
		{ 114, 67 },
		{ 454, 446 },
		{ 201, 146 },
		{ 165, 112 },
		{ 178, 124 },
		{ 238, 185 },
		{ 329, 282 },
		{ 473, 471 },
		{ 170, 117 },
		{ 321, 274 },
		{ 448, 436 },
		{ 313, 263 },
		{ 297, 246 },
		{ 171, 118 },
		{ 248, 194 },
		{ 276, 224 },
		{ 143, 88 },
		{ 344, 299 },
		{ 137, 83 },
		{ 127, 77 },
		{ 112, 65 },
		{ 182, 128 },
		{ 406, 379 },
		{ 407, 379 },
		{ 408, 379 },
		{ 409, 379 },
		{ 410, 379 },
		{ 411, 379 },
		{ 412, 379 },
		{ 413, 379 },
		{ 414, 379 },
		{ 208, 153 },
		{ 305, 255 },
		{ 424, 383 },
		{ 351, 306 },
		{ 352, 307 },
		{ 382, 346 },
		{ 147, 92 },
		{ 156, 101 },
		{ 462, 457 },
		{ 330, 284 },
		{ 251, 197 },
		{ 89, 43 },
		{ 288, 236 },
		{ 268, 213 },
		{ 270, 215 },
		{ 361, 317 },
		{ 292, 240 },
		{ 224, 171 },
		{ 272, 218 },
		{ 295, 244 },
		{ 90, 44 },
		{ 115, 68 },
		{ 188, 134 },
		{ 369, 328 },
		{ 151, 96 },
		{ 279, 227 },
		{ 453, 445 },
		{ 289, 237 },
		{ 199, 144 },
		{ 449, 437 },
		{ 236, 183 },
		{ 379, 344 },
		{ 380, 344 },
		{ 60, 29 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 59, 29 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ -52, 1, 0 },
		{ 1, 0, 0 },
		{ 0, 0, 1 },
		{ 0, 0, 2 },
		{ 470, 20, 4 },
		{ 0, 0, 5 },
		{ 0, 0, 6 },
		{ 0, 0, 7 },
		{ 0, 0, 8 },
		{ 0, 0, 9 },
		{ 0, 0, 10 },
		{ 16, 27, 11 },
		{ 16, 29, 12 },
		{ 0, 0, 13 },
		{ 0, 0, 14 },
		{ 0, 18, 15 },
		{ 0, 3, 117 },
		{ 0, 0, 17 },
		{ 0, 0, 18 },
		{ 0, 0, 19 },
		{ 0, 0, 20 },
		{ 0, 0, 21 },
		{ 0, 0, 22 },
		{ 0, 0, 23 },
		{ 0, 0, 24 },
		{ 0, 0, 25 },
		{ 0, 0, 26 },
		{ 0, 0, 27 },
		{ 0, 506, 28 },
		{ 0, 0, 29 },
		{ 106, 13, 117 },
		{ 476, 22, 117 },
		{ 476, 53, 117 },
		{ 476, 27, 117 },
		{ 453, 141, 117 },
		{ 471, 40, 117 },
		{ 476, 167, 117 },
		{ 466, 167, 117 },
		{ 475, 285, 117 },
		{ 373, 43, 117 },
		{ 470, 21, 117 },
		{ 477, 144, 117 },
		{ 457, 429, 117 },
		{ 457, 438, 117 },
		{ 461, 379, 117 },
		{ 473, 33, 117 },
		{ 453, 146, 117 },
		{ 475, 258, 117 },
		{ 476, 174, 117 },
		{ 466, 178, 117 },
		{ 477, 113, 117 },
		{ 0, 0, 117 },
		{ 380, 328, 3 },
		{ 105, 35, 0 },
		{ 0, 0, 31 },
		{ 0, 0, 32 },
		{ 0, 0, 30 },
		{ 0, 0, 16 },
		{ -59, 2, 33 },
		{ 0, 0, 34 },
		{ 106, 0, 0 },
		{ 462, 230, 0 },
		{ 477, 36, 0 },
		{ 468, 249, 0 },
		{ 457, 407, 0 },
		{ 477, 207, 0 },
		{ 471, 385, 0 },
		{ 457, 439, 0 },
		{ 453, 131, 0 },
		{ 476, 170, 0 },
		{ 475, 259, 0 },
		{ 324, 330, 0 },
		{ 476, 183, 0 },
		{ 473, 97, 0 },
		{ 476, 131, 0 },
		{ 466, 171, 0 },
		{ 457, 406, 0 },
		{ 476, 171, 0 },
		{ 324, 328, 0 },
		{ 0, 0, 44 },
		{ 472, 48, 0 },
		{ 466, 54, 0 },
		{ 457, 405, 0 },
		{ 466, 175, 0 },
		{ 475, 309, 0 },
		{ 324, 329, 0 },
		{ 473, 56, 0 },
		{ 224, 402, 0 },
		{ 450, 20, 0 },
		{ 475, 302, 0 },
		{ 470, 352, 0 },
		{ 457, 424, 0 },
		{ 450, 25, 0 },
		{ 453, 148, 0 },
		{ 464, 337, 0 },
		{ 457, 442, 0 },
		{ 461, 381, 0 },
		{ 473, 64, 0 },
		{ 464, 336, 0 },
		{ 472, 118, 0 },
		{ 457, 425, 0 },
		{ 473, 65, 0 },
		{ 453, 142, 0 },
		{ 105, 0, 0 },
		{ 380, 318, 4 },
		{ -61, 6, 35 },
		{ 470, 342, 0 },
		{ 476, 189, 0 },
		{ 472, 76, 0 },
		{ 477, 219, 0 },
		{ 475, 288, 0 },
		{ 471, 388, 0 },
		{ 475, 291, 0 },
		{ 373, 57, 0 },
		{ 477, 216, 0 },
		{ 472, 123, 0 },
		{ 471, 393, 0 },
		{ 224, 399, 0 },
		{ 477, 221, 0 },
		{ 462, 227, 0 },
		{ 477, 55, 0 },
		{ 398, 319, 0 },
		{ 470, 350, 0 },
		{ 471, 389, 0 },
		{ 473, 66, 0 },
		{ 470, 362, 0 },
		{ 468, 252, 0 },
		{ 457, 408, 0 },
		{ 0, 1, 0 },
		{ 398, 316, 0 },
		{ 470, 355, 0 },
		{ 464, 335, 0 },
		{ 466, 165, 0 },
		{ 457, 440, 0 },
		{ 473, 67, 0 },
		{ 475, 289, 0 },
		{ 473, 72, 0 },
		{ 470, 361, 0 },
		{ 324, 333, 0 },
		{ 476, 173, 0 },
		{ 468, 236, 0 },
		{ 475, 310, 0 },
		{ 475, 312, 0 },
		{ 445, 448, 0 },
		{ 468, 237, 0 },
		{ 471, 387, 0 },
		{ 477, 217, 0 },
		{ 473, 77, 0 },
		{ 470, 348, 0 },
		{ 0, 0, 116 },
		{ 477, 192, 0 },
		{ 473, 89, 0 },
		{ 457, 418, 0 },
		{ 468, 241, 0 },
		{ 475, 308, 0 },
		{ 324, 332, 0 },
		{ 470, 369, 0 },
		{ 0, 0, 106 },
		{ 453, 134, 0 },
		{ 453, 135, 0 },
		{ 473, 90, 0 },
		{ 0, 0, 114 },
		{ 473, 91, 0 },
		{ 477, 1, 0 },
		{ 473, 92, 0 },
		{ 472, 111, 0 },
		{ 472, 115, 0 },
		{ 470, 376, 0 },
		{ 466, 174, 0 },
		{ 475, 304, 0 },
		{ 457, 435, 0 },
		{ 473, 93, 0 },
		{ 470, 351, 0 },
		{ 324, 326, 0 },
		{ 476, 184, 0 },
		{ 476, 188, 0 },
		{ 453, 132, 0 },
		{ 373, 44, 0 },
		{ 473, 99, 0 },
		{ 453, 137, 0 },
		{ 470, 347, 0 },
		{ 473, 62, 0 },
		{ 445, 450, 0 },
		{ 473, 63, 0 },
		{ 471, 390, 0 },
		{ 373, 53, 0 },
		{ 470, 233, 0 },
		{ 373, 56, 0 },
		{ 398, 323, 0 },
		{ 393, 36, 0 },
		{ 470, 363, 0 },
		{ 453, 150, 0 },
		{ 398, 320, 0 },
		{ 224, 400, 0 },
		{ 453, 154, 0 },
		{ 470, 344, 0 },
		{ 457, 428, 0 },
		{ 470, 346, 0 },
		{ 475, 257, 0 },
		{ 476, 186, 0 },
		{ 468, 242, 0 },
		{ 472, 121, 0 },
		{ 373, 58, 115 },
		{ 472, 103, 0 },
		{ 475, 292, 0 },
		{ 475, 300, 0 },
		{ 398, 324, 0 },
		{ 473, 68, 0 },
		{ 470, 372, 0 },
		{ 468, 238, 0 },
		{ 470, 341, 0 },
		{ 477, 107, 0 },
		{ 457, 431, 0 },
		{ 445, 1, 101 },
		{ 457, 432, 0 },
		{ 0, 0, 109 },
		{ 461, 378, 0 },
		{ 457, 436, 0 },
		{ 398, 322, 0 },
		{ 0, 0, 86 },
		{ 0, 0, 38 },
		{ 470, 345, 0 },
		{ 472, 114, 0 },
		{ 0, 401, 0 },
		{ 468, 243, 0 },
		{ 477, 213, 0 },
		{ 445, 445, 0 },
		{ 477, 215, 0 },
		{ 324, 331, 0 },
		{ 475, 260, 0 },
		{ 468, 234, 0 },
		{ 470, 359, 0 },
		{ 470, 360, 0 },
		{ 0, 0, 96 },
		{ 475, 282, 0 },
		{ 457, 430, 0 },
		{ 445, 447, 0 },
		{ 473, 69, 0 },
		{ 472, 116, 0 },
		{ 457, 434, 0 },
		{ 453, 143, 0 },
		{ 468, 239, 0 },
		{ 0, 0, 92 },
		{ 457, 437, 0 },
		{ 453, 144, 0 },
		{ 471, 397, 0 },
		{ 473, 70, 0 },
		{ 453, 147, 0 },
		{ 475, 307, 0 },
		{ 0, 0, 68 },
		{ 468, 245, 0 },
		{ 477, 211, 0 },
		{ 473, 71, 0 },
		{ 373, 59, 0 },
		{ 457, 419, 0 },
		{ 468, 161, 0 },
		{ 453, 151, 0 },
		{ 398, 318, 0 },
		{ 473, 73, 0 },
		{ 470, 356, 0 },
		{ 0, 0, 83 },
		{ 470, 358, 0 },
		{ 471, 396, 0 },
		{ 476, 182, 0 },
		{ 0, 0, 100 },
		{ 475, 287, 0 },
		{ 472, 125, 0 },
		{ 0, 0, 36 },
		{ 462, 231, 0 },
		{ 477, 203, 0 },
		{ 470, 365, 0 },
		{ 468, 244, 0 },
		{ 0, 0, 81 },
		{ 471, 394, 0 },
		{ 475, 295, 0 },
		{ 475, 297, 0 },
		{ 475, 298, 0 },
		{ 473, 74, 0 },
		{ 472, 104, 0 },
		{ 472, 105, 0 },
		{ 453, 136, 0 },
		{ 471, 391, 0 },
		{ 0, 0, 104 },
		{ 457, 427, 0 },
		{ 461, 382, 0 },
		{ 468, 235, 0 },
		{ 476, 195, 0 },
		{ 473, 76, 0 },
		{ 472, 110, 0 },
		{ 475, 2, 0 },
		{ 470, 354, 0 },
		{ 431, 8, 0 },
		{ 472, 113, 0 },
		{ 473, 78, 0 },
		{ 473, 79, 0 },
		{ 477, 210, 0 },
		{ 476, 190, 0 },
		{ 0, 0, 84 },
		{ 457, 404, 0 },
		{ 473, 80, 0 },
		{ 475, 290, 0 },
		{ 473, 81, 0 },
		{ 470, 368, 0 },
		{ 473, 82, 0 },
		{ 453, 149, 0 },
		{ 457, 421, 0 },
		{ 457, 422, 0 },
		{ 470, 374, 0 },
		{ 476, 185, 0 },
		{ 470, 340, 0 },
		{ 477, 220, 0 },
		{ 0, 0, 95 },
		{ 473, 83, 0 },
		{ 477, 222, 0 },
		{ 476, 187, 0 },
		{ 475, 306, 0 },
		{ 457, 433, 0 },
		{ 473, 84, 0 },
		{ 453, 153, 0 },
		{ 0, 0, 37 },
		{ 473, 85, 0 },
		{ 476, 192, 0 },
		{ 468, 246, 0 },
		{ 0, 327, 0 },
		{ 0, 0, 82 },
		{ 475, 313, 0 },
		{ 0, 0, 108 },
		{ 457, 441, 0 },
		{ 0, 0, 41 },
		{ 453, 127, 0 },
		{ 0, 0, 79 },
		{ 468, 250, 0 },
		{ 477, 214, 0 },
		{ 0, 0, 46 },
		{ 476, 198, 0 },
		{ 476, 199, 0 },
		{ 0, 0, 73 },
		{ 0, 0, 87 },
		{ 475, 283, 0 },
		{ 0, 0, 89 },
		{ 475, 284, 0 },
		{ 475, 286, 0 },
		{ 462, 228, 0 },
		{ 0, 498, 0 },
		{ 398, 321, 0 },
		{ 457, 423, 0 },
		{ 0, 0, 69 },
		{ 453, 129, 0 },
		{ 0, 0, 66 },
		{ 470, 373, 0 },
		{ 453, 130, 0 },
		{ 473, 86, 0 },
		{ 0, 0, 77 },
		{ 468, 240, 0 },
		{ 0, 0, 78 },
		{ 473, 87, 0 },
		{ 475, 293, 0 },
		{ 0, 0, 98 },
		{ 453, 133, 0 },
		{ 473, 88, 0 },
		{ 466, 176, 0 },
		{ 0, 0, 85 },
		{ 0, 0, 113 },
		{ 475, 299, 0 },
		{ 477, 204, 0 },
		{ 475, 301, 0 },
		{ 398, 317, 0 },
		{ 0, 1, 0 },
		{ 466, 164, 0 },
		{ 0, 0, 74 },
		{ 475, 305, 0 },
		{ 0, 0, 43 },
		{ 0, 52, 0 },
		{ 477, 212, 0 },
		{ 476, 194, 0 },
		{ 393, 33, 0 },
		{ 476, 197, 0 },
		{ 466, 168, 0 },
		{ 0, 457, 0 },
		{ 344, 33, 0 },
		{ 462, 229, 0 },
		{ 472, 112, 0 },
		{ 457, 420, 0 },
		{ 0, 0, 72 },
		{ 470, 366, 0 },
		{ 470, 367, 0 },
		{ 461, 380, 0 },
		{ 0, 0, 80 },
		{ 476, 200, 0 },
		{ 0, 0, 105 },
		{ 431, 9, 0 },
		{ 0, 0, 76 },
		{ 0, 37, 0 },
		{ 0, 0, 67 },
		{ 473, 94, 0 },
		{ 473, 95, 0 },
		{ 470, 375, 0 },
		{ 0, 315, 0 },
		{ 466, 179, 0 },
		{ 453, 145, 0 },
		{ 0, 0, 45 },
		{ 477, 205, 0 },
		{ 470, 343, 0 },
		{ 477, 206, 0 },
		{ 468, 251, 0 },
		{ 0, 0, 49 },
		{ 0, 0, 50 },
		{ 0, 0, 51 },
		{ 0, 0, 52 },
		{ 0, 0, 53 },
		{ 0, 0, 54 },
		{ 0, 0, 55 },
		{ 0, 0, 56 },
		{ 0, 0, 57 },
		{ 0, 0, 58 },
		{ 0, 0, 59 },
		{ 0, 0, 60 },
		{ 0, 0, 61 },
		{ 0, 0, 62 },
		{ 0, 0, 63 },
		{ 0, 0, 64 },
		{ 0, 0, 88 },
		{ 0, 0, 90 },
		{ 473, 96, 0 },
		{ 477, 208, 0 },
		{ 0, 0, 97 },
		{ 0, 0, 91 },
		{ 477, 209, 0 },
		{ 0, 0, 111 },
		{ 470, 349, 0 },
		{ 0, 15, 0 },
		{ 0, 0, 70 },
		{ 0, 0, 102 },
		{ 475, 294, 0 },
		{ 472, 119, 0 },
		{ 471, 395, 0 },
		{ 445, 449, 107 },
		{ 0, 0, 103 },
		{ 0, 0, 47 },
		{ 470, 353, 0 },
		{ 475, 296, 0 },
		{ 473, 98, 0 },
		{ 0, 0, 99 },
		{ 0, 0, 40 },
		{ 0, 446, 0 },
		{ 471, 386, 0 },
		{ 476, 193, 0 },
		{ 470, 357, 0 },
		{ 472, 122, 0 },
		{ 0, 28, 0 },
		{ 476, 196, 0 },
		{ 0, 0, 75 },
		{ 0, 152, 0 },
		{ 0, 0, 39 },
		{ 475, 303, 0 },
		{ 0, 0, 71 },
		{ 0, 426, 0 },
		{ 0, 0, 48 },
		{ 477, 218, 0 },
		{ 470, 364, 0 },
		{ 0, 383, 0 },
		{ 0, 226, 0 },
		{ 0, 0, 65 },
		{ 0, 338, 0 },
		{ 0, 0, 42 },
		{ 0, 177, 0 },
		{ 468, 247, 0 },
		{ 0, 248, 0 },
		{ 470, 370, 0 },
		{ 0, 371, 0 },
		{ 0, 392, 0 },
		{ 0, 124, 0 },
		{ 0, 100, 0 },
		{ 0, 0, 110 },
		{ 0, 311, 0 },
		{ 0, 201, 0 },
		{ 0, 223, 0 },
		{ 0, 0, 112 }
	};
	yystate = state;

	static const yybackup_t YYNEARFAR YYBASED_CODE backup[] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	yybackup = backup;
}
