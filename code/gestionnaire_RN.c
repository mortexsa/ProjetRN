#include <math.h>
#include "gestionnaire_RN.h"
#include <string.h>
#include <stdlib.h>

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


//mettre des val aleatoire dans W et B
void Remplissage(RN rn) 
{ int i,j;
	
	COUCHE* tmp = rn.couche_deb->suiv;
	//faire le test pour tester si il y a au moins deux couches
while(tmp!=NULL){
	for(i=0;i<tmp->taille;i++) //taille_M1 nbr de lignes de la 1ere matrice
	{	//rn.couche_deb->A[i] = 0;         pas sur de mettre les activation à 0
		tmp->B[i] = rand();
		
		for(j=0;j<tmp->prec->taille;j++)  // taille_M2 nbr de colonnes de la seconde matrice
		{
			
				tmp->W[i][j]= rand(); //attricution de poids aleatoires
		} 
	}
	tmp=tmp->suiv;
}
}

/*ajouter une couche à la fin */
void Ajout_couche_Fin(RN rn, int taille)
{ 
COUCHE* new = malloc(sizeof(COUCHE));
new->suiv=NULL;
new->prec=rn.couche_fin;
rn.couche_fin->suiv=new;
new->taille=taille;
}

/*propagation de l'image application de AJ=σ(AJ-1*W+b)*/
void Propagation(Image* im, RN rn)
{
COUCHE* tmp = rn.couche_deb;
	
	//insertion activation
for(int i=0;i<tmp->taille;i++){
	//tmp->A[i]=val;
	}	
	//
	
	tmp = tmp->suiv;
	
	while(tmp != NULL)
	{
		MultiplicationMatriceVecteur(tmp->W,tmp->prec->A,tmp->A,tmp->taille,tmp->prec->taille);
		AdditionVecteurVecteur(tmp->B,tmp->A,tmp->A,tmp->taille);
		SigmoideV(tmp->A,tmp->A,tmp->taille);
		Reconnaissance(rn);
		
	tmp=tmp->suiv;}	
}


char** Reconnaissance(RN rn)
{
	/*
	char* top[3];
	int t[3];
	
	int i;
	int max1 = 0;
	int max2 = 0;
	int max3 = 0;
	
	for(i=0;i<rn.couche_fin->taille;i++)
		{if(rn.couche_fin->A[i]>max1)				
			{
				max1 = rn.couche_fin->A[i];
				t[0] = i;
		
			}
		}
		
	for(i=0;i<rn.couche_fin->taille;i++)
		{if(rn.couche_fin->A[i]>max2)
			{if(max1!=rn.couche_fin->A[i])				
				{
				max2 = rn.couche_fin->A[i];
				t[1] = i;
				}
			}
		}
		
	for(i=0;i<rn.couche_fin->taille;i++)
		{if(rn.couche_fin->A[i]>max3)
			{if(max1!=rn.couche_fin->A[i])				
				{if(max2!=rn.couche_fin->A[i])	
					{
						max3 = rn.couche_fin->A[i];
						t[2] = i;
					}
				}
			}
		}
		
	top[0] = rn.info->etiquettes[t[0]];
	top[1] = rn.info->etiquettes[t[1]];
	top[2] = rn.info->etiquettes[t[2]];
		
	
	return top;
	*/
}

