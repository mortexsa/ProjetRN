#include "interface.h"
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

void page_principal(){
	int taille=nombreReseau();
	INFO_RN* info=ChargerInfo();
	GtkWidget *pWindow;
    GtkWidget *pLabel;
 	GtkWidget *pVBox;
 	GtkWidget *pHBox;
 	GtkWidget **pButton;
 	pButton = malloc((taille+2)*sizeof(GtkWidget*));
 	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "TFOu");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 640, 400);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    pVBox = gtk_vbox_new(FALSE, 0);
    pHBox = gtk_hbox_new(FALSE, 0);
    pLabel = gtk_label_new("Programme de merde");
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, FALSE, FALSE, 0);
    
    for(int i=0;i<taille;i++){
    pButton[i] = gtk_button_new_with_label(info[i].nom);
    gtk_box_pack_start(GTK_BOX(pVBox), pButton[i], FALSE, TRUE, 2);
    }
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, TRUE, 2);
    pButton[taille] = gtk_button_new_with_label("Creer");
    pButton[taille+1] = gtk_button_new_with_label("Quitter");
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[taille], TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[taille+1], TRUE, TRUE, 2);
    gtk_widget_show_all(pWindow);
    g_signal_connect(G_OBJECT(pButton[5]), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(pButton[4]), "clicked", G_CALLBACK(gtk_widget_hide),pWindow);
}


