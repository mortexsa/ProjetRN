#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include "Structures.h"

Image* ChargerBmp(const char* fichier);
Image* ChargerMnist(const char* fichier);
int Sauver(Image*,const char* fichier);
Image* NouvelleImage(int w,int h);
Image* CopieImage(Image*);
void SetPixel(Image*,int i,int j,Pixel p);
Pixel GetPixel(Image*,int i,int j);
void DelImage(Image*);



char* ChargerEtiquette(const char* fichier);

RN* ChargerRN(const char* fichier);
void SaveRN(RN);

#endif

//~ #ifndef STR_H
//~ #define STR_H
//~ #include "Structures.h"
//~ #endif



//~ Image* ChargerBmp(const char* fichier);
//~ Image* ChargerMnist(const char* fichier);
//~ int Sauver(Image*,const char* fichier);
//~ Image* NouvelleImage(int w,int h);
//~ Image* CopieImage(Image*);
//~ void SetPixel(Image*,int i,int j,Pixel p);
//~ Pixel GetPixel(Image*,int i,int j);
//~ void DelImage(Image*);



//~ char* ChargerEtiquette(const char* fichier);

//~ //RN* ChargerRN(const char* fichier);
//~ void SaveRN(RN);

