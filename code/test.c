#include "test.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//printf("%f\n",);

void fct_cout(RN rn ,char* eti)
{	
	for(int i=0;i<rn.couche_fin->taille;i++)
	{
		rn.couche_fin->DELTA[i] = (rn.couche_fin->A[i] - (((strcmp(eti,rn.info.etiquettes[i]))==0)?1.0:0.0));
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
	
	int i;
	for(i=0;i<tmp->taille;i++)
	{
		printf("%f\n",tmp->DELTA[i]);
	}
	
	
	SigmoidePrimeZ(tmp->A,tmp->tmp,tmp->taille);
	printf("\nSig Prime :\n\n");
	
	for(i=0;i<tmp->taille;i++)
	{
		printf("%f\n",tmp->tmp[i]);
	}
	
	Hadamard(tmp->tmp,tmp->DELTA,tmp->DELTA,tmp->taille);
	printf("\nHadamard :\n\n");
	//l'erreur locale de la derniere couche est mtn calculée
		
	for(i=0;i<tmp->taille;i++)
	{
		printf("%f\n",tmp->DELTA[i]);
	}
	
	i=3;
	while(tmp->prec != NULL)
	{
		tmp = tmp->prec;
		
		i--;
		printf("\nCouche : %d\n\n",i);
		
		//on propage l'erreur
		SigmoidePrimeZ(tmp->A,tmp->tmp,tmp->taille);
		printf("\nSig Prime Z :\n\n");
		
		for(i=0;i<tmp->taille;i++)
		{
			printf("%f\n",tmp->tmp[i]);
		}
		
		MultiplicationMatricielleTransposeeTM(tmp->suiv->W,&(tmp->suiv->DELTA),&(tmp->DELTA),tmp->taille,1,tmp->suiv->taille);
		printf("\nMultiplicationMatricielleTransposeeTM :\n\n");
		
		for(i=0;i<tmp->taille;i++)
		{
			printf("%f\n",tmp->DELTA[i]);
		}
		
		Hadamard(tmp->tmp,tmp->DELTA,tmp->DELTA,tmp->taille);
		printf("\nHadamard :\n\n");
		
		for(i=0;i<tmp->taille;i++)
		{
			printf("%f\n",tmp->DELTA[i]);
		}
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
	
	strcpy(rn.info.etiquettes[0],"eti_1\0");
	strcpy(rn.info.etiquettes[1],"eti_2\0");
	
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
	
	C0->DELTA = malloc(C0->taille*sizeof(float));
	C1->DELTA = malloc(C1->taille*sizeof(float));
	C2->DELTA = malloc(C2->taille*sizeof(float));
	C3->DELTA = malloc(C3->taille*sizeof(float));
	
	C0->tmp = malloc(C0->taille*sizeof(float));
	C1->tmp = malloc(C1->taille*sizeof(float));
	C2->tmp = malloc(C2->taille*sizeof(float));
	C3->tmp = malloc(C3->taille*sizeof(float));
	
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
	
	C0->A[0] = 0.5;
	C0->A[1] = -0.1;
	
	C1->W[0][0] = 5.0;  C1->W[0][1] = 7.0;
	C1->W[1][0] = -2.0; C1->W[1][1] = 3.0;
	C1->W[2][0] = 9.0;  C1->W[2][1] = -4.0;
	
	C1->B[0] = -1.0;
	C1->B[1] = -8.0;
	C1->B[2] = 2.0;
	
	C1->A[0] = 0.7;
	C1->A[1] = 0.0;
	C1->A[2] = 1.0;
	
	C2->W[0][0] = 9.0;  C2->W[0][1] = 12.0;  C2->W[0][2] = -3.0;
	C2->W[1][0] = 5.0;  C2->W[1][1] = -2.0;  C2->W[1][2] = 7.0;
	C2->W[2][0] = 4.0;  C2->W[2][1] = 10.0;  C2->W[2][2] = 1.0;
	
	C2->B[0] = -11.0;
	C2->B[1] = 3.0;
	C2->B[2] = 8.0;
	
	C2->A[0] = 0.2;
	C2->A[1] = 1.0;
	C2->A[2] = 1.0;
	
	C3->W[0][0] = 5.0;  C3->W[0][1] = 9.0;  C3->W[0][2] = 2.0;
	C3->W[1][0] = -4.0; C3->W[1][1] = 3.0;  C3->W[1][2] = 1.0;
	
	C3->B[0] = 7.0;
	C3->B[1] = -6.0;
	
	C3->A[0] = 1.0;
	C3->A[1] = 0.1;
	
	C0->suiv = C1;
	C1->suiv = C2;
	C2->suiv = C3;
	C3->suiv = NULL;
	
	C0->prec = NULL;
	C1->prec = C0;
	C2->prec = C1;
	C3->prec = C2;
	
	rn.couche_deb = C0;
	rn.couche_fin = C3;
	
	BackProp(&rn,"eti_2");
	
	return 0;
}
