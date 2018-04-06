#ifndef RN_H
#define RN_H

#include "Structures.h"

RN* initialisation(INFO_RN);

void AjoutFin(RN, float*, float**);

void Traitement(Image*, RN);
char** Reconnaissance(RN);

void MultiplicationMatricielle(float**, float**, float**, int, int, int);
void AdditionVecteurVecteur(float*, float*, float*, int);
void SigmoideV(float*, float*, int);
float Sigmoide(float);

#endif
