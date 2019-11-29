#include <gtk/gtk.h>
#include "../../assembler/assembler.hpp"
#include <stdio.h>
#include "../../simulator/babySim.hpp"

// Created using this tutorial
// https://prognotes.net/2015/06/gtk-3-c-program-using-glade-3/

extern "C"
{
    int argNum;
    char **argV;
    GtkFileChooserButton *gfileChooserImport;
    GtkFileChooserButton *gfileChooserExport;
    GtkWidget *gspinBtnMemory;

    int main(int argc, char **argv)
    {
        argNum = argc;
        argV = argv;

        GtkBuilder *builder;
        GtkWidget *window;

        gtk_init(&argc, &argv);
        builder = gtk_builder_new_from_file("gui/glade/windowMain.glade");

        window = GTK_WIDGET(gtk_builder_get_object(builder, "windowMain"));
        gtk_builder_connect_signals(builder, NULL);

        gfileChooserImport = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "fileChooserImport"));
        gfileChooserExport = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "fileChooserExport"));
        gspinBtnMemory = GTK_WIDGET(gtk_builder_get_object(builder, "spinBtnMemory"));

        g_object_unref(builder);
        gtk_widget_show(window);
        gtk_main();

        return 0;
    }

    // Called when a file to import is set by the user
    void on_fileChooserBtnImport_current_folder_changed(GtkFileChooserButton *fileChooserBtnImport, gpointer user_data)
    {
        printf("Import File attempted");
    }

    // Called when window is closed
    void on_windowMain_destroy()
    {
        gtk_main_quit();
    }

    void get_args(char *args)
    {
        int memsize = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gspinBtnMemory));
        int num = memsize;
        int intLength;
        for (intLength = 0; num != 0; intLength++, num = num / 10)
        {
        }
        char *length = (char *)intLength;
        char *readname = gtk_file_chooser_get_filename((GTK_FILE_CHOOSER(gfileChooserImport)));
        char *writename = gtk_file_chooser_get_filename((GTK_FILE_CHOOSER(gfileChooserExport)));

        args = new char[intLength + strlen(readname) + strlen(writename)];
        strcpy(args, "-memsize");
        strcat(args, (char *)memsize);
        strcat(args, "-readname");
        strcat(args, readname);
        strcat(args, "-writename");
        strcat(args, writename);
    }

    // Called when assemble button is clicked
    void on_btnAssembler_clicked()
    {

        Assembler assemblerObj = Assembler();
        // assemblerObj.assignArgs(assemblerObj.getArgs(argNum, argV));
        printf("Doc");

        char *run_args;
        get_args(run_args);
        assemblerObj.assignArgs((int)strlen(run_args), run_args);
        assemblerObj.assembly();
    }

    // Called when simulator button is clicked
    void on_btnSimulator_clicked()
    {
        BabySim babyObj = BabySim("Subtraction");
        // char *run_args[] = get_args();
        // babyObj.assignArgs(run_args);
        // babyObj.babyMemory = babyObj.readInCode();
        // babyObj.babyRun();
    }
}