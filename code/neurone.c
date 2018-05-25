/* Documentation tag for Doxygen
 */

/*! \mainpage Documentation
 *
 * \section Présentation
 *
 * Le but de l'application est de permettre créer et utiliser des réseaux de neurones de simplement. 
 * Les formats soutenues par l'application comme images a traiter sont le BMP et l'IDX.
 *
 * \section Compilation
 * GTK2 est necessaire a la compilation du projet, le package a installer est libgtk2.0-dev.
 * 
 * La compilation s'effectue simplement en utilisant le Makefile fourni :
 * 
 * lancez la commande : make pour compiler celui ci.
 * 
 * \section Utilisation
 * lancez la commande : make run pour lancer le programme.
 * 
 * Apres utilisattion n'oubliez pas d'effacer les executable en lancant la commande : make clean
 *
 * Pour plus de détails, consulter le manuel d'utilisation.
 * <BR><BR>
 *
 */

#include "neurone.h"

int main(int argc, char** argv)
{
 	gtk_init(&argc,&argv);//initialise la bibilo , toujours appeler en debut de programme 
 	afficherInterface();//On affiche l'interface
 	gtk_main();//appeler dans toutes les fct gtk , cette fct attends le clique de la souris ou toucher le clavier 
}
