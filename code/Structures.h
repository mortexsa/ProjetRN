#ifndef STRUCT_H
#define STRUCT_H

#define debug printf("line : %d in function : %s in file %s\n",__LINE__,__func__,__FILE__);

//#define float float

typedef struct Pixel
{
	unsigned char r,g,b;
} Pixel;

typedef struct Image
{
	int w,h;
	Pixel* dat;
} Image;

struct COUCHE
{
	float* A;
	float* B;
	float** W;
	
	float* DELTA;     // Vecteur de modification des biais
	float** DELTA_M;  // Matrice de modification des poids
	
	int taille;
		
	struct COUCHE* prec;
	struct COUCHE* suiv;
};
typedef struct COUCHE COUCHE;
typedef COUCHE* Liste_Couche;

struct INFO_RN
{
	char** etiquettes;
	char* nom;
	char* date;
	char* repertoire;
	int reussite;
	int echec;
	int w,h;
};
typedef struct INFO_RN INFO_RN;

struct RN
{
	INFO_RN info;
	Liste_Couche couche_deb;
	Liste_Couche couche_fin;
};
typedef struct RN RN;

struct Apprentissage
{
	Image* image;
	char* etiquette;
};
typedef struct Apprentissage App;

#endif
