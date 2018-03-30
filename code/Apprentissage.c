#include "gestionnaire_RN.h"

void BackProp(RN, Image* ,char*)
{
	
}


void SigmoideDER(float* in, float* out, int taille)
{
	int i;
	float sig;
	
	for(i=0;i<taille;i++)
	{
		float sig = Sigmoide(in[i]);
		out[i] = sig*(1-sig);
	}
}


void Hadamard(float* in_a, float* in_b, float* out, int taille)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		out[i] = in_a[i]*in_b[i];
	}
}
