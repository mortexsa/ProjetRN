//#include "Interface.h"
#include <stdlib.h>
#include <gtk/gtk.h>
 
int main(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *pLabel;
 	GtkWidget *pVBox;
 	GtkWidget *pHBox;
 	GtkWidget *pButton[6];
    gtk_init(&argc,&argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Application");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 640, 400);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    pVBox = gtk_vbox_new(FALSE, 0);
    pHBox = gtk_hbox_new(FALSE, 0);
    pLabel = gtk_label_new("Manipulation Reseau de neurones");
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, FALSE, FALSE, 0);
    pButton[0] = gtk_button_new_with_label("Reseau 1");
    pButton[1] = gtk_button_new_with_label("Reseau 2");
    pButton[2] = gtk_button_new_with_label("Reseau 3");
    pButton[3] = gtk_button_new_with_label("Reseau 4");
    gtk_box_pack_start(GTK_BOX(pVBox), pButton[0], FALSE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(pVBox), pButton[1], FALSE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(pVBox), pButton[2], FALSE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(pVBox), pButton[3], FALSE, TRUE, 2);
    
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, TRUE, 2);
    pButton[4] = gtk_button_new_with_label("Creer");
    pButton[5] = gtk_button_new_with_label("Quitter");
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[4], TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[5], TRUE, TRUE, 2);
    g_signal_connect(G_OBJECT(pButton[5]), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(pWindow);
    gtk_main();
    
    
 
    return EXIT_SUCCESS;
}
