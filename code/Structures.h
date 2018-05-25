/**
 * \file Structures.h
 * \brief Code contenant les structures utilisées dans le programme.
 * \author PEPIN Thibaut
 * \author REZGUI Soumia
 * \author SLIMANI Arezki
 * \author SELAQUET Severine
 * \author SZULEK Isaac
 * \author MONTIGNET Anthony
 */

#ifndef STRUCT_H
#define STRUCT_H

#define debug printf("line : %d in function : %s in file %s\n",__LINE__,__func__,__FILE__);

/**
 * \struct Pixel
 * \brief definie les composantes rgb d'un pixel
 */
typedef struct Pixel
{
	unsigned char r,g,b;/*!< composante couleur entre 0 et 255 */
} Pixel;

/**
 * \struct Image
 * \brief contient chaque pixel deffinissant une image ainsi que la taille de celle ci
 */
typedef struct Image
{
	int w,h; /*!< taille de l'image */
	Pixel* dat;/*!< tableau contenant les pixels */
} Image;

/**
 * \struct COUCHE
 * \brief decrit une couche d'un réseau de neurone
 */
struct COUCHE
{
	float* A; /*!< vecteur des activation de la couche */
	float* B; /*!< vecteur des biais de la couche */
	float** W; /*!< matrice des poids de la couche */
	
	float* DELTA; /*!< Vecteur de modification des biais */
	float** DELTA_M; /*!< Matrice de modification des poids */
	
	int taille; /*!< nombre de neurone de la couche */
		
	struct COUCHE* prec; /*!< pointeur vers la couche précedente */
	struct COUCHE* suiv; /*!< pointeur vers la couche suivante */
};
typedef struct COUCHE COUCHE;
typedef COUCHE* Liste_Couche;

/**
 * \struct INFO_RN
 * \brief contient les information concernant un réseau de neurones
 */
struct INFO_RN
{
	char** etiquettes; /*!< tableau de chaine de caractères contenant toutes les étiquettes des neurones de la derniere couche d'un réseau de neurones */
	char* nom; /*!< nom du réseau de neurones */
	char* date; /*!< date de création du réseau de neurones */
	char* repertoire; /*!< repertoire ou se situent les exemples d'apprentissage */
	int reussite; /*!< nombre d'image bien reconnue lors de l'apprentissage */
	int echec; /*!< nombre d'image mal reconnue lors de l'apprentissage */
	int w,h; /*!< taille des images acceptées par le réseau de neurones */ //w = largeur, h = hauteur
};
typedef struct INFO_RN INFO_RN;

/**
 * \struct RN
 * \brief defini un réseau de neurones
 */
struct RN
{
	INFO_RN* info; /*!< information du réseau de neurones */
	Liste_Couche couche_deb; /*!< pointeur vers la premiere couche du réseau de neurone */
	Liste_Couche couche_fin; /*!< pointeur vers la derniere couche du réseau de neurone */
};
typedef struct RN RN;

/**
 * \struct Apprentissage
 * \brief regroupe un couple données d'entré et sortie attendue necessaire lors de l'apprentissage
 */
struct Apprentissage
{
	Image* image; /*!< image correspondant a l'étiquette */
	char* etiquette; /*!< étiquette correspondant a l'image */
};
typedef struct Apprentissage App;

#endif
