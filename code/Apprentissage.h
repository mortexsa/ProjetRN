#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "gestionnaire_RN.h"
#include "gestionnaire_IO.h"

void BackProp(RN*, Image* ,char*);
//void SigmoideDER(float*, float*, int); //sert a rien normalement
//void SigmoideINV(float*, float*, int); //sert a rien normalement
void SigmoidePrimeZ(float* in, float* out, int taille);
void MultiplicationMatricielleTransposeeTM(float**, float*, float*, int, int);
void MultiplicationMatricielleTransposeeMT(float**, float**, float**, int, int, int);
void Hadamard(float*, float*, float*, int);
//~ float* fct_cout(RN,char*);
void fct_cout(RN,char*);

#endif


//~ #ifndef RN_H
//~ #define RN_H
//~ #include "gestionnaire_RN.h"
//~ #endif

//~ #ifndef IO_H
//~ #define IO_H
//~ #include "gestionnaire_IO.h"
//~ #endif

//~ void BackProp(RN*, Image* ,char*);
//~ //void SigmoideDER(float*, float*, int);
//~ //void SigmoideINV(float*, float*, int);
//~ void MultiplicationMatricielleTransposee(float**, float**, float**, int, int, int);
//~ void Hadamard(float*, float*, float*, int);
//~ float* fct_cout(RN,char*);

