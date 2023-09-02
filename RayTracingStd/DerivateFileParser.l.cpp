#include <clex.h>

#line 1 "DerivateFileParser.l"

/*	Parser servant à compiler les fichiers d'entrée pour les traduire en
 *  structure de données
 */
#pragma warning(disable : 4786)
#include "TraceService.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <map>
#include "Color.h"
#include "ParserUnDef.h"

class CDerivateFileLexer;
#include "DerivateFileParser.h"

#line 22 "DerivateFileParser.l.cpp"
// repeated because of possible precompiled header
#include <clex.h>

#include "DerivateFileParser.l.h"

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
#line 47 "DerivateFileParser.l"
return DASH_TOKEN;
#line 85 "DerivateFileParser.l.cpp"
		}
		break;
	case 2:
		{
#line 48 "DerivateFileParser.l"
return PLUS_TOKEN;
#line 92 "DerivateFileParser.l.cpp"
		}
		break;
	case 3:
		{
#line 50 "DerivateFileParser.l"
return FLOAT_TOKEN;
#line 99 "DerivateFileParser.l.cpp"
		}
		break;
	case 4:
		{
#line 51 "DerivateFileParser.l"
return FLOAT_TOKEN;
#line 106 "DerivateFileParser.l.cpp"
		}
		break;
	case 5:
		{
#line 53 "DerivateFileParser.l"
return LEFT_CURLY_TOKEN;
#line 113 "DerivateFileParser.l.cpp"
		}
		break;
	case 6:
		{
#line 54 "DerivateFileParser.l"
return RIGHT_CURLY_TOKEN;
#line 120 "DerivateFileParser.l.cpp"
		}
		break;
	case 7:
		{
#line 56 "DerivateFileParser.l"
return LEFT_PAREN_TOKEN;
#line 127 "DerivateFileParser.l.cpp"
		}
		break;
	case 8:
		{
#line 57 "DerivateFileParser.l"
return RIGHT_PAREN_TOKEN;
#line 134 "DerivateFileParser.l.cpp"
		}
		break;
	case 9:
		{
#line 59 "DerivateFileParser.l"
return LEFT_SQUARE_TOKEN;
#line 141 "DerivateFileParser.l.cpp"
		}
		break;
	case 10:
		{
#line 60 "DerivateFileParser.l"
return RIGHT_SQUARE_TOKEN;
#line 148 "DerivateFileParser.l.cpp"
		}
		break;
	case 11:
		{
#line 62 "DerivateFileParser.l"
return LEFT_ANGLE_TOKEN;
#line 155 "DerivateFileParser.l.cpp"
		}
		break;
	case 12:
		{
#line 63 "DerivateFileParser.l"
return RIGHT_ANGLE_TOKEN;
#line 162 "DerivateFileParser.l.cpp"
		}
		break;
	case 13:
		{
#line 65 "DerivateFileParser.l"
return BAR_TOKEN;
#line 169 "DerivateFileParser.l.cpp"
		}
		break;
	case 14:
		{
#line 66 "DerivateFileParser.l"
return TILDE_TOKEN;
#line 176 "DerivateFileParser.l.cpp"
		}
		break;
	case 15:
		{
#line 67 "DerivateFileParser.l"
return EXCLAMATION_TOKEN;
#line 183 "DerivateFileParser.l.cpp"
		}
		break;
	case 16:
		{
#line 68 "DerivateFileParser.l"
return AT_TOKEN;
#line 190 "DerivateFileParser.l.cpp"
		}
		break;
	case 17:
		{
#line 69 "DerivateFileParser.l"
return DOLLAR_TOKEN;
#line 197 "DerivateFileParser.l.cpp"
		}
		break;
	case 18:
		{
#line 70 "DerivateFileParser.l"
return PERCENT_TOKEN;
#line 204 "DerivateFileParser.l.cpp"
		}
		break;
	case 19:
		{
#line 71 "DerivateFileParser.l"
return HAT_TOKEN;
#line 211 "DerivateFileParser.l.cpp"
		}
		break;
	case 20:
		{
#line 72 "DerivateFileParser.l"
return AMPERSAND_TOKEN;
#line 218 "DerivateFileParser.l.cpp"
		}
		break;
	case 21:
		{
#line 73 "DerivateFileParser.l"
return STAR_TOKEN;
#line 225 "DerivateFileParser.l.cpp"
		}
		break;
	case 22:
		{
#line 74 "DerivateFileParser.l"
return COMMA_TOKEN;
#line 232 "DerivateFileParser.l.cpp"
		}
		break;
	case 23:
		{
#line 75 "DerivateFileParser.l"
return SEMI_COLON_TOKEN;
#line 239 "DerivateFileParser.l.cpp"
		}
		break;
	case 24:
		{
#line 76 "DerivateFileParser.l"
return COLON_TOKEN;
#line 246 "DerivateFileParser.l.cpp"
		}
		break;
	case 25:
		{
#line 77 "DerivateFileParser.l"
return BACK_QUOTE_TOKEN;
#line 253 "DerivateFileParser.l.cpp"
		}
		break;
	case 26:
		{
#line 78 "DerivateFileParser.l"
return EQUALS_TOKEN;
#line 260 "DerivateFileParser.l.cpp"
		}
		break;
	case 27:
		{
#line 79 "DerivateFileParser.l"
return QUESTION_TOKEN;
#line 267 "DerivateFileParser.l.cpp"
		}
		break;
	case 28:
		{
#line 80 "DerivateFileParser.l"
return SLASH_TOKEN;
#line 274 "DerivateFileParser.l.cpp"
		}
		break;
	case 29:
		{
#line 81 "DerivateFileParser.l"
return BACK_SLASH_TOKEN;
#line 281 "DerivateFileParser.l.cpp"
		}
		break;
	case 30:
		{
#line 83 "DerivateFileParser.l"
return REL_NE_TOKEN;
#line 288 "DerivateFileParser.l.cpp"
		}
		break;
	case 31:
		{
#line 84 "DerivateFileParser.l"
return REL_LE_TOKEN;
#line 295 "DerivateFileParser.l.cpp"
		}
		break;
	case 32:
		{
#line 85 "DerivateFileParser.l"
return REL_GE_TOKEN;
#line 302 "DerivateFileParser.l.cpp"
		}
		break;
	case 33:
		{
#line 87 "DerivateFileParser.l"

#line 309 "DerivateFileParser.l.cpp"
		}
		break;
	case 34:
		{
#line 88 "DerivateFileParser.l"

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
			
#line 332 "DerivateFileParser.l.cpp"
		}
		break;
#line 105 "DerivateFileParser.l"
            
#line 337 "DerivateFileParser.l.cpp"
	case 35:
		{
#line 107 "DerivateFileParser.l"
return STRING_LITERAL_TOKEN;
#line 342 "DerivateFileParser.l.cpp"
		}
		break;
	case 36:
		{
#line 109 "DerivateFileParser.l"
 return CAMERA_TOKEN;		
#line 349 "DerivateFileParser.l.cpp"
		}
		break;
	case 37:
		{
#line 110 "DerivateFileParser.l"
 return FRACTAL_TOKEN;		
#line 356 "DerivateFileParser.l.cpp"
		}
		break;
	case 38:
		{
#line 111 "DerivateFileParser.l"
 return PLANE_TOKEN;		
#line 363 "DerivateFileParser.l.cpp"
		}
		break;
	case 39:
		{
#line 112 "DerivateFileParser.l"
 return ORTHOGRAPHIC_TOKEN;
#line 370 "DerivateFileParser.l.cpp"
		}
		break;
	case 40:
		{
#line 113 "DerivateFileParser.l"
 return PERSPECTIVE_TOKEN; 
#line 377 "DerivateFileParser.l.cpp"
		}
		break;
	case 41:
		{
#line 114 "DerivateFileParser.l"
 return LOCATION_TOKEN;	
#line 384 "DerivateFileParser.l.cpp"
		}
		break;
	case 42:
		{
#line 115 "DerivateFileParser.l"
 return UP_TOKEN;			
#line 391 "DerivateFileParser.l.cpp"
		}
		break;
	case 43:
		{
#line 116 "DerivateFileParser.l"
 return DIRECTION_TOKEN;	
#line 398 "DerivateFileParser.l.cpp"
		}
		break;
	case 44:
		{
#line 117 "DerivateFileParser.l"
 return LOOK_AT_TOKEN;		
#line 405 "DerivateFileParser.l.cpp"
		}
		break;
	case 45:
		{
#line 118 "DerivateFileParser.l"
 return QUATERNION_TOKEN;	
#line 412 "DerivateFileParser.l.cpp"
		}
		break;
	case 46:
		{
#line 119 "DerivateFileParser.l"
 return HYPERCOMPLEX_TOKEN;
#line 419 "DerivateFileParser.l.cpp"
		}
		break;
	case 47:
		{
#line 120 "DerivateFileParser.l"
 return MAX_ITERATION_TOKEN;
#line 426 "DerivateFileParser.l.cpp"
		}
		break;
	case 48:
		{
#line 121 "DerivateFileParser.l"
 return BAILOUT_TOKEN;		
#line 433 "DerivateFileParser.l.cpp"
		}
		break;
	case 49:
		{
#line 122 "DerivateFileParser.l"
 return PRECISION_TOKEN;	
#line 440 "DerivateFileParser.l.cpp"
		}
		break;
	case 50:
		{
#line 123 "DerivateFileParser.l"
 return ANGLE_TOKEN;		
#line 447 "DerivateFileParser.l.cpp"
		}
		break;
	case 51:
		{
#line 124 "DerivateFileParser.l"
 return AMBIENT_TOKEN;		
#line 454 "DerivateFileParser.l.cpp"
		}
		break;
	case 52:
		{
#line 125 "DerivateFileParser.l"
 return POINTLIGHT_TOKEN;	
#line 461 "DerivateFileParser.l.cpp"
		}
		break;
	case 53:
		{
#line 126 "DerivateFileParser.l"
 return LIGHT_SOURCE_TOKEN;
#line 468 "DerivateFileParser.l.cpp"
		}
		break;
	case 54:
		{
#line 127 "DerivateFileParser.l"
 return DECLARE_TOKEN;		
#line 475 "DerivateFileParser.l.cpp"
		}
		break;
	case 55:
		{
#line 128 "DerivateFileParser.l"
 return DIFFUSE_TOKEN;		
#line 482 "DerivateFileParser.l.cpp"
		}
		break;
	case 56:
		{
#line 129 "DerivateFileParser.l"
 return SPECULAR_TOKEN;	
#line 489 "DerivateFileParser.l.cpp"
		}
		break;
	case 57:
		{
#line 130 "DerivateFileParser.l"
 return TRANSPARENT_TOKEN;	
#line 496 "DerivateFileParser.l.cpp"
		}
		break;
	case 58:
		{
#line 131 "DerivateFileParser.l"
 return COLOR_MAP_TOKEN;	
#line 503 "DerivateFileParser.l.cpp"
		}
		break;
	case 59:
		{
#line 132 "DerivateFileParser.l"
 return TEXTURE_TOKEN;		
#line 510 "DerivateFileParser.l.cpp"
		}
		break;
	case 60:
		{
#line 133 "DerivateFileParser.l"
 return GRANITE_TOKEN;		
#line 517 "DerivateFileParser.l.cpp"
		}
		break;
	case 61:
		{
#line 134 "DerivateFileParser.l"
 return SPOTTED_TOKEN;		
#line 524 "DerivateFileParser.l.cpp"
		}
		break;
	case 62:
		{
#line 135 "DerivateFileParser.l"
 return FINISH_TOKEN;		
#line 531 "DerivateFileParser.l.cpp"
		}
		break;
	case 63:
		{
#line 136 "DerivateFileParser.l"
 return PIGMENT_TOKEN;		
#line 538 "DerivateFileParser.l.cpp"
		}
		break;
	case 64:
		{
#line 137 "DerivateFileParser.l"
 return WIDTH_TOKEN;		
#line 545 "DerivateFileParser.l.cpp"
		}
		break;
	case 65:
		{
#line 138 "DerivateFileParser.l"
 return HEIGHT_TOKEN;		
#line 552 "DerivateFileParser.l.cpp"
		}
		break;
	case 66:
		{
#line 139 "DerivateFileParser.l"
 return CONSTANT_TOKEN;	
#line 559 "DerivateFileParser.l.cpp"
		}
		break;
	case 67:
		{
#line 140 "DerivateFileParser.l"
 return FOCUS_TOKEN;		
#line 566 "DerivateFileParser.l.cpp"
		}
		break;
	case 68:
		{
#line 141 "DerivateFileParser.l"
 return DISPLAY_TOKEN;		
#line 573 "DerivateFileParser.l.cpp"
		}
		break;
	case 69:
		{
#line 142 "DerivateFileParser.l"
 return ALGORITHM_TOKEN;	
#line 580 "DerivateFileParser.l.cpp"
		}
		break;
	case 70:
		{
#line 143 "DerivateFileParser.l"
 return DEFAULT_TOKEN;		
#line 587 "DerivateFileParser.l.cpp"
		}
		break;
	case 71:
		{
#line 144 "DerivateFileParser.l"
 return ANTIALIAS_TOKEN;	
#line 594 "DerivateFileParser.l.cpp"
		}
		break;
	case 72:
		{
#line 145 "DerivateFileParser.l"
 return WIDTH_TOKEN;		
#line 601 "DerivateFileParser.l.cpp"
		}
		break;
	case 73:
		{
#line 146 "DerivateFileParser.l"
 return HEIGHT_TOKEN;		
#line 608 "DerivateFileParser.l.cpp"
		}
		break;
	case 74:
		{
#line 147 "DerivateFileParser.l"
 ; 
#line 615 "DerivateFileParser.l.cpp"
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
#line 149 "DerivateFileParser.l"


void   CDerivateFileLexer::Create(CDerivateFileParser *Parser)
{
	yycreate(Parser);
	m_pParser=Parser;
}
#line 639 "DerivateFileParser.l.cpp"

void YYLEXNAME::yytables()
{
	yystext_size = YYTEXT_SIZE;
	yysunput_size = YYUNPUT_SIZE;

	static const yymatch_t YYNEARFAR YYBASED_CODE match[] = {
		0
	};
	yymatch = match;

	yytransitionmax = 381;
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
		{ 0, 56 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 91 },
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
		{ 44, 1 },
		{ 18, 1 },
		{ 19, 1 },
		{ 21, 1 },
		{ 91, 91 },
		{ 8, 1 },
		{ 9, 1 },
		{ 22, 1 },
		{ 4, 1 },
		{ 23, 1 },
		{ 3, 1 },
		{ 58, 31 },
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
		{ 50, 5 },
		{ 55, 17 },
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
		{ 89, 51 },
		{ 53, 13 },
		{ 89, 51 },
		{ 54, 16 },
		{ 52, 12 },
		{ 57, 29 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 56, 29 },
		{ 51, 5 },
		{ 0, 0 },
		{ 0, 0 },
		{ 10, 1 },
		{ 30, 1 },
		{ 11, 1 },
		{ 20, 1 },
		{ 209, 176 },
		{ 26, 1 },
		{ 43, 1 },
		{ 42, 1 },
		{ 32, 1 },
		{ 38, 1 },
		{ 77, 40 },
		{ 33, 1 },
		{ 47, 1 },
		{ 40, 1 },
		{ 247, 219 },
		{ 88, 48 },
		{ 140, 105 },
		{ 36, 1 },
		{ 41, 1 },
		{ 96, 62 },
		{ 35, 1 },
		{ 34, 1 },
		{ 39, 1 },
		{ 99, 65 },
		{ 45, 1 },
		{ 46, 1 },
		{ 37, 1 },
		{ 286, 274 },
		{ 48, 1 },
		{ 51, 5 },
		{ 76, 40 },
		{ 241, 212 },
		{ 6, 1 },
		{ 14, 1 },
		{ 7, 1 },
		{ 15, 1 },
		{ 65, 34 },
		{ 124, 86 },
		{ 114, 78 },
		{ 302, 297 },
		{ 68, 34 },
		{ 108, 73 },
		{ 62, 33 },
		{ 64, 34 },
		{ 116, 80 },
		{ 180, 145 },
		{ 67, 34 },
		{ 191, 156 },
		{ 63, 33 },
		{ 66, 34 },
		{ 194, 159 },
		{ 61, 33 },
		{ 218, 185 },
		{ 107, 73 },
		{ 109, 73 },
		{ 75, 39 },
		{ 278, 263 },
		{ 117, 80 },
		{ 132, 97 },
		{ 178, 143 },
		{ 176, 141 },
		{ 103, 69 },
		{ 146, 111 },
		{ 157, 122 },
		{ 192, 157 },
		{ 159, 124 },
		{ 210, 177 },
		{ 216, 183 },
		{ 217, 184 },
		{ 161, 126 },
		{ 227, 195 },
		{ 234, 205 },
		{ 237, 208 },
		{ 164, 129 },
		{ 242, 213 },
		{ 246, 218 },
		{ 248, 220 },
		{ 249, 221 },
		{ 257, 229 },
		{ 258, 231 },
		{ 165, 130 },
		{ 171, 136 },
		{ 287, 276 },
		{ 292, 282 },
		{ 299, 293 },
		{ 174, 139 },
		{ 86, 46 },
		{ 203, 170 },
		{ 129, 94 },
		{ 238, 209 },
		{ 283, 268 },
		{ 211, 178 },
		{ 134, 99 },
		{ 166, 131 },
		{ 193, 158 },
		{ 167, 132 },
		{ 162, 127 },
		{ 250, 222 },
		{ 226, 194 },
		{ 85, 46 },
		{ 163, 128 },
		{ 267, 245 },
		{ 271, 251 },
		{ 272, 253 },
		{ 69, 35 },
		{ 235, 206 },
		{ 87, 47 },
		{ 82, 43 },
		{ 81, 43 },
		{ 80, 43 },
		{ 289, 278 },
		{ 182, 147 },
		{ 214, 181 },
		{ 189, 154 },
		{ 71, 36 },
		{ 104, 70 },
		{ 121, 84 },
		{ 59, 32 },
		{ 225, 193 },
		{ 281, 266 },
		{ 70, 36 },
		{ 112, 76 },
		{ 169, 134 },
		{ 84, 45 },
		{ 144, 109 },
		{ 72, 37 },
		{ 122, 84 },
		{ 105, 70 },
		{ 273, 256 },
		{ 277, 261 },
		{ 93, 60 },
		{ 60, 32 },
		{ 94, 60 },
		{ 244, 215 },
		{ 280, 265 },
		{ 259, 232 },
		{ 263, 238 },
		{ 264, 239 },
		{ 236, 207 },
		{ 154, 119 },
		{ 128, 93 },
		{ 185, 150 },
		{ 173, 138 },
		{ 303, 298 },
		{ 279, 264 },
		{ 160, 125 },
		{ 262, 236 },
		{ 243, 214 },
		{ 229, 199 },
		{ 136, 101 },
		{ 133, 98 },
		{ 290, 280 },
		{ 205, 172 },
		{ 293, 285 },
		{ 220, 188 },
		{ 275, 259 },
		{ 158, 123 },
		{ 304, 303 },
		{ 266, 244 },
		{ 228, 198 },
		{ 92, 59 },
		{ 137, 102 },
		{ 284, 269 },
		{ 179, 144 },
		{ 150, 115 },
		{ 230, 200 },
		{ 291, 281 },
		{ 219, 187 },
		{ 190, 155 },
		{ 223, 191 },
		{ 213, 180 },
		{ 151, 116 },
		{ 204, 171 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 90, 90 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 50, 50 },
		{ 74, 38 },
		{ 131, 96 },
		{ 232, 203 },
		{ 233, 204 },
		{ 73, 38 },
		{ 152, 117 },
		{ 195, 160 },
		{ 170, 135 },
		{ 184, 149 },
		{ 221, 189 },
		{ 265, 243 },
		{ 239, 210 },
		{ 153, 118 },
		{ 207, 174 },
		{ 295, 288 },
		{ 298, 292 },
		{ 115, 79 },
		{ 101, 67 },
		{ 274, 258 },
		{ 113, 77 },
		{ 141, 106 },
		{ 276, 260 },
		{ 269, 249 },
		{ 183, 148 },
		{ 288, 277 },
		{ 196, 161 },
		{ 201, 166 },
		{ 138, 103 },
		{ 148, 113 },
		{ 260, 233 },
		{ 119, 82 },
		{ 206, 173 },
		{ 102, 68 },
		{ 106, 71 },
		{ 110, 74 },
		{ 143, 108 },
		{ 168, 133 },
		{ 186, 151 },
		{ 202, 169 },
		{ 285, 272 },
		{ 245, 217 },
		{ 188, 153 },
		{ 100, 66 },
		{ 270, 250 },
		{ 120, 83 },
		{ 147, 112 },
		{ 181, 146 },
		{ 254, 226 },
		{ 294, 286 },
		{ 255, 227 },
		{ 297, 291 },
		{ 224, 192 },
		{ 172, 137 },
		{ 301, 296 },
		{ 142, 107 },
		{ 240, 211 },
		{ 127, 92 },
		{ 83, 44 },
		{ 126, 88 },
		{ 252, 224 },
		{ 156, 121 },
		{ 296, 289 },
		{ 130, 95 },
		{ 135, 100 },
		{ 97, 63 },
		{ 300, 295 },
		{ 155, 120 },
		{ 215, 182 },
		{ 231, 202 },
		{ 177, 142 },
		{ 118, 81 },
		{ 261, 235 },
		{ 125, 87 },
		{ 78, 41 },
		{ 212, 179 },
		{ 139, 104 },
		{ 197, 162 },
		{ 199, 164 },
		{ 268, 247 },
		{ 200, 165 },
		{ 187, 152 },
		{ 79, 42 },
		{ 251, 223 },
		{ 98, 64 },
		{ 253, 225 },
		{ 95, 61 },
		{ 123, 85 },
		{ 256, 228 },
		{ 222, 190 },
		{ 111, 75 },
		{ 145, 110 },
		{ 208, 175 },
		{ 282, 267 },
		{ 175, 140 },
		{ 198, 163 },
		{ 149, 114 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ -49, 1, 0 },
		{ 1, 0, 0 },
		{ 0, 0, 1 },
		{ 0, 0, 2 },
		{ 296, 20, 4 },
		{ 0, 0, 5 },
		{ 0, 0, 6 },
		{ 0, 0, 7 },
		{ 0, 0, 8 },
		{ 0, 0, 9 },
		{ 0, 0, 10 },
		{ 16, 21, 11 },
		{ 16, 18, 12 },
		{ 0, 0, 13 },
		{ 0, 0, 14 },
		{ 0, 20, 15 },
		{ 0, 3, 74 },
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
		{ 0, 41, 28 },
		{ 0, 0, 29 },
		{ 91, 13, 74 },
		{ 298, 112, 74 },
		{ 298, 29, 74 },
		{ 298, 27, 74 },
		{ 278, 82, 74 },
		{ 298, 101, 74 },
		{ 266, 105, 74 },
		{ 296, 184, 74 },
		{ 263, 30, 74 },
		{ 296, 1, 74 },
		{ 267, 261, 74 },
		{ 267, 269, 74 },
		{ 303, 91, 74 },
		{ 224, 242, 74 },
		{ 266, 103, 74 },
		{ 296, 77, 74 },
		{ 278, 84, 74 },
		{ 292, 2, 74 },
		{ 0, 0, 74 },
		{ 90, 227, 3 },
		{ 90, 35, 0 },
		{ 0, 0, 31 },
		{ 0, 0, 32 },
		{ 0, 0, 30 },
		{ 0, 0, 16 },
		{ -56, 2, 33 },
		{ 0, 0, 34 },
		{ 91, 0, 0 },
		{ 269, 143, 0 },
		{ 303, 114, 0 },
		{ 267, 273, 0 },
		{ 303, 1, 0 },
		{ 295, 250, 0 },
		{ 267, 271, 0 },
		{ 278, 1, 0 },
		{ 296, 226, 0 },
		{ 292, 197, 0 },
		{ 233, 214, 0 },
		{ 293, 37, 0 },
		{ 298, 108, 0 },
		{ 233, 215, 0 },
		{ 0, 0, 42 },
		{ 278, 31, 0 },
		{ 108, 217, 0 },
		{ 267, 277, 0 },
		{ 266, 101, 0 },
		{ 292, 199, 0 },
		{ 297, 10, 0 },
		{ 292, 196, 0 },
		{ 293, 33, 0 },
		{ 0, 257, 0 },
		{ 233, 212, 0 },
		{ 296, 228, 0 },
		{ 298, 107, 0 },
		{ 267, 274, 0 },
		{ 297, 9, 0 },
		{ 267, 260, 0 },
		{ 224, 243, 0 },
		{ 90, 0, 0 },
		{ 0, 217, 4 },
		{ -58, 6, 35 },
		{ 296, 240, 0 },
		{ 298, 121, 0 },
		{ 268, 65, 0 },
		{ 295, 248, 0 },
		{ 292, 181, 0 },
		{ 263, 33, 0 },
		{ 303, 132, 0 },
		{ 268, 69, 0 },
		{ 295, 249, 0 },
		{ 303, 131, 0 },
		{ 269, 144, 0 },
		{ 277, 208, 0 },
		{ 267, 263, 0 },
		{ 0, 1, 0 },
		{ 277, 201, 0 },
		{ 296, 238, 0 },
		{ 0, 218, 0 },
		{ 266, 104, 0 },
		{ 267, 278, 0 },
		{ 293, 38, 0 },
		{ 296, 229, 0 },
		{ 233, 210, 0 },
		{ 176, 285, 0 },
		{ 281, 148, 0 },
		{ 281, 155, 0 },
		{ 292, 185, 0 },
		{ 292, 192, 0 },
		{ 298, 120, 0 },
		{ 295, 252, 0 },
		{ 295, 246, 0 },
		{ 293, 39, 0 },
		{ 303, 138, 0 },
		{ 293, 41, 0 },
		{ 303, 127, 0 },
		{ 293, 45, 0 },
		{ 278, 74, 0 },
		{ 278, 78, 0 },
		{ 293, 49, 0 },
		{ 293, 56, 0 },
		{ 268, 70, 0 },
		{ 268, 72, 0 },
		{ 296, 220, 0 },
		{ 266, 102, 0 },
		{ 292, 187, 0 },
		{ 293, 57, 0 },
		{ 296, 236, 0 },
		{ 298, 123, 0 },
		{ 293, 61, 0 },
		{ 176, 283, 0 },
		{ 293, 36, 0 },
		{ 295, 255, 0 },
		{ 263, 34, 0 },
		{ 281, 147, 0 },
		{ 263, 20, 0 },
		{ 296, 230, 0 },
		{ 278, 89, 0 },
		{ 277, 204, 0 },
		{ 292, 188, 0 },
		{ 298, 122, 0 },
		{ 296, 221, 0 },
		{ 267, 268, 0 },
		{ 296, 225, 0 },
		{ 278, 91, 0 },
		{ 281, 152, 0 },
		{ 263, 22, 0 },
		{ 293, 40, 0 },
		{ 268, 71, 0 },
		{ 263, 25, 0 },
		{ 292, 186, 0 },
		{ 277, 206, 0 },
		{ 267, 264, 0 },
		{ 176, 284, 0 },
		{ 267, 265, 0 },
		{ 267, 267, 0 },
		{ 277, 207, 0 },
		{ 0, 0, 67 },
		{ 0, 0, 38 },
		{ 296, 222, 0 },
		{ 268, 64, 0 },
		{ 281, 156, 0 },
		{ 303, 134, 0 },
		{ 233, 213, 0 },
		{ 292, 193, 0 },
		{ 267, 279, 0 },
		{ 0, 1, 0 },
		{ 293, 42, 0 },
		{ 268, 68, 0 },
		{ 267, 262, 0 },
		{ 281, 154, 0 },
		{ 278, 90, 0 },
		{ 295, 253, 0 },
		{ 293, 43, 0 },
		{ 293, 44, 0 },
		{ 263, 27, 0 },
		{ 0, 0, 50 },
		{ 281, 151, 0 },
		{ 303, 136, 0 },
		{ 292, 189, 0 },
		{ 267, 276, 0 },
		{ 281, 153, 0 },
		{ 296, 235, 0 },
		{ 266, 98, 0 },
		{ 278, 76, 0 },
		{ 293, 46, 0 },
		{ 0, 0, 64 },
		{ 0, 0, 36 },
		{ 269, 142, 0 },
		{ 303, 130, 0 },
		{ 281, 149, 0 },
		{ 0, 0, 62 },
		{ 295, 254, 0 },
		{ 292, 182, 0 },
		{ 292, 183, 0 },
		{ 293, 47, 0 },
		{ 278, 83, 0 },
		{ 298, 119, 0 },
		{ 293, 48, 0 },
		{ 268, 66, 0 },
		{ 292, 191, 0 },
		{ 296, 239, 0 },
		{ 0, 2, 0 },
		{ 293, 50, 0 },
		{ 303, 129, 0 },
		{ 298, 114, 0 },
		{ 0, 0, 65 },
		{ 296, 224, 0 },
		{ 293, 51, 0 },
		{ 292, 1, 0 },
		{ 293, 52, 0 },
		{ 293, 53, 0 },
		{ 278, 75, 0 },
		{ 267, 270, 0 },
		{ 0, 244, 0 },
		{ 267, 272, 0 },
		{ 296, 231, 0 },
		{ 296, 233, 0 },
		{ 267, 275, 0 },
		{ 293, 54, 0 },
		{ 0, 0, 37 },
		{ 293, 55, 0 },
		{ 298, 116, 0 },
		{ 0, 211, 0 },
		{ 0, 0, 63 },
		{ 267, 259, 0 },
		{ 303, 128, 0 },
		{ 0, 0, 44 },
		{ 298, 117, 0 },
		{ 298, 118, 0 },
		{ 0, 0, 55 },
		{ 0, 0, 68 },
		{ 0, 0, 70 },
		{ 292, 190, 0 },
		{ 269, 141, 0 },
		{ 278, 79, 0 },
		{ 0, 0, 48 },
		{ 267, 266, 0 },
		{ 0, 0, 51 },
		{ 277, 203, 0 },
		{ 296, 227, 0 },
		{ 278, 80, 0 },
		{ 0, 0, 61 },
		{ 278, 81, 0 },
		{ 0, 0, 59 },
		{ 0, 0, 60 },
		{ 266, 108, 0 },
		{ 0, 0, 66 },
		{ 292, 198, 0 },
		{ 303, 137, 0 },
		{ 277, 202, 0 },
		{ 266, 109, 0 },
		{ 0, 0, 41 },
		{ 0, 31, 0 },
		{ 303, 126, 0 },
		{ 298, 115, 0 },
		{ 0, 99, 0 },
		{ 0, 280, 0 },
		{ 0, 67, 0 },
		{ 0, 145, 0 },
		{ 0, 0, 54 },
		{ 0, 0, 56 },
		{ 296, 223, 0 },
		{ 0, 0, 58 },
		{ 0, 1, 0 },
		{ 0, 0, 49 },
		{ 293, 58, 0 },
		{ 0, 205, 0 },
		{ 0, 88, 0 },
		{ 0, 0, 43 },
		{ 303, 133, 0 },
		{ 0, 150, 0 },
		{ 293, 59, 0 },
		{ 0, 0, 71 },
		{ 0, 0, 69 },
		{ 303, 135, 0 },
		{ 296, 232, 0 },
		{ 0, 0, 52 },
		{ 292, 194, 0 },
		{ 295, 247, 0 },
		{ 0, 0, 45 },
		{ 296, 234, 0 },
		{ 0, 195, 0 },
		{ 0, 60, 0 },
		{ 0, 0, 40 },
		{ 0, 251, 0 },
		{ 0, 237, 0 },
		{ 0, 11, 0 },
		{ 0, 124, 0 },
		{ 0, 0, 57 },
		{ 0, 0, 39 },
		{ 0, 0, 53 },
		{ 0, 0, 46 },
		{ 0, 139, 0 },
		{ 0, 0, 47 }
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
		0
	};
	yybackup = backup;
}
