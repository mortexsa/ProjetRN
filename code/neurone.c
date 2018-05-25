#include "neurone.h"

int main(int argc, char** argv)
{
 	gtk_init(&argc,&argv);//initialise la bibilo , toujours appeler en debut de programme 
 	afficherInterface();//On affiche l'interface
 	gtk_main();//appeler dans toutes les fct gtk , cette fct attends le clique de la souris ou toucher le clavier 
}
