
struct COUCHE
{
	float* A;
	float* B;
	float** W;
		
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
	Liste_Couche couche;
};
typedef struct RN RN;

void initialisation(RN*, INFO_RN);
void AjoutFin(RN, float*, float, float**);


char* Traitement(Image*, RN);

void MultiplicationMatriceVecteur(float*, float**, float*);
void AdditionVecteurVecteur(float*, float*, float*);
void Sigmoide(float*);

