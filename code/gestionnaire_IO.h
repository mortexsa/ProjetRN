#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include "Structures.h"
#include "gestionnaire_RN.h"

Image* ChargerBmp(const char* fichier, int, int);
Image* ChargerMnist(const char* fichier, int, int);
int Sauver(Image*,const char* fichier);
Image* NouvelleImage(int w,int h);
Image* CopieImage(Image*);
void SetPixel(Image*,int i,int j,Pixel p);
Pixel GetPixel(Image*,int i,int j);
void DelImage(Image*);



char* ChargerEtiquetteMNIST(const char* path);

App* ChargementCoupleAttIn(char* repertoire_app, int w_max, int h_max);

INFO_RN* ChargerInfo();

RN* ChargerRN(INFO_RN *info);
void SaveRN(RN);

#endif
