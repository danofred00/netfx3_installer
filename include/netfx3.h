
#if !defined(__NETFX3__)

    #define __NETFX3__

    #define PACKAGE_NAME "cm.netfx3.danofred"
    #define RESOURCE_PATH "/cm/netfx3/danofred"
    #define RESOURCE_BUILDER_PATH "/cm/netfx3/danofred/assets/builder.ui"
    #define RESOURCE_CSS_PATH "/cm/netfx3/danofred/assets/style.css"
    #define CMD_PATTERN "dism /Online /Enable-Feature /FeatureName:NetFX3 /Source:%c:\\sources\\sxs" 

    #include <gtk/gtk.h>

    void on_application_activate(GtkApplication *app, gpointer data);

    /**
     * This function load and apply the css style to the current window
    */
    static void load_css(void);

    // button install clicked
    void on_btn_install_clicked(GtkButton *button, gpointer data);

    /////////
    static void on_window_check_resize(GtkWidget *win, gpointer data);

    void on_driver_entry_text_changed(GtkEntry *entry, gpointer data);

    void on_expander_activate(GtkExpander *expander, gpointer data);

    /**
     * This function set the header_bar to the window
     * @param window the window widget
    */
    static void update_header_bar(GtkWindow *window);

    /**
     * @param stack Represent the stack 
    */
    static void update_stack_add_childs(GtkWidget *stack);

    static gchararray update_cmd(char drive_letter);

#endif // __NETFX3__
