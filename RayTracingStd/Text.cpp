///Adapté de PoVRAY

#include "stdio.h"
#include "BaseGeometry.h"
#include "Text.h"
#include "BaseIntersection.h"
#include "Ray.h"
#include "Constants.h"
#include "TraceService.h"

CText::CText()
{
	m_DistanceTolerance=EPSILON;
	m_Offset=CVector(0,0,0);
}

CText::CText(const std::string& font,const std::string &text)
{
	m_FontName=font;
	m_Text=text;
	m_DistanceTolerance=EPSILON;
	m_Offset=CVector(0,0,0);
	Init();
}


CText::~CText()
{
	std::vector<CTextChar*>::iterator i;
	for(i=m_ListText.begin();i!=m_ListText.end();i++)
	{
		CTextChar *pChar=(*i);
		pChar->Release();
	}
}

void	CText::Init()
{
	CreateObjectText(m_FontName,m_Text);

	std::vector<CTextChar*>::iterator i;
	for(i=m_ListText.begin();i!=m_ListText.end();i++)
	{
		CTextChar *pChar=(*i);

		//Init des matières
		pChar->SetMatiere(GetMatiere());
		pChar->AddRef();
	}

	Center();
	ComputeBoundingBox();
}

void	CText::Center()
{
	//Calcul le vecteur de translate
	CVector vTranslate=-(m_FinalOffset/2.0);

	//Déplace les caractères
	std::vector<CTextChar*>::iterator i;
	for(i=m_ListText.begin();i!=m_ListText.end();i++)
	{
		CTextChar *pChar=(*i);

		//Init des matières
		pChar->Translate(vTranslate);
	}
}

void	CText::ComputeBoundingBox()
{
	CCoord FinalMin(MAX_DISTANCE,MAX_DISTANCE,MAX_DISTANCE);
	CCoord  FinalMax(-MAX_DISTANCE,-MAX_DISTANCE,-MAX_DISTANCE);

	std::vector<CTextChar*>::iterator i;
	for(i=m_ListText.begin();i!=m_ListText.end();i++)
	{
		CCoord Min;
		CCoord Max;
		CTextChar *pChar=(*i);

		//Init des matières
		pChar->ComputeBoundingBox(Min,Max);
		FinalMin.SetMin(Min);
		FinalMax.SetMax(Max);
	}

	_TRACE_INFO(_STR("FinalMin :  %.3f - %.3f - %.3f",FinalMin.m_Value[0],FinalMin.m_Value[1],FinalMin.m_Value[2]));
	_TRACE_INFO(_STR("FinalMax :  %.3f - %.3f - %.3f",FinalMax.m_Value[0],FinalMax.m_Value[1],FinalMax.m_Value[2]));
	m_BoundingBox=CBox(FinalMin,FinalMax);
	//m_BoundingBox.SetTrans(GetTrans());
}


CText&	CText::operator=(CText	&Origin)
{
	std::vector<CTextChar*>::iterator i;
	for(i=Origin.m_ListText.begin();i!=Origin.m_ListText.end();i++)
	{
		CTextChar *pChar=(*i);
		m_ListText.push_back(pChar);
		pChar->AddRef();
	}

	m_BoundingBox=Origin.m_BoundingBox;

	return (*this);
}


/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec un plan
bool	CText::Intersection(CRay &Ray)
{ 
	bool Flag=false;

	if(m_BoundingBox.Intersection(Ray,false))
	{
		//_FTRACE("Intersection","CText");


		std::vector<CTextChar*>::iterator i;
		for(i=m_ListText.begin();i!=m_ListText.end();i++)
		{
			CTextChar *pChar=(*i);
			if(pChar!=NULL)
				Flag=pChar->Intersection(Ray);	
		}
	}

  return Flag;
}

bool CText::AddIntersect(CRay &Ray,double Distance)
{
	return false;
}

//////////////////////////////////////////
//Normal au plan ---> coefficients directeurs sans la constante
CVector	CText::Normal(const CCoord &coord)
{
	//return(m_Coeff);
	return CVector(0,0,0);
}



void	CText::GetOutputStream(ostream &o)
{
}

void CText::ForceEqual(CBaseGeometry &Origin)
{
	CText *pTrueOrigin=static_cast<CText*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

CBaseGeometry*	CText::Instantiate()
{
	return new CText;
}


//*********************************************
//cf POVRAY
void	CText::CreateObjectText(const std::string& font,const std::string &text)
{
	CTextFont	Font(font);

	if(!Font.GetExistFont()) return;	//si pas de fonte pas de création des objets

	m_FinalOffset=CVector(0,0,0);

	unsigned int last_index=0;
	unsigned int glyph_index;
	double		funit_size;


	//Pour chaque lettre de la chaine --> construction d'un objet
	for(int i=0;i<text.size();i++)
	{
		unsigned char	caract=text[i];

		CTextChar	*pChar=new CTextChar;
		pChar->ProcessCharacter(caract,Font,glyph_index);

		//Calcul de l'espacement entre les caractères
		if(i==0)
		{
			//Le premier caractère
			funit_size = 1.0 / Font.GetUnitsPerEm();

			m_FinalOffset.SetX(-pChar->GetGlyph().header.xMin*funit_size);
			pChar->Translate(m_FinalOffset);

			m_FinalOffset.SetX((Font.GetCurrentFont().hmtx_table[pChar->GetGlyph().myMetrics].advanceWidth -
								Font.GetCurrentFont().hmtx_table[pChar->GetGlyph().myMetrics].lsb) * funit_size);

		} else {
			//Les autres caractères
			  short kern_value_x=0; short kern_value_y=0;
			  short kern_value_min_x=-Font.GetUnitsPerEm();
			  short kern_value_min_y=-Font.GetUnitsPerEm();

			  CVector CharOffset(0,0,0);

			  for (int j = 0; j < Font.GetCurrentFont().kerning_tables.nTables; j++)
			  {

				CKernStruct *table = Font.GetCurrentFont().kerning_tables.tables;
				unsigned short coverage = table->coverage;

				if (!(coverage & KERN_HORIZONTAL))
				  continue;

				for (int k = 0; k < table[j].nPairs; k++)
				{
				  if (table[j].kern_pairs[k].left == last_index &&
					  table[j].kern_pairs[k].right == pChar->GetGlyph().myMetrics)
				  {
					if (coverage & KERN_MINIMUM)
					{
					  if (coverage & KERN_CROSS_STREAM)
						kern_value_min_y = table[j].kern_pairs[k].value;
					  else
						kern_value_min_x = table[j].kern_pairs[k].value;
					}
					else
					{
					  if (coverage & KERN_CROSS_STREAM)
					  {
						if (table[j].kern_pairs[k].value == 0x8000)
						{
						  kern_value_y = 0;
						}
						else
						{
						  if (coverage & KERN_OVERRIDE)
							kern_value_y = table[j].kern_pairs[k].value;
						  else 
							kern_value_y += table[j].kern_pairs[k].value;
						}
					  }
					  else
					  {
						if (coverage & KERN_OVERRIDE)
						  kern_value_x = table[j].kern_pairs[k].value;
						else 
						  kern_value_x += table[j].kern_pairs[k].value;
					  }
					}
					break;
				  }
				  /* Abort now if we have passed all potential matches */
				  else if (table[j].kern_pairs[k].left > last_index)
				  {
					break;
				  }
				}
			  }

		  kern_value_x = (kern_value_x > kern_value_min_x ?
						  kern_value_x : kern_value_min_x);
		  kern_value_y = (kern_value_y > kern_value_min_y ?
						  kern_value_y : kern_value_min_y);

		  CharOffset.SetX(m_FinalOffset.GetX() + (Font.GetCurrentFont().hmtx_table[pChar->GetGlyph().myMetrics].lsb -
						 pChar->GetGlyph().header.xMin + kern_value_x) * funit_size);

		  CharOffset.SetY(m_FinalOffset.GetY() + kern_value_y * funit_size);

		  pChar->Translate(CharOffset);

		  m_FinalOffset.m_Value[0]+=(Font.GetCurrentFont().hmtx_table[pChar->GetGlyph().myMetrics].advanceWidth + kern_value_x) * funit_size;

		}

		m_FinalOffset=m_FinalOffset+m_Offset;

		m_ListText.push_back(pChar);

		last_index = glyph_index;

	}	///Fin boucle de toutes les lettres

}


void	CText::Scale(const CVector &vect)
{
	std::vector<CTextChar*>::iterator i;
	for(i=m_ListText.begin();i!=m_ListText.end();i++)
	{
		CTextChar *pChar=(*i);
		pChar->Scale(vect);
	}

	ComputeBoundingBox();
}

void	CText::Rotate(const CVector &vect)
{
	std::vector<CTextChar*>::iterator i;
	for(i=m_ListText.begin();i!=m_ListText.end();i++)
	{
		CTextChar *pChar=(*i);
		pChar->Rotate(vect);
	}

	ComputeBoundingBox();
}

void	CText::Translate(const CVector &vect)
{
	std::vector<CTextChar*>::iterator i;
	for(i=m_ListText.begin();i!=m_ListText.end();i++)
	{
		CTextChar *pChar=(*i);
		pChar->Translate(vect);
	}

	ComputeBoundingBox();
}
