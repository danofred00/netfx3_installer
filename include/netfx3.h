
#if !defined(__NETFX3__)

    #define __NETFX3__
    #define PACKAGE_NAME "cm.netfx3.danofred"
    #define RESOURCE_PATH "/cm/netfx3/danofred"
    #define RESOURCE_BUILDER_PATH "/cm/netfx3/danofred/assets/builder.ui"
    #define RESOURCE_CSS_PATH "/cm/netfx3/danofred/assets/style.css"

    #include <gtk/gtk.h>

    void on_application_activate(GtkApplication *app, gpointer data);
    static void load_css(void);

#endif // __NETFX3__
