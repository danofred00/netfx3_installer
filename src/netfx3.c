
#include <stdio.h>
#include <stdlib.h>
#include <netfx3.h>
#include <directory.h>

GtkBuilder *builder;    // represent the builder used to get objects
GdkDisplay *display_w;  // the gdk_display_get_default()
GError *error;      // use to constaint errors
gchararray drive_letter = "X";  // the default drive_letter
gboolean show_drive = FALSE;

static void on_window_check_resize(GtkWidget *win, gpointer data){
    g_print(
        "The window size : (%d, %d) \n\n", 
        gtk_widget_get_allocated_width(win),
        gtk_widget_get_allocated_height(win)
    );
}

void on_application_activate(GtkApplication *app, gpointer data){

    GtkWidget *window;

    // init globals vars
    display_w = gdk_display_get_default();

    // load css
    load_css();

    // getting te builder from resources
    builder = gtk_builder_new_from_resource(RESOURCE_BUILDER_PATH);

    // enable all events
    //gtk_builder_connect_signals(builder, NULL);
    connect_signals(builder);

    // getting the window
    window = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder), "window"));
    //g_signal_connect(window, "check-resize", G_CALLBACK(on_window_check_resize), NULL);

    // add window to the current app
    gtk_application_add_window(app, GTK_WINDOW(window));

    // customise the window
    gtk_window_set_icon(
        GTK_WINDOW(window),
        gtk_image_get_pixbuf(GTK_IMAGE(
            gtk_image_new_from_resource(
                "/cm/netfx3/danofred/assets/images/icon_64x64.png"
        )))
    );
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    update_header_bar(GTK_WINDOW(window));
    update_stack_add_childs(GTK_WIDGET(gtk_builder_get_object(builder, "stack")));

    // update all drives
    update_all_drives(GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "drives_text")));
    
    // desactivate the install button
    // to do after

    // show window with all child's widgets
    gtk_widget_show_all(window);
}


void on_btn_install_clicked(GtkButton *button, gpointer data) {

    // when the button is clicked, the new process for install is created
    gchararray cmd = "cmd.exe";
    gchar args[128];
    GSubprocess *subprocess;
    GError *error_ = NULL;

    if (show_drive == TRUE) {
    	g_snprintf(args, 128, "/c %s", update_cmd(drive_letter[0]));
        subprocess = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE, &error_, cmd, args, NULL);
    } else 
        show_message_box(
            (GtkWindow *)data,
            "ERROR !!! ",
            "Can't install the feature",
            "No NetFx3 feature detect in the selected drive"
        );
}

void on_drives_text_changed(GtkComboBoxText *combo_box, gpointer data) {
    drive_letter = gtk_combo_box_text_get_active_text(combo_box);
    gtk_label_set_text(
        GTK_LABEL(gtk_builder_get_object(builder, "cmd_command")),
        update_cmd(drive_letter[0])
    );
}

void on_expander_activate(GtkExpander *expander, gpointer data) {

    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "cmd_command")), update_cmd(drive_letter[0]));
}

static void update_stack_add_childs(GtkWidget *stack){

    GtkWidget *stack_simple_mode;
    GtkWidget *about;
    GtkWidget *stackswitcher;

    // getting objects
    stackswitcher = GTK_WIDGET(gtk_builder_get_object(builder, "stackswitcher"));
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stackswitcher), GTK_STACK(stack));

    //// get childs
    
    stack_simple_mode = GTK_WIDGET(gtk_builder_get_object(builder, "stack_simple"));
    about = GTK_WIDGET(gtk_builder_get_object(builder, "stack_about"));

    // add childs
    gtk_stack_add_titled(
        GTK_STACK(stack),
        stack_simple_mode,
        "stack_simple",
        "Simple Mode"
    );
    
    gtk_stack_add_titled(
        GTK_STACK(stack),
        about,
        "stack_about",
        "About"
    );

}

static int show_message_box(GtkWindow *parent, gchararray title, gchararray msg, gchararray second_msg) {

    GtkWidget *dialog;
    gint response;

    // create a new message_dialog here
    dialog = gtk_message_dialog_new(
        parent,             // the parent of this dialog
        GTK_DIALOG_MODAL,   // the dialog flag
        GTK_MESSAGE_ERROR,  // the type of message in this box
        GTK_BUTTONS_OK,     // avaliables buttons in the screen
        msg                 // the message of the box
    );

    // adding the title
    gtk_window_set_title(GTK_WINDOW(dialog), title);

    // adding the secondary message in the box if it exists
    if(second_msg)
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), second_msg);

    // run the dialog and return a value of this one
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    if(response)
        gtk_widget_destroy(GTK_WIDGET(dialog));

    return response;
}

static gchararray update_cmd(char drive_letter){
    gchararray cmd = (gchararray) malloc(128);
    g_snprintf(cmd, 127, CMD_PATTERN, drive_letter);
    cmd[127] = '\0';
    return cmd;
}

static void update_header_bar(GtkWindow *window) {
    // get the headerbar
    GtkWidget *headerbar = GTK_WIDGET(gtk_builder_get_object(builder, "headerbar"));
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    
    // apply the bar to the window
    gtk_window_set_titlebar(window, headerbar);
}

static void update_all_drives(GtkComboBoxText *combo_box) {

    /*
    gchararray *all_drives = (char **) malloc(MAX_DRIVES_COUNT*4*sizeof(char));
    if(all_drives == NULL) {
        g_print("Error during this party");
        //g_signal_emit_by_name(window, "destroy");
        exit(-1);
    }
    */

    FILE *fp;
    save_currents_drives(FILENAME);

    fp = fopen(FILENAME, "r");

    // if they have no avaliables drives
    if(fp == NULL) {
        // show drive is false already
        // append no avaliables devices text 
        gtk_combo_box_text_append_text(combo_box, "No Avaliables devices");
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);
        return;
    }

g_print("have many drives\n");
    // the otherwise case
    gchararray d = (gchararray) malloc(4);

    while (!feof(fp)){

        fscanf(fp, "%s", d);
        g_print("Drive : %s \n", d);
        gtk_combo_box_text_append_text(combo_box, d);
    }

    free(d);

    g_print("finish this \n");

    fclose(fp);
    remove(FILENAME);

    // set show_drive to TRUE
    show_drive = TRUE;
    
    // free the space allocated by the function get_drives()
    //if(all_drives)
    //    free(all_drives);
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

static void connect_signals(GtkBuilder *builder){

    // connect expander to activate event
    g_signal_connect(
        gtk_builder_get_object(builder, "expander"),
        "activate",
        G_CALLBACK(on_expander_activate),
        NULL
    );
    
    // connect combo_box_text to changed event
    g_signal_connect(
        gtk_builder_get_object(builder, "drives_text"),
        "changed",
        G_CALLBACK(on_drives_text_changed),
        NULL
    );
    

    // connect btn_install to signal clicked
    g_signal_connect(
        gtk_builder_get_object(builder, "btn_install"),
        "clicked",
        G_CALLBACK(on_btn_install_clicked),
        NULL
    );
}