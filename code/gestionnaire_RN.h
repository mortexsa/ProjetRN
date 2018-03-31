#ifndef RN_H
#define RN_H

#include "Structures.h"

void initialisation(RN*, INFO_RN);

void AjoutFin(RN, float*, float**);

void Traitement(Image*, RN);
char** Reconnaissance(RN);//wtf pk tu t appelle reconnaissance si t es meme pas reconnue ?!

void MultiplicationMatricielle(float**, float**, float**, int, int, int);
void AdditionVecteurVecteur(float*, float*, float*, int);
void SigmoideV(float*, float*, int);
float Sigmoide(float);

#endif



//~ #ifndef STR_H
//~ #define STR_H
//~ #include "Structures.h"
//~ #endif

//~ void initialisation(RN*, INFO_RN);

//~ void AjoutFin(RN, float*, float**);

//~ void Traitement(Image*, RN); //inclure IO.h pour qu'il reconnaisse la structure Image
//~ char** Reconnaissance(RN);

//~ void MultiplicationMatricielle(float**, float**, float**, int, int, int);
//~ void AdditionVecteurVecteur(float*, float*, float*, int);
//~ void SigmoideV(float*, float*, int);
//~ float Sigmoide(float);


