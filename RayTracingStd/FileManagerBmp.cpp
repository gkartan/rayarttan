#pragma warning(disable : 4786)

#include <stdio.h>
#include "BaseFileManager.h"
#include "FileManagerBmp.h"
#include "Structures.h"

CFileManagerBmp::CFileManagerBmp()
{
}

CFileManagerBmp::~CFileManagerBmp()
{
}


bool CFileManagerBmp::Write()
{

  FILE *         fichier; // Handle du fichier
  S_BMP_Header * header;  // Header du fichier BMP

  fichier = fopen(m_name,"wb");
  if(!fichier)
  {
    fprintf(stderr,"Impossible de sauver l'image %s\n",m_name);
	return false;
  }

  // Renseignement et ecriture du header
  header=(S_BMP_Header *)malloc(sizeof(S_BMP_Header));
  header->signature=0x4D42;
  header->taille_fichier=m_Width*m_Height*sizeof(S_RVB)*sizeof(header);
  header->reserv_1=0;
  header->reserv_2=0;
  header->decalage=54;
  header->taille_chunk=40;
  header->largeur=m_Width;
  header->hauteur=m_Height;
  header->nb_plans=1;
  header->nb_bits=24;
  header->compression=0;
  header->taille_X=0;
  header->XPM=0;
  header->YPM=0;
  header->Nb_Clr=0;
  header->Clr_Imprt=0;

/*  if (gethostsex()==BIGENDIAN) ///autres machines que x86
  {
    // La machine utilise une representation des nombres inversee par rapport a celle utilisee dans le format BMP
    header->signature     =swap_half(header->signature);
    header->taille_fichier=swap_word(header->taille_fichier);
    header->reserv_1      =swap_half(header->reserv_1);
    header->reserv_2      =swap_half(header->reserv_2);
    header->decalage      =swap_word(header->decalage);
    header->taille_chunk  =swap_word(header->taille_chunk);
    header->largeur       =swap_word(header->largeur);
    header->hauteur       =swap_word(header->hauteur);
    header->nb_plans      =swap_half(header->nb_plans);
    header->nb_bits       =swap_half(header->nb_bits);
    header->compression   =swap_word(header->compression);
    header->taille_X      =swap_word(header->taille_X);
    header->XPM           =swap_word(header->XPM);
    header->YPM           =swap_word(header->YPM);
    header->Nb_Clr        =swap_word(header->Nb_Clr);
    header->Clr_Imprt     =swap_word(header->Clr_Imprt);
  }*/
  fwrite(((byte *)header)+2,54,1,fichier);
  free(header);

  // On cree un buffer de codage des couleurs de ligne
  S_RVB * buffer=(S_RVB *)malloc(sizeof(S_RVB)*m_Width);

  ///Faire double boucle sur matrice image
  /* read it out */
  int x=0;
  int index=0;
  for (ColorMatrix::iterator i = m_Image.begin(); i != m_Image.end(); ++i) 
  {
	x=0;
	for (ColorMatrix::OneD::iterator j = (*i).begin(); j != (*i).end(); ++j) 
	{
		CBaseColor<unsigned char>	*pColorPixel=*j;
		buffer[x].r=pColorPixel->GetBlue();
		buffer[x].v=pColorPixel->GetGreen();
		buffer[x].b=pColorPixel->GetRed();

		x++;
	}
	index++;
	fwrite(buffer,sizeof(S_RVB),m_Width,fichier);
  }

  // On libere le buffer
  free(buffer);

  fclose(fichier);

  return true;
}