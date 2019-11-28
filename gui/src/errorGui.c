// Imports error codes
#include "errorGui.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>

extern "C"
{
    GtkBuilder *builder;
    GtkWidget *dialog;

    void errorBox()
    {
        if (dialog == NULL)
        {
            builder = gtk_builder_new_from_file("glade/errGeneric.glade");
            dialog = GTK_WIDGET(gtk_builder_get_object(builder, "errGeneric"));
            gtk_builder_connect_signals(builder, NULL);
            gtk_widget_show_all(dialog);
            g_object_unref(G_OBJECT(builder));
        }
    }

    void on_btnExit_clicked()
    {
        gtk_widget_destroy(dialog);
        dialog = NULL;
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
        printf("Function has been called using a null pointer");
        break;

    case INVALID_FILE:
        errorBox();
        printf("A file has attempted to be imported that is invalid");
        break;

    case INVALID_FILENAME:
        errorBox();
        printf("The filename passed as a parameter is invalid while attempting to save or load a file");
        break;

    case FILE_NOT_FOUND:
        errorBox();
        printf("A file has attempted to be imported that doesn't exist");
        break;

    case FILE_NOT_SAVED:
        errorBox();
        printf("A file cannot be saved in the location provided, this could be an invalid filename or there may be insufficient permissions for access");
        break;

    case INVALID_INPUT_PARAMETER:
        errorBox();
        printf("Invalid Input detected. Please try again");
        break;

    case INVALID_MEMORY_SIZE:
        errorBox();
        printf("Invalid or unsupported memory size input detected.");
        break;

    case INVALID_NUMBER_OF_ARGS:
        errorBox();
        printf("Invalid number of arguments when executing the assembler.");
        break;
    default:
        errorBox();
        printf("Error Code is invalid or has not been fully implemented");
    }
    printf("\n");
}
