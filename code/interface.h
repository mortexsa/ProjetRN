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
} INFO_FENETRE;


int nombreReseau();
void viderContainer(GtkWidget *data);
void retourAccueille(GtkWidget *widget, gpointer data);
void selectReseau(GtkWidget *widget, gpointer data);
<<<<<<< HEAD
void page_principale(GtkWidget *Window);
=======
void traitement(GtkWidget *widget, gpointer data);
void page_principale(INFO_FENETRE *fenetre);
>>>>>>> 2e3fc7f984bb0529153160b304ac3c1e88d54c6c
void creer_folder_selection (GtkButton * button, gpointer data);
void creation(GtkWidget *widget, gpointer data);
void quitter(GtkWidget* widget);
void afficherInterface();
#endif
