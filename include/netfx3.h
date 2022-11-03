
#if !defined(__NETFX3__)

    #define __NETFX3__

    #define FILENAME ".drives"
    #define PACKAGE_NAME "cm.netfx3.danofred"
    #define RESOURCE_PATH "/cm/netfx3/danofred"
    #define RESOURCE_BUILDER_PATH "/cm/netfx3/danofred/assets/builder.ui"
    #define RESOURCE_CSS_PATH "/cm/netfx3/danofred/assets/style.css"
    #define CMD_PATTERN "dism /Online /Enable-Feature /FeatureName:NetFX3 /Source:%c:\\sources\\sxs" 

    #if defined(_WIN32) || defined(_WIN64)
        #define MY_APP_FLAGS G_APPLICATION_FLAGS_NONE
    #else
        #define MY_APP_FLAGS G_APPLICATION_DEFAULT_FLAGS
    #endif

    #include <gtk/gtk.h>

    /**
     * @brief Call when the app is active
     * @param app Instance of a app
     * @param data Represent a data transfered with the app when signal activate is raised
    */
    void on_application_activate(GtkApplication *app, gpointer data);


    /**
     * @brief This function load and apply the css style to the current window
    */
    static void load_css(void);


    /**
     * @brief Event called when button's install is clicked
     * @param button represent the button who is raised this event
     * @param data Data transfered
    */ 
    void on_btn_install_clicked(GtkButton *button, gpointer data);

    /**
     * @brief Event called when widget is resized
     * @param win represent the widget who is raised this event
     * @param data Data transfered
    */
    static void on_window_check_resize(GtkWidget *win, gpointer data);

    /**
     * @brief Event called when expander is activate
     * @param expander GtkExpander *
     * @param data Data transfered
    */
    void on_expander_activate(GtkExpander *expander, gpointer data);

    /**
     * This function set the header_bar to the window
     * @param window the window widget
    */
    static void update_header_bar(GtkWindow *window);

    /**
     * @brief It update childs of the stack passed in argument
     * @param stack Represent the stack 
    */
    static void update_stack_add_childs(GtkWidget *stack);

    /**
     * @brief Update command to install netfx3
     * @param drive_letter
     * @return gchararray 
    */
    static gchararray update_cmd(char drive_letter);

    /**
     * @brief This function check avaliables drives and update values in combo_box
     * @param combo_box The combo_box_text to apply values
     */ 
    static void update_all_drives(GtkComboBoxText *combo_box);

    /**
     * @brief The function show a simple message dialogbox
     * 
     * @param parent represent the parent Window
     * @param title The title of the box
     * @param msg Represent the showing message in the box
     * @param second_msg it represent the second message for more details
     * @return The result of the showing dialog
    */
    static int show_message_box(GtkWindow *parent, gchararray title, gchararray msg, gchararray second_msg);

    /**
     * @brief connect all signals 
     * @param builder GtkBuilder *
    */
    static void connect_signals(GtkBuilder *builder);

#endif // __NETFX3__
