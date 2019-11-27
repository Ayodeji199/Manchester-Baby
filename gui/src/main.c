#include <gtk/gtk.h>
#include "../../assembler/assembler.hpp"

// Created using this tutorial
// https://prognotes.net/2015/06/gtk-3-c-program-using-glade-3/

extern "C"
{
    int argNum;
    char **argV;
    GtkWidget *gfileChooserImport;
    GtkWidget *gfileChooserExport;
    GtkWidget *gspinBtnMemory;

    int main(int argc, char *argv[])
    {
        argNum = argc;
        argV = argv;

        GtkBuilder *builder;
        GtkWidget *window;

        gtk_init(&argc, &argv);

        builder = gtk_builder_new_from_file("glade/windowMain.glade");

        window = GTK_WIDGET(gtk_builder_get_object(builder, "windowMain"));
        gtk_builder_connect_signals(builder, NULL);

        gfileChooserImport = GTK_WIDGET(gtk_builder_get_object(builder, "fileChooserImport"));
        gfileChooserExport = GTK_WIDGET(gtk_builder_get_object(builder, "fileChooserExport"));
        gspinBtnMemory = GTK_WIDGET(gtk_builder_get_object(builder, "spinBtnMemory"));

        g_object_unref(builder);

        gtk_widget_show(window);
        gtk_main();

        return 0;
    }

    // Called when window is closed
    void on_windowMain_destroy()
    {
        gtk_main_quit();
    }

    // Called when assemble button is clicked
    void on_btnAssembler_clicked()
    {
        Assembler assemblerObj = Assembler();
        // assemblerObj.assignArgs(assemblerObj.getArgs(argNum, argV));
        std::string memsize = std::to_string(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gspinBtnMemory)));
        // std::string readme = std::to_string(GtkFileChooser(gfileChooserImport)->get_filename());
        // std::string writename = std::to_string(gtk_file_chooser_button_get_title(GtkFileChooserButton(gfileChooserExport)));
        // std::vector<std::string> run_args = {"-memsize ", memsize, "-readname", readme, "-writename", writename};
        // assemblerObj.assignArgs(run_args);
        assemblerObj.assembly();
    }

    // Called when simulator button is clicked
    void on_btnSimulator_clicked()
    {
    }
}