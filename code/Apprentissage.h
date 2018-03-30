#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "gestionnaire_RN.h"

void BackProp(RN*, Image* ,char*);
void SigmoideDER(float*, float*, int);
void SigmoideINV(float*, float*, int);
void Hadamard(float*, float*, float*, int);
float* fct_cout(RN,char*);

#endif
