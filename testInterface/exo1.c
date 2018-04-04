#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


void mafonction(GtkWidget *widget, gpointer user_data)
{
	int i;
	const gchar * mot = gtk_window_get_title(GTK_WINDOW(widget));
	for(i=strlen(mot); i>=0; i--){
		printf("%c", mot[i]);
	}
	printf("\n");
    gtk_main_quit();
}


int main(int argc,char **argv)
{
	GtkWidget* Fenetre = NULL;
	char * titre = "Bonjour din yemmak";
	gtk_init(&argc, &argv);

    Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(Fenetre), titre);
    gtk_window_set_default_size(GTK_WINDOW(Fenetre), 300, 100);
    gtk_widget_show_all(Fenetre);
    g_signal_connect(G_OBJECT(Fenetre), "delete-event", G_CALLBACK(mafonction), NULL);
    
    gtk_main();
	return EXIT_SUCCESS;
}