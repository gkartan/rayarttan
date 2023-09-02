%{
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
%}

// include file
%include {
// forward references
class CDerivateFileLexer;
class CDerivateFileParser;
}

%name CDerivateFileLexer

// class definition
{
// Attributes
private:
	CDerivateFileParser *m_pParser;
public:
	void   Create(CDerivateFileParser *Parser);
}


DIGIT       [0-9]
ALPHA       [a-zA-Z]
ALPHANUM    {ALPHA}|{DIGIT}

EXPFIELD    ([Ee][+-]?[0-9]+)

IDENTIFIER  ({ALPHA}|"_")({ALPHANUM}|"_")*

%%
"-"								{return DASH_TOKEN;}
"+"								{return PLUS_TOKEN;}

{DIGIT}+"."{DIGIT}*				{return FLOAT_TOKEN;}
{DIGIT}+{EXPFIELD}?				{return FLOAT_TOKEN;}

"{"			{return LEFT_CURLY_TOKEN;}
"}"			{return RIGHT_CURLY_TOKEN;}

"("			{return LEFT_PAREN_TOKEN;}
")"			{return RIGHT_PAREN_TOKEN;}

"["			{return LEFT_SQUARE_TOKEN;}
"]"			{return RIGHT_SQUARE_TOKEN;}

"<"			{return LEFT_ANGLE_TOKEN;}
">"			{return RIGHT_ANGLE_TOKEN;}

"|"         {return BAR_TOKEN;}
"~"			{return TILDE_TOKEN;}
"!"			{return EXCLAMATION_TOKEN;}
"@@"        {return AT_TOKEN;}
"$"			{return DOLLAR_TOKEN;}
"%"			{return PERCENT_TOKEN;}
"^"			{return HAT_TOKEN;}
"&"			{return AMPERSAND_TOKEN;}
"*"			{return STAR_TOKEN;}
","			{return COMMA_TOKEN;}
";"			{return SEMI_COLON_TOKEN;}
":"			{return COLON_TOKEN;}
"`"			{return BACK_QUOTE_TOKEN;}
"="			{return EQUALS_TOKEN;}
"?"			{return QUESTION_TOKEN;}
"/"			{return SLASH_TOKEN;}
\\			{return BACK_SLASH_TOKEN;}

"!="        {return REL_NE_TOKEN;}
"<="        {return REL_LE_TOKEN;}
">="        {return REL_GE_TOKEN;}

"//".*      {} 
"/*"        {
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
			}
            

\".+\"				{return STRING_LITERAL_TOKEN;}

"camera"			{ return CAMERA_TOKEN;		}
"fractal"			{ return FRACTAL_TOKEN;		}
"plane"				{ return PLANE_TOKEN;		}
"orthographic"		{ return ORTHOGRAPHIC_TOKEN;}
"perspective"		{ return PERSPECTIVE_TOKEN; }
"location"			{ return LOCATION_TOKEN;	}
"up"				{ return UP_TOKEN;			}
"direction"			{ return DIRECTION_TOKEN;	}
"look_at"			{ return LOOK_AT_TOKEN;		}
"quaternion"		{ return QUATERNION_TOKEN;	}
"hypercomplex"		{ return HYPERCOMPLEX_TOKEN;} 
"max_iteration"		{ return MAX_ITERATION_TOKEN;}
"bailout"			{ return BAILOUT_TOKEN;		}
"precision"			{ return PRECISION_TOKEN;	}
"angle"				{ return ANGLE_TOKEN;		}
"ambient"			{ return AMBIENT_TOKEN;		}
"pointlight"		{ return POINTLIGHT_TOKEN;	}
"light_source"		{ return LIGHT_SOURCE_TOKEN;}
"#declare"			{ return DECLARE_TOKEN;		}
"diffuse"			{ return DIFFUSE_TOKEN;		}
"specular"			{ return SPECULAR_TOKEN;	}
"transparent"		{ return TRANSPARENT_TOKEN;	}
"color_map"			{ return COLOR_MAP_TOKEN;	}
"texture"			{ return TEXTURE_TOKEN;		}
"granite"			{ return GRANITE_TOKEN;		}
"spotted"			{ return SPOTTED_TOKEN;		}
"finish"			{ return FINISH_TOKEN;		}
"pigment"			{ return PIGMENT_TOKEN;		}
"width"				{ return WIDTH_TOKEN;		}
"height"			{ return HEIGHT_TOKEN;		}
"constant"			{ return CONSTANT_TOKEN;	}
"focus"				{ return FOCUS_TOKEN;		}
"display"			{ return DISPLAY_TOKEN;		}
"algorithm"			{ return ALGORITHM_TOKEN;	}
"default"			{ return DEFAULT_TOKEN;		}
"antialias"			{ return ANTIALIAS_TOKEN;	}
"width"				{ return WIDTH_TOKEN;		}
"height"			{ return HEIGHT_TOKEN;		}
.					{ ; }

%%

void   CDerivateFileLexer::Create(CDerivateFileParser *Parser)
{
	yycreate(Parser);
	m_pParser=Parser;
}