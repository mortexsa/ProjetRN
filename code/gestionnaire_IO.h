#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include "gestionnaire_RN.h"

typedef struct Pixel
{
	unsigned char r,g,b;
} Pixel;

typedef struct Image
{
	int w,h;
	Pixel* dat;
} Image;

Image* ChargerBmp(const char* fichier);
Image* ChargerMnist(const char* fichier);
int Sauver(Image*,const char* fichier);
Image* NouvelleImage(int w,int h);
Image* CopieImage(Image*);
void SetPixel(Image*,int i,int j,Pixel p);
Pixel GetPixel(Image*,int i,int j);
void DelImage(Image*);



char* ChargerEtiquette(const char* fichier);

//RN* ChargerRN(const char* fichier);
void SaveRN(RN);

#endif
