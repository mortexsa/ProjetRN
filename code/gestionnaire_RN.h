
struct COUCHE
{
	float* A;
	float* B;
	float** W;
	
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

void initialisation(RN*, INFO_RN);


void AjoutFin(RN, float*, float**);


void Traitement(Image*, RN);
char** Reconnaissance(RN);

void MultiplicationMatriceVecteur(float*, float**, float*, int, int);
void AdditionVecteurVecteur(float*, float*, float*, int);
void SigmoideV(float*, float*, int);
float Sigmoide(float);


