
#include "interface.h"

#include <stdlib.h>
#include <gtk/gtk.h>

int nombreReseau(){
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
    return i;
}

void page_principale(){	
	int taille=nombreReseau();
	INFO_RN* info=ChargerInfo();
	
	GtkWidget *Window;//poiteur sur la fenetre 
	GtkWidget *Vbox;
	GtkWidget *Hbox;
	GtkWidget **button;
	button = malloc((taille+2)*sizeof(GtkWidget*));
	GtkWidget *label;
	
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creation de la fenetre graphique par defaut elle aura une taille 200*200pixel
	
	gtk_window_set_default_size(GTK_WINDOW(Window), 640, 400); //donner les dimmenssion de la fenetre 
	
	g_signal_connect(G_OBJECT(Window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //pour pouvoir fermer la fenetre avec exit 
	
	
	Vbox = gtk_vbox_new(FALSE, 0);
	Hbox = gtk_hbox_new(FALSE, 0);
	
	label = gtk_label_new("Reseaux de neurones");
	
	gtk_container_add(GTK_CONTAINER(Window), Vbox);
	
	gtk_box_pack_start(GTK_BOX(Vbox), label, FALSE, FALSE, 0);
	
	for(int i=0;i<taille;i++){
    button[i] = gtk_button_new_with_label(info[i].nom);
    gtk_box_pack_start(GTK_BOX(Vbox), button[i], FALSE, TRUE, 2);
    }
	
	 
	gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);

    button[taille] = gtk_button_new_with_label("Creer");

    button[taille+1] = gtk_button_new_with_label("Quitter");

    gtk_box_pack_start(GTK_BOX(Hbox), button[taille], TRUE, TRUE, 2);

    gtk_box_pack_start(GTK_BOX(Hbox), button[taille+1], TRUE, TRUE, 2);
	 
	gtk_widget_show_all(Window); //afin d'afficher tout dans la fenetre 
  
    g_signal_connect(G_OBJECT(button[taille+1]), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    //g_signal_connect(G_OBJECT(button[taille]), "clicked", G_CALLBACK(gtk_widget_hide),Window); //elle ne fait qu'effacer le boutton 
    
    
	}

