#include "interface.h"


void afficherkloul(){
	int i=0;
	DIR* rep = opendir("../sav");
	if (rep == NULL)
        exit(1);
    struct dirent* fichier = NULL;
    while((fichier = readdir(rep))&&(fichier->d_type == DT_DIR)){
    	if(!(!strcmp(fichier->d_name,"..") || !strcmp(fichier->d_name,"."))){
    		i++;
		}
    }
	
	INFO_RN* merde = ChargerInfo();
	etiquettes;
	nom;
	date;
	reussite;
	echec;
}
