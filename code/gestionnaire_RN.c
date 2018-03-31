#include <math.h>
#include "gestionnaire_RN.h"


void MultiplicationMatricielle(float** in_M1, float** in_M2, float** out, int taille_M1,int taille_M2,int taille_M3)
{
	int i,j,k; 
	
	for(i=0;i<taille_M1;i++) //taille_M1 nbr de lignes de la 1ere matrice
	{
		for(j=0;j<taille_M2;j++)  // taille_M2 nbr de colonnes de la seconde matrice
		{
			out[i][j]=0;
			for(k=0;k<taille_M3;k++) // taille_M3 dimenssion commune aux deux matrices (obligatoire)
			{
				out[i][j] += in_M1[i][k] * in_M2[k][j];
				//[ligne][colonne]
			}
		}
	}
}


void AdditionVecteurVecteur(float* in_V1, float* in_V2, float* out, int taille)
{
	int i; 
	
	for(i=0;i<taille;i++)
	{
		out[i] = in_V1[i] + in_V2[i];
	}
}

//sigmoide appliquée a un vecteur
void SigmoideV(float* in, float* out, int taille)
{
	int i; 
	
	for(i=0;i<taille;i++)
	{
		out[i]=Sigmoide(in[i]);
	}
}

float Sigmoide(float in)
{   
	float expo = (float)exp(-in);
	return 1/(1+expo);
}

void Traitement(Image* a, RN b)//juste un test
{
	
}
