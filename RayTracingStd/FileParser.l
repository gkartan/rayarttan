%{
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
%}

// include file
%include {
// forward references
class CFileLexer;
class CFileParser;
}

%name CFileLexer

// class definition
{
// Attributes
private:
	CFileParser *m_pParser;
public:
	void   Create(CFileParser *Parser);
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
"spheric"			{ return SPHERIC_TOKEN;		}
"superellipsoid"	{ return SUPERELLIPSOID_TOKEN;}
"location"			{ return LOCATION_TOKEN;	}
"up"				{ return UP_TOKEN;			}
"direction"			{ return DIRECTION_TOKEN;	}
"look_at"			{ return LOOK_AT_TOKEN;		}
"quaternion"		{ return QUATERNION_TOKEN;	}
"hypercomplex"		{ return HYPERCOMPLEX_TOKEN;	  }
"algebra01"			{ return HYPERCOMPLEXEXOT01_TOKEN;} 
"algebra02"			{ return HYPERCOMPLEXEXOT02_TOKEN;} 
"algebra03"			{ return HYPERCOMPLEXEXOT03_TOKEN;} 
"algebra04"			{ return HYPERCOMPLEXEXOT04_TOKEN;} 
"algebra05"			{ return HYPERCOMPLEXEXOT05_TOKEN;} 
"algebra06"			{ return HYPERCOMPLEXEXOT06_TOKEN;} 
"algebra07"			{ return HYPERCOMPLEXEXOT07_TOKEN;} 
"algebra08"			{ return HYPERCOMPLEXEXOT08_TOKEN;} 
"algebra09"			{ return HYPERCOMPLEXEXOT09_TOKEN;} 
"algebra10"			{ return HYPERCOMPLEXEXOT10_TOKEN;} 
"algebra11"			{ return HYPERCOMPLEXEXOT11_TOKEN;} 
"algebra12"			{ return HYPERCOMPLEXEXOT12_TOKEN;} 
"algebra13"			{ return HYPERCOMPLEXEXOT13_TOKEN;} 
"algebra14"			{ return HYPERCOMPLEXEXOT14_TOKEN;} 
"algebra15"			{ return HYPERCOMPLEXEXOT15_TOKEN;} 
"algebra16"			{ return HYPERCOMPLEXEXOT16_TOKEN;} 
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
"gradient"			{ return GRADIENT_TOKEN;	}
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
"threshold"			{ return THRESHOLD_TOKEN;	}
"depth"				{ return DEPTH_TOKEN;		}
"width"				{ return WIDTH_TOKEN;		}
"height"			{ return HEIGHT_TOKEN;		}
"rotate"			{ return ROTATE_TOKEN;		}
"scale"				{ return SCALE_TOKEN;		}
"translate"			{ return TRANSLATE_TOKEN;	}
"epsilon"			{ return EPSILON_TOKEN;		}
"reflection"		{ return REFLECTION_TOKEN;	}
"image"				{ return IMAGE_TOKEN;		}
"color"				{ return COLOR_TOKEN;		}
"phong_size"		{ return PHONG_SIZE_TOKEN;	}
"derivative"		{ return DERIVATIVE_TOKEN;	}
"sphere"			{ return SPHERE_TOKEN;		}
"interior"			{ return INTERIOR_TOKEN;	}
"ior"				{ return IOR_TOKEN;			}
"dispersion"		{ return DISPERSION_TOKEN;	}
"photons"			{ return PHOTONS_TOKEN;		}
"count"				{ return COUNT_TOKEN;		}
"dispersion_samples"		{ return DISPERSION_SAMPLES_TOKEN;	}
"intensity"			{ return INTENSITY_TOKEN;	}
"probability_reflection"	{ return PROBABILITY_REFLECTION_TOKEN;}
"cylinder"			{ return CYLINDER_TOKEN;}
"cone"				{ return CONE_TOKEN;}
"text"				{ return TEXT_TOKEN;}
"ttf"				{ return TTF_TOKEN;}
.					{ ; }

%%

void   CFileLexer::Create(CFileParser *Parser)
{
	yycreate(Parser);
	m_pParser=Parser;
}