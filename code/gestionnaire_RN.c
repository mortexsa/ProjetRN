#include <math.h>


void MultiplicationMatriceVecteur(float* in_V, float** in_M, float* out, int taille_V,int taille_M)
{
	int i,j; 
	
	for(i=0;i<taille_M;i++)
	{
		out[i]=0;
		for(j=0;j<taille_V;j++)
		{
			out[i] += in_V[j]*in_M[i][j];
		}
	}
}

void AdditionVecteurVecteur(float* in_V1, float* in_V2, float* out, int taille)
{
	int i; 
	
	for(i=0;i<taille;i++)
	{
		out[i] = in_V1[i] + in_V2[i];
	}
}

void SigmoideV(float* in, float* out, int taille)
{
	int i; 
	
	for(i=0;i<taille;i++)
	{
		out[i]=Sigmoide(in[i]);
	}
}

float Sigmoide(float in)
{
	float expo = (float)exp(-x);
	return 1/(1+expo);
}

