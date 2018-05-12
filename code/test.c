#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"

#define WHT   "\x1B[8;47m"
#define BLK   "\x1B[8;40m"
#define RESET "\x1B[0m"
#include <gtk/gtk.h>

int main(int argc, char **argv)
{ 
	//printf("oui je marche parfaitement ! soumsoum t'inquiete pas et le nbr des sous reseaux sont :%d!\n",nombreReseau());
	
 gtk_init(&argc,&argv);//initialise la bibilo , toujours appeler en debut de programme 

 afficherInterface();

 gtk_main();//appeler dans toutes les fct gtk , cette fct attends le clique de la souris ou toucher le clavier 
	
	
	return 0;
}
