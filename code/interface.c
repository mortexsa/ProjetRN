
#include "interface.h"



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

void viderContainer(GtkWidget *data){
     GList *children = gtk_container_get_children(GTK_CONTAINER(data));

    while (children) {
        gtk_widget_destroy(children->data);
        children = g_list_next(children);
    }

    g_list_free(children);
}

void retourAccueille(GtkWidget *widget, gpointer data){
    //pour suprimer l'ancienne page
    viderContainer(data);
    page_principale(data);
}

void selectReseau(GtkWidget *widget, gpointer data){
    INFO_RN *info = (INFO_RN*) data;
    GtkWidget *pWidget = gtk_widget_get_parent(widget);
    GtkWidget *label;
    viderContainer(pWidget);
    char tab[200];
    strcpy(tab, "Nom du Reseau de Neurone :  ");
    label = gtk_label_new(strcat(tab,info->nom));
    gtk_box_pack_start(GTK_BOX(pWidget), label, FALSE, FALSE, 0);

    gtk_widget_show_all(pWidget);
}

// //delete evenement 

// /*static gboolean delet_event(GtkWidget *window, Gtkgpointer data){
// 	}*/
	
void page_principale(GtkWidget *Window){	
	int taille=nombreReseau();
	INFO_RN* info=ChargerInfo();
	GtkWidget *Vbox;
	GtkWidget *Hbox;
	GtkWidget **button;
	button = malloc((taille+2)*sizeof(GtkWidget*));
	GtkWidget *label;
	int tmp = -1;
	
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
    g_signal_connect(G_OBJECT(button[i]), "clicked", G_CALLBACK(selectReseau),&info[i]);
    }
	
	 
	gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);

    button[taille] = gtk_button_new_with_label("Creer");

    button[taille+1] = gtk_button_new_with_label("Quitter");

    gtk_box_pack_start(GTK_BOX(Hbox), button[taille], TRUE, TRUE, 2);

    gtk_box_pack_start(GTK_BOX(Hbox), button[taille+1], TRUE, TRUE, 2);
	 
	gtk_widget_show_all(Window); //afin d'afficher tout dans la fenetre 
  
    g_signal_connect(G_OBJECT(button[taille+1]), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button[taille]), "clicked", G_CALLBACK(creation),Window); 
    
    
	}

void creation(GtkWidget *widget, gpointer data){

  //pour suprimer l'ancienne page
    viderContainer(data);

    //GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pFrame;
    GtkWidget *pVBoxFrame;
    GtkWidget *pSeparator;
    GtkWidget *pEntry;
    GtkWidget *pLabel;
    gchar *sUtf8;
    
//pour les boutons    
    GtkWidget *pHBox;
    GtkWidget *pButton[2];
    
    //destroyed(window,data);
     
    // pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    

    //   On ajoute un espace de 5 sur les bords de la fenetre */
    //   gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
    //   gtk_window_set_title(GTK_WINDOW(pWindow), "Creation Reseaux de neurones ");
    //   gtk_window_set_default_size(GTK_WINDOW(data), 500, 400);
    
 
 //pour mes boutons 
    pHBox = gtk_hbox_new(FALSE, 0);
    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(data), pVBox);
 
    /* Creation du premier GtkFrame */
    pFrame = gtk_frame_new("parametres du Reseau :");
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);
    
    /* Creation et insertion d une boite pour le premier GtkFrame */
    pVBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);
 
    /* Creation et insertion des elements contenus dans le premier GtkFrame */
    pLabel = gtk_label_new("Nom du Reseau de neurones :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new(); //pour que l'utilisateur peut saisir une entrée
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
    
    sUtf8 = g_locale_to_utf8("nombre de couches cachées :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    sUtf8 = g_locale_to_utf8("nombre de neurones cachés :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
   /* Creation d un GtkHSeparator */
    pSeparator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSeparator, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("etiquette de sortie :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new(); 
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    /* Creation du deuxieme GtkFrame */
    pFrame = gtk_frame_new("Choix repertoire :");
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);
    
 
    /* Creation et insertion d une boite pour le deuxieme GtkFrame */
    pVBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);
    
    pLabel = gtk_label_new("nom repertoire :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
    
    //definir la taille max des images qu'il devra analyser 
     sUtf8 = g_locale_to_utf8("taille max :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
  //afficher les bouton dans la même frame 
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, FALSE, 2);
 
   //gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);
    pButton[0] = gtk_button_new_with_label("Creer");
    pButton[1] = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[1], TRUE, TRUE, 0);
    //g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(page_principale), NULL);
    g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(retourAccueille), data);
    
     //g_signal_connect(G_OBJECT(pEntry), "activate", G_CALLBACK(activate_entry), (GtkWidget*) pLabel);
    /* g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(creation_RN), (GtkWidget*) pLabel);*/
    gtk_widget_show_all(data);
}

void afficherInterface(){
    GtkWidget *Window;
    Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creation de la fenetre graphique par defaut elle aura une taille 200*200pixel
    page_principale(Window);
}
