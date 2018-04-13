#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include "Structures.h"
#include "gestionnaire_RN.h"

Image* ChargerBmp(const char* fichier);
Image* ChargerMnist(const char* fichier);
int Sauver(Image*,const char* fichier);
Image* NouvelleImage(int w,int h);
Image* CopieImage(Image*);
void SetPixel(Image*,int i,int j,Pixel p);
Pixel GetPixel(Image*,int i,int j);
void DelImage(Image*);



char* ChargerEtiquetteMNIST(const char* fichier);
char* ChargerEtiquetteBMP(const char* fichier);

INFO_RN* ChargerInfo();

RN* ChargerRN(INFO_RN info);
void SaveRN(RN);

#endif
