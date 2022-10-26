
#include <netfx3.h>

GtkBuilder *builder;
GdkDisplay *display_w;  // the gdk_display_get_default()

GError *error;

gchararray drive_letter = "C";
gchararray total_cmd;

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
    gtk_builder_connect_signals(builder, NULL);

    // getting the window
    window = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder), "window"));
    //g_signal_connect(window, "check-resize", G_CALLBACK(on_window_check_resize), NULL);

    // add window to the current app
    gtk_application_add_window(app, GTK_WINDOW(window));

    // customise the window
    update_header_bar(GTK_WINDOW(window));
    update_stack_add_childs(GTK_WIDGET(gtk_builder_get_object(builder, "stack")));

    // show window with all child's widgets
    gtk_widget_show_all(window);
}

void on_driver_entry_text_changed(GtkEntry *entry, gpointer data) {
    drive_letter = gtk_entry_get_text(entry);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "cmd_command")), update_cmd(drive_letter[0]));
}

void on_expander_activate(GtkExpander *expander, gpointer data) {

    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "cmd_command")), update_cmd(drive_letter[0]));
}

static void update_stack_add_childs(GtkWidget *stack){

    GtkWidget *stack_simple_mode;
    //GtkWidget *stack_advance_mode;
    GtkWidget *stackswitcher;

    // getting objects
    stackswitcher = GTK_WIDGET(gtk_builder_get_object(builder, "stackswitcher"));
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stackswitcher), GTK_STACK(stack));

    //// get childs
    
    stack_simple_mode = GTK_WIDGET(gtk_builder_get_object(builder, "stack_simple"));
    //stack_advance_mode = GTK_WIDGET(gtk_builder_get_object(builder, "stack_advance"));

    // add childs
    gtk_stack_add_titled(GTK_STACK(stack), stack_simple_mode, "stack_simple", "Simple Mode");
    //gtk_stack_add_titled(GTK_STACK(stack), stack_advance_mode, "stack_advance", "Advance Mode");

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