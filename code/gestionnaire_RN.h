#ifndef RN_H
#define RN_H

#include "Structures.h"


void MultiplicationMatriceVecteur(type**, type*, type*, int, int);
void AdditionVecteurVecteur(type*, type*, type*, int);
void SigmoideV(type*, type*, int);
type Sigmoide(type);
RN* initialisation(INFO_RN);
void Remplissage(RN rn); 
void Ajout_couche_Fin(RN* rn, int taille);
void AjoutPremiereCouche(RN* rn, int taille);
void Propagation(Image*, RN);
char** Reconnaissance(RN);


#endif
