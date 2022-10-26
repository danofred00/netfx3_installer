
#include <netfx3.h>

GtkBuilder *builder;
GtkWidget *window;
GdkDisplay *display_w;  // the gdk_display_get_default()

GError *error;

void on_application_activate(GtkApplication *app, gpointer data){

    // init globals vars
    display_w = gdk_display_get_default();

    // load css
    load_css();

    // getting te builder from resources
    builder = gtk_builder_new_from_resource(RESOURCE_BUILDER_PATH);

    // enable all events
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);

    // getting the window
    window = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder), "window"));

    // add window to the current app
    gtk_application_add_window(app, GTK_WINDOW(window));

    // show window with all child's widgets
    gtk_widget_show_all(window);
}

static void load_css(void) {
    GtkCssProvider *provider;

    // load the css provider
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, RESOURCE_CSS_PATH);

    gtk_style_context_add_provider_for_screen(
        gdk_display_get_default_screen(display_w),      // the window screen
        GTK_STYLE_PROVIDER(provider),                   // the css provider
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION         // style priority
    );
}