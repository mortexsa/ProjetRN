/**
 * \file gestionnaire_IO.c
 * \brief Gestionnaire d'entrées sorties.
 * \author PEPIN Thibaut
 * \author REZGUI Soumia
 * \author SLIMANI Arezki
 * \author SELAQUET Severine
 * \author SZULEK Isaac
 * \author MONTIGNE Anthony
 *
 * Ce module s'occupe de lire , charger et sauvegarder les données.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/dir.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

#include "gestionnaire_IO.h"

#define debug printf("line : %d in function : %s in file %s\n",__LINE__,__func__,__FILE__);

/**
 * \fn Image* NouvelleImage(int w,int h)
 * \brief alloue la mémoire nécessaire pour stocker une image avec sa hauteur et largeur passées en parametres
 * 
 * \param w largeur de l'image
 * \param h Hauteur de l'image
 * \return renvoie l'adresse de l'image créée
 */
Image* NouvelleImage(int w,int h)
{
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->dat = calloc(1,w*h*sizeof(Pixel*));
	return I;
}



/**
 * \fn Image* CopieImage(Images* I)
 * \brief créé une copie de l'image passée en parametre
 * 
 * \param I l'image à copier
 * \return renvoie l'adresse de l'image copiée
 */
Image* CopieImage(Image* I)
{
	Image* res;
	if (!I)
		return NULL;
	res = NouvelleImage(I->w,I->h);
	memcpy(res->dat,I->dat,I->w*I->h*sizeof(Pixel));
	return res;
}

/**
 * \fn void DelImage(Images* I)
 * \brief libère la mémoire d'une variable de type Image
 * 
 * \param I l'image à supprimer
 */
void DelImage(Image* I)
{
	if (I)
	{
		free(I->dat);
		free(I);
	}
}

/**
 * \fn void SetPixel(Images* I, int i, int j, Pixel p)
 * \brief modifie le pixel aux coordonnées i*j de l'image passée en paramètre afin de correspondre au pixel p
 * 
 * \param I l'image à analyser
 * \param i,j coordonnées de l'image
 * \param p pixel correspondant
 * 
 */
void SetPixel(Image* I,int i,int j,Pixel p)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	I->dat[I->w*j+i] = p;
}

/**
 * \fn Pixel SetPixel(Images* I, int i, int j)
 * \brief obtenir le pixel aux coordonnées i*j de l'image passée en paramètre afin de correspondre au pixel p
 * 
 * \param I l'image à analyser
 * \param i,j coordonnées
 * \return renvoie le pixel de l'image 
 * 
 */
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

/**
 * \fn Image* ChargerBmp(const char* fichier, int, int)
 * \brief On lis une image de format bmp et on l'enregistre dans la structure Image.
 * 
 * \param fichier Chemin absolue de l'image à charger.
 * \param 
 * \return Image la structure qui stock le contenu d'une image.
 */
Image* ChargerBmp(const char* fichier, int w_max, int h_max)
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
	{
		debug
		fclose(F);
		//remove(fichier);
		return NULL;
	}  // mauvaise signature, ou BMP non supporté.
	if (head.imhead.bpp!=24)
	{
		debug
		fclose(F);
		//remove(fichier);
		return NULL;
	}  // supporte que le 24 bits pour l'instant
	if (head.imhead.compression!=0)
	{
		debug
		fclose(F);
		//remove(fichier);
		return NULL;
	}  // rarrissime, je ne sais même pas si un logiciel écrit/lit des BMP compressés. 
	if (head.imhead.cpalette!=0 || head.imhead.cIpalette!=0)
	{
		debug
		fclose(F);
		//remove(fichier);
		return NULL;
	} // pas de palette supportée, cependant, a bpp 24, il n'y a pas de palette.
	if(head.imhead.height != h_max || head.imhead.width != w_max)
	{
		debug
		fclose(F);
		//remove(fichier);
		return NULL;
	}
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
/**
 * \fn int Sauver(Image* I, const char* fichier)
 * \brief enregistrement de l'image passée en paramètre dans le fichier passé en paramètre au format bmp.
 * 
 * \param fichier Chemin absolue de l'endroit ou on va enregistrer l'image''.
 * \param  I l'image à enregistrer
 * \return int pour savoir si l'enregistrement c'est fait ou pas.
 */
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

/**
 * \fn Image* ChargerMnist(const char* path, int, int)
 * \brief lecture d'image de format Mnist non compressé et l'enregistre dans la structure Image, elle supprime le fichier de mauvais format.
 * \param path Chemin absolue de l'image à charger.
 * \param w_max largeur maximale de l'image
 * \param w_max largeur maximale de l'image
 * \return Image la structure qui stock le contenu d'une image.
 */
Image* ChargerMnist(const char* path, int w_max, int h_max)
{
	unsigned int t[4];
	
	FILE* fichier = fopen(path,"rb+");
	if(!fichier)
	{
		debug
		exit(-1);
	}
	
	fread(t,4,4,fichier);
	
	int k;
	for(k=0;k<4;k++)
	{
		t[k] = ((t[k]&0xFF)<<24) + ((t[k]&0xFF00)<<8) + ((t[k]&0xFF0000)>>8) + (t[k]>>24);
	}

	
	//printf("%u\n%u\n%u\n%u\n",t[0],t[1],t[2],t[3]);
	if(t[2] != h_max || t[3] != w_max)
	{
		debug
		fclose(fichier);
		//remove(path);
		return NULL;
	}
		
	Image* im = NouvelleImage(t[3],t[2]);
	
	fseek(fichier,t[1]*t[2]*t[3]-t[2]*t[3]+4*4,SEEK_SET);
	
	unsigned char tmp[t[3]*t[2]];
	fread(tmp,1,t[3]*t[2],fichier);
	
	t[1]--;
	t[1] = ((t[1]&0xFF)<<24) + ((t[1]&0xFF00)<<8) + ((t[1]&0xFF0000)>>8) + (t[1]>>24);
	fseek(fichier,4,SEEK_SET);
	fwrite(&t[1],4,1,fichier);
	
	fclose(fichier);
	
	if(t[1] == 0)
		remove(path);
	
	
	int i;
	for(i=0;i<t[3]*t[2];i++)
	{
		im->dat[i].r = tmp[i];
		im->dat[i].g = tmp[i];
		im->dat[i].b = tmp[i];
	}

	return im;
}

/**
 * \fn char* ChargerEtiquetteMNIST(const char* path)
 * \brief recuperer l'ettiquette du fichier passé e parametres, supprimser celui ci s'il contient plus d'images.
 * \param path Chemin absolue de l'etiquette à charger.
 * \return l'etiquette recupérée du fichier
 */
char* ChargerEtiquetteMNIST(const char* path)
{
	unsigned int t[2];
	
	FILE* fichier = fopen(path,"rb+");
	if(!fichier)
	{
		printf("%d\n",errno);
		debug
		exit(-1);
	}
	
	fread(t,4,2,fichier);
	
	int k;
	for(k=0;k<2;k++)
	{
		t[k] = ((t[k]&0xFF)<<24) + ((t[k]&0xFF00)<<8) + ((t[k]&0xFF0000)>>8) + (t[k]>>24);
	}
	
	//printf("%u\n%u\n",t[0],t[1]);
		
	char* c = malloc(sizeof(char)*2);
	fseek(fichier,t[1]-1+4*2,SEEK_SET);
	fread(c,1,1,fichier);
	*c += 48;
	c[1] = '\0';
	
	t[1]--;
	t[1] = ((t[1]&0xFF)<<24) + ((t[1]&0xFF00)<<8) + ((t[1]&0xFF0000)>>8) + (t[1]>>24);
	fseek(fichier,4,SEEK_SET);
	fwrite(&t[1],4,1,fichier);
	
	fclose(fichier);
	
	if(t[1] == 0)
		remove(path);
	
	return c;
}

/**
 * \fn App* ChargementCoupleAttIn(char* repertoire_app, int w_max, int h_max)
 * \brief rechercher dans le répertoire le premier couple donnée image et étiquette présent tout en supprimant tout fichier au mauvais format ou non reconnu
 * \param repertoire_app chemin absolue du repertoire de données
 * \return la structure app renvoie le couple image etiquette
 */
App* ChargementCoupleAttIn(char* repertoire_app, int w_max, int h_max)
{
	App* couple = malloc(sizeof(App));
	couple->image = NULL;
	
	DIR* rep = opendir(repertoire_app);
	if (rep == NULL)
        exit(1);
        
	char path[512],path2[512];
	struct dirent* fichier = NULL;
	
	while(!couple->image)
	{
		fichier = readdir(rep);
		if(!fichier)
			return NULL;
		
		//~ printf("%s\n",fichier->d_name);
		
		sprintf(path,"%s/%s",repertoire_app,fichier->d_name);
		//~ printf("%s\n",path);
		
		if(strcmp(fichier->d_name,".") == 0 || strcmp(fichier->d_name,"..") == 0);
		else if(strcmp(&(fichier->d_name[strlen(fichier->d_name) - strlen(".idx3-ubyte")]),".idx3-ubyte") == 0)
		{
			sprintf(path2,"%s",path);
			sprintf(&path2[strlen(path) - strlen(".idx3-ubyte")],".idx1-ubyte");
			//~ printf("%s\n",path2);
			
			if((couple->etiquette = ChargerEtiquetteMNIST(path2)))
			{
				couple->image = ChargerMnist(path, w_max, h_max);
			}
			else
			{
				remove(path);
				remove(path2);
			}
		}
		else if(strcmp(&(fichier->d_name[strlen(fichier->d_name) - strlen(".idx1-ubyte")]),".idx1-ubyte") == 0)
		{
			sprintf(path2,"%s",path);
			sprintf(&path2[strlen(path) - strlen(".idx1-ubyte")],".idx3-ubyte");
			//~ printf("%s\n",path2);
			
			//debug
			if((couple->etiquette = ChargerEtiquetteMNIST(path)))
			{
				couple->image = ChargerMnist(path2, w_max, h_max);
			}
			else
			{
				remove(path);
				remove(path2);
			}
		}
		else if(strcmp(&(fichier->d_name[strlen(fichier->d_name) - strlen(".bmp")]),".bmp") == 0)
		{
			if((couple->image = ChargerBmp(path, w_max, h_max)))
			{
				couple->etiquette = malloc(sizeof(char)*(strlen(fichier->d_name) - strlen(".bmp") + 1));
				strncpy(couple->etiquette,fichier->d_name,sizeof(char)*(strlen(fichier->d_name) - strlen(".bmp")));
			}
			else
			{
				remove(path);
			}
		}
		else
		{
			remove(path);
		}
	}
	closedir(rep);
	
	return couple;
}

/**
 * \fn INFO_RN* ChargerInfo()
 * \brief récupère les structures INFO_RN de tous les réseaux de neurones enrigistrés dans le repertoire ../sav/ et le retourne sous forme de tableau
 * \return renvoie l'adresse du tableau contenant tous les information sur les reseaux de neurones
 */
INFO_RN* ChargerInfo()
{
	char path[268],tmp[268];
	FILE* verif;
	int i = 0;
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
	
    if (closedir(rep) == -1){
    	debug
        exit(-1);
    }
    INFO_RN* res = malloc(i*sizeof(INFO_RN));
    rep = opendir("../sav");
	if (rep == NULL){
		debug
        exit(1);
	}
    
    i=0;

    while((fichier = readdir(rep))&&(fichier->d_type == DT_DIR))
    {

		sprintf(path,"../sav/%s/INFO",fichier->d_name);
		//printf("%s\n",path);
		verif = fopen(path,"r");
		if(verif)
		{

			fscanf(verif,"%s\n",tmp);
			//printf("%s\n", tmp);
			res[i].nom = malloc(strlen(tmp)*sizeof(char));
			strcpy(res[i].nom,tmp);
			
			fscanf(verif,"%s\n",tmp);
			res[i].date = malloc(strlen(tmp)*sizeof(char));
			strcpy(res[i].date,tmp);
			
			fscanf(verif,"%s\n",tmp);
			res[i].repertoire = malloc(strlen(tmp)*sizeof(char));
			strcpy(res[i].repertoire,tmp);
			
			fscanf(verif,"%d\n%d\n%d\n%d\n",&(res[i].w),&(res[i].h),&(res[i].reussite),&(res[i].echec));
			
			fclose(verif);
			i++;
		}
	}
	
    if(closedir(rep) == -1){
    	debug
		exit(-1);
    }
    
	return res;
}

/**
 * \fn RN* ChargerRN(INFO_RN *info)
 * \brief initialise et remplit un réseau de neurones dont les informations sont à l'emplacement passé en paramètres
 * \param info information sur le reseau de neurones choisi par l'utilisateur
 * \return renvoie l'adresse du reseau de neurone chargé
 */
RN* ChargerRN(INFO_RN *info) 
{
	//printf("%s\n%s\n", info->date,info->nom);
	RN* rn = initialisation(info);
	char path[100];
	int i = 1,j;
	sprintf(path,"../sav/%s_%s/C%d.rn",info->date,info->nom,i);
	FILE* fichier = fopen(path,"rb");	
	if(!fichier){
		debug
		exit(-1);
	}
	
	int t[2];
	fread(t,sizeof(int),2,fichier);
	
	AjoutPremiereCouche(rn,t[0]);
	
	fseek(fichier, 0, SEEK_SET);
	
	while(fichier)
	{
		fread(t,sizeof(int),2,fichier);
		//printf("%s\n%d %d\n",path,t[0],t[1]);
		
		Ajout_couche_Fin(rn,t[1]);
		
		fread(rn->couche_fin->B,sizeof(float),t[1],fichier);
		
		for(j=0;j<t[1];j++)
		{
			fread(rn->couche_fin->W[j],sizeof(float),t[0],fichier);
		}
		
		fclose(fichier);
		
		i++;
		sprintf(path,"../sav/%s_%s/C%d.rn",info->date,info->nom,i);
		fichier = fopen(path,"r");
	}
	
	sprintf(path,"../sav/%s_%s/INFO",info->date,info->nom);
	fichier = fopen(path,"rb");
	if(!fichier){
		debug
		exit(-1);
	}
	i=0;
	while(fgets(path, 1024, fichier))
		i++;
	i-=7;
	rn->info->etiquettes = malloc(i*sizeof(char*));
	fseek(fichier, 0, SEEK_SET);
	
	i=0;
	while(fgets(path, 1024, fichier))
	{
		if(i>=7)
		{
			path[strlen(path)-1] = '\0';
			//printf("%s\n",path);
			rn->info->etiquettes[i-7] = malloc(strlen(path)*sizeof(char));
			strcpy(rn->info->etiquettes[i-7],path);
		}
		i++;
	}
	fclose(fichier);
		
	return rn;
}

/**
 * \fn void SaveRN(RN rn) 
 * \brief va créer ou modifier tous les fichers nécessaires afin de sauvegarder le réseau de neurones passé en paramètre.
 * \param rn le reseau de neurone à recuperer
 */
void SaveRN(RN rn)
{
	DIR* rep;
	if((rep = opendir("../sav")) == NULL)
	{
		mkdir("../sav",S_IRWXU);
	}
	closedir(rep);
	
	char path[100];
	sprintf(path,"../sav/%s_%s",rn.info->date,rn.info->nom);
	
	if((rep = opendir(path)) == NULL)
	{
		mkdir(path,S_IRWXU);
	}
	closedir(rep);
	
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
			//printf("%s\n",path2);
			if((fichier = fopen(path2,"wb+")) == NULL)
			{
				printf("%d\n",errno);
				debug
				exit(-1);
			}
			
			temp[0] = tmp->prec->taille;
			temp[1] = tmp->taille;
			fwrite(temp,sizeof(int),2,fichier);
			
			//printf("%s\n%d %d\n",path2,temp[0],temp[1]);
			
			fwrite(tmp->B,sizeof(float),temp[1],fichier);
			
			for(m=0;m<temp[1];m++)
			{
				fwrite(tmp->W[m],sizeof(float),temp[0],fichier);
			}
			
			fclose(fichier);
			tmp = tmp->suiv;
			i++;
		}
	}
	
	sprintf(path2,"%s/INFO",path);
	if((fichier = fopen(path2,"w+")) == NULL)
	{
		debug
		exit(-1);
	}
	
	fprintf(fichier,"%s\n%s\n%s\n%d\n%d\n%d\n%d\n",rn.info->nom,rn.info->date,rn.info->repertoire,rn.info->w,rn.info->h,rn.info->reussite,rn.info->echec);
	
	for(i=0;i<rn.couche_fin->taille;i++)
		fprintf(fichier,"%s\n",rn.info->etiquettes[i]);
	
	fclose(fichier);
	
	
}

void LibererInfo(INFO_RN *info)
{
	RN *rn = ChargerRN(info);
	int i;
	for(i=0;i<rn->couche_fin->taille;i++)
	{
		free(info->etiquettes[i]);
	}
	
	free(info->nom);
	free(info->date);
	free(info->repertoire);
	libererRN(rn);
}


