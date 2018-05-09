#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "gestionnaire_RN.h"
#include "gestionnaire_IO.h"

void BackProp(RN*, Image* ,char*, float);
void SigmoidePrimeZ(type* in, type** out, int taille);
void MultiplicationMatricielleTransposeeTM(type**, type*, type*, int, int);
void MultiplicationMatricielleTransposeeMT(type*, type*, type**, int, int);
void Hadamard(type**, type*, type*, int);
void fct_cout(RN,char*);
void ModifPoids(type**, type**, int, int, float);
void ModifBiais(type*, type*, int, float);
void DelApp(App*);

#endif
