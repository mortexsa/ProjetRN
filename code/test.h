

struct COUCHE
{
	float* A;
	float* B;
	float** W;
	
	float* DELTA;//plane
	float* tmp;//juste pour eviter d'avoir a faire des malloc dans la backprop pour stocker 2-3 truc
	
	int taille;
		
	struct COUCHE* prec;
	struct COUCHE* suiv;
};
typedef struct COUCHE COUCHE;
typedef COUCHE* Liste_Couche;

struct INFO_RN
{
	char** etiquettes;
	char* nom;
	char* date;
	int reussite;
	int echec;
};
typedef struct INFO_RN INFO_RN;

struct RN
{
	INFO_RN info;
	Liste_Couche couche_deb;
	Liste_Couche couche_fin;
};
typedef struct RN RN;


void BackProp(RN*, char*);
void SigmoidePrimeZ(float* in, float* out, int taille);
void MultiplicationMatricielleTransposeeTM(float**, float*, float*, int, int);
void Hadamard(float*, float*, float*, int);
void fct_cout(RN,char*);
