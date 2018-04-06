#include <math.h>
#include "gestionnaire_RN.h"
#include <string.h>

void MultiplicationMatriceVecteur(float** in_M, float* in_V, float* out, int taille_M1,int taille_M3)
{
	int i,k; 
	
	for(i=0;i<taille_M1;i++) //taille_M1 nbr de lignes de la 1ere matrice
	{
			out[i]=0;
			for(k=0;k<taille_M3;k++) // taille_M3 dimenssion commune aux deux matrices (obligatoire)
			{
				out[i] += in_M[i][k] * in_V[k];
				
			}
	}
}

/*in_V1 vecteur d'activation (l-1*w)
 * in_V2 vecteur des biais de la couche l
 * activation de l
 * */
void AdditionVecteurVecteur(float* in_V1, float* in_V2, float* out ,int taille)
{
	int i; 	
	for(i=0;i<taille;i++)
	{
		out[i] = in_V1[i] + in_V2[i];
	}
}

/*sigmoide appliquée sur un vecteur 
 * AJ=σ(AJ-1*W+b)*/
void SigmoideV(float* in_V, float* out, int taille)
{
	int i; 
	
	for(i=0;i<taille;i++)
	{
		out[i]=Sigmoide(in_V[i]);
	}
}

/*calcul de la sigmoide sur un float*/
float Sigmoide(float in)
{   
	float expo = (float)exp(-in);
	return 1/(1+expo);
}

/*initialisation des champs du reseau de neurones*/
RN* initialisation(INFO_RN info)
{
	
	RN* rn = malloc(sizeof(RN));
	rn->couche_deb=NULL;
	rn->couche_fin=NULL;
	
//remplissage de la structure
	rn->info.etiquettes = info.etiquettes;
	strcpy(rn->info.nom,info.nom);
	strcpy(rn->info.date,info.date);
	rn->info.reussite = info.reussite;
	rn->info.echec = info.echec;	
return rn;	
}
/*void AjoutFin(RN rn, float* b, float** w)
{
	
}

void Traitement(Image* im, RN rn)
{
	
}

char** Reconnaissance(RN rn)
{
	
}
*/
