// Imports error codes
#include "errorGui.h"
#include <stdio.h>
#include <gtk/gtk.h>

extern "C"
{
    GtkBuilder *builder;
    GtkWidget *dialog;

    void errorBox()
    {
        builder = gtk_builder_new_from_file("glade/errGeneric.glade");
        dialog = GTK_WIDGET(gtk_builder_get_object(builder, "errGeneric"));
        gtk_builder_connect_signals(builder, NULL);
        gtk_widget_show_all(dialog);
        g_object_unref(G_OBJECT(builder));
    }

    void on_errGeneric_response() {
        printf("Dog");
        gtk_widget_destroy(dialog);
    }
}

// Displays an error message to the user based on the apppropriate error code
// imported and quits the program, will do nothing if SUCCESS is passed
void checkValidity(int valid)
{
    if (valid == SUCCESS)
    {
        return;
    }

    switch (valid)
    {
    case UNEXPECTED_NULL_POINTER:
        errorBox();
        // cout << "Function has been called using a null pointer";
        break;

    case INVALID_FILE:
        errorBox();
        // cout << "A file has attempted to be imported that is invalid";
        break;

    case INVALID_FILENAME:
        errorBox();
        // cout << "The filename passed as a parameter is invalid while "
        //         "attempting to save or load a file";
        break;

    case FILE_NOT_FOUND:
        errorBox();
        // cout << "A file has attempted to be imported that doesn't exist";
        break;

    case FILE_NOT_SAVED:
        errorBox();
        // cout << "A file cannot be saved in the location provided, this "
        //         "could be an invalid filename or there may be insufficient "
        //         "permissions for access";
        break;

    case INVALID_INPUT_PARAMETER:
        errorBox();
        // cout << "Invalid Input detected. Please try again ";
        break;

    case INVALID_MEMORY_SIZE:
        errorBox();
        // cout << "Invalid or unsupported memory size input detected. "
        //         "This could be caused by the input not being an integer "
        //         "or the input size being invalid/unsupported";
        break;

    case INVALID_NUMBER_OF_ARGS: // REVIEW - there might be too many endlines here, not sure.
        errorBox();
        // cout << "Invalid number of arguments when executing the assembler. "
        //         "Please make sure to enter the argument type, then value."
        //      << endl
        //      << "Arguments: [-memsize [INTEGER]] [-readname [STRING]] [-writename [STRING]] [-extended [BOOLEAN(true/false/1/0)]]"
        //      << endl
        //      << "Examples:" << endl
        //      << "./assembler -memsize 64 -extended true" << endl
        //      << "./assembler" << endl
        //      << "./assembler -extended 0 -writename yourwritename.txt -readname yourreadname.txt -memsize 64";
        break;
        default:
        errorBox();
        // cout << "Error Code is invalid or has not been fully implemented";
    }

    // cout << endl;
}
// }
