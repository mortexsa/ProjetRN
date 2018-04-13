#ifndef STRUCT_H
#define STRUCT_H

#define debug printf("line : %d in function : %s in file %s\n",__LINE__,__func__,__FILE__);
#define type float

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
	type* A;
	type* B;
	type** W;
	
	type* DELTA;     // Vecteur de modifcation des biais
	type** DELTA_M;  // Matrice de modification des poids
	
	int taille;
		
	struct COUCHE* prec;
	struct COUCHE* suiv;
};
typedef struct COUCHE COUCHE;
typedef COUCHE* Liste_Couche; //jz nz vois pas l'interet du typedef ici

struct INFO_RN
{
	char** etiquettes;
	char* nom;
	char* date;
	int reussite;
	int echec;
};
typedef struct INFO_RN INFO_RN;

struct RN
{
	INFO_RN info;
	Liste_Couche couche_deb;
	Liste_Couche couche_fin;
};
typedef struct RN RN;

#endif
