#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<GL/gl.h>

#include"network/client.h"
#include"utils/utillib.h"

void presetButtonClicked(GtkButton *button, __attribute__((unused)) gpointer pointer);
void setBrightnessClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);
void customColorButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);
void searchScriptButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);
void saveButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);
void openButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);
gboolean renderAiBubble(GtkGLArea *area, __attribute__((unused)) GdkGLContext *context);
void windowDelete(__attribute__((unused)) GtkWidget *widget, 
        __attribute__((unused)) GdkEvent *event, __attribute__((unused)) gpointer data);

MemoryStack *memoryStack;

int main(int argc, char *argv[]){
    GtkBuilder *builder = NULL;
    GtkWidget *window;

    memoryStack = utilStackInit();

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "gui.glade", NULL) == 0){
        g_print("gtk_builder_add_from_file FAILED\n");
        return EXIT_FAILURE;
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mWindow"));
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);
    gtk_main();

    utilFreeAll(memoryStack);

    return EXIT_SUCCESS;
}

void presetButtonClicked(GtkButton *button, __attribute__((unused)) gpointer pointer){
    const gchar *func = gtk_widget_get_name(GTK_WIDGET(button));
    const char *reqMsg = "/program?func=";

    Request req;
    req.data = malloc(sizeof(reqMsg) * sizeof(char));
    strncpy(req.data, reqMsg, strlen(reqMsg));
    req.length = strlen(req.data);


    if (req.data == NULL){
        g_print("ERROR allocating memory for variable 'request'");
        utilFreeAll(memoryStack);
        exit(EXIT_FAILURE);
    }
    if (utilPushStack((void *)req.data, memoryStack) != SUCCESSFULLY_PUSHED){
        g_print("ERROR: failed to push memory");
        utilFreeAll(memoryStack);
        exit(EXIT_FAILURE);
    }

    if (func == NULL){
        g_print("ERROR: no function name for button");
        utilFreeAll(memoryStack);
        exit(EXIT_FAILURE);
    }

    int funcLength = strlen(func);
    req.length += funcLength;
    req.data = realloc(req.data, req.length);
    strncat(req.data, func, req.length);
   
    if (clientSend(&req) != SEND_SUCCESSFUL){
        g_print("Failed to send data");
    }

    utilFree(req.data, memoryStack);
}

void setBrightnessClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer){
    g_print("setBrightnessButtonClicked");
}

void customColorButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer){
    g_print("customColorButtonClicked");
}

void searchScriptButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer){
    g_print("searchScriptButtonClicked");
}

void saveButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer){
    g_print("saveButtonClicked");
}

void openButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer){
    g_print("openButtonClicked");
}

gboolean renderAiBubble(GtkGLArea *area, __attribute__((unused)) GdkGLContext *context){
    return TRUE;
}

void windowDelete(__attribute__((unused)) GtkWidget *widget, 
        __attribute__((unused)) GdkEvent *event, __attribute__((unused)) gpointer data){
    gtk_main_quit();
}
