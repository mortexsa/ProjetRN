
#include "interface.h"
#define Cmax 5


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
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    viderContainer(fenetre->Window);
    page_principale(fenetre);
}

void traitement(GtkWidget *widget, gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    
    gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Traitement d'images");
    viderContainer(fenetre->Window);
    
    GtkWidget *Vbox;
    GtkWidget *Hbox;
    GtkWidget *button[3];
    GtkWidget *label;
    
    Vbox = gtk_vbox_new(FALSE, 0);
    Hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(fenetre->Window), Vbox);
    
    char tab[200];
    strcpy(tab, "Lancer un traitement d'images sur le Reseau: ");
    
    char resultat[200];
    label = gtk_label_new(strcat(tab,fenetre->info[fenetre->reseauSelectionner].nom));
    gtk_box_pack_start(GTK_BOX(Vbox), label, FALSE, FALSE, 0);
    strcpy(tab,"Choisissez un fichier");
    if(fenetre->chemin[0] != 0){
        strcpy(resultat,fenetre->chemin);
        char *parse = strtok(resultat,"/");
        while(parse != NULL){
            strcpy(resultat,parse);
            parse = strtok(NULL, "/");
        }
        strcpy(tab,"Fichier Choisi : ");
        strcat(tab,resultat);
    }

    button[0] = gtk_button_new_with_label(tab);
    gtk_box_pack_start(GTK_BOX(Vbox), button[0], FALSE, TRUE, 20);

    gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);
    button[1] = gtk_button_new_with_label("Retour");
    button[2] = gtk_button_new_with_label("Lancer");

    gtk_box_pack_start(GTK_BOX(Hbox), button[1], TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(Hbox), button[2], TRUE, TRUE, 2);

    gtk_widget_show_all(fenetre->Window);
    g_signal_connect(G_OBJECT(button[1]), "clicked", G_CALLBACK(selectReseau), fenetre);
    g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(creer_file_selection), fenetre);
    g_signal_connect(G_OBJECT(button[2]), "clicked", G_CALLBACK(resultatTraitement), fenetre);
}

void resultatTraitement(GtkWidget *widget, gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    
    gtk_window_set_title(GTK_WINDOW(fenetre->Window), "TOP 3 des Resultats ");
    viderContainer(fenetre->Window);
    
    GtkWidget* pLabel;
    GtkWidget *label;
    GtkWidget *Vbox;
    GtkWidget *Hbox;
 	INFO_RN *k=fenetre->info;	  
	//~ RN *rn1 =initialisation(k); 
	//~ RN *rn= ChargerRN(k); //charger RN
	RN *rn = initialisation(k); 
	rn = ChargerRN(k); //charger RN
	
	
	char** rec;
 	//~ char** rec=malloc(sizeof(char*)*3);
 	//~ for(int i=0;i<3;i++){
		//~ rec[i]=malloc(sizeof(char));}
 	
    Image * image;
    char resultat[200];
    strcpy(resultat,fenetre->chemin);
    char *parse = strtok(resultat,".");
    while(parse != NULL){
        strcpy(resultat,parse);
        parse = strtok(NULL, ".");
    }
    
   printf("yew %s\n", fenetre->chemin);
 
    if(strcmp(resultat,"bmp") == 0)
    {
        //~ image = ChargerBmp(fenetre->chemin,rn[fenetre->reseauSelectionner].info->w, rn[fenetre->reseauSelectionner].info->h);
        image = ChargerBmp(fenetre->chemin,rn->info->w, rn->info->h);
        if(image == NULL) printf("HAHAHAHAHAHAHAHAHAHHAAH\n");
        Propagation(image,*rn);
	}
	
	//~ rec = Reconnaissance(rn[fenetre->reseauSelectionner]);
	rec = Reconnaissance(*rn);
	int j=0;
	 Vbox = gtk_vbox_new(FALSE, 0);
	Hbox = gtk_hbox_new(FALSE, 0);

gtk_container_add(GTK_CONTAINER(fenetre->Window), Vbox);
	
	label = gtk_label_new("resultat 1: " );	
	gtk_box_pack_start(GTK_BOX(Vbox), label, TRUE, FALSE, 2);
	label = gtk_label_new(rec[j]);	
	gtk_box_pack_start(GTK_BOX(Hbox), label, TRUE, FALSE, 2);
		
    pLabel = gtk_label_new("resultat 2 :");
    gtk_box_pack_start(GTK_BOX(Vbox), pLabel, TRUE, FALSE, 2);
    pLabel = gtk_label_new("resultat 3 :");
    gtk_box_pack_start(GTK_BOX(Vbox), pLabel, TRUE, FALSE, 2);
    
    
    
 
  
 
    /* Affichage de la fenêtré et de tout ce qu'il contient */
    gtk_widget_show_all(fenetre->Window);  
    
    

}

void selectReseau(GtkWidget *widget, gpointer data){

    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Tableau de bord");
    char titre[256];
    strcpy(titre,gtk_button_get_label((GtkButton *)widget));
    if(fenetre->chemin[0] != 0){
        for(int w = 0;w<200;w++){
            fenetre->chemin[w] = 0;
        }
    }
    GtkWidget *label;
    GtkWidget *button[4];
    GtkWidget *Vbox;
    GtkWidget *Hbox;
    Vbox = gtk_vbox_new(FALSE, 0);
    Hbox = gtk_hbox_new(FALSE, 0);
    if(fenetre->reseauSelectionner == -1){
        int i = 16;
        int j = 0;
        char name[50] = {0};
        char date[20] = {0};
        while(titre[i] != '\n'){
            name[j] = titre[i];
            i++;
            j++;
        }
        i += 20;
        j = 0;
        int indiceReseau = 0;
        while(titre[i] != '\0'){
            date[j] = titre[i];
            i++;
            j++;
        }
        for(i=0;i<fenetre->nombreReseau;i++){
            if(strcmp(fenetre->info[i].nom,name) == 0){
                if(strcmp(fenetre->info[i].date,date) == 0){
                   fenetre->reseauSelectionner = i; 
                }
            }
        }
    }
    Hbox = gtk_hbox_new(FALSE, 0);
    char tab[200];
    strcpy(tab, "Nom du Reseau de Neurone :  ");
    viderContainer(fenetre->Window);
    
    gtk_container_add(GTK_CONTAINER(fenetre->Window), Vbox);
    
    label = gtk_label_new(strcat(tab,fenetre->info[fenetre->reseauSelectionner].nom));
    gtk_box_pack_start(GTK_BOX(Vbox), label, FALSE, FALSE, 0);
    
    strcpy(tab, "Pourcentage de reussite :  ");
    char b[100];
    double pourcentageReussite = 0;
    if(fenetre->info[fenetre->reseauSelectionner].reussite != 0){
    	pourcentageReussite = ((double)fenetre->info[fenetre->reseauSelectionner].reussite / (fenetre->info[fenetre->reseauSelectionner].reussite + fenetre->info[fenetre->reseauSelectionner].echec)) * 100;
    }
    sprintf(b,"%.3f", pourcentageReussite);
    strcat(tab,b);
    label = gtk_label_new(strcat(tab," %"));    
    gtk_box_pack_start(GTK_BOX(Vbox), label, FALSE, FALSE, 0);

    strcpy(tab, "Date de creation :  ");
    label = gtk_label_new(strcat(tab,fenetre->info[fenetre->reseauSelectionner].date));    
    gtk_box_pack_start(GTK_BOX(Vbox), label, FALSE, FALSE, 0);
    
    button[0] = gtk_button_new_with_label("Afficher la matrice des poids");
    gtk_box_pack_start(GTK_BOX(Vbox), button[0], FALSE, TRUE, 2);


    gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);
    
    button[1] = gtk_button_new_with_label("Retour");
    button[2] = gtk_button_new_with_label("Traitement");
    button[3] = gtk_button_new_with_label("Apprentissage");
    
    gtk_box_pack_start(GTK_BOX(Hbox), button[1], TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(Hbox), button[2], TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(Hbox), button[3], TRUE, TRUE, 2);

    gtk_widget_show_all(fenetre->Window);

    g_signal_connect(G_OBJECT(button[1]), "clicked", G_CALLBACK(retourAccueille), fenetre);
    g_signal_connect(G_OBJECT(button[2]), "clicked", G_CALLBACK(traitement), fenetre);

    
}

// //delete evenement 

// /*static gboolean delet_event(GtkWidget *window, Gtkgpointer data){
// 	}*/
	
void page_principale(INFO_FENETRE *fenetre){
	gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Accueil");	
	fenetre->info = ChargerInfo();
    fenetre->nombreReseau = nombreReseau();
    fenetre->reseauSelectionner = -1;
	GtkWidget *Vbox;
	GtkWidget *Hbox;
	GtkWidget **button;
	button = malloc((fenetre->nombreReseau+2)*sizeof(GtkWidget*));
	GtkWidget *label;
	
	gtk_window_set_default_size(GTK_WINDOW(fenetre->Window), 640, 400); //donner les dimmenssion de la fenetre 
	
	g_signal_connect(G_OBJECT(fenetre->Window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //pour pouvoir fermer la fenetre avec exit 
	
	
	Vbox = gtk_vbox_new(FALSE, 0);
	Hbox = gtk_hbox_new(FALSE, 0);
	
	label = gtk_label_new("Reseaux de neurones");
	
	gtk_container_add(GTK_CONTAINER(fenetre->Window), Vbox);
	
	gtk_box_pack_start(GTK_BOX(Vbox), label, FALSE, FALSE, 0);
	char tab[200];
	for(int i=0;i<fenetre->nombreReseau;i++){
    strcpy(tab,"Nom du Reseau : ");
    strcat(tab, fenetre->info[i].nom); 
    strcat(tab,"\nDate de creation : "); 
    strcat(tab,fenetre->info[i].date); 
    button[i] = gtk_button_new_with_label(tab);
    gtk_box_pack_start(GTK_BOX(Vbox), button[i], FALSE, TRUE, 2);
    g_signal_connect(G_OBJECT(button[i]), "clicked", G_CALLBACK(selectReseau),fenetre);
    }
	
	 
	gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);

    button[fenetre->nombreReseau] = gtk_button_new_with_label("Creer");

    button[fenetre->nombreReseau+1] = gtk_button_new_with_label("Quitter");

    gtk_box_pack_start(GTK_BOX(Hbox), button[fenetre->nombreReseau], TRUE, TRUE, 2);

    gtk_box_pack_start(GTK_BOX(Hbox), button[fenetre->nombreReseau+1], TRUE, TRUE, 2);
	 
	gtk_widget_show_all(fenetre->Window); //afin d'afficher tout dans la fenetre 
  
    g_signal_connect(G_OBJECT(button[fenetre->nombreReseau+1]), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button[fenetre->nombreReseau]), "clicked", G_CALLBACK(creation),fenetre); 
    
    
	}

void creation(GtkWidget *widget, gpointer data){

  //pour suprimer l'ancienne page
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Creation d'un reseau");
    viderContainer(fenetre->Window);

    //GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pEntry[6];
    GtkWidget *pLabel;
    gchar *sUtf8;
    
//pour les boutons    
    GtkWidget *pHBox;
    GtkWidget *pButton[2];
    GtkWidget *bouton_explorer;
   
    pHBox = gtk_hbox_new(TRUE, 0);
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(fenetre->Window), pVBox);
 
    /* Creation et insertion des elements contenus dans le premier GtkFrame */
    pLabel = gtk_label_new("Nom du Réseau de neurones :");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 2);
    pEntry[0] = gtk_entry_new_with_max_length(30);//pour que l'utilisateur peut saisir une entrée
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry[0], TRUE, FALSE, 2);
    
    sUtf8 = g_locale_to_utf8("nombre de couches cachées :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 2);
    pEntry[1] = gtk_entry_new_with_max_length(8);
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry[1], TRUE, FALSE, 2);
 
    sUtf8 = g_locale_to_utf8("nombre de neurones cachés :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 2);
    pEntry[2] = gtk_entry_new_with_max_length(8);
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry[2], TRUE, FALSE, 2);
 
   // /* Creation d un GtkHSeparator */
   //  pSeparator = gtk_hseparator_new();
   //  gtk_box_pack_start(GTK_BOX(pVBox), pSeparator, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("etiquette de sortie :");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 2);
    pEntry[3] = gtk_entry_new_with_max_length(200);
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry[3], TRUE, FALSE, 2);
 
    
    pLabel = gtk_label_new("nom repertoire :");
    bouton_explorer=gtk_button_new_with_label("Explorer repertoire ...");
    
    //on met le bouton Explorer dans la frame
    gtk_box_pack_start(GTK_BOX(pHBox),bouton_explorer, TRUE, FALSE, 3);
    g_signal_connect(G_OBJECT(bouton_explorer), "clicked", G_CALLBACK(creer_folder_selection), fenetre->Window);
    
    /*definir la taille max des images qu'il devra analyser pour connaitre le nbr de neurones en entrées
      definir la hauteur*/
     sUtf8 = g_locale_to_utf8("Hauteur des images :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    pEntry[4] = gtk_entry_new_with_max_length(Cmax);
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry[4], TRUE, FALSE, 0);
    
    //definir la largeur des images
    sUtf8 = g_locale_to_utf8("Largeur des images :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    pEntry[5] = gtk_entry_new_with_max_length(Cmax); //j'ai limité à 30 on verra si on voudra modifier
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry[5], TRUE, FALSE, 0); 
    
    
  //afficher les bouton dans la même frame 
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 20);
 
   //gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);
    pButton[0] = gtk_button_new_with_label("Creer");
    pButton[1] = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[0], FALSE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[1], FALSE, TRUE, 3);
    //g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(page_principale), NULL);
    g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(retourAccueille), fenetre);
    
    g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(creationRN), fenetre);
    gtk_widget_show_all(fenetre->Window);
}

void creationRN(GtkWidget *widget, gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    GList *pList = gtk_container_get_children(GTK_CONTAINER(fenetre->Window));
    pList = gtk_container_get_children(GTK_CONTAINER(pList->data));
    
    pList = g_list_next(pList);
    if(strlen(gtk_entry_get_text(pList->data))){
        //ici on stock et on test si elle son rempli a chaque fois 
        
    }
    // if( == 0){
    //     printf("tfouu");
    // }
    // else{
    //     printf("merde%stfou\n", gtk_entry_get_text(pList->data));
    // }
    

    g_list_free(pList);
}

/*afin de selectionner un repertoire au choix*/
void creer_folder_selection (GtkButton * button, gpointer data)
{   
    gchar* chemin;
    GtkWidget *pDialog;
    GtkWidget *msgError;
     
    GtkWidget *pParent;
        
     //cast en GTK_WIDGET 
    pParent = GTK_WIDGET(data);   
    GtkWidget *pFileSelection;
     
    /* Creation de la fenetre de selection */
        pFileSelection = gtk_file_chooser_dialog_new("selectionnez un repertoire...",
    GTK_WINDOW(pParent),
    //GTK_FILE_CHOOSER_ACTION_OPEN
    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
    GTK_STOCK_OPEN, GTK_RESPONSE_OK,
    NULL);
    
    /*pour afficher toutes les fenetres*/
    gtk_widget_show(pFileSelection);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);   
    
    
    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
        case GTK_RESPONSE_OK:
            /* Recuperation du chemin */
            chemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
            pDialog = gtk_message_dialog_new(GTK_WINDOW(pFileSelection),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "Chemin du repertoire choisi :\n%s", chemin);
                
            gtk_dialog_run(GTK_DIALOG(pDialog));
            gtk_widget_destroy(pDialog);break;
                      
        default : break;
    }
   //g_free(chemin); j'ai un probleme avec ce free
   gtk_widget_destroy(pFileSelection);
}

//pour pouvoir selectionner un fichier 
void creer_file_selection(GtkWidget *widget, gpointer data) {
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    GtkWidget *p_dialog = NULL;
    gtk_widget_hide(fenetre->Window);
    p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier",NULL,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,NULL);
    //gtk_window_set_accept_focus(GTK_WINDOW(fenetre->Window), FALSE);
    //gtk_window_set_modal(GTK_WINDOW(fenetre->Window),FALSE);
    gtk_widget_show(p_dialog);
    if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
        char *file_name = NULL;
        file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
        //fenetre->chemin = malloc(sizeof(strlen(file_name+2)));
        strcpy(fenetre->chemin,file_name);
    
    }
    gtk_widget_show_all(fenetre->Window);
    gtk_widget_destroy (p_dialog);
    traitement(NULL,fenetre);
}


//recuperation du chemin du fichier 
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
    const gchar* chemin;
    GtkWidget *dialog;
    chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );
     
    dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_INFO,
    GTK_BUTTONS_OK,
    "Vous avez choisi :\n%s", chemin);
     
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
}

void quitter(GtkWidget* widget)
{
    // destruction de win et de tout ce qu'il contient
    gtk_widget_destroy(widget);
    gtk_main_quit();
}

void afficherInterface(){
    INFO_FENETRE *fenetre = malloc(sizeof(INFO_FENETRE));
    for(int i = 0; i<200; i++)
        fenetre->chemin[i] = 0;
    fenetre->Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creation de la fenetre graphique par defaut elle aura une taille 200*200pixel
    
    page_principale(fenetre);
}
