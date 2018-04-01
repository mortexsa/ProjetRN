#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "gestionnaire_RN.h"
#include "gestionnaire_IO.h"

void BackProp(RN*, Image* ,char*);
void SigmoidePrimeZ(float* in, float* out, int taille);
void MultiplicationMatricielleTransposeeTM(float**, float*, float*, int, int);
void MultiplicationMatricielleTransposeeMT(float**, float**, float**, int, int, int);
void Hadamard(float*, float*, float*, int);
void fct_cout(RN,char*);

#endif
