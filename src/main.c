
#include <netfx3.h>
//#include <directory.h>
//#include <stdio.h>

int main(int argc, char *argv[])
{

    // this is my app widget
    GtkApplication *app;
    // the exit's status code
    gint status;

    app = gtk_application_new(PACKAGE_NAME, MY_APP_FLAGS);

    // connect the activate signal to our app
    g_signal_connect(app, "activate", G_CALLBACK(on_application_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
    /*/

   if(get_drives() == NULL)
        puts("No avaliables drives");

   return 0;*/
}
