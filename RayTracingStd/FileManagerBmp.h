/////Etat classe : VALIDE

struct S_BMP_Header
{
  unsigned short	Dummy;          // On est oblige de tenir compte de ce Word excessif car de toutes manieres le compilateur en cree un
  unsigned short	signature;      // =0x4D42
  unsigned int		taille_fichier; // Taille du fichier
  unsigned short	reserv_1;       // =0
  unsigned short	reserv_2;       // =0
  unsigned int		decalage;       // Nb d'octets avant les donnees bitmap
  unsigned int		taille_chunk;   // Taille du descriptif d'image (=40)
  unsigned int		largeur;        // Largeur de l'image
  unsigned int		hauteur;        // Hauteur de l'image
  unsigned short	nb_plans;       // Nombre de plans (=1)
  unsigned short	nb_bits;        // Nombre de bits par pixel (=24)
  unsigned int		compression;    // Utilisation d'une compression (=0)
  unsigned int		taille_X;
  unsigned int		XPM;
  unsigned int		YPM;
  unsigned int		Nb_Clr;
  unsigned int		Clr_Imprt;
};

class CFileManagerBmp: public CBaseFileManager
{
// Construction
public:
	CFileManagerBmp();

// Attributes
protected:

// Operations
public:
	virtual bool	Write();

// Implementation
public:
	virtual ~CFileManagerBmp();

	// Generated message map functions
protected:
};

