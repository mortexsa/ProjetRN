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
//#include "01_09_02_bmp.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/dir.h>
#include <errno.h>
#include <sys/stat.h>

#include <gtk/gtk.h>

typedef struct INFO_FENETRE
{
	INFO_RN *info;
	GtkWidget *Window;
	int nombreReseau;
	int reseauSelectionner;
	char chemin[200];
} INFO_FENETRE;


int nombreReseau();
void viderContainer(GtkWidget *data);
void retourAccueille(GtkWidget *widget, gpointer data);
void selectReseau(GtkWidget *widget, gpointer data);
void traitement(GtkWidget *widget, gpointer data);
void resultatTraitement(GtkWidget *widget, gpointer data);
void page_principale(INFO_FENETRE *fenetre);
void creer_file_selection();
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
void creer_folder_selection (GtkButton * button, gpointer data);
void creation(GtkWidget *widget, gpointer data);
void creationRN(GtkWidget *widget, gpointer data);
void quitter(GtkWidget* widget);
void afficherInterface();
#endif
