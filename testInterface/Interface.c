#include "Interface.h"
#include <stdlib.h>
#include <gtk/gtk.h>



void page_principal(){
	GtkWidget *pWindow;
    GtkWidget *pLabel;
 	GtkWidget *pVBox;
 	GtkWidget *pHBox;
 	GtkWidget *pButton[6];
 	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "TFOu");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 640, 400);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    pVBox = gtk_vbox_new(FALSE, 0);
    pHBox = gtk_hbox_new(FALSE, 0);
    pLabel = gtk_label_new("Programme de merde");
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
    gtk_widget_show_all(pWindow);
    g_signal_connect(G_OBJECT(pButton[5]), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(pButton[4]), "clicked", G_CALLBACK(gtk_widget_hide),pWindow);
}

void page_creation(){
	GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pEntry;
    GtkWidget *pButton;
    GtkWidget *pLabel;
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Le widget GtkEntry");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 640, 400);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_widget_show_all(pWindow);
}

void test(){
   GtkWidget* pWindow;
   GtkWidget *pMainVBox;
   GtkWidget *pFrame;
   GtkWidget *pSpin;
 
   
 
   pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pWindow), "GtkSpinButton");
   gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
   gtk_container_set_border_width(GTK_CONTAINER(pWindow), 4);
 
   pMainVBox = gtk_vbox_new(TRUE, 0);
   gtk_container_add(GTK_CONTAINER(pWindow), pMainVBox);
 
   pFrame = gtk_frame_new("Rouge");
   /* Création du widget GtkSpinButton */
   pSpin = gtk_spin_button_new_with_range(0, 255, 1);
   gtk_container_add(GTK_CONTAINER(pFrame), pSpin);
   gtk_box_pack_start(GTK_BOX(pMainVBox), pFrame, FALSE, FALSE, 0);
 
   pFrame = gtk_frame_new("Vert");
   pSpin = gtk_spin_button_new_with_range(0, 255, 1);
   gtk_container_add(GTK_CONTAINER(pFrame), pSpin);
   gtk_box_pack_start(GTK_BOX(pMainVBox), pFrame, FALSE, FALSE, 0);
 
   pFrame = gtk_frame_new("Bleu");
   pSpin = gtk_spin_button_new_with_range(0, 255, 1);
   gtk_container_add(GTK_CONTAINER(pFrame), pSpin);
   gtk_box_pack_start(GTK_BOX(pMainVBox), pFrame, FALSE, FALSE, 0);
 
   gtk_widget_show_all(pWindow);
 
   g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

int main(int argc, char **argv)
{
 
  // gtk_init(&argc,&argv);
  // page_principal();
  // gtk_main();

  INFO_RN* merde = ChargerInfo();
 
  return EXIT_SUCCESS;
}