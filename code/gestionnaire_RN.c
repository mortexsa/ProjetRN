#include <math.h>
#include "gestionnaire_RN.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
	//rn->info.etiquettes = info.etiquettes;
	rn->info.nom = malloc(sizeof(char)*strlen(info.nom));
	rn->info.date = malloc(sizeof(char)*strlen(info.date));
	strcpy(rn->info.nom,info.nom);
	strcpy(rn->info.date,info.date);
	rn->info.reussite = info.reussite;
	rn->info.echec = info.echec;	
	
	return rn;	
}


//mettre des val aleatoire dans W et B
void Remplissage(RN rn) 
{
	srand(time(NULL));
	int i,j;
	
	COUCHE* tmp = rn.couche_deb->suiv;
	
//if(tmp!=NULL && tmp->suiv!=NULL){  //faire le test pour tester si il y a au moins deux couches
	
	while(tmp!=NULL)
		{
		for(i=0;i<tmp->taille;i++) //taille_M1 nbr de lignes de la 1ere matrice
		{
			tmp->B[i] = (float) (rand()%201 - 100)/100;
		
			for(j=0;j<tmp->prec->taille;j++)  // taille_M2 nbr de colonnes de la seconde matrice
			{
				tmp->W[i][j]= (float) (rand()%201 - 100)/100; //attricution de poids aleatoires
			} 
		}
		tmp=tmp->suiv;
	}
//}

/*else { printf("le nombre de couche est < à 2");//envoyer un message d'erreur 
	exit(1);}*/
}

/*ajouter une couche à la fin */
void Ajout_couche_Fin(RN* rn, int taille)
{
	COUCHE* new = malloc(sizeof(COUCHE));
	new->suiv = NULL;
	new->prec = rn->couche_fin;
	rn->couche_fin->suiv = new;
	new->taille = taille;
	
	rn->couche_fin = new;
	
	new->A = malloc(taille*sizeof(float));
	new->B = malloc(taille*sizeof(float));
	new->W = malloc(taille*sizeof(float*));
	new->DELTA = malloc(taille*sizeof(float));
	new->DELTA_M = malloc(taille*sizeof(float*));
	
	int i,taille_prec = new->prec->taille;
	for(i = 0;i<taille;i++)
	{
		new->W[i] = malloc(taille_prec*sizeof(float));
		new->DELTA_M[i] = malloc(taille_prec*sizeof(float));
	}
}

void AjoutPremiereCouche(RN* rn, int taille)
{ 
	COUCHE* new = malloc(sizeof(COUCHE));
	new->suiv = NULL;
	new->prec = NULL;
	rn->couche_fin = new;
	rn->couche_deb = new;
	new->taille = taille;
	
	new->A = malloc(taille*sizeof(float));
	new->B = NULL;
	new->W = NULL;
	new->DELTA = NULL;
	new->DELTA_M = NULL;
}

/*propagation de l'image application de AJ=σ(AJ-1*W+b)*/
void Propagation(Image* im, RN rn)
{
	COUCHE* tmp = rn.couche_deb;
	float act;
	
	//insertion activation
	for(int i=0;i<im->w*im->h;i++)
		{
			act=(float)im->dat[i].r/255;
			rn.couche_deb->A[3*i] = act;
			act=(float)im->dat[i].g/255;
			rn.couche_deb->A[3*i+1] = act;
			act=(float)im->dat[i].b/255;
			rn.couche_deb->A[3*i+2] = act;
			
			/*if(rn.couche_deb->A[3*i] > 0)
				printf("\x1B[8;47m \x1B[0m");
			else
				printf("\x1B[8;40m \x1B[0m");
			
			if(i%im->w == 0)
				printf("\n");*/
		}	
	//printf("\n");
	tmp = tmp->suiv;
	
	while(tmp != NULL)
	{
		MultiplicationMatriceVecteur(tmp->W,tmp->prec->A,tmp->A,tmp->taille,tmp->prec->taille);
		AdditionVecteurVecteur(tmp->B,tmp->A,tmp->A,tmp->taille);
		SigmoideV(tmp->A,tmp->A,tmp->taille);
		
		tmp=tmp->suiv;
	}	
}


char** Reconnaissance(RN rn)
{
	
	char** top = malloc(sizeof(char*)*3);
	int i;
	int id1 = 0;
	int id2 = 0;
	int id3 = 0;
	
	for(i=0;i<rn.couche_fin->taille;i++)
	{
		//printf("%f\n",rn.couche_fin->A[i]);
		if(rn.couche_fin->A[i]>rn.couche_fin->A[id1])				
		{
			id1 = i;
		}
	}
	top[0] = malloc(sizeof(char)*strlen(rn.info.etiquettes[id1]));
	strcpy(top[0],rn.info.etiquettes[id1]);
	
	while(id2 == id1) id2++;
	for(i=0;i<rn.couche_fin->taille;i++)
	{
		if(i != id1 && rn.couche_fin->A[i]>rn.couche_fin->A[id2])				
		{
			id2 = i;
		}
	}
	top[1] = malloc(sizeof(char)*strlen(rn.info.etiquettes[id2]));
	strcpy(top[1],rn.info.etiquettes[id2]);
	
	while(id3 == id1 || id3 == id2) id3++;
	for(i=0;i<rn.couche_fin->taille;i++)
	{
		if(i != id1 && i != id2 && rn.couche_fin->A[i]>rn.couche_fin->A[id3])				
		{
			id3 = i;
		}
	}
	
	top[2] = malloc(sizeof(char)*strlen(rn.info.etiquettes[id3]));
	strcpy(top[2],rn.info.etiquettes[id3]);
			
	return top;
	
}

void libererRN(RN* rn)
{
	int i;
	for(i=0;i<rn->couche_fin->taille;i++)
	{
		free(rn->info.etiquettes[i]);
	}
	free(rn->info.etiquettes);
	free(rn->info.date);
	free(rn->info.nom);
	
	COUCHE* tmp = rn->couche_deb;
	free(tmp->A);
	tmp = tmp->suiv;
	free(tmp->prec);
	
	while(tmp)
	{
		for(i=0;i<tmp->taille;i++)
		{
			free(tmp->W[i]);
			free(tmp->DELTA_M[i]);
		}
		free(tmp->W);
		free(tmp->DELTA_M);
		free(tmp->DELTA);
		free(tmp->A);
		free(tmp->B);
		tmp = tmp->suiv;
		if(tmp)
			free(tmp->prec);
	}
	free(rn->couche_fin);
}

