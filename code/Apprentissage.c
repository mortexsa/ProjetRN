#include "gestionnaire_RN.h"

void BackProp(RN* rn, Image* im,char* sortie_att)
{
	Traitement(im, rn*);
	char** sortie_calc = Reconnaissance(rn*);
	
	if(strcmp(sortie_calc[0],sortie_att)==0)
		rn->info.reussite++;
	else
		rn->info.echec++;
	
	float* cout = fct_cout(rn*, sortie_att);
}

void SigmoideDER(float* in, float* out, int taille)
{
	int i;
	float sig;
	
	for(i=0;i<taille;i++)
	{
		sig = Sigmoide(in[i]);
		out[i] = sig*(1-sig);
	}
}

void SigmoideINV(float* in, float* out, int taille)
{
	int i;
	double tmp;
	
	for(i=0;i<taille;i++)
	{
		tmp = -log(1/in[i] - 1);
		out[i] = (float)tmp;
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
