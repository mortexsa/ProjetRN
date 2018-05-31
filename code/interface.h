#ifndef INTER_H
#define INTER_H

#include "gestionnaire_RN.h"
#include "Apprentissage.h"
#include "gestionnaire_IO.h"
#include "Structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/dir.h>
#include <errno.h>
#include <sys/stat.h>

#include <gtk/gtk.h>

/**
 * \struct INFO_FENETRE
 * \brief Information circulant entre les fonctions
 *
 * INFO_FENETRE est un objet de transmission des informations 
 * entre les differentes fonction et fenetres.
 */
typedef struct INFO_FENETRE
{
	INFO_RN *info; /*!< Structure contenant tout les Réseaux de neurone existant. */
	GtkWidget *Window; /*!< Fenetre principal qu'on modifie dans les fonctions. */
	int nombreReseau;	/*!< Nombre de Réseaux de neurones. */
	int reseauSelectionner; /*!< Réseau sélectionner */
	char chemin[200]; /*!< Chemin des fichier ou dossier à enregistrer */
	int etatBoutton; /*!< Etat du boutton Apprentissage du réseau de neurones */
} INFO_FENETRE;


int nombreReseau();
void viderContainer(GtkWidget *data);
void retourAccueille(GtkWidget *widget, gpointer data);
void selectReseau(GtkWidget *widget, gpointer data);
void traitement(GtkWidget *widget, gpointer data);
void resultatTraitement(GtkWidget *widget, gpointer data);
void lancerApprentissage(GtkWidget *widget, gpointer data);
void* fctThreadApp(gpointer data);
void matrice(GtkWidget *widget, gpointer data);
void* fctMatriceThread(gpointer data);
void page_principale(INFO_FENETRE *fenetre);
void creation(GtkWidget *widget, gpointer data);
void creationRN(GtkWidget *widget, gpointer data);
void creer_file_selection();
void creer_folder_selection (GtkButton * button, gpointer data);
void quitter(GtkWidget *widget, gpointer data);
void afficherInterface();
#endif
