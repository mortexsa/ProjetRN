#include "gestionnaire_RN.h"
#include <strings.h>
#include <math.h>


//calcul de l'erreur 

float* fct_cout(RN rn ,char* eti){
	
float* errtmp = malloc(rn.couche_fin->taille*sizeof(float));	

for(int i=0;i<rn.couche_fin->taille;i++){
	errtmp[i] = (rn.couche->A[i] - ((strcmp(eti,rn.info.etiquettes[i]))==0)?1:0);	
	}
	}
	
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
