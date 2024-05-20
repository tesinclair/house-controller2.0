#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<GL/gl.h>

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
GtkBuilder *builder = NULL;

int main(int argc, char *argv[]){
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

    utilStackEmpty(memoryStack);

    return EXIT_SUCCESS;
}

void presetButtonClicked(GtkButton *button, __attribute__((unused)) gpointer pointer){
    const gchar *func = gtk_widget_get_name(GTK_WIDGET(button));
    const size_t funcLen = strlen(func);
    const char reqMsg[] = "func:";
    const size_t reqMsgLen = strlen(reqMsg);
    Request req;

    req.length = reqMsgLen + funcLen;
    req.data = malloc(req.length + 1);

    if (req.data == NULL){
        g_print("ERROR allocating memory for variable 'request' in: %s", __function__);
        utilStackEmpty(memoryStack);
        free(memoryStack);
        exit(EXIT_FAILURE);
    }
    utilStackPush(memoryStack, (void *)req.data);

    strncpy(req.data, reqMsg, reqMsgLen);
    strncat(req.data, func, funcLen);

    if (clientSend(&req) != SEND_SUCCESSFUL){
        g_print("Failed to send data");
    }

    utilStackFree(memoryStack, req.data);
}

void setBrightnessClicked(__attribute__((unused)) GtkWidget *widget,
                            __attribute__((unused)) gpointer pointer){
    GtkWidget *brightnessSlider = gtk_builder_get_object(builder, "brightnessAdjustment");
    
    if (brightnessSlider == NULL){
        g_print("ERROR: failed to get brightnessSlider from glade in %s", __function__);
        utilStackEmpty(memoryStack);
        free(memoryStack);
        exit(EXIT_FAILURE);
    }

    int brightnessValue = (int)gtk_adjustment_get_value(GTK_ADJUSTMENT(brightnessSlider));
    char brightnessValStr[4];
    itoa(brightnessValue, brightnessValStr, 4);

    const char reqMsg[] = "brightness:";
    const size_t reqMsgLen = strlen(reqMsg);
    const size_t brightnessValLen = strlen(brightnessValStr);
    Request req;

    req.length = reqMsgLen + brightnessValLen
    req.data = malloc(req.length + 1);

    if (req.data == NULL){
        g_print("ERROR allocating memory for variable 'req' in: %s", __function__);
        utilStackEmpty(memorystack);
        free(memoryStack);
        exit(EXIT_FAILURE);
    }
    utilStackPush(memoryStack, (void *)req.data);

    strncpy(req.data, reqMsg, reqMsgLen);
    strncat(req.data, brightnessValStr, brightnessValLen);

    if (clientSend(&req) != SEND_SUCCESSFUL){
        g_print("Failed to send data");
    }

    utilStackFree(memoryStack, req.data);
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
