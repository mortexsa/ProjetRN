#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "Apprentissage.h"

//calcul de l'erreur 

float* fct_cout(RN rn ,char* eti)
{	
	float* errtmp = malloc(rn.couche_fin->taille*sizeof(float));	

	for(int i=0;i<rn.couche_fin->taille;i++)
	{
		errtmp[i] = (rn.couche_fin->A[i] - ((strcmp(eti,rn.info.etiquettes[i]))==0)?1:0);	
	}
	
	return errtmp;
}
	
void BackProp(RN* rn, Image* im,char* sortie_att)
{
	Traitement(im, *rn);
	char** sortie_calc = Reconnaissance(*rn);
	
	if(strcmp(sortie_calc[0],sortie_att)==0)
		rn->info.reussite++;
	else
		rn->info.echec++;
	
	float* cout = fct_cout(*rn, sortie_att);
}

/*void SigmoideDER(float* in, float* out, int taille)
{
	int i;
	float sig;
	
	for(i=0;i<taille;i++)
	{
		sig = Sigmoide(in[i]);
		out[i] = sig*(1-sig);
	}
}*/

/*void SigmoideINV(float* in, float* out, int taille)
{
	int i;
	double tmp;
	
	for(i=0;i<taille;i++)
	{
		tmp = -log(1/in[i] - 1);
		out[i] = (float)tmp;
	}
}*/

void MultiplicationMatricielleTransposee(float** in_M1, float** in_M2, float** out, int taille_M1,int taille_M2,int taille_M3) // = (in_M1)T * in_M2
{
	int i,j,k; 
	
	for(i=0;i<taille_M1;i++) //taille_M1 nbr de colonnes de la 1ere matrice
	{
		for(j=0;j<taille_M2;j++)  // taille_M2 nbr de colonnes de la seconde matrice
		{
			out[i][j]=0;
			for(k=0;k<taille_M3;k++) // taille_M3 dimenssion commune aux deux matrices (obligatoire)
			{
				out[i][j] += in_M1[k][i] * in_M2[k][j];
				//[ligne][colonne]
			}
		}
	}
}

void Hadamard(float* in_a, float* in_b, float* out, int taille)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		out[i] = in_a[i]*in_b[i];
	}
}
