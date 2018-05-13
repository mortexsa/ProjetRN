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

int nombreReseau();
void viderContainer(GtkWidget *data);
void retourAccueille(GtkWidget *widget, gpointer data);
void selectReseau(GtkWidget *widget, gpointer data);
void page_principale(GtkWidget *Window);
void creation(GtkWidget *widget, gpointer data);
void afficherInterface();
#endif
