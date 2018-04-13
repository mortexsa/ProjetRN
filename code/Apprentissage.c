#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "Apprentissage.h"

//calcul de l'erreur 
void fct_cout(RN rn ,char* eti)
{	
	for(int i=0;i<rn.couche_fin->taille;i++)
	{
		rn.couche_fin->DELTA[i] = (rn.couche_fin->A[i] - (((strcmp(eti,rn.info.etiquettes[i]))==0)?1:0));	
	}
}
	
void BackProp(RN* rn, Image* im,char* sortie_att, float eta)
{
	COUCHE* tmp = rn->couche_fin;
	
	Propagation(im, *rn);
	char** sortie_calc = Reconnaissance(*rn);
	
	if(strcmp(sortie_calc[0],sortie_att)==0)
		rn->info.reussite++;
	else
		rn->info.echec++;
	
	fct_cout(*rn, sortie_att);
	
	SigmoidePrimeZ(tmp->A,tmp->DELTA_M,tmp->taille);
	Hadamard(tmp->DELTA_M,tmp->DELTA,tmp->DELTA,tmp->taille);
	//l'erreur locale de la derniere couche est mtn calculée
		
	while(tmp->prec != NULL)
	{
		tmp = tmp->prec;
		
		//on propage l'erreur
		SigmoidePrimeZ(tmp->A,tmp->DELTA_M,tmp->taille);
		MultiplicationMatricielleTransposeeTM(tmp->suiv->W,tmp->suiv->DELTA,tmp->DELTA,tmp->taille,tmp->suiv->taille);
		Hadamard(tmp->DELTA_M,tmp->DELTA,tmp->DELTA,tmp->taille);
		
		//on en profite pour calculer la matrice de modif des poids DELTA_M puis apporter ces modifications aux poids et aux biais
		if(tmp->prec != NULL)
		{
			MultiplicationMatricielleTransposeeMT(tmp->DELTA,tmp->prec->A,tmp->DELTA_M,tmp->taille,tmp->prec->taille);
			ModifPoids(tmp->W,tmp->DELTA_M,tmp->prec->taille,tmp->taille,eta);
			ModifBiais(tmp->B,tmp->DELTA,tmp->taille,eta);
		}
	}
}

void ModifPoids(type** W, type** DELTA, int W_w, int W_h, int eta)
{
	int i,j;
	
	for(i=0;i<W_h;i++)
	{
		for(j=0;j<W_w;j++)
		{
			W[i][j] -= eta*DELTA[i][j];
		}
	}
}

void ModifBiais(type* B, type* DELTA, int taille, int eta)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		B[i] -= eta*DELTA[i];
	}
}

/*
 * W -> W - rate*(DELTA(l)*A(l-1)T)
 * B -> B - rate*DELTA(l)
 */

void SigmoidePrimeZ(type* in, type** out, int taille)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		out[i][0]=in[i]*(1-in[i]);
	}
}

void MultiplicationMatricielleTransposeeTM(type** in_M, type* in_V, type* out, int taille_M1,int taille_M3) // = (in_M1)T * in_M2
{
	int i,k; 
	
	for(i=0;i<taille_M1;i++) //taille_M1 nbr de colonnes de la 1ere matrice
	{
		out[i]=0;
		for(k=0;k<taille_M3;k++) // taille_M3 dimenssion commune aux deux matrices (obligatoire)
		{
			out[i] += in_M[k][i] * in_V[k];
			//[ligne][colonne]
		}
	}
}

void MultiplicationMatricielleTransposeeMT(type* in_M1, type* in_M2, type** out, int taille_M1,int taille_M2) // = in_M1 * (in_M2)T
{
	int i,j; 
	
	for(i=0;i<taille_M1;i++) //taille_M1 nbr de lignes de la 1ere matrice
	{
		for(j=0;j<taille_M2;j++)  // taille_M2 nbr de lignes de la seconde matrice
		{
			out[i][j]=in_M1[i] * in_M2[j];
		}
	}
}

void Hadamard(type** in_a, type* in_b, type* out, int taille)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		out[i] = in_a[i][0]*in_b[i];
	}
}
