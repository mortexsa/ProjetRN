#include "test.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>



void fct_cout(RN rn ,char* eti)
{	
	for(int i=0;i<rn.couche_fin->taille;i++)
	{
		rn.couche_fin->DELTA[i] = (rn.couche_fin->A[i] - ((strcmp(eti,rn.info.etiquettes[i]))==0)?1:0);	
	}
}
	
void BackProp(RN* rn, char* sortie_att)
{
	COUCHE* tmp = rn->couche_fin;
	
	//Traitement(im, *rn);
	//char** sortie_calc = Reconnaissance(*rn);
	
	/*if(strcmp(sortie_calc[0],sortie_att)==0)
		rn->info.reussite++;
	else
		rn->info.echec++;*/
	
	//float* cout = fct_cout(*rn, sortie_att);
	fct_cout(*rn, sortie_att);
	
	SigmoidePrimeZ(tmp->A,tmp->tmp,tmp->taille);
	Hadamard(tmp->tmp,tmp->DELTA,tmp->DELTA,tmp->taille);
	//l'erreur locale de la derniere couche est mtn calculée
		
	while(tmp->prec != NULL)
	{
		tmp = tmp->prec;
		
		//on propage l'erreur
		SigmoidePrimeZ(tmp->A,tmp->tmp,tmp->taille);
		MultiplicationMatricielleTransposeeTM(tmp->suiv->W,&(tmp->suiv->DELTA),&(tmp->DELTA),tmp->taille,1,tmp->suiv->taille);
		Hadamard(tmp->tmp,tmp->DELTA,tmp->DELTA,tmp->taille);
	}
}

void MultiplicationMatricielleTransposeeTM(float** in_M1, float** in_M2, float** out, int taille_M1,int taille_M2,int taille_M3) // = (in_M1)T * in_M2
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

void SigmoidePrimeZ(float* in, float* out, int taille)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		out[i]=in[i]*(1-in[i]);
	}
}

void MultiplicationMatricielleTransposeeMT(float** in_M1, float** in_M2, float** out, int taille_M1,int taille_M2,int taille_M3) // = (in_M1)T * in_M2
{
	int i,j,k; 
	
	for(i=0;i<taille_M1;i++) //taille_M1 nbr de lignes de la 1ere matrice
	{
		for(j=0;j<taille_M2;j++)  // taille_M2 nbr de lignes de la seconde matrice
		{
			out[i][j]=0;
			for(k=0;k<taille_M3;k++) // taille_M3 dimenssion commune aux deux matrices (obligatoire)
			{
				out[i][j] += in_M1[i][k] * in_M2[j][k];
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

int main()
{
	RN rn;
	rn.info.etiquettes = malloc(2*sizeof(char*));
	rn.info.etiquettes[0] = malloc(10*sizeof(char));
	rn.info.etiquettes[1] = malloc(10*sizeof(char));
	
	COUCHE* C0 = malloc(sizeof(COUCHE));
	COUCHE* C1 = malloc(sizeof(COUCHE));
	COUCHE* C2 = malloc(sizeof(COUCHE));
	COUCHE* C3 = malloc(sizeof(COUCHE));
	
	
	C0->taille = 2;
	C1->taille = 3;
	C2->taille = 3;
	C3->taille = 2;
	
	C0->A = malloc(C0->taille*sizeof(float));
	C1->A = malloc(C1->taille*sizeof(float));
	C2->A = malloc(C2->taille*sizeof(float));
	C3->A = malloc(C3->taille*sizeof(float));
	
	C0->B = malloc(C0->taille*sizeof(float));
	C1->B = malloc(C1->taille*sizeof(float));
	C2->B = malloc(C2->taille*sizeof(float));
	C3->B = malloc(C3->taille*sizeof(float));
	
	//C0->W = malloc(C0->taille*sizeof(float*));
	C1->W = malloc(C1->taille*sizeof(float*));
	C2->W = malloc(C2->taille*sizeof(float*));
	C3->W = malloc(C3->taille*sizeof(float*));
	
	int i;
	for(i=0;i<C1->taille;i++)
	{
		C1->W[i] = malloc(C0->taille*sizeof(float));
	}
	for(i=0;i<C2->taille;i++)
	{
		C2->W[i] = malloc(C1->taille*sizeof(float));
	}
	for(i=0;i<C3->taille;i++)
	{
		C3->W[i] = malloc(C2->taille*sizeof(float));
	}
	
	C1->W[0][0] = 5;  C1->W[0][1] = 7;
	C1->W[1][0] = -2; C1->W[1][1] = 3;
	C1->W[2][0] = 9;  C1->W[2][1] = -4;
	
	return 0;
}
