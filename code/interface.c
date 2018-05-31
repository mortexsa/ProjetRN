/**
 * \file interface.c
 * \brief Interface du programme.
 * \author PEPIN Thibaut
 * \author REZGUI Soumia
 * \author SLIMANI Arezki
 * \author SELAQUET Severine
 * \author SZULEK Isaac
 * \author MONTIGNE Anthony
 *
 * Interface du programme de reconnaissance d'image.
 *
 */

#include "interface.h"

/**
 * \fn int nombreReseau()
 * \brief Nombre de Réseaux de neurones existant.
 *
 * \return int nombre de Réseau.
 */
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
    closedir(rep);
    return i;
}

/**
 * \fn void viderContainer(GtkWidget *data)
 * \brief Vider le contenu de la fenetre.
 *
 * \param data Pour le passage de la structure INFO_FENETRE.
 */
void viderContainer(GtkWidget *data){
     GList *children = gtk_container_get_children(GTK_CONTAINER(data));

    while (children) {
        gtk_widget_destroy(children->data);
        children = g_list_next(children);
    }

    g_list_free(children);
}

/**
 * \fn void retourAccueille(GtkWidget *widget, gpointer data)
 * \brief Retourner a la page d'accueille.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void retourAccueille(GtkWidget *widget, gpointer data){
    //pour suprimer l'ancienne page
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    if(fenetre->chemin[0] != 0){
        for(int w = 0;w<200;w++){
            fenetre->chemin[w] = 0;
        }
    }
    viderContainer(fenetre->Window);
    page_principale(fenetre);
}

/**
 * \fn void selectReseau(GtkWidget *widget, gpointer data)
 * \brief Selection d'un reseau de neurone.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void selectReseau(GtkWidget *widget, gpointer data){

    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Tableau de bord");
    fenetre->pageActuel = 3;
    if(fenetre->chemin[0] != 0){
        for(int w = 0;w<200;w++){
            fenetre->chemin[w] = 0;
        }
    }
    GtkWidget *label;
    GtkWidget *button[4];
    GtkWidget *toggleBtn;
    GtkWidget *Vbox;
    GtkWidget *Hbox;
    Vbox = gtk_vbox_new(FALSE, 0);
    Hbox = gtk_hbox_new(FALSE, 0);
    if(fenetre->reseauSelectionner == -1){
        char titre[256];
        strcpy(titre,gtk_button_get_label((GtkButton *)widget));
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
    else if(fenetre->reseauSelectionner == -2){
        char titre[256];
        strcpy(titre,gtk_label_get_text((GtkLabel *)widget));
        char *parse = strtok(titre,"/");
        strcpy(titre,parse);
        parse = strtok(NULL, "/");
        for(int i=0;i<fenetre->nombreReseau;i++){
            if(strcmp(fenetre->info[i].nom,titre) == 0){
                if(strcmp(fenetre->info[i].date,parse) == 0){
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
    toggleBtn = gtk_toggle_button_new_with_label("Apprentissage");
    button[3] = gtk_button_new_with_label("Suprimer ce Reseaux");
    
    gtk_box_pack_start(GTK_BOX(Hbox), button[1], TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(Hbox), button[2], TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(Hbox), toggleBtn, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(Vbox), button[3], FALSE, TRUE, 7);
    gtk_widget_show_all(fenetre->Window);
    if(fenetre->etatBoutton == 1){
        gtk_toggle_button_set_active((GtkToggleButton *)toggleBtn,1);
        gtk_widget_hide(GTK_WIDGET(button[1]));   
    } else {
        gtk_toggle_button_set_active((GtkToggleButton *)toggleBtn,0);
        gtk_widget_show(GTK_WIDGET(button[1]));
    }
    g_signal_connect(G_OBJECT(button[1]), "clicked", G_CALLBACK(retourAccueille), fenetre);
    g_signal_connect(G_OBJECT(button[2]), "clicked", G_CALLBACK(traitement), fenetre);
    g_signal_connect(G_OBJECT(toggleBtn), "toggled", G_CALLBACK(lancerApprentissage), fenetre);
    g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(matrice), fenetre);
    g_signal_connect(G_OBJECT(button[3]), "clicked", G_CALLBACK(suprimerReseau), fenetre);
}

/**
 * \fn void suprimerReseau(GtkWidget *widget, gpointer data)
 * \brief Suprime un reseau de neurone
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void suprimerReseau(GtkWidget *widget, gpointer data) {
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    GtkWidget *pQuestion;
    DIR *repertoire;           /* pointeur de répertoire */
    struct dirent *entry;     /* représente une entrée dans un répertoire. */
    struct stat file_stat;    /* informations sur un fichier. */
    char buffer[1024] = {0};
    char name[200];
    pQuestion = gtk_message_dialog_new (GTK_WINDOW(fenetre->Window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vraiment\nsuprimer ce reseau?");
     switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            sprintf(name,"../sav/%s_%s",fenetre->info[fenetre->reseauSelectionner].date,fenetre->info[fenetre->reseauSelectionner].nom);
            repertoire = opendir(name);
            if ( repertoire == NULL ) {
                fprintf(stderr, "Impossible d'ouvrir le dossier %s\n", name);
                exit(1);
            }

            while ( (entry = readdir(repertoire)) != NULL ) {
                if ( strcmp(entry->d_name, ".") == 0 ||
                     strcmp(entry->d_name, "..") == 0 ) {
                    continue;
                }
                snprintf(buffer, 1024, "%s/%s", name, entry->d_name);
                stat(buffer, &file_stat);
                if ( S_ISREG(file_stat.st_mode) ) {
                    remove(buffer);
                }
            }
            closedir(repertoire);
            remove(name);
            gtk_widget_destroy(pQuestion);
            retourAccueille(NULL,fenetre);
            break;
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(pQuestion);
            break;
    } 
}

/**
 * \fn void traitement(GtkWidget *widget, gpointer data)
 * \brief Lance le traitement d'une image.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void traitement(GtkWidget *widget, gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    
    gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Traitement d'images");
    viderContainer(fenetre->Window);
    fenetre->pageActuel = 4;
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

/**
 * \fn void resultatTraitement(GtkWidget *widget, gpointer data)
 * \brief Affiche le résultat du traitement d'une image.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void resultatTraitement(GtkWidget *widget, gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    if(fenetre->chemin[0] == 0){
        GtkWidget * avertissement;
        avertissement = gtk_message_dialog_new(GTK_WINDOW(fenetre->Window), 
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez selectionner un fichier !!");
        gtk_dialog_run(GTK_DIALOG(avertissement));
        gtk_widget_destroy(avertissement);
    }
    else {
        char resultat[200];
        strcpy(resultat,fenetre->chemin);
        char *parse = strtok(resultat,".");
        while(parse != NULL){
            strcpy(resultat,parse);
            parse = strtok(NULL, ".");
        }
        if(strcmp(resultat,"bmp") == 0 || strcmp(resultat,"idx3-ubyte") == 0){

            gtk_window_set_title(GTK_WINDOW(fenetre->Window), "TOP 3 des Resultats ");
            viderContainer(fenetre->Window);
            
            GtkWidget *label;
            GtkWidget *Vbox;
            GtkWidget *Hbox;
            GtkWidget *pbutton[2];
         	INFO_RN *k=&(fenetre->info[fenetre->reseauSelectionner]);	  
        	RN *rn = ChargerRN(k); //charger RN
        	
        	char** rec;
            Image * image;
            if(strcmp(resultat,"bmp") == 0){
                image = ChargerBmp(fenetre->chemin,rn->info->w, rn->info->h);            
            }
            else{
                image = ChargerMnist(fenetre->chemin,rn->info->w, rn->info->h);
            }

            if(image == NULL)
            {
    			//truc a faire si la lecture de l'image n a pas reussi
    		}
            Propagation(image,*rn);
        	rec = Reconnaissance(*rn);
        	
        	DelImage(image);
        	libererRN(rn);
        	
        	Vbox = gtk_vbox_new(FALSE, 0);
        	Hbox = gtk_hbox_new(FALSE, 0);

            gtk_container_add(GTK_CONTAINER(fenetre->Window), Vbox);
        	strcpy(resultat,"resultat 1: ");
            strcat(resultat,rec[0]);
        	label = gtk_label_new(resultat);	
        	gtk_box_pack_start(GTK_BOX(Vbox), label, TRUE, FALSE, 2);
        	
            strcpy(resultat,"resultat 2: ");
            strcat(resultat,rec[1]);
            label = gtk_label_new(resultat);    
            gtk_box_pack_start(GTK_BOX(Vbox), label, TRUE, FALSE, 2);

            strcpy(resultat,"resultat 3: ");
            strcat(resultat,rec[2]);
            label = gtk_label_new(resultat);    
            gtk_box_pack_start(GTK_BOX(Vbox), label, TRUE, FALSE, 2);
            
            free(rec[0]);
            free(rec[1]);
            free(rec[2]);
            free(rec);
            
            gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, TRUE, 2);
            pbutton[0] = gtk_button_new_with_label("Ok");
            gtk_box_pack_start(GTK_BOX(Hbox), pbutton[0], TRUE, TRUE, 2); 
            pbutton[1] = gtk_button_new_with_label("quitter");
            gtk_box_pack_start(GTK_BOX(Hbox), pbutton[1], TRUE, TRUE, 2); 
         
            /* Affichage de la fenêtré et de tout ce qu'il contient */
            gtk_widget_show_all(fenetre->Window);  
            g_signal_connect(G_OBJECT(pbutton[0]), "clicked", G_CALLBACK(traitement), fenetre);  
            g_signal_connect(G_OBJECT(pbutton[1]), "clicked", G_CALLBACK(quitter), fenetre); 
        
        }
    }
}


/**
 * \fn void lancerApprentissage(GtkWidget *widget, gpointer data)
 * \brief Lancer l'apprentissage du réseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void lancerApprentissage(GtkWidget *widget, gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    GList *gList = NULL;
    static GThread* t2;
    int i=0;
    gList = gtk_container_get_children(GTK_CONTAINER(fenetre->Window));
    gList = gtk_container_get_children(GTK_CONTAINER(gList->data));
    while(gList && i<4){
        gList = g_list_next(gList);
        i++;
    }
    gList = gtk_container_get_children(GTK_CONTAINER(gList->data));
    if(gtk_toggle_button_get_active ((GtkToggleButton *)widget)){
        fenetre->etatBoutton = 1;
        gtk_widget_hide(GTK_WIDGET(gList->data));
        t2 = g_thread_new("Apprentissage",fctThreadApp,(void*)fenetre);
    }
    else
    {
        fenetre->etatBoutton = 0;
        gtk_widget_show(gList->data);
        g_thread_join(t2);
        gList = gtk_container_get_children(GTK_CONTAINER(fenetre->Window));
        gList = gtk_container_get_children(GTK_CONTAINER(gList->data));
        gList = g_list_next(gList);
        char tab[200];
        char b[100];
        double pourcentageReussite = 0;
        if(fenetre->info[fenetre->reseauSelectionner].reussite != 0){
                pourcentageReussite = ((double)fenetre->info[fenetre->reseauSelectionner].reussite / (fenetre->info[fenetre->reseauSelectionner].reussite + fenetre->info[fenetre->reseauSelectionner].echec)) * 100;
        }
        strcpy(tab, "Pourcentage de reussite :  ");
        sprintf(b,"%.3f", pourcentageReussite);
        strcat(tab,b);
        strcat(tab," %");
        gtk_label_set_text(GTK_LABEL(gList->data),tab); 
    }
    g_list_free(gList);
}

/**
 * \fn void* fctThreadApp(gpointer data)
 * \brief Fonction appeler par le thread qui fait l'apprentissage du reseau de neurone.
 *
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void* fctThreadApp(gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    RN* rn = ChargerRN(&(fenetre->info[fenetre->reseauSelectionner]));
    int i = 0;
    App* app;

    while((fenetre->etatBoutton)&&(app = ChargementCoupleAttIn(rn->info->repertoire,rn->info->w,rn->info->h)))
    {
        BackProp(rn,app->image,app->etiquette,1.5);
        i++;
        if(!(i%10000))
            SaveRN(*rn);

        DelApp(app);
    }
    
    SaveRN(*rn);
    libererRN(rn);
    
    if(fenetre->etatBoutton == 1){
        fenetre->etatBoutton = gtk_idle_add(afficherWarning,fenetre);
    }

    return NULL;
}

/**
 * \fn int afficherWarning(gpointer data)
 * \brief Fonction appeler pour afficher une boite de dialogue
 *
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
int afficherWarning(gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *) data;
    GtkWidget * avertissement;
    
    avertissement = gtk_message_dialog_new(GTK_WINDOW(fenetre->Window), 
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Apprentissage Terminé");
    gtk_dialog_run(GTK_DIALOG(avertissement));
    gtk_widget_destroy(avertissement);
    gtk_idle_remove(fenetre->etatBoutton);
    fenetre->etatBoutton = 0;
    if(fenetre->pageActuel == 3){
        selectReseau(NULL,fenetre);
    }
    return 1;
}

/**
 * \fn void matrice(GtkWidget *widget, gpointer data)
 * \brief Affichage de la matrice des poid du reseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void matrice(GtkWidget *widget, gpointer data)
{
   INFO_FENETRE *fenetre = (INFO_FENETRE *) data;

    GtkWidget *table;
    GtkWidget *window;

    gchar text[200];
    gchar *result;
    GtkWidget *scrollbar;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1300, 650);
    gtk_window_set_title(GTK_WINDOW(window), "Matrice des poids");
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window),scrollbar);
    RN* rn = ChargerRN(&(fenetre->info[fenetre->reseauSelectionner])); //charger le reseau de neurones
    COUCHE* tmp = rn->couche_deb->suiv;  //se positionner dans la couche de sortie
    int i;
    int j;
    table = gtk_table_new ((tmp->taille), (tmp->taille), TRUE); //création tableau 
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbar), table);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
    gtk_table_set_row_spacings (GTK_TABLE (table), 3); //defini l'espacement
    gtk_table_set_col_spacings (GTK_TABLE (table), 4);
    
   for( i=0;i<(tmp->taille); i++){
       for(j=0; j<(tmp->taille); j++){
            GtkWidget *cell;
            cell = gtk_label_new(NULL);
            if(tmp->W[i][j] > 0){
                if(tmp->W[i][j] > 0.5){
                    strcpy(text,"<span background=\"#00FF00\">");
                }else {
                    strcpy(text,"<span background=\"#B2FA6E\">");
                }
                
            }else {
                if(tmp->W[i][j] < -0.5){
                    strcpy(text,"<span background=\"#FF0000\">");
                }
                else {
                    strcpy(text,"<span background=\"#FF5E4D\">");
                }
                
            }
            strcat(text,g_strdup_printf("%0.2f", tmp->W[i][j])); //création d'une chaine contenant la valeur de la cellule        
            strcat(text,"</span>");
            result = g_markup_printf_escaped(text,-1,NULL,NULL,NULL);
            gtk_label_set_markup(GTK_LABEL(cell), result);
            gtk_table_attach (GTK_TABLE (table), cell, j, j+1, i, i+1, GTK_EXPAND, GTK_EXPAND, 0, 0); //ajout de la cellule au tableau
            g_free (result);                   
        }
    }
    gtk_widget_show_all(window); 
    //g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_widget_destroy),window);
    libererRN(rn);
}

/**
 * \fn void page_principale(INFO_FENETRE *fenetre)
 * \brief Page d'accueille du programme
 *
 * \param fenetre La fenetre qu'on affichera dans l'accueille. 
 */
void page_principale(INFO_FENETRE *fenetre){
	gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Accueil");	
	fenetre->info = ChargerInfo();
    fenetre->nombreReseau = nombreReseau();
    fenetre->pageActuel = 1;
    fenetre->reseauSelectionner = -1;
	GtkWidget *Vbox;
	GtkWidget *Hbox;
	GtkWidget **button;
	button = malloc((fenetre->nombreReseau+2)*sizeof(GtkWidget*));
	GtkWidget *label;
	
	gtk_window_set_default_size(GTK_WINDOW(fenetre->Window), 640, 400); //donner les dimmenssion de la fenetre 
	
	g_signal_connect(G_OBJECT(fenetre->Window), "destroy", G_CALLBACK(quitter), fenetre); //pour pouvoir fermer la fenetre avec exit 
	
	
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
  
    g_signal_connect(G_OBJECT(button[fenetre->nombreReseau+1]), "clicked", G_CALLBACK(quitter), fenetre);

    g_signal_connect(G_OBJECT(button[fenetre->nombreReseau]), "clicked", G_CALLBACK(creation),fenetre); 
    
    
	}

/**
 * \fn void creation(GtkWidget *widget, gpointer data)
 * \brief Interface de creation d'un reseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void creation(GtkWidget *widget, gpointer data){

  //pour suprimer l'ancienne page
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    gtk_window_set_title(GTK_WINDOW(fenetre->Window), "Creation d'un reseau de neurones");
    viderContainer(fenetre->Window);
    fenetre->pageActuel = 2;
    //GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pEntry[2];
    GtkWidget *pLabel;
    gchar *sUtf8;
    GtkWidget *pSpin[4];
    
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
    pSpin[0] = gtk_spin_button_new_with_range(1, 1000, 1);
    gtk_box_pack_start(GTK_BOX(pVBox), pSpin[0], TRUE, FALSE, 0);
 
    sUtf8 = g_locale_to_utf8("nombre de neurones cachés :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 2);
    pSpin[1] = gtk_spin_button_new_with_range(1, 1000, 1);
    gtk_box_pack_start(GTK_BOX(pVBox), pSpin[1], TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("etiquette de sortie (format: etiquette1//etiquette2 ...) :");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 2);
    pEntry[1] = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry[1], TRUE, FALSE, 2);
 
    
    bouton_explorer=gtk_button_new_with_label("Explorer repertoire ...");
    
    //on met le bouton Explorer dans la frame
    gtk_box_pack_start(GTK_BOX(pHBox),bouton_explorer, TRUE, FALSE, 3);
    g_signal_connect(G_OBJECT(bouton_explorer), "clicked", G_CALLBACK(creer_folder_selection), fenetre);
    
    /*definir la taille max des images qu'il devra analyser pour connaitre le nbr de neurones en entrées
      definir la hauteur*/
     sUtf8 = g_locale_to_utf8("Hauteur des images :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    pSpin[2] = gtk_spin_button_new_with_range(1, 8000, 1);
    gtk_box_pack_start(GTK_BOX(pVBox), pSpin[2], TRUE, FALSE, 0);
    
    //definir la largeur des images
    sUtf8 = g_locale_to_utf8("Largeur des images :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    pSpin[3] = gtk_spin_button_new_with_range(1, 8000, 1);
    gtk_box_pack_start(GTK_BOX(pVBox), pSpin[3], TRUE, FALSE, 0);
    
  //afficher les bouton dans la même frame 
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 20);
 
    pButton[0] = gtk_button_new_with_label("Creer");
    pButton[1] = gtk_button_new_with_label("Retour");
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[0], FALSE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[1], FALSE, TRUE, 3);
    g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(retourAccueille), fenetre);
    
    g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(creationRN), fenetre);
    gtk_widget_show_all(fenetre->Window);
}

/**
 * \fn void creationRN(GtkWidget *widget, gpointer data)
 * \brief Recuperation des données et sauvegarde du réseau de neurones.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void creationRN(GtkWidget *widget, gpointer data){
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    GtkWidget *label;
    GList *pList = gtk_container_get_children(GTK_CONTAINER(fenetre->Window));
    GList *pCopie = NULL;
    pList = gtk_container_get_children(GTK_CONTAINER(pList->data));
    int i = 0;
    pList = g_list_next(pList);
    while(i<6){
        if(!strcmp("GtkEntry",gtk_widget_get_name(pList->data))){
            if(!strlen(gtk_entry_get_text(GTK_ENTRY(pList->data)))){
                break;
            }
        }
        pCopie = g_list_append(pCopie,pList->data);
        if(i<5){
            pList = g_list_next(pList);
            pList = g_list_next(pList);
        }
        i++;
    }

    if(g_list_length(pCopie) == 6 && fenetre->chemin[0] != 0){
        int nbrCouche = 0;
        int nbrNeurones = 0;
        INFO_RN *newinfo = malloc(sizeof(INFO_RN));
        newinfo->nom = malloc(sizeof(char)*(strlen(gtk_entry_get_text(GTK_ENTRY(pList->data)))+10));
        strcpy(newinfo->nom,gtk_entry_get_text(GTK_ENTRY(pCopie->data)));
        newinfo->repertoire = malloc(sizeof(char)*(strlen(fenetre->chemin)+10));
        strcpy(newinfo->repertoire,fenetre->chemin);
        if(fenetre->chemin[0] != 0){
            for(int w = 0;w<200;w++){
                fenetre->chemin[w] = 0;
            }
        }
        pCopie = g_list_next(pCopie);
        nbrCouche = gtk_spin_button_get_value_as_int(pCopie->data);
        pCopie = g_list_next(pCopie);
        nbrNeurones = gtk_spin_button_get_value_as_int(pCopie->data);
        pCopie = g_list_next(pCopie);
        char *resultat = malloc(sizeof(char)*(strlen(gtk_entry_get_text(GTK_ENTRY(pList->data)))+100));
        strcpy(resultat,gtk_entry_get_text(GTK_ENTRY(pCopie->data)));
        char *parse = strtok(resultat,"//");
        int compteur = 0;
        while(parse != NULL){
            parse = strtok(NULL, "//");
            compteur++;
        }
        i = 0;
        newinfo->etiquettes = malloc(sizeof(char*)*compteur);        
        strcpy(resultat,gtk_entry_get_text(GTK_ENTRY(pCopie->data)));
        parse = strtok(resultat,"//");
        while(parse != NULL){
            if(strlen(parse) != 0){
                newinfo->etiquettes[i] = malloc(sizeof(char)*(strlen(parse)+10));
                strcpy(newinfo->etiquettes[i],parse);
            }
            parse = strtok(NULL, "//");
            i++;
        }
        pCopie = g_list_next(pCopie);
        newinfo->h = gtk_spin_button_get_value_as_int(pCopie->data);
        pCopie = g_list_next(pCopie);
        newinfo->w = gtk_spin_button_get_value_as_int(pCopie->data);
        newinfo->reussite = 0;
        newinfo->echec = 0;
        time_t timestamp; 
        struct tm * t; 
        timestamp = time(NULL); 
        t = localtime(&timestamp); 
        newinfo->date = malloc(sizeof(char)*20);
        sprintf(resultat,"%04u", 1900 + t->tm_year);
        strcpy(newinfo->date,resultat);
        strcat(newinfo->date,"-");
        sprintf(resultat,"%02u",t->tm_mon+1);
        strcat(newinfo->date,resultat);
        strcat(newinfo->date,"-");
        sprintf(resultat,"%02u",t->tm_mday);
        strcat(newinfo->date,resultat);
        RN *rn = initialisation(newinfo);
        AjoutPremiereCouche(rn, newinfo->h*newinfo->w*3);
        for(i=0;i<nbrCouche;i++){
            Ajout_couche_Fin(rn, nbrNeurones);
        }
        Ajout_couche_Fin(rn,compteur);
        Remplissage(*rn);
        SaveRN(*rn);
        libererRN(rn);
        gchar *sUtf8;
        strcpy(resultat,newinfo->nom);
        strcat(resultat,"/");
        strcat(resultat,newinfo->date);
        for(i=0;i<fenetre->nombreReseau;i++){
            LibererInfo(&(fenetre->info[i]));
        }
        fenetre->info = ChargerInfo();
        fenetre->nombreReseau = nombreReseau();
        fenetre->reseauSelectionner=-2;
        sUtf8 = g_locale_to_utf8(resultat, -1, NULL, NULL, NULL);
        label = gtk_label_new(sUtf8);
        g_free(sUtf8);
        selectReseau(GTK_WIDGET(label), fenetre);
    }

    g_list_free(pList);
    g_list_free(pCopie);
}

/**
 * \fn void creer_file_selection(GtkWidget *widget, gpointer data)
 * \brief Selection d'un fichier a analyser dans traitement.
 *
 */
void creer_file_selection(GtkWidget *widget, gpointer data) {
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    GtkWidget *p_dialog = NULL;
    GtkWidget *avertissement;
    gtk_widget_hide(fenetre->Window);
    p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier",NULL,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,NULL);
    //gtk_window_set_accept_focus(GTK_WINDOW(fenetre->Window), FALSE);
    //gtk_window_set_modal(GTK_WINDOW(fenetre->Window),FALSE);
    gtk_widget_show(p_dialog);
    while(1){
        if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
            char *file_name = NULL;
            file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
            DIR *dir;
            dir = opendir(file_name);
            if(dir == NULL){
                strcpy(fenetre->chemin,file_name);
                break;
            }
            else{
                closedir(dir);
                avertissement = gtk_message_dialog_new(GTK_WINDOW(fenetre->Window),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    "Veuillez selectionner un Fichier !!");
                gtk_dialog_run(GTK_DIALOG(avertissement));
                gtk_widget_destroy(avertissement);
            }
        }
        else {
            break;
        }
    }
    
    gtk_widget_show_all(fenetre->Window);
    gtk_widget_destroy (p_dialog);
    traitement(NULL,fenetre);
}

/**
 * \fn void creer_folder_selection (GtkButton * button, gpointer data)
 * \brief Selection du dossier ou ce trouverons les données pour l'apprentissage.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void creer_folder_selection (GtkButton * button, gpointer data)
{   
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    GtkWidget *pFileSelection = NULL;
    GtkWidget *cheminDossier;
    gtk_widget_hide(fenetre->Window);
        
     
    /* Creation de la fenetre de selection */
    pFileSelection = gtk_file_chooser_dialog_new("selectionnez un repertoire...",
    NULL,
    //GTK_FILE_CHOOSER_ACTION_OPEN
    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
    GTK_STOCK_OPEN, GTK_RESPONSE_OK,
    NULL);
    
    /*pour afficher toutes les fenetres*/
    gtk_widget_show(pFileSelection);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);   
    
    char *file_name = NULL;
    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
        case GTK_RESPONSE_OK:
            /* Recuperation du chemin */
            file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pFileSelection));
            strcpy(fenetre->chemin,file_name);
            cheminDossier = gtk_message_dialog_new(GTK_WINDOW(fenetre->Window),
                    GTK_DIALOG_MODAL,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_OK,
                    file_name);
                gtk_dialog_run(GTK_DIALOG(cheminDossier));
                gtk_widget_destroy(cheminDossier);
            break;
                      
        default : break;
    }
    gtk_widget_show_all(fenetre->Window);
    gtk_widget_destroy(pFileSelection);
}

/**
 * \fn void quitter(GtkWidget *widget, gpointer data)
 * \brief Lorsque l'on quitte la fenetre.
 *
 * \param widget Le widget qui est associer a la fonction.
 * \param data Pour le passage de la structure INFO_FENETRE. 
 */
void quitter(GtkWidget *widget, gpointer data)
{
    INFO_FENETRE *fenetre = (INFO_FENETRE *)data;
    int i;
    for(i=0;i<fenetre->nombreReseau;i++){
        LibererInfo(&(fenetre->info[i]));
    }
    free(fenetre);
    gtk_main_quit();    
}

/**
 * \fn void afficherInterface()
 * \brief Contenant toute l'interface et les fonction
 *
 */
void afficherInterface(){
    INFO_FENETRE *fenetre = malloc(sizeof(INFO_FENETRE));
    
    for(int i = 0; i<200; i++)
        fenetre->chemin[i] = 0;
    
    fenetre->Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creation de la fenetre graphique par defaut elle aura une taille 200*200pixel
    
    page_principale(fenetre);
}

