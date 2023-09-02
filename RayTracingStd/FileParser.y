%{
/* 
 * compilateur d'expression mathematique
 */
#pragma warning(disable : 4530)
#pragma warning(disable : 4006)
#pragma warning(disable : 4005)

#define NOMINMAX 
#include "FrontalCamera.h"
#include "FrontalLight.h"
#include "FrontalMaterial.h"
#include "ListExpr.h"
#include "FileParser.l.h"
#include "Quaternion.h"
#include "HyperComplex.h"
#include "HyperComplexExot01.h"
#include "HyperComplexExot02.h"
#include "HyperComplexExot03.h"
#include "HyperComplexExot04.h"
#include "HyperComplexExot05.h"
#include "HyperComplexExot06.h"
#include "HyperComplexExot07.h"
#include "HyperComplexExot08.h"
#include "HyperComplexExot09.h"
#include "HyperComplexExot10.h"
#include "HyperComplexExot11.h"
#include "HyperComplexExot12.h"
#include "HyperComplexExot13.h"
#include "HyperComplexExot14.h"
#include "HyperComplexExot15.h"
#include "HyperComplexExot16.h"
#include "Fractal.h"
#include "BaseGeometry.h"
#include "TraceService.h"
#include "RenderStructure.h"
#include "Color.h"
#include "Sphere.h"
#include "Box.h"
#include "Torus.h"
#include "Cylinder.h"
#include "Cone.h"
#include "ParserUnDef.h"
#include "Text.h"

%}


%name CFileParser
// class definition
{
public:
	~CFileParser();
// Attributes
private:
	CFileLexer*			m_plexer;
	char				m_value;
	CBaseCamera*		m_pTmpCamera;
	CBaseGeometry*		m_pTmpGeometry;
	CBaseLight*			m_pTmpLight;
	CBaseMatiere*		m_pTmpMatiere;
	CTextureElement*	m_pTmpTexture;
	char				m_tmpStr[255];
	CColor				m_tmpColor;

	CRenderStructure*	m_pRenderStructure;

	int					m_Result;

public:
	void		SetRenderStructure(CRenderStructure*);
	CFileLexer* CreateLexer();
	void		SetValue(char val) {m_value=val;};
	int			GetResult()			{return m_Result;}
}



%token ABS_TOKEN ATAN2_TOKEN CEIL_TOKEN CLOCK_TOKEN COS_TOKEN DEGREES_TOKEN DIV_TOKEN EXP_TOKEN FLOAT_ID_TOKEN
       FLOAT_TOKEN FLOOR_TOKEN INT_TOKEN LOG_TOKEN MAX_TOKEN MIN_TOKEN MOD_TOKEN PI_TOKEN POW_TOKEN RADIANS_TOKEN
       SIN_TOKEN SQRT_TOKEN VDOT_TOKEN VLENGTH_TOKEN VERSION_TOKEN ON_TOKEN OFF_TOKEN TRUE_TOKEN FALSE_TOKEN
       YES_TOKEN NO_TOKEN ACOS_TOKEN ASIN_TOKEN TAN_TOKEN ASC_TOKEN STRLEN_TOKEN VAL_TOKEN FILE_EXISTS_TOKEN
       STRCMP_TOKEN SEED_TOKEN RAND_TOKEN CLOCK_DELTA_TOKEN DIMENSIONS_TOKEN DIMENSION_SIZE_TOKEN DEFINED_TOKEN
       FLOAT_FUNCT_TOKEN VAXIS_ROTATE_TOKEN VCROSS_TOKEN VECTOR_ID_TOKEN VNORMALIZE_TOKEN VROTATE_TOKEN X_TOKEN
       Y_TOKEN Z_TOKEN VECTOR_FUNCT_TOKEN ALPHA_TOKEN BLUE_TOKEN FILTER_TOKEN TRANSMIT_TOKEN GREEN_TOKEN RED_TOKEN
       RGBF_TOKEN RGBFT_TOKEN RGBT_TOKEN RGB_TOKEN COLOUR_KEY_TOKEN COLOR_TOKEN COLOUR_TOKEN COLOUR_ID_TOKEN
       ADAPTIVE_TOKEN AGATE_TOKEN ALL_TOKEN AMBIENT_TOKEN AMPERSAND_TOKEN AREA_LIGHT_TOKEN AT_TOKEN BACK_QUOTE_TOKEN
       BACK_SLASH_TOKEN BAR_TOKEN BICUBIC_PATCH_TOKEN BLOB_TOKEN BOUNDED_BY_TOKEN BOX_TOKEN BOZO_TOKEN BRICK_TOKEN
       BRILLIANCE_TOKEN BUMPS_TOKEN BUMP_MAP_TOKEN BUMP_SIZE_TOKEN CAMERA_ID_TOKEN CAMERA_TOKEN CHECKER_TOKEN
       CLIPPED_BY_TOKEN COLON_TOKEN COLOR_MAP_TOKEN COLOUR_MAP_ID_TOKEN COLOUR_MAP_TOKEN COMMA_TOKEN COMPONENT_TOKEN
       COMPOSITE_TOKEN CONE_TOKEN CRAND_TOKEN CUBIC_TOKEN CYLINDER_TOKEN DASH_TOKEN DECLARE_TOKEN DEFAULT_TOKEN
       DENTS_TOKEN DIFFERENCE_TOKEN DIFFUSE_TOKEN DIRECTION_TOKEN DISC_TOKEN DISTANCE_TOKEN DOLLAR_TOKEN END_OF_FILE_TOKEN
       EQUALS_TOKEN EXCLAMATION_TOKEN FALLOFF_TOKEN FINISH_ID_TOKEN FINISH_TOKEN FLATNESS_TOKEN FOG_TOKEN FREQUENCY_TOKEN
       GIF_TOKEN GRADIENT_TOKEN GRANITE_TOKEN HASH_TOKEN HAT_TOKEN HEIGHT_FIELD_TOKEN HEXAGON_TOKEN IDENTIFIER_TOKEN IFF_TOKEN
       IMAGE_MAP_TOKEN INCLUDE_TOKEN INTERPOLATE_TOKEN INTERSECTION_TOKEN INVERSE_TOKEN IOR_TOKEN JITTER_TOKEN LAMBDA_TOKEN
       LEFT_ANGLE_TOKEN LEFT_CURLY_TOKEN LEFT_PAREN_TOKEN LEFT_SQUARE_TOKEN LEOPARD_TOKEN LIGHT_SOURCE_TOKEN LOCATION_TOKEN
       LOOKS_LIKE_TOKEN LOOK_AT_TOKEN MANDEL_TOKEN MAP_TYPE_TOKEN MARBLE_TOKEN MATERIAL_MAP_TOKEN MAX_INTERSECTIONS_TOKEN
       MAX_TRACE_LEVEL_TOKEN JPG_TOKEN MERGE_TOKEN METALLIC_TOKEN MORTAR_TOKEN NO_SHADOW_TOKEN OBJECT_ID_TOKEN OBJECT_TOKEN
       OCTAVES_TOKEN OMEGA_TOKEN ONCE_TOKEN  ONION_TOKEN PERCENT_TOKEN PHASE_TOKEN PHONG_SIZE_TOKEN PHONG_TOKEN PIGMENT_ID_TOKEN
       PIGMENT_TOKEN PLANE_TOKEN PLUS_TOKEN POINT_AT_TOKEN POLY_TOKEN POT_TOKEN QUADRIC_TOKEN QUARTIC_TOKEN QUESTION_TOKEN
       QUICK_COLOR_TOKEN QUICK_COLOUR_TOKEN RADIAL_TOKEN RADIUS_TOKEN BRICK_SIZE_TOKEN REFLECTION_TOKEN REFRACTION_TOKEN
       RIGHT_ANGLE_TOKEN RIGHT_CURLY_TOKEN RIGHT_PAREN_TOKEN RIGHT_SQUARE_TOKEN RIGHT_TOKEN RIPPLES_TOKEN ROTATE_TOKEN
       ROUGHNESS_TOKEN SCALE_TOKEN SEMI_COLON_TOKEN SINGLE_QUOTE_TOKEN SKY_TOKEN SLASH_TOKEN SMOOTH_TOKEN SMOOTH_TRIANGLE_TOKEN
       SPECULAR_TOKEN SPHERE_TOKEN SPOTLIGHT_TOKEN SPOTTED_TOKEN STAR_TOKEN STRING_LITERAL_TOKEN STURM_TOKEN TEXTURE_ID_TOKEN 
       TEXTURE_TOKEN TGA_TOKEN THRESHOLD_TOKEN TIGHTNESS_TOKEN TILDE_TOKEN TILE2_TOKEN TILES_TOKEN TNORMAL_ID_TOKEN NORMAL_TOKEN
       TORUS_TOKEN TRACK_TOKEN TRANSFORM_ID_TOKEN TRANSFORM_TOKEN TRANSLATE_TOKEN TRIANGLE_TOKEN TURBULENCE_TOKEN TYPE_TOKEN
       UNION_TOKEN UP_TOKEN USE_COLOR_TOKEN USE_COLOUR_TOKEN USE_INDEX_TOKEN U_STEPS_TOKEN V_STEPS_TOKEN WATER_LEVEL_TOKEN
       WAVES_TOKEN WOOD_TOKEN WRINKLES_TOKEN BACKGROUND_TOKEN OPEN_TOKEN AGATE_TURB_TOKEN IRID_TOKEN THICKNESS_TOKEN IRID_WAVELENGTH_TOKEN
       CRACKLE_TOKEN ADC_BAILOUT_TOKEN FILL_LIGHT_TOKEN NUMBER_OF_WAVES_TOKEN FOG_TYPE_TOKEN FOG_ALT_TOKEN FOG_OFFSET_TOKEN
       TEXT_TOKEN TTF_TOKEN REL_GE_TOKEN REL_LE_TOKEN REL_NE_TOKEN APERTURE_TOKEN BLUR_SAMPLES_TOKEN FOCAL_POINT_TOKEN QUILTED_TOKEN 
       CONTROL0_TOKEN CONTROL1_TOKEN RAINBOW_TOKEN SKYSPHERE_TOKEN ANGLE_TOKEN WIDTH_TOKEN ARC_ANGLE_TOKEN 
       PERSPECTIVE_TOKEN ORTHOGRAPHIC_TOKEN FISHEYE_TOKEN ULTRA_WIDE_ANGLE_TOKEN OMNIMAX_TOKEN PANORAMIC_TOKEN LATHE_TOKEN LINEAR_SPLINE_TOKEN 
       QUADRATIC_SPLINE_TOKEN CUBIC_SPLINE_TOKEN BEZIER_SPLINE_TOKEN POLYGON_TOKEN PRISM_TOKEN LINEAR_SWEEP_TOKEN CONIC_SWEEP_TOKEN 
       SOR_TOKEN SPIRAL1_TOKEN SPIRAL2_TOKEN STRENGTH_TOKEN HIERARCHY_TOKEN RAMP_WAVE_TOKEN TRIANGLE_WAVE_TOKEN SINE_WAVE_TOKEN 
       SCALLOP_WAVE_TOKEN PIGMENT_MAP_TOKEN NORMAL_MAP_TOKEN SLOPE_MAP_TOKEN TEXTURE_MAP_TOKEN PIGMENT_MAP_ID_TOKEN NORMAL_MAP_ID_TOKEN 
       SLOPE_MAP_ID_TOKEN TEXTURE_MAP_ID_TOKEN SUPERELLIPSOID_TOKEN QUATERNION_TOKEN CUBE_TOKEN MAX_ITERATION_TOKEN HYPERCOMPLEX_TOKEN
       RAINBOW_ID_TOKEN FOG_ID_TOKEN SKYSPHERE_ID_TOKEN FADE_POWER_TOKEN FADE_DISTANCE_TOKEN TURB_DEPTH_TOKEN PPM_TOKEN 
       PGM_TOKEN AVERAGE_TOKEN MESH_TOKEN WARP_TOKEN OFFSET_TOKEN REPEAT_TOKEN BLACK_HOLE_TOKEN FLIP_TOKEN 
       AMBIENT_LIGHT_TOKEN IF_TOKEN ELSE_TOKEN END_TOKEN SWITCH_TOKEN CASE_TOKEN RANGE_TOKEN WHILE_TOKEN BREAK_TOKEN FALLOFF_ANGLE_TOKEN
       CAUSTICS_TOKEN JULIA_FRACTAL_TOKEN SQR_TOKEN RECIPROCAL_TOKEN STR_TOKEN CONCAT_TOKEN CHR_TOKEN SUBSTR_TOKEN STRING_ID_TOKEN
       WARNING_TOKEN ERROR_TOKEN RENDER_TOKEN STATISTICS_TOKEN DEBUG_TOKEN VARIENCE_TOKEN CONFIDENCE_TOKEN RADIOSITY_TOKEN
       BRIGHTNESS_TOKEN COUNT_TOKEN DISTANCE_MAXIMUM_TOKEN ERROR_BOUND_TOKEN GRAY_THRESHOLD_TOKEN LOW_ERROR_FACTOR_TOKEN MINIMUM_REUSE_TOKEN
       NEAREST_COUNT_TOKEN RECURSION_LIMIT_TOKEN HF_GRAY_16_TOKEN GLOBAL_SETTINGS_TOKEN ECCENTRICITY_TOKEN HOLLOW_TOKEN 
       MEDIA_ATTENUATION_TOKEN MEDIA_INTERACTION_TOKEN MATRIX_TOKEN PERIOD_TOKEN SYS_TOKEN 
       STRUPR_TOKEN STRLWR_TOKEN U_TOKEN V_TOKEN IFDEF_TOKEN PNG_TOKEN PRECISION_TOKEN SLICE_TOKEN ASSUMED_GAMMA_TOKEN 
       ATAN_TOKEN COSH_TOKEN SINH_TOKEN TANH_TOKEN ATANH_TOKEN ACOSH_TOKEN ASINH_TOKEN PWR_TOKEN T_TOKEN 
       IFNDEF_TOKEN MEDIA_TOKEN MEDIA_ID_TOKEN DENSITY_ID_TOKEN DENSITY_TOKEN DENSITY_FILE_TOKEN RATIO_TOKEN 
       SCATTERING_TOKEN EMISSION_TOKEN ABSORPTION_TOKEN SAMPLES_TOKEN INTERVALS_TOKEN INTERIOR_TOKEN INTERIOR_ID_TOKEN 
       LOCAL_TOKEN UNDEF_TOKEN MACRO_TOKEN MACRO_ID_TOKEN PARAMETER_ID_TOKEN ARRAY_TOKEN ARRAY_ID_TOKEN  
       EMPTY_ARRAY_TOKEN  FILE_ID_TOKEN FOPEN_TOKEN FCLOSE_TOKEN WRITE_TOKEN READ_TOKEN 
       APPEND_TOKEN PLANAR_TOKEN SPHERICAL_TOKEN BOXED_TOKEN CYLINDRICAL_TOKEN CUBIC_WAVE_TOKEN POLY_WAVE_TOKEN 
       DENSITY_MAP_TOKEN DENSITY_MAP_ID_TOKEN REFLECTION_EXPONENT_TOKEN DF3_TOKEN EXTINCTION_TOKEN  MATERIAL_TOKEN 
       MATERIAL_ID_TOKEN UV_ID_TOKEN VECTOR_4D_ID_TOKEN DOT_TOKEN ENERGY_TOKEN FRACTAL_TOKEN QUATERNION_TOKEN HYPERCOMPLEX_TOKEN MAX_ITERATION_TOKEN
	   BAILOUT_TOKEN PRECISION_TOKEN ANGLE_TOKEN POINTLIGHT_TOKEN TRANSPARENT_TOKEN WIDTH_TOKEN HEIGHT_TOKEN CONSTANT_TOKEN FOCUS_TOKEN
	   PERSPECTIVE_TOKEN DISPLAY_TOKEN ALGORITHM_TOKEN DEFAULT_TOKEN ANTIALIAS_TOKEN WIDTH_TOKEN HEIGHT_TOKEN
	   HYPERCOMPLEXEXOT01_TOKEN HYPERCOMPLEXEXOT02_TOKEN HYPERCOMPLEXEXOT03_TOKEN HYPERCOMPLEXEXOT04_TOKEN HYPERCOMPLEXEXOT05_TOKEN
	   HYPERCOMPLEXEXOT06_TOKEN HYPERCOMPLEXEXOT07_TOKEN HYPERCOMPLEXEXOT08_TOKEN HYPERCOMPLEXEXOT09_TOKEN HYPERCOMPLEXEXOT10_TOKEN
	   HYPERCOMPLEXEXOT11_TOKEN HYPERCOMPLEXEXOT12_TOKEN HYPERCOMPLEXEXOT13_TOKEN HYPERCOMPLEXEXOT14_TOKEN HYPERCOMPLEXEXOT15_TOKEN HYPERCOMPLEXEXOT16_TOKEN
	   SPHERIC_TOKEN SUPERELLIPSOID_TOKEN EPSILON_TOKEN REFLECTION_TOKEN IMAGE_TOKEN GRADIENT_TOKEN THRESHOLD_TOKEN DEPTH_TOKEN DERIVATIVE_TOKEN
	   IOR_TOKEN DISPERSION_TOKEN DISPERSION_SAMPLES_TOKEN PHOTONS_TOKEN INTENSITY_TOKEN PROBABILITY_REFLECTION_TOKEN CYLINDER_TOKEN TEXT_TOKEN
	   TTF_TOKEN


%type  <fval> fexpr
%type  <fval> double
%type  <fval> double_function
%type  <fval> double_builtin_ident

%type  <ival> bool
%type  <ival> integer
%type  <ival> lexpr
%type  <ival> full_expression

%type  <vval> vector
%type  <vval> vector_literal
%type  <vval> vector_builtin_ident
%type  <vval> vector_function
%type  <vval> vexpr

%type  <qval> quaternion_literal
	   
%left  BAR_TOKEN
%left  AMPERSAND_TOKEN
%left  PLUS_TOKEN  DASH_TOKEN
%left  STAR_TOKEN  SLASH_TOKEN
%left  UMINUS

%start scene

%%
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Start Symbol, general scene format */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
scene :	scene_item			{m_Result=0;}
      |	scene  scene_item	{m_Result=0;}
	  | error				{m_Result=m_plexer->yylineno; yyexit(1);}
      ;

scene_item	:	language_directives
			|	camera
			|	object
			|	texture
			|   display
			|	algorithm
	   //| atmospheric_effects
	   //| global_settings
			;
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Language Directives                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

language_directives : 
					;

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Display Directives                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

display : //DISPLAY_TOKEN LEFT_CURLY_TOKEN WIDTH_TOKEN integer HEIGHT_TOKEN integer RIGHT_CURLY_TOKEN
		  IMAGE_TOKEN LEFT_CURLY_TOKEN WIDTH_TOKEN integer HEIGHT_TOKEN integer RIGHT_CURLY_TOKEN
		  {
			m_pRenderStructure->GetImage()->SetSize($4,$6);
		  }
		;

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Algorithm Directives                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

algorithm :	ALGORITHM_TOKEN	LEFT_CURLY_TOKEN algorithm_item RIGHT_CURLY_TOKEN
		  ;
algorithm_item
	:	DEFAULT_TOKEN		{m_pRenderStructure->SetTypeAlgo(ALGO_NORMAL);}
				|	ANTIALIAS_TOKEN algorithm_modifier_list	{m_pRenderStructure->SetTypeAlgo(ALGO_ANTIALIAS);}
				;

algorithm_modifier_list :
						| algorithm_modifier
						| algorithm_modifier_list algorithm_modifier
						;
algorithm_modifier
	:	THRESHOLD_TOKEN	double {m_pRenderStructure->GetRefStructAlgo().m_Threshold=$2;}
	|	DEPTH_TOKEN integer	   {m_pRenderStructure->GetRefStructAlgo().m_Depth=$2;}
	;
	
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Camera                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
camera	:	CAMERA_TOKEN  LEFT_CURLY_TOKEN  cam_type cam_item_list  RIGHT_CURLY_TOKEN
			{
				m_pRenderStructure->GetFrontalCamera()->SetCamera(m_pTmpCamera);
				m_pTmpCamera=NULL;
			}
		;		

cam_item_list : cam_item
			  | cam_item_list cam_item
			  ;

cam_item : cam_vector
		 | cam_modifier
		 ;

cam_type	: ORTHOGRAPHIC_TOKEN	{m_pTmpCamera=new CCamParalPlane;}
			| PERSPECTIVE_TOKEN		{m_pTmpCamera=new CCamPersPlane;}
			| SPHERIC_TOKEN			{m_pTmpCamera=new CCamSphere;}
			| SUPERELLIPSOID_TOKEN	{m_pTmpCamera=new CCamSuperEllipsoid;}
			;

cam_vector	: LOCATION_TOKEN  vector				{m_pTmpCamera->SetCenter(CVector($2)); }
			| RIGHT_TOKEN  vector					//{ tmpCamera.setRight($2); }
			| UP_TOKEN  vector						{m_pTmpCamera->SetTop(CVector($2)); }
			| DIRECTION_TOKEN  vector				{m_pTmpCamera->SetDirect(CVector($2)); }
			;

cam_modifier	:	LOOK_AT_TOKEN  vector			{m_pTmpCamera->SetLookAt(CCoord($2)); }
				|	WIDTH_TOKEN	   double			{m_pTmpCamera->SetWidth($2);}
				|	HEIGHT_TOKEN   double			{m_pTmpCamera->SetHeight($2);}
				|	FOCUS_TOKEN	   double			{m_pTmpCamera->SetFocal($2);}
				|	ANGLE_TOKEN	   double COMMA_TOKEN double {((CCamSuperEllipsoid*) m_pTmpCamera)->SetAngle($2,$4);}
				|	SCALE_TOKEN	   vector			{((CCamSuperEllipsoid*) m_pTmpCamera)->SetScale(CVector($2));}
				|	EPSILON_TOKEN  double COMMA_TOKEN double {((CCamSuperEllipsoid*) m_pTmpCamera)->SetEpsilon($2,$4);}
				;

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Objects                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



object : finite_solid_object
       | infinite_solid_object
       | finite_patch_object
       | csg_object
       | light_source
       | OBJECT_TOKEN LEFT_CURLY_TOKEN object RIGHT_CURLY_TOKEN 
       ;

csg_object	:
			;

finite_patch_object : 
					;

finite_solid_object : box
					| fractal
					| sphere
					| torus
					| cylinder
					| cone
					| text
					;

infinite_solid_object : plane
					  ;

/*======================*/
/* Finite Patch Objects */
/*----------------------*/


/*======================*/
/* Finite Solid Objects */
/*----------------------*/

/****************sphere***************/
sphere : SPHERE_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN double {m_pTmpGeometry=new CSphere(CCoord($3),$5);}
		 objmods RIGHT_CURLY_TOKEN								{m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);}
	   ;

/****************box******************/
box : BOX_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN vector		{m_pTmpGeometry=new CBox(CCoord($3),CCoord($5));}
	  objmods RIGHT_CURLY_TOKEN									{m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);}
	;

/****************sphere***************/
cylinder : CYLINDER_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN vector COMMA_TOKEN double {m_pTmpGeometry=new CCylinder(CCoord($3),CCoord($5),$7);}
		 objmods RIGHT_CURLY_TOKEN								{m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);}
	   ;

/****************cone***************/
cone : CONE_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN double COMMA_TOKEN
								   vector COMMA_TOKEN double	{m_pTmpGeometry=new CCone(CCoord($3),$5,CCoord($7),$9);}
		 objmods RIGHT_CURLY_TOKEN								{m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);}
	   ;

/****************cone***************/
text : TEXT_TOKEN LEFT_CURLY_TOKEN								{m_pTmpGeometry=new CText;}
		 TTF_TOKEN string										{((CText*) m_pTmpGeometry)->SetFont(std::string(m_tmpStr));}
		 string													{
																	((CText*) m_pTmpGeometry)->SetStr(std::string(m_tmpStr));
																}
		 objmods RIGHT_CURLY_TOKEN								{
		 															((CText*) m_pTmpGeometry)->Init();
																	m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);
																}
	   ;


/***************fractal***************/
fractal : FRACTAL_TOKEN  LEFT_CURLY_TOKEN fractal_type fractal_item_list objmods RIGHT_CURLY_TOKEN
		  {
			  m_pRenderStructure->GetFrontalFractal()->SetFractal((CBaseFractal*) m_pTmpGeometry,false);
			  ///Appel de cette méthode pour initialiser les structures manquantes
			  if(!((CBaseFractal*)m_pTmpGeometry)->GetManualDerivative())
			  {
				m_pRenderStructure->GetFrontalFractal()->ChangeType(((CBaseFractal*) m_pTmpGeometry)->GetAlgebraType(),
																	((CBaseFractal*) m_pTmpGeometry)->GetStrExpr(),
																	((CBaseFractal*) m_pTmpGeometry)->GetOptimisation());
			  } else {
			  	m_pRenderStructure->GetFrontalFractal()->ChangeType(((CBaseFractal*) m_pTmpGeometry)->GetAlgebraType(),
																	((CBaseFractal*) m_pTmpGeometry)->GetStrExpr(),
																	((CBaseFractal*) m_pTmpGeometry)->GetStrExprDerivate(),
																	((CBaseFractal*) m_pTmpGeometry)->GetOptimisation());
			  }

			  m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pRenderStructure->GetFrontalFractal()->GetFractal());
			  m_pTmpGeometry=NULL;
			  _TRACE_INFO("Fractale Ajoutée");
		  }
		;

fractal_item_list : fractal_item
				  | fractal_item_list fractal_item
				  ;

fractal_item : fractal_mod
			 | quaternion_literal	{_TRACE_INFO("Fractal - init value");((CBaseFractal*)m_pTmpGeometry)->SetInitValue(CBaseVector<4,double>($1));}	
			 | string				{_TRACE_INFO("Fractal - string"); ((CBaseFractal*)m_pTmpGeometry)->SetStrExpr(std::string(m_tmpStr));}
			 | DERIVATIVE_TOKEN string {
											((CBaseFractal*)m_pTmpGeometry)->SetStrExprDerivate(std::string(m_tmpStr));
											((CBaseFractal*)m_pTmpGeometry)->SetManualDerivative(true);
									   }
			 ;

fractal_type : QUATERNION_TOKEN		
			   { 
					typedef CQuaternion<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }

			 | HYPERCOMPLEX_TOKEN	
			   {
			   		typedef CHyperComplex<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT01_TOKEN	
			   {
			   		typedef CHyperComplexExot01<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT02_TOKEN	
			   {
			   		typedef CHyperComplexExot02<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT03_TOKEN	
			   {
			   		typedef CHyperComplexExot03<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT04_TOKEN	
			   {
			   		typedef CHyperComplexExot04<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT05_TOKEN	
			   {
			   		typedef CHyperComplexExot05<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT06_TOKEN	
			   {
			   		typedef CHyperComplexExot06<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT07_TOKEN	
			   {
			   		typedef CHyperComplexExot07<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT08_TOKEN	
			   {
			   		typedef CHyperComplexExot08<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT09_TOKEN	
			   {
			   		typedef CHyperComplexExot09<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT10_TOKEN	
			   {
			   		typedef CHyperComplexExot10<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT11_TOKEN	
			   {
			   		typedef CHyperComplexExot11<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT12_TOKEN	
			   {
			   		typedef CHyperComplexExot12<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT13_TOKEN	
			   {
			   		typedef CHyperComplexExot13<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT14_TOKEN	
			   {
			   		typedef CHyperComplexExot14<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT15_TOKEN	
			   {
			   		typedef CHyperComplexExot15<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }
			 | HYPERCOMPLEXEXOT16_TOKEN	
			   {
			   		typedef CHyperComplexExot16<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   }

			 ;

fractal_mod	:	MAX_ITERATION_TOKEN integer	{_TRACE_INFO("Max iteration");	((CBaseFractal*)m_pTmpGeometry)->SetMaxIter($2);}
			|	BAILOUT_TOKEN		double	{_TRACE_INFO("Bailout");		((CBaseFractal*)m_pTmpGeometry)->SetBailout($2);}
			|	PRECISION_TOKEN		double	{_TRACE_INFO("Precision");		((CBaseFractal*)m_pTmpGeometry)->SetNbStep($2);}
			|	ANGLE_TOKEN			double	{_TRACE_INFO("Angle");			((CBaseFractal*)m_pTmpGeometry)->SetAngleDeg($2);}		
			;


/******************torus*********************/
torus : TORUS_TOKEN  LEFT_CURLY_TOKEN vector COMMA_TOKEN double COMMA_TOKEN double {m_pTmpGeometry=new CTorus(CCoord($3),$5,$7);}
		objmods RIGHT_CURLY_TOKEN												 {m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);}
	  ;
/*========================*/
/* Infinite Solid Objects */
/*------------------------*/
plane : PLANE_TOKEN										
	    LEFT_CURLY_TOKEN vector CONSTANT_TOKEN double	{m_pTmpGeometry=new CPlane(CVector($3),$5); _TRACE_INFO("Creation Plan");}
		objmods RIGHT_CURLY_TOKEN						{m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry); _TRACE_INFO("Ajout Plan OK");}
	  |
		PLANE_TOKEN
		LEFT_CURLY_TOKEN vector COMMA_TOKEN vector		{m_pTmpGeometry=new CPlane(CVector($3),CCoord($5)); _TRACE_INFO("Creation Plan");}
		objmods RIGHT_CURLY_TOKEN						{m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry); _TRACE_INFO("Ajout Plan OK");}
	  ;

/*==================================================*/
/* Object Modifiers        */
/*--------------------------------------------------*/
objmods : /* can be empty */
        | objmod
        | objmods objmod
        ;

objmod : //CLIPPED_BY_TOKEN LEFT_CURLY_TOKEN RIGHT_CURLY_TOKEN
       //| CLIPPED_BY_TOKEN LEFT_CURLY_TOKEN BOUNDED_BY_TOKEN RIGHT_CURLY_TOKEN
       //| BOUNDED_BY_TOKEN LEFT_CURLY_TOKEN RIGHT_CURLY_TOKEN
       //| BOUNDED_BY_TOKEN LEFT_CURLY_TOKEN CLIPPED_BY_TOKEN RIGHT_CURLY_TOKEN
       //| NO_SHADOW_TOKEN
       //| INVERSE_TOKEN
       //| STURM_TOKEN bool
       //| HIERARCHY_TOKEN bool
       | interior
	   | photons
       //| material
		| TEXTURE_TOKEN LEFT_CURLY_TOKEN string RIGHT_CURLY_TOKEN	{m_pTmpGeometry->SetMatiere(m_pRenderStructure->GetFrontalMaterial()->GetMaterial(m_tmpStr));}
       //| pigment
       //| normal
       //| finish
        | transformation
       ;

/*==================================================*/
/* Light Source */
/*--------------------------------------------------*/

light_source	: LIGHT_SOURCE_TOKEN  LEFT_CURLY_TOKEN light_type string 	{ m_pTmpLight->SetName(m_tmpStr);}
				  light_position COLOR_TOKEN color							{ m_pTmpLight->SetColor(m_tmpColor);}
				  light_mod_list  RIGHT_CURLY_TOKEN
				  {
					m_pRenderStructure->GetFrontalLight()->AddLight(m_pTmpLight);
					m_pTmpLight=NULL;
					_TRACE_INFO("Light Ok");
				  }
				;

light_position  : /*ambient n'a pas de position*/
				| vector	{((CLightPoint*) m_pTmpLight)->SetPosition(CCoord($1));}
				;

light_mod_list	: light_mod
				| light_mod_list  light_mod
				;

light_mod	: /* list can be empty */
			; 

light_type	: AMBIENT_TOKEN		{m_pTmpLight=new CLightAmbient;}
			| POINTLIGHT_TOKEN	{m_pTmpLight=new CLightPoint;}
			| SPOTLIGHT_TOKEN
			| NO_SHADOW_TOKEN
			| CYLINDER_TOKEN
			;

/*******************************************************************
 **************** Texture
 *******************************************************************/

texture : plain_texture
        | patterned_texture
        | layered_texture
        //| TEXTURE_TOKEN LEFT_CURLY_TOKEN texture RIGHT_CURLY_TOKEN /* for #declare */
        ;

plain_texture : TEXTURE_TOKEN {m_pTmpMatiere=new CBaseMatiere;}
				LEFT_CURLY_TOKEN pnf_items RIGHT_CURLY_TOKEN {m_pRenderStructure->GetFrontalMaterial()->AddMatiere(m_pTmpMatiere); m_pTmpMatiere=NULL;}
              ;

/* PNF_IDENTIFIER: PIGMENT_IDENTIFIER | NORMAL_IDENTIFIER | FINISH_IDENTIFIER */

pnf_items : /* can be empty*/
          | pnf_item
          | pnf_items pnf_item
          ;

pnf_item : pigment
         //| normal
         | finish
         //| transformation
		 | string			{m_pTmpMatiere->SetName(m_tmpStr);}
		 | interior
		 | photons
         ;

patterned_texture : ;
layered_texture : ;

/**===============================*/
//       pigment
//===============================
pigment : PIGMENT_TOKEN LEFT_CURLY_TOKEN pigment RIGHT_CURLY_TOKEN 
		| PIGMENT_TOKEN LEFT_CURLY_TOKEN pig_type pig_mods RIGHT_CURLY_TOKEN
		;

pig_type : /* optional */
         | color
         | pattern_type
		 ;

pig_mods : 
         | pig_mod
         | pig_mods pig_mod
         ;

pig_mod : color_map
		;

color_map : COLOR_MAP_TOKEN {m_pTmpTexture->GetProcedural()->Clear();}
			LEFT_CURLY_TOKEN /* id */ color_map_entries RIGHT_CURLY_TOKEN
		  ;

color_map_entries : color_map_entry
                  | color_map_entries color_map_entry
                  ;

color_map_entry : LEFT_SQUARE_TOKEN double color RIGHT_SQUARE_TOKEN	{m_pTmpTexture->GetProcedural()->SetColor($2,m_tmpColor);}
                ;

pattern_type :	 GRANITE_TOKEN	{CNoise3DGranite *pNoise=new CNoise3DGranite; m_pTmpTexture->ChangeFunctionNoise(pNoise);}
			   | SPOTTED_TOKEN	{CNoise3D *pNoise=new CNoise3D; m_pTmpTexture->ChangeFunctionNoise(pNoise);}
			   | GRADIENT_TOKEN	{			
									CBaseProcedural *pProc=new CProcGradientMatiere;
									m_pTmpTexture->SetProcedural(pProc);
								}
             ;


/* ----------------------------------------------------------------------------------
 * Finish
 */

finish : FINISH_TOKEN LEFT_CURLY_TOKEN finish RIGHT_CURLY_TOKEN
       | FINISH_TOKEN LEFT_CURLY_TOKEN fin_items RIGHT_CURLY_TOKEN
       ;

fin_items : 
          | fin_item
          | fin_items fin_item
          ;

fin_item : AMBIENT_TOKEN color			{m_pTmpMatiere->SetColorAmbient(m_tmpColor);}
         | DIFFUSE_TOKEN color			{m_pTmpMatiere->SetColorDiffuse(m_tmpColor);}
         | SPECULAR_TOKEN color			{m_pTmpMatiere->SetColorSpecular(m_tmpColor);}
		 | TRANSPARENT_TOKEN color		{m_pTmpMatiere->SetColorTransparent(m_tmpColor);}
		 | AMBIENT_TOKEN				{m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);}
		   pigment						{m_pTmpMatiere->SetTexture(TYPE_AMBIENT,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;}
         | DIFFUSE_TOKEN				{m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);}
		   pigment						{m_pTmpMatiere->SetTexture(TYPE_DIFFUSE,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;}
         | SPECULAR_TOKEN				{m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);}
		   pigment						{m_pTmpMatiere->SetTexture(TYPE_SPECULAR,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;}
		 | TRANSPARENT_TOKEN			{m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);}
		   pigment						{m_pTmpMatiere->SetTexture(TYPE_TRANSPARENT,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;}
		 | REFLECTION_TOKEN double		{m_pTmpMatiere->SetReflexion($2);}
		 | PHONG_SIZE_TOKEN double		{
											if(m_pTmpMatiere->GetModelLight()==NULL)
												m_pTmpMatiere->SetModelLight(new CBaseModelLight($2));
											else
												m_pTmpMatiere->GetModelLight()->SetPhongExp($2);
										}
		| TRANSPARENT_TOKEN double		{m_pTmpMatiere->SetTransparency($2);}
         ;

/* ----------------------------------------------------------------------------------
 * Transformation
 */

transformation : tran
               | transformation tran
               ; 

tran : ROTATE_TOKEN vector	{ m_pTmpGeometry->Rotate(CVector($2)); }
     | SCALE_TOKEN vector   { m_pTmpGeometry->Scale(CVector($2)); }
     | TRANSLATE_TOKEN vector { m_pTmpGeometry->Translate(CVector($2)); }
	 ;

/* ----------------------------------------------------------------------------------
 * interior
 */

interior	:	INTERIOR_TOKEN LEFT_CURLY_TOKEN interior_items RIGHT_CURLY_TOKEN
			;

interior_items  :	interior_item
				|	interior_items interior_item
				;
				
interior_item	:	IOR_TOKEN	double	{
											if(m_pTmpMatiere->GetRefDispersion().IsActif())
											{
												m_pTmpMatiere->GetRefDispersion().SetIor($2);
											} else
												m_pTmpMatiere->SetMilieu2($2);
										}
				|	DISPERSION_TOKEN	double	{m_pTmpMatiere->GetRefDispersion().SetDispersionRatio($2);}
				|	DISPERSION_SAMPLES_TOKEN	integer	 {m_pTmpMatiere->GetRefDispersion().SetDispersionSamples($2);}
				;
			
/* ----------------------------------------------------------------------------------
 * photons
 */

photons		:	PHOTONS_TOKEN LEFT_CURLY_TOKEN photons_items RIGHT_CURLY_TOKEN
			;

photons_items  :	photons_item
				|	photons_items photons_item
				;
				
photons_item	:	COUNT_TOKEN	double	{m_pTmpMatiere->GetRefPhotonsParameters().SetCount($2);}
				|	INTENSITY_TOKEN double {m_pTmpMatiere->GetRefPhotonsParameters().SetIntensity($2);}	
				|	PROBABILITY_REFLECTION_TOKEN double {m_pTmpMatiere->GetRefPhotonsParameters().SetProbReflect($2);}
				;


/*================================*/
/* Integer stuff */

integer : double 
        { $$ = (int) $1; }
    ;

/*================================*/
/* double stuff */

double : fexpr;

fexpr : LEFT_PAREN_TOKEN fexpr RIGHT_PAREN_TOKEN
        { $$ = $2; }
      | fexpr  PLUS_TOKEN  fexpr
            { $$ = $1 + $3; }
      | fexpr  DASH_TOKEN  fexpr
            { $$ = $1 - $3; }
      | fexpr  STAR_TOKEN  fexpr
            { $$ = $1 * $3; }
      | fexpr  SLASH_TOKEN fexpr
            { $$ = $1 / $3; }
      | DASH_TOKEN  fexpr      
            { $$ = - $2; }
      | FLOAT_TOKEN
            { char   *string; $$ = (double) strtod(m_plexer->yytext,&string); }
      | PLUS_TOKEN FLOAT_TOKEN
            { $$ = atof(m_plexer->yytext); }
      | double_function 
      | double_builtin_ident
      | LEFT_PAREN_TOKEN full_expression RIGHT_PAREN_TOKEN
            { $$ = (double) $2; }

      ;

double_builtin_ident : CLOCK_TOKEN
            { $$ = 0; /* temp */ }
            | CLOCK_DELTA_TOKEN
                { $$ = 0; /* temp */ }
            | PI_TOKEN
                { $$ = 3.141592654; }
            | VERSION_TOKEN
                { $$ = 4.2; }
            | TRUE_TOKEN
                { $$ = 1; }
            | YES_TOKEN
                { $$ = 1; }
            | ON_TOKEN
                { $$ = 1; }
            | FALSE_TOKEN
                { $$ = 0; }
            | NO_TOKEN
                { $$ = 0; }
            | OFF_TOKEN
                { $$ = 0; }
            ;


double_function : ABS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN
					{ $$ = fabs($3); }
				| ACOS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN
					{ $$ = acos($3); }
				| ASIN_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN
					{ $$ = asin($3); }
				| COS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN
					{ $$ = cos($3); }
               | SIN_TOKEN  LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN
                    { $$ = sin($3); }
               | TAN_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN
                    { $$ = tan($3); }
               | RADIANS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN
                        { $$ = $3 * 0.017453293f; }
			   ;

full_expression : lexpr
            { $$ = $1; } 
        | lexpr QUESTION_TOKEN full_expression COLON_TOKEN full_expression
            { if ($1) $$=$3; else $$=$5; }
        ;

lexpr : LEFT_PAREN_TOKEN lexpr RIGHT_PAREN_TOKEN
        { $$ = $2; }
      | lexpr  BAR_TOKEN lexpr
            { $$ = ($1 || $3); }
      | lexpr  AMPERSAND_TOKEN lexpr
            { $$ = ($1 && $3); }
      | lexpr  LEFT_ANGLE_TOKEN  lexpr
            { $$ = ($1 < $3); }
      | lexpr  RIGHT_ANGLE_TOKEN  lexpr
            { $$ = ($1 > $3); }
      | lexpr  REL_NE_TOKEN  lexpr
            { $$ = ($1 != $3); }
      | lexpr  REL_LE_TOKEN lexpr
            { $$ = ($1 <= $3); }
      | lexpr  REL_GE_TOKEN lexpr
            { $$ = ($1 >= $3); }
      | lexpr  EQUALS_TOKEN lexpr
            { $$ = ($1 == $3); }
      | double
            { $$ = (int) $1; }
      ;
/*================================*/
/* Vector stuff */
vector : double { $$[0] = $1; $$[1] = $1; $$[2] = $1;}
       | vexpr
       ;

vexpr : LEFT_PAREN_TOKEN vexpr RIGHT_PAREN_TOKEN
        { $$[0] = $2[0]; $$[1] = $2[1]; $$[2] = $2[2];}
      | vexpr  PLUS_TOKEN  vexpr
            { $$[0] = $1[0] + $3[0];
              $$[1] = $1[1] + $3[1];
              $$[2] = $1[2] + $3[2];
            }
      | fexpr  PLUS_TOKEN  vexpr
            { $$[0] = $1 + $3[0];
              $$[1] = $1 + $3[1];
              $$[2] = $1 + $3[2];
            }
      | vexpr  DASH_TOKEN  vexpr
            { $$[0] = $1[0] - $3[0];
              $$[1] = $1[1] - $3[1];
              $$[2] = $1[2] - $3[2];
            }
      | fexpr  DASH_TOKEN  vexpr
            { $$[0] = $1 - $3[0];
              $$[1] = $1 - $3[1];
              $$[2] = $1 - $3[2];
            }
            
      | vexpr  STAR_TOKEN  vexpr
            { $$[0] = $1[0] * $3[0];
              $$[1] = $1[1] * $3[1];
              $$[2] = $1[2] * $3[2];
            }
      | fexpr  STAR_TOKEN  vexpr
            { $$[0] = $1 * $3[0];
              $$[1] = $1 * $3[1];
              $$[2] = $1 * $3[2];
            }
      | vexpr  SLASH_TOKEN  vexpr
            { $$[0] = $1[0] / $3[0];
              $$[1] = $1[1] / $3[1];
              $$[2] = $1[2] / $3[2];
            }
      | fexpr  SLASH_TOKEN  vexpr
            { $$[0] = $1 / $3[0];
              $$[1] = $1 / $3[1];
              $$[2] = $1 / $3[2];
            }
      | DASH_TOKEN  vexpr      %prec  UMINUS
            { $$[0] = -$2[0];
              $$[1] = -$2[1];
              $$[2] = -$2[2];
            }
      | vector_literal
      | vector_function
      | vector_builtin_ident
	  | quaternion_literal
   /* | LEFT_PAREN_TOKEN full_expression  RIGHT_PAREN_TOKEN */ 
      ;

vector_literal : LEFT_ANGLE_TOKEN double COMMA_TOKEN double COMMA_TOKEN double RIGHT_ANGLE_TOKEN
            { $$[0] = $2; $$[1] = $4; $$[2] = $6; }
			   ;
        
    
vector_function : VAXIS_ROTATE_TOKEN LEFT_PAREN_TOKEN vector COMMA_TOKEN vector COMMA_TOKEN double RIGHT_PAREN_TOKEN
            | VCROSS_TOKEN LEFT_PAREN_TOKEN vector COMMA_TOKEN vector RIGHT_PAREN_TOKEN
			{ /*CVector v1($3),v2($5);
              //v1 = v1 ^ v2;
              $$[0] = v1[0]; $$[1] = v1[1]; $$[2] = v1[2];     */   
            }
            | VROTATE_TOKEN LEFT_PAREN_TOKEN vector COMMA_TOKEN vector RIGHT_PAREN_TOKEN
			| VNORMALIZE_TOKEN LEFT_PAREN_TOKEN vector RIGHT_PAREN_TOKEN
                        {/* Vector v($3); v.Normalize(); $$[0] = v[0]; $$[1] = v[1]; $$[2] = v[2];*/ } 
			;
vector_builtin_ident : X_TOKEN
            { $$[0] = 1; $$[1] = 0; $$[2] = 0; }
             | Y_TOKEN
                { $$[0] = 0; $$[1] = 1; $$[2] = 0; }
             | Z_TOKEN
                { $$[0] = 0; $$[1] = 0; $$[2] = 1; }
             | T_TOKEN
                { $$[0] = 0; $$[1] = 0; $$[2] = 0; } /* should be 0,0,0,1 */
             | U_TOKEN
                { $$[0] = 1; $$[1] = 0; $$[2] = 0; } /* should be 1,0 */
             | V_TOKEN
                { $$[0] = 0; $$[1] = 1; $$[2] = 0; } /* should be 0,1 */
             ;

quaternion_literal : LEFT_ANGLE_TOKEN double COMMA_TOKEN double COMMA_TOKEN double COMMA_TOKEN double RIGHT_ANGLE_TOKEN
            { $$[0] = $2; $$[1] = $4; $$[2] = $6; $$[3] = $8;}
			   ;


/*================================*/
/* Color stuff */

color : color_body
      | COLOR_TOKEN color_body
      | COLOUR_TOKEN color_body
      | COLOR_TOKEN COLOR_TOKEN color_body // for macros
      ;

color_body : color_vector color_keyword_group
           | color_keyword_group
           ;
     
color_vector :
			   RGB_TOKEN vector
                         { m_tmpColor.SetRGB($2);}

			 
             | vector
                         { m_tmpColor.SetRGB($1);}
/*  | RGBF_TOKEN vector4 */
/*  | RGBT_TOKEN vector4 */
/*  | RGBFT_TOKEN vector5 */
             ;

color_keyword_group :
                    | color_keyword
                    | color_keyword_group color_keyword
                    ;
color_keyword : RED_TOKEN double 
                         { m_tmpColor.SetRed($2);}   
              | BLUE_TOKEN double
                         { m_tmpColor.SetBlue($2);}
              | GREEN_TOKEN double
                         { m_tmpColor.SetGreen($2);}   
              | FILTER_TOKEN double
                         //{ tmpColor.SetFilter($2);}
              | TRANSMIT_TOKEN double
                         //{ tmpColor.SetTransmit($2);}
              ;

/*================================*/
/* String stuff */

string : STRING_LITERAL_TOKEN
         {
			memset(m_tmpStr,'\0',255);
			strncpy(m_tmpStr, m_plexer->yytext+1,
					  strlen(m_plexer->yytext) -2);
		 }

       ;
%%

CFileParser::~CFileParser()
{
}

CFileLexer* CFileParser::CreateLexer()
{
	m_plexer=new CFileLexer;

	if (!yycreate(m_plexer)) {
		return 0;
	}

	m_plexer->Create(this);

	return m_plexer;	// success
}

void		CFileParser::SetRenderStructure(CRenderStructure* pRender)
{
	m_pRenderStructure=pRender;
}


