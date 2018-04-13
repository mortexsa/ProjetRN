#ifndef RN_H
#define RN_H

#include "Structures.h"


void MultiplicationMatriceVecteur(float**, float*, float*, int, int);
void AdditionVecteurVecteur(float*, float*, float*, int);
void SigmoideV(float*, float*, int);
float Sigmoide(float);
RN* initialisation(INFO_RN);
void Remplissage(RN rn); 
void Ajout_couche_Fin(RN* rn, int taille);
void AjoutPremiereCouche(RN* rn, int taille);
void Propagation(Image*, RN);
char** Reconnaissance(RN);


#endif
