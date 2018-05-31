/**
 * \file Apprentissage.c
 * \brief Code de la partie propagation-inverse ainsi que toutes les fonctions necessaire a celle ci.
 * \author PEPIN Thibaut
 * \author REZGUI Soumia
 * \author SLIMANI Arezki
 * \author SELAQUET Severine
 * \author SZULEK Isaac
 * \author MONTIGNE Anthony
 */

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "Apprentissage.h"

/**
 * \fn void fct_cout(RN rn ,char* eti)
 * \brief sotcke dans le vecteur DELTA de la derniere couche du réseau la difference entre la valeur obtenue et la valeur souhaitée.
 * \param rn le réseau de neurones
 * \param eti l'etiquette attendue
 */
void fct_cout(RN rn ,char* eti)
{	
	for(int i=0;i<rn.couche_fin->taille;i++)
	{
		rn.couche_fin->DELTA[i] = (rn.couche_fin->A[i] - (((strcmp(eti,rn.info->etiquettes[i]))==0)?1:0));	
	}
}


/**
 * \fn void BackProp(RN* rn, Image* im,char* sortie_att, float eta)
 * \brief effectue une fois l'algorithme de backpropagation sur un réseau de neurone.
 * \param rn le réseau de neurones
 * \param im l'image a fournir comme donnée d'entré au réseau de neurones
 * \param sortie_att l'etiquette attendu correspondant a l'image fournie
 * \param eta le taux d'apprentissage
 */
void BackProp(RN* rn, Image* im,char* sortie_att, float eta)
{
	COUCHE* tmp = rn->couche_fin;
	
	Propagation(im, *rn);
	
	char** sortie_calc = Reconnaissance(*rn);
	if(strcmp(sortie_calc[0],sortie_att)==0)
		rn->info->reussite++;
	else
		rn->info->echec++;
	
	free(sortie_calc[0]);
	free(sortie_calc[1]);
	free(sortie_calc[2]);
	free(sortie_calc);
	
	fct_cout(*rn, sortie_att);
	
	SigmoidePrimeZ(tmp->A,tmp->DELTA_M,tmp->taille);
	Hadamard(tmp->DELTA_M,tmp->DELTA,tmp->DELTA,tmp->taille);
	//l'erreur locale de la derniere couche est mtn calculée
	
	tmp = tmp->prec;
	
	while(tmp->prec != NULL)
	{
		//on propage l'erreur
		SigmoidePrimeZ(tmp->A,tmp->DELTA_M,tmp->taille);
		MultiplicationMatricielleTransposeeTM(tmp->suiv->W,tmp->suiv->DELTA,tmp->DELTA,tmp->taille,tmp->suiv->taille);
		Hadamard(tmp->DELTA_M,tmp->DELTA,tmp->DELTA,tmp->taille);
		
		tmp = tmp->prec;
	}
	
	//on calcule la matrice de modif des poids DELTA_M puis on apporte ces modifications aux poids et aux biais
	tmp = tmp->suiv;
	while(tmp)
	{
		MultiplicationMatricielleTransposeeMT(tmp->DELTA,tmp->prec->A,tmp->DELTA_M,tmp->taille,tmp->prec->taille);
		ModifPoids(tmp->W,tmp->DELTA_M,tmp->prec->taille,tmp->taille,eta);
		ModifBiais(tmp->B,tmp->DELTA,tmp->taille,eta);
		
		tmp = tmp->suiv;
	}
}

/**
 * \fn void ModifPoids(float** W, float** DELTA, int W_w, int W_h, float eta)
 * \brief modifie les poids d'un réseau de neurone
 * \param W la matrice des poids d'un réseau de neurone
 * \param DELTA les modifications a apporter
 * \param W_w largeur de W
 * \param W_h hauteur de W
 * \param eta taux d'apprentissage
 */
void ModifPoids(float** W, float** DELTA, int W_w, int W_h, float eta)
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

/**
 * \fn void ModifBiais(float* B, float* DELTA, int taille, float eta)
 * \brief modifie les biais d'un réseau de neurone
 * \param B le vecteur des biais d'un réseau de neurone
 * \param DELTA les modifications a apporter
 * \param taille taille du vecteur B
 * \param eta taux d'apprentissage
 */
void ModifBiais(float* B, float* DELTA, int taille, float eta)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		B[i] -= eta*DELTA[i];
	}
}

/**
 * \fn void SigmoidePrimeZ(float* in, float** out, int taille)
 * \brief effectue le calcul a*(1-a)
 * \param in vecteur d'entrée
 * \param out vecteur de sortie
 * \param taille taille du vecteur d'entrée
 */
void SigmoidePrimeZ(float* in, float** out, int taille)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		out[i][0]=in[i]*(1-in[i]);
	}
}

/**
 * \fn void MultiplicationMatricielleTransposeeTM(float** in_M, float* in_V, float* out, int taille_M1,int taille_M3)
 * \brief effectue une multiplication matricielle en transposant la premiere matrice
 * \param in_M premiere matrice du calcul, sera transposée avant d'etre multipliée
 * \param in_V vecteur qui sera multiplié a la matrice
 * \param out vecteur ou sera stocké le résultat
 * \param taille_M1 largeur de la matrice
 * \param taille_M3 hauteur de la matrice
 */
void MultiplicationMatricielleTransposeeTM(float** in_M, float* in_V, float* out, int taille_M1,int taille_M3) // = (in_M1)T * in_M2
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

/**
 * \fn void MultiplicationMatricielleTransposeeTM(float** in_M, float* in_V, float* out, int taille_M1,int taille_M3)
 * \brief effectue une multiplication matricielle en transposant la deuxieme matrice (qui est un vecteur)
 * \param in_M premiere matrice du calcul
 * \param in_V vecteur, sera transposée avant d'etre multipliée a la matrice
 * \param out vecteur ou sera stocké le résultat
 * \param taille_M1 hauteur de la matrice
 * \param taille_M3 largeur de la matrice
 */
void MultiplicationMatricielleTransposeeMT(float* in_M1, float* in_M2, float** out, int taille_M1,int taille_M2) // = in_M1 * (in_M2)T
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

/**
 * \fn void Hadamard(float** in_a, float* in_b, float* out, int taille)
 * \brief effectue le produit hadamard
 * \param in_a premier vecteur de l'opération
 * \param in_b deuxieme vecteur de l'opération
 * \param out vecteur ou sera stocké le résultat
 * \param taille taille du vecteur d'entrée
 */
void Hadamard(float** in_a, float* in_b, float* out, int taille)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		out[i] = in_a[i][0]*in_b[i];
	}
}

/**
 * \fn void DelApp(App* app)
 * \brief libere la mémoire d'une structure App
 * \param app élément a liberer de la mémoire
 */
void DelApp(App* app)
{
	DelImage(app->image);
	free(app->etiquette);
	free(app);
}
