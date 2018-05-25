/**
 * \file interface.h
 * \brief Interface du programme.
 * \author PEPIN Thibaut
 * \author REZGUI Soumia
 * \author SLIMANI Arezki
 * \author SELAQUET Severine
 * \author SZULEK Isaac
 * \author MONTIGNET Anthony
 *
 * Interface du programme de reconnaissance d'image.
 *
 */
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

/**
 * \fn int nombreReseau()
 * \brief Nombre de Réseaux de neurones existant.
 *
 * \return int nombre de Réseau.
 */
int nombreReseau();

/**
 * \fn void viderContainer(GtkWidget *data)
 * \brief Vider le contenu de la fenetre.
 *
 * \param data Pour le passage de la structure INFO_FENETRE.
 */
void viderContainer(GtkWidget *data);

/**
 * \fn void retourAccueille(GtkWidget *widget, gpointer data)
 * \brief Retourner a la page d'accueille.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void retourAccueille(GtkWidget *widget, gpointer data);

/**
 * \fn void selectReseau(GtkWidget *widget, gpointer data)
 * \brief Selection d'un reseau de neurone.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void selectReseau(GtkWidget *widget, gpointer data);

/**
 * \fn void traitement(GtkWidget *widget, gpointer data)
 * \brief Lance le traitement d'une image.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void traitement(GtkWidget *widget, gpointer data);

/**
 * \fn void lancerApprentissage(GtkWidget *widget, gpointer data)
 * \brief Lancer l'apprentissage du réseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void lancerApprentissage(GtkWidget *widget, gpointer data);

/**
 * \fn void* fctThreadApp(void* arg)
 * \brief Fonction appeler par le thread qui fait l'apprentissage du reseau de neurone.
 *
 * \param arg Pour le passage de la structure INFO_FENETRE. 
 */
void* fctThreadApp(void* arg);

/**
 * \fn void matrice(GtkWidget *widget, gpointer data)
 * \brief Affichage de la matrice des poid du reseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void matrice(GtkWidget *widget, gpointer data);

/**
 * \fn void resultatTraitement(GtkWidget *widget, gpointer data)
 * \brief Affiche le résultat du traitement d'une image.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void resultatTraitement(GtkWidget *widget, gpointer data);

/**
 * \fn void page_principale(INFO_FENETRE *fenetre)
 * \brief Page d'accueille du programme
 *
 * \param fenetre La fenetre qu'on affichera dans l'accueille. 
 */
void page_principale(INFO_FENETRE *fenetre);

/**
 * \fn void creer_file_selection()
 * \brief Selection d'un fichier a analyser dans traitement.
 *
 */
void creer_file_selection();

/**
 * \fn void creer_folder_selection (GtkButton * button, gpointer data)
 * \brief Selection du dossier ou ce trouverons les données pour l'apprentissage.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void creer_folder_selection (GtkButton * button, gpointer data);

/**
 * \fn void creation(GtkWidget *widget, gpointer data)
 * \brief Interface de creation d'un reseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void creation(GtkWidget *widget, gpointer data);

/**
 * \fn void creation(GtkWidget *widget, gpointer data)
 * \brief Recuperation des données et sauvegarde du réseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void creationRN(GtkWidget *widget, gpointer data);

/**
 * \fn void quitter(GtkWidget *widget, gpointer data)
 * \brief Lorsque l'on quitte la fenetre.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void quitter(GtkWidget *widget, gpointer data);

/**
 * \fn void afficherInterface()
 * \brief Contenant toute l'interface et les fonction
 *
 */
void afficherInterface();
#endif
