#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "gestionnaire_RN.h"
#include "gestionnaire_IO.h"

void BackProp(RN*, Image* ,char*);
//void SigmoideDER(float*, float*, int);
//void SigmoideINV(float*, float*, int);
void MultiplicationMatricielleTransposee(float**, float**, float**, int, int, int);
void Hadamard(float*, float*, float*, int);
float* fct_cout(RN,char*);

#endif
