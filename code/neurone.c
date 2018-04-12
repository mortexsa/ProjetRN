#include "interface.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int i;
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
	
	C2->W[0][0] = 9.0;  C2->W[0][1] = 12.0;  C2->W[0][2] = -3.0;
	C2->W[1][0] = 5.0;  C2->W[1][1] = -2.0;  C2->W[1][2] = 7.0;
	C2->W[2][0] = 4.0;  C2->W[2][1] = 10.0;  C2->W[2][2] = 1.0;
	
	C2->B[0] = -11.0;
	C2->B[1] = 3.0;
	C2->B[2] = 8.0;
	
	C3->W[0][0] = 5.0;  C3->W[0][1] = 9.0;  C3->W[0][2] = 2.0;
	C3->W[1][0] = -4.0; C3->W[1][1] = 3.0;  C3->W[1][2] = 1.0;
	
	C3->B[0] = 7.0;
	C3->B[1] = -6.0;
	
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
	
	rn.info.date = malloc(20*sizeof(char));
	rn.info.nom = malloc(20*sizeof(char));
	
	strcpy(rn.info.date,"2018-04-12\0");
	strcpy(rn.info.nom,"test1\0");
	
	SaveRN(rn);
	
	return 0;
}
