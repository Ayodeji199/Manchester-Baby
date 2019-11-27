#include <gtk/gtk.h>
#include "../../assembler/assembler.hpp"

// Created using this tutorial
// https://prognotes.net/2015/06/gtk-3-c-program-using-glade-3/

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

// called when window is closed
void on_windowMain_destroy()
{
    gtk_main_quit();
}

void on_btnAssembler_clicked()
{
    Assembler assemblerObj = Assembler();
    assemblerObj.assignArgs(assemblerObj.getArgs(argNum, argV));
    // assemblerObj.assignArgs("-memsize " + gtk_spin_button_get_value_as_int(gspinBtnMemory) + "-readname" + gtk_file_chooser_button_get_title(gfileChooserImport) + "-writename" + gtk_file_chooser_button_get_title(gfileChooserExport));
    assemblerObj.assembly();
}

void on_btnSimulator_clicked()
{
}