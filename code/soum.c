
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "gestionnaire_RN.h"
#include "Apprentissage.h"
#include "gestionnaire_IO.h"

int main(){
	int taille=0;
INFO_RN* info= ChargerInfo(taille);	
printf("la taille est :%d",taille);

//juste comme ça
printf("le nom est :%s",info[0].nom	);
	
	
	return 0 ;}
