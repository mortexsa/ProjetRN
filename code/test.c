#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "test.h"

#define WHT   "\x1B[8;47m"
#define BLK   "\x1B[8;40m"
#define RESET "\x1B[0m"
#include <gtk/gtk.h>


int main(int argc, char** argv)
{
	srand(time(NULL));
	test_chargerMNIST("/home/user/Bureau/App/train-images-idx3-ubyte");
	//test_ChargerEtiquetteMNIST("/home/user/Bureau/App/train-labels-idx1-ubyte");
	
	//test_ChargementCoupleAttIn("/home/user/Bureau/App");
	
	//test_Apprentissage("/home/user/Bureau/App");
	
	//test_MultiplicationMatricielleTransposeeTM();
	//test_MultiplicationMatricielleTransposeeMT();
	
	//test_Propagation();
	
	//test_BackProp();
	
	//printf("oui je marche parfaitement ! soumsoum t'inquiete pas et le nbr des sous reseaux sont :%d!\n",nombreReseau());
	
 	gtk_init(&argc,&argv);//initialise la bibilo , toujours appeler en debut de programme 

 	afficherInterface();

 	gtk_main();//appeler dans toutes les fct gtk , cette fct attends le clique de la souris ou toucher le clavier 
}


void test_chargerMNIST(char* path)
{	
	Image* im = ChargerMnist(path, 28, 28);
	
	if(!im) exit(-1);
	
	int i, j;
	for(i=0;i<28;i++)
	{
		for(j=0;j<28;j++)
		{
			if(im->dat[i*28+j].r > 0)
				printf(WHT "1" RESET);
			else
				printf(BLK "0" RESET);
		}
		printf("\n");
	}
}

void test_ChargerEtiquetteMNIST(char* path)
{
	char* c = ChargerEtiquetteMNIST(path);
	printf("%c\n",*c);
	free(c);
}

void test_ChargementCoupleAttIn(char* path)
{
	App* app = ChargementCoupleAttIn(path,28,28);
	if(!app) exit(-2);
	
	int i, j;
	for(i=0;i<28;i++)
	{
		for(j=0;j<28;j++)
		{
			if(app->image->dat[i*28+j].r > 0)
				printf(WHT "1" RESET);
			else
				printf(BLK "0" RESET);
		}
		printf("\n");
	}
	
	printf("%s\n",app->etiquette);
	
	DelImage(app->image);
	free(app->etiquette);
	free(app);
}

void test_Apprentissage(char* path)
{
	RN* rn = malloc(sizeof(RN));
	rn->couche_deb=NULL;
	rn->couche_fin=NULL;
	
	rn->info->nom = malloc(sizeof(char)*10);
	rn->info->date = malloc(sizeof(char)*20);
	strcpy(rn->info->nom,"MNIST");
	strcpy(rn->info->date,"2018-05-08");
	rn->info->reussite = 0;
	rn->info->echec = 0;
	
	rn->info->etiquettes = malloc(sizeof(char*)*10);
	
	rn->info->etiquettes[0] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[0],"0\0");
	rn->info->etiquettes[1] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[1],"1\0");
	rn->info->etiquettes[2] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[2],"2\0");
	rn->info->etiquettes[3] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[3],"3\0");
	rn->info->etiquettes[4] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[4],"4\0");
	rn->info->etiquettes[5] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[5],"5\0");
	rn->info->etiquettes[6] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[6],"6\0");
	rn->info->etiquettes[7] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[7],"7\0");
	rn->info->etiquettes[8] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[8],"8\0");
	rn->info->etiquettes[9] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[9],"9\0");

	AjoutPremiereCouche(rn, 2352);
	
	//76% eta = 1
	/*Ajout_couche_Fin(rn, 16);
	Ajout_couche_Fin(rn, 16);
	Ajout_couche_Fin(rn, 16);*/
	
	//86% eta = 1
	/*Ajout_couche_Fin(rn, 64);
	Ajout_couche_Fin(rn, 64);*/
	
	//83% eta = 1
	/*Ajout_couche_Fin(rn, 128);
	Ajout_couche_Fin(rn, 128);*/
	
	//85% eta = 1
	/*Ajout_couche_Fin(rn, 64);
	Ajout_couche_Fin(rn, 64);
	Ajout_couche_Fin(rn, 64);*/
	
	//87% eta = 1.5
	Ajout_couche_Fin(rn, 64);
	Ajout_couche_Fin(rn, 64);
	Ajout_couche_Fin(rn, 64);
	
	Ajout_couche_Fin(rn, 10);

	Remplissage(*rn);
	
	SaveRN(*rn);
	
	int i = 0;
	App* app;
	float po;
	
	while((app = ChargementCoupleAttIn(path,28,28)))
	{
		BackProp(rn,app->image,app->etiquette,0.5);
		
		po = (float) rn->info->reussite / (rn->info->echec + rn->info->reussite);
		po *= 100;
		printf("%d : %f%c\n",i,po,'%');
		
		i++;
		
		if(!(i%5000))
			SaveRN(*rn);
		
		DelApp(app);
	}
	
	SaveRN(*rn);
	libererRN(rn);
}

void test_MultiplicationMatricielleTransposeeTM()
{
	int i, j;
	float *inV,**inM, *out;
	
	inV = malloc(sizeof(float)*5);
	out = malloc(sizeof(float)*5);
	inM = malloc(sizeof(float*)*5);
	
	for(i=0;i<5;i++)
	{
		inM[i] = malloc(sizeof(float)*5);
		
		inV[i] = rand()%10 - 5;
		for(j=0;j<5;j++)
			inM[i][j] = rand()%10 - 5;
	}
	
	MultiplicationMatricielleTransposeeTM(inM,inV,out,5,5);
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			printf("%f  ",inM[i][j]);
		printf("\n");
	}
	printf("\n");
	for(i=0;i<5;i++)
	{
		printf("%f\n",inV[i]);
	}
	printf("\n");
	for(i=0;i<5;i++)
	{
		printf("%f\n",out[i]);
	}
	printf("\n");
}

void test_MultiplicationMatricielleTransposeeMT()
{
	int i, j;
	float *inV1,*inV2, **out;
	
	inV1 = malloc(sizeof(float)*5);
	inV2 = malloc(sizeof(float)*5);
	out = malloc(sizeof(float*)*5);
	
	for(i=0;i<5;i++)
	{
		out[i] = malloc(sizeof(float)*5);
		
		inV1[i] = rand()%10 - 5;
		inV2[i] = rand()%10 - 5;
	}
	
	MultiplicationMatricielleTransposeeMT(inV1,inV2,out,5,5);
	
	for(i=0;i<5;i++)
	{
		printf("%f\n",inV1[i]);
	}
	printf("\n");
	for(i=0;i<5;i++)
	{
		printf("%f\n",inV2[i]);
	}
	printf("\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			printf("%f  ",out[i][j]);
		printf("\n");
	}
	printf("\n");
}


void test_Propagation()
{
	int i,j;
	
	RN* rn = malloc(sizeof(RN));
	rn->couche_deb=NULL;
	rn->couche_fin=NULL;

	AjoutPremiereCouche(rn, 5);
	Ajout_couche_Fin(rn, 5);

	Remplissage(*rn);
	
	for(i=0;i<5;i++)
		rn->couche_deb->A[i] = (float) (rand()%201 -100)/100;
	
	COUCHE* tmp = rn->couche_deb;
	tmp = tmp->suiv;
	
	while(tmp != NULL)
	{
		MultiplicationMatriceVecteur(tmp->W,tmp->prec->A,tmp->A,tmp->taille,tmp->prec->taille);
		AdditionVecteurVecteur(tmp->B,tmp->A,tmp->A,tmp->taille);
		SigmoideV(tmp->A,tmp->A,tmp->taille);
		
		tmp=tmp->suiv;
	}
	
	for(i=0;i<5;i++)
		printf("%f\n",rn->couche_deb->A[i]);
	printf("\n");
	for(i=0;i<5;i++)
		printf("%f\n",rn->couche_fin->B[i]);
	printf("\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			printf("%f  ",rn->couche_fin->W[i][j]);
		printf("\n");
	}
	printf("\n");
	for(i=0;i<5;i++)
		printf("%f\n",rn->couche_fin->A[i]);
	printf("\n\n\n\n");
}

void test_BackProp()
{
	int i,j;
	
	RN* rn = malloc(sizeof(RN));
	rn->couche_deb=NULL;
	rn->couche_fin=NULL;
	
	rn->info->nom = malloc(sizeof(char)*10);
	rn->info->date = malloc(sizeof(char)*20);
	strcpy(rn->info->nom,"MNIST");
	strcpy(rn->info->date,"2018-05-08");
	rn->info->reussite = 0;
	rn->info->echec = 0;
	
	rn->info->etiquettes = malloc(sizeof(char*)*10);
	
	rn->info->etiquettes[0] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[0],"0\0");
	rn->info->etiquettes[1] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[1],"1\0");
	rn->info->etiquettes[2] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[2],"2\0");
	rn->info->etiquettes[3] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[3],"3\0");
	rn->info->etiquettes[4] = malloc(sizeof(char)*5);
	strcpy(rn->info->etiquettes[4],"4\0");

	AjoutPremiereCouche(rn, 5);
	Ajout_couche_Fin(rn, 5);

	Remplissage(*rn);
	
	for(i=0;i<5;i++)
		rn->couche_deb->A[i] = (float) (rand()%201 -100)/100;
	
	COUCHE* tmp = rn->couche_deb;
	tmp = tmp->suiv;
	
	while(tmp != NULL)
	{
		MultiplicationMatriceVecteur(tmp->W,tmp->prec->A,tmp->A,tmp->taille,tmp->prec->taille);
		AdditionVecteurVecteur(tmp->B,tmp->A,tmp->A,tmp->taille);
		SigmoideV(tmp->A,tmp->A,tmp->taille);
		
		tmp=tmp->suiv;
	}
	
	
	for(i=0;i<5;i++)
		printf("%f\n",rn->couche_deb->A[i]);
	printf("\n");
	for(i=0;i<5;i++)
		printf("%f\n",rn->couche_fin->B[i]);
	printf("\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			printf("%f  ",rn->couche_fin->W[i][j]);
		printf("\n");
	}
	printf("\n");
	for(i=0;i<5;i++)
		printf("%f\n",rn->couche_fin->A[i]);
	printf("\n\n\n");
	
	
	int eta = 1;
	tmp = rn->couche_fin;
	
	fct_cout(*rn, "1");
	
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
	
	tmp = tmp->suiv;
	while(tmp)
	{
		MultiplicationMatricielleTransposeeMT(tmp->DELTA,tmp->prec->A,tmp->DELTA_M,tmp->taille,tmp->prec->taille);
		ModifPoids(tmp->W,tmp->DELTA_M,tmp->prec->taille,tmp->taille,eta);
		ModifBiais(tmp->B,tmp->DELTA,tmp->taille,eta);
		
		tmp = tmp->suiv;
	}
	
	
	for(i=0;i<5;i++)
		printf("%f\n",rn->couche_fin->B[i]);
	printf("\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			printf("%f  ",rn->couche_fin->W[i][j]);
		printf("\n");
	}
	printf("\n");
}













