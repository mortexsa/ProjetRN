#ifndef RN_H
#define RN_H

#include "Structures.h"


void MultiplicationMatriceVecteur(float**, float*, float*, int, int);
void AdditionVecteurVecteur(float*, float*, float*, int);
void SigmoideV(float*, float*, int);
float Sigmoide(float);
RN* initialisation(INFO_RN);
void Remplissage(RN rn); 
void Ajout_couche_FinFin(RN, float*, float**);
void Propagation(Image*, RN);
char** Reconnaissance(RN);



#endif
