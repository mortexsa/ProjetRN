#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include "01_09_02_bmp.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/dir.h>
#include <errno.h>
#include <sys/stat.h>

#include "gestionnaire_IO.h"

#define debug printf("line : %d in function : %s in file %s\n",__LINE__,__func__,__FILE__);

Image* NouvelleImage(int w,int h)
{
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->dat = calloc(1,w*h*sizeof(Pixel*));
	return I;
}

Image* CopieImage(Image* I)
{
	Image* res;
	if (!I)
		return NULL;
	res = NouvelleImage(I->w,I->h);
	memcpy(res->dat,I->dat,I->w*I->h*sizeof(Pixel));
	return res;
}

void DelImage(Image* I)
{
	if (I)
	{
		free(I->dat);
		free(I);
	}
}

void SetPixel(Image* I,int i,int j,Pixel p)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	I->dat[I->w*j+i] = p;
}

Pixel GetPixel(Image* I,int i,int j)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	return I->dat[I->w*j+i];
}

// -------------------------------------------

#pragma pack(1)  // desative l'alignement mémoire
typedef int int32;
typedef short int16;

struct BMPImHead
{
	int32 size_imhead;
	int32 width;
	int32 height;
	int16 nbplans; // toujours 1
	int16 bpp;
	int32 compression;
	int32 sizeim;
	int32 hres;
	int32 vres;
	int32 cpalette;
	int32 cIpalette;
};

struct BMPHead
{
	char signature[2];
	int32 taille;
	int32 rsv;
	int32 offsetim;
	struct BMPImHead imhead;
};

Image* ChargerBmp(const char* fichier)
{
	struct BMPHead head;
	Image* I;
	int i,j,pitch;
	unsigned char bgrpix[3];
	char corrpitch[4] = {0,3,2,1};
	Pixel p;
	FILE* F = fopen(fichier,"rb");
	if (!F)
		return NULL;
	fread(&head,sizeof(struct BMPHead),1,F);
	if (head.signature[0]!='B' || head.signature[1]!='M')
		return NULL;  // mauvaise signature, ou BMP non supporté.
	if (head.imhead.bpp!=24)
		return NULL;  // supporte que le 24 bits pour l'instant
	if (head.imhead.compression!=0)
		return NULL;  // rarrissime, je ne sais même pas si un logiciel écrit/lit des BMP compressés. 
	if (head.imhead.cpalette!=0 || head.imhead.cIpalette!=0)
		return NULL; // pas de palette supportée, cependant, a bpp 24, il n'y a pas de palette.
	I = NouvelleImage(head.imhead.width,head.imhead.height);
	pitch = corrpitch[(3*head.imhead.width)%4];
	for(j=0;j<I->h;j++)
	{
		for(i=0;i<I->w;i++)
		{
			fread(&bgrpix,1,3,F);
			p.r = bgrpix[2];
			p.g = bgrpix[1];
			p.b = bgrpix[0];
			SetPixel(I,i,I->h-j-1,p);
		}
		fread(&bgrpix,1,pitch,F);
	}
	fclose(F);
	return I;
}

int Sauver(Image* I,const char* fichier)
{
	struct BMPHead head;
	Pixel p;
	int i,j,tailledata,pitch;
	unsigned char bgrpix[3];
	char corrpitch[4] = {0,3,2,1};
	FILE* F = fopen(fichier,"wb");
	if (!F)
		return -1;
	memset(&head,0,sizeof(struct BMPHead));
	head.signature[0] = 'B';
	head.signature[1] = 'M';
	head.offsetim = sizeof(struct BMPHead); // je vais toujours écrire sur le même moule.
	head.imhead.size_imhead = sizeof(struct BMPImHead);
	head.imhead.width = I->w;
	head.imhead.height = I->h;
	head.imhead.nbplans = 1;
	head.imhead.bpp = 24;
	pitch = corrpitch[(3*head.imhead.width)%4];
	tailledata = 3*head.imhead.height*head.imhead.width + head.imhead.height*pitch;
	head.imhead.sizeim = tailledata;
	head.taille = head.offsetim + head.imhead.sizeim;
	fwrite(&head,sizeof(struct BMPHead),1,F);
	for(j=0;j<I->h;j++)
	{
		for(i=0;i<I->w;i++)
		{
			p = GetPixel(I,i,I->h-j-1);
			bgrpix[0] = p.b;
			bgrpix[1] = p.g;
			bgrpix[2] = p.r;
			fwrite(&bgrpix,1,3,F);
		}
		bgrpix[0] = bgrpix[1] = bgrpix[2] = 0;
		fwrite(&bgrpix,1,pitch,F);
	}
	fclose(F);
	return 0;
}


Image* ChargerMnist(const char* fichier)
{
	
}

char* ChargerEtiquetteMNIST(const char* fichier)
{
	
}

char* ChargerEtiquetteBMP(const char* fichier)
{
	
}

INFO_RN* ChargerInfo()
{
	char path[268],tmp[268];
	FILE* verif;
	int i;
	DIR* rep = opendir("../sav");
	if (rep == NULL)
        exit(1);
    struct dirent* fichier = NULL;
    
    while((fichier = readdir(rep))&&(fichier->d_type == DT_DIR))
    {
		sprintf(path,"../sav/%s/INFO",fichier->d_name);
		if((verif = fopen(path,"r")))
		{
			i++;
			fclose(verif);
		}
	}
	
    if (closedir(rep) == -1)
        exit(-1);
    
    INFO_RN* res = malloc(i*sizeof(INFO_RN));
    
    rep = opendir("../sav");
	if (rep == NULL)
        exit(1);
    
    i=0;
    while((fichier = readdir(rep))&&(fichier->d_type == DT_DIR))
    {
		sprintf(path,"../sav/%s/INFO",fichier->d_name);
		printf("%s\n",path);
		verif = fopen(path,"r");
		if(verif)
		{
			fscanf(verif,"%s\n",tmp);
			res[i].nom = malloc(strlen(tmp)*sizeof(char));
			strcpy(res[i].nom,tmp);
			
			fscanf(verif,"%s\n",tmp);
			res[i].date = malloc(strlen(tmp)*sizeof(char));
			strcpy(res[i].date,tmp);
			
			fscanf(verif,"%d\n%d\n",&(res[i].reussite),&(res[i].echec));
			
			fclose(verif);
			i++;
		}
	}
	
    if(closedir(rep) == -1)
		exit(-1);
        
	return res;
}

RN* ChargerRN(INFO_RN info)
{
	RN* rn = initialisation(info);
	char path[100];
	int i = 1,j;
	sprintf(path,"../sav/%s_%s/C%d.rn",info.date,info.nom,i);
	FILE* fichier = fopen(path,"rb");	
	if(!fichier)
		exit(-1);
	
	int t[2];
	fread(t,sizeof(int),2,fichier);
	
	AjoutPremiereCouche(rn,t[0]);
	
	fseek(fichier, 0, SEEK_SET);
	
	while(fichier)
	{
		fread(t,sizeof(int),2,fichier);
		//printf("%s\n%d %d\n",path,t[0],t[1]);
		
		Ajout_couche_Fin(rn,t[1]);
		
		fread(rn->couche_fin->B,sizeof(type),t[1],fichier);
		
		for(j=0;j<t[1];j++)
		{
			fread(rn->couche_fin->W[j],sizeof(type),t[0],fichier);
		}
		
		fclose(fichier);
		
		i++;
		sprintf(path,"../sav/%s_%s/C%d.rn",info.date,info.nom,i);
		fichier = fopen(path,"r");
	}
	
	sprintf(path,"../sav/%s_%s/INFO",info.date,info.nom);
	fichier = fopen(path,"rb");
	if(!fichier)
		exit(-1);
		
	i=0;
	while(fgets(path, 1024, fichier))
		i++;
	i-=4;
	rn->info.etiquettes = malloc(i*sizeof(char*));
	fseek(fichier, 0, SEEK_SET);
	
	i=0;
	while(fgets(path, 1024, fichier))
	{
		if(i>=4)
		{
			rn->info.etiquettes[i-4] = malloc(strlen(path)*sizeof(char));
			strcpy(rn->info.etiquettes[i-4],path);
		}
		i++;
	}
	fclose(fichier);
		
	return rn;
}

void SaveRN(RN rn)
{
	if(opendir("../sav") == NULL)
	{
		mkdir("../sav",S_IRWXU);
	}
	
	char path[100];
	sprintf(path,"../sav/%s_%s",rn.info.date,rn.info.nom);
	
	if(opendir(path) == NULL)
	{
		mkdir(path,S_IRWXU);
	}
	
	//printf("%s\n",path);
	
	FILE* fichier = NULL;
	COUCHE* tmp = rn.couche_deb->suiv;
	char path2[100];
	int i = 1,m;
	int temp[2];
	
	if(tmp)
	{
		while(tmp)
		{
			sprintf(path2,"%s/C%d.rn",path,i);
			
			if((fichier = fopen(path2,"wb+")) == NULL)
			{
				exit(-1);
			}
			
			temp[0] = tmp->prec->taille;
			temp[1] = tmp->taille;
			fwrite(temp,sizeof(int),2,fichier);
			
			//printf("%s\n%d %d\n",path2,temp[0],temp[1]);
			
			fwrite(tmp->B,sizeof(type),temp[1],fichier);
			
			for(m=0;m<temp[1];m++)
			{
				fwrite(tmp->W[m],sizeof(type),temp[0],fichier);
			}
			
			fclose(fichier);
			tmp = tmp->suiv;
			i++;
		}
	}
	
	sprintf(path2,"%s/INFO",path);
	if((fichier = fopen(path2,"w+")) == NULL)
		exit(-1);
	fprintf(fichier,"%s\n%s\n%d\n%d\n",rn.info.nom,rn.info.date,rn.info.reussite,rn.info.echec);
	for(i=0;i<rn.couche_fin->taille;i++)
		fprintf(fichier,"%s\n",rn.info.etiquettes[i]);
	fclose(fichier);
}
