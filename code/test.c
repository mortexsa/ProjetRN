#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"

#define WHT   "\x1B[8;47m"
#define BLK   "\x1B[8;40m"
#define RESET "\x1B[0m"

int main()
{
	//test_chargerMNIST("/home/user/Bureau/App/train-images-idx3-ubyte");
	//test_ChargerEtiquetteMNIST("/home/user/Bureau/App/train-labels-idx1-ubyte");
	
	//test_ChargementCoupleAttIn("/home/user/Bureau/App");
	
	test_Apprentissage("/home/user/Bureau/App");
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
	
	DelImage(im);
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
	
	rn->info.nom = malloc(sizeof(char)*10);
	rn->info.date = malloc(sizeof(char)*20);
	strcpy(rn->info.nom,"MNIST");
	strcpy(rn->info.date,"2018-05-08");
	rn->info.reussite = 0;
	rn->info.echec = 0;
	
	rn->info.etiquettes = malloc(sizeof(char*)*10);
	
	rn->info.etiquettes[0] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[0],"0\0");
	rn->info.etiquettes[1] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[1],"1\0");
	rn->info.etiquettes[2] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[2],"2\0");
	rn->info.etiquettes[3] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[3],"3\0");
	rn->info.etiquettes[4] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[4],"4\0");
	rn->info.etiquettes[5] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[5],"5\0");
	rn->info.etiquettes[6] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[6],"6\0");
	rn->info.etiquettes[7] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[7],"7\0");
	rn->info.etiquettes[8] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[8],"8\0");
	rn->info.etiquettes[9] = malloc(sizeof(char)*5);
	strcpy(rn->info.etiquettes[9],"9\0");

	AjoutPremiereCouche(rn, 2352);
	
	Ajout_couche_Fin(rn, 16);
	Ajout_couche_Fin(rn, 16);
	Ajout_couche_Fin(rn, 16);
	
	Ajout_couche_Fin(rn, 10);

	Remplissage(*rn);
	
	SaveRN(*rn);
	
	int i;
	App* app;
	float po;
	
	while((app = ChargementCoupleAttIn(path,28,28)))
	{
		BackProp(rn,app->image,app->etiquette,1);
		
		po = (float) rn->info.reussite / rn->info.echec;
		printf("%d : %f%c\n",i,po,'%');
		
		i++;
		
		if(!(i%10))
			SaveRN(*rn);
		
		DelApp(app);
	}
	
	SaveRN(*rn);
	libererRN(rn);//y a un pb la dedans
}























