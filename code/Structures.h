#ifndef STRUCT_H
#define STRUCT_H

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
	
	float* DELTA;     // Vecteur de modifcation des biais
	float** DELTA_M;  // Matrice de modification des poids
	
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
