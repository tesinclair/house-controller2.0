#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
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

void ***memoryStack;

int main(int argc, char *argv[]){
    GtkBuilder *builder = NULL;
    GtkWidget *window;

    memoryStack = utilStackInit();

    if (*memoryStack == (void **)FAILED_ALLOCATION_ERROR){
        g_print("ERROR: failed to allocate memory to memory_allocations");
        return EXIT_FAILURE;
    }

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

    utilFreeAll(*memoryStack);

    return EXIT_SUCCESS;
}

void presetButtonClicked(GtkButton *button, __attribute__((unused)) gpointer pointer){
    // TODO: add individual messages for each error case
    const gchar *label = gtk_button_get_label(button);
    char *request = malloc(36 * sizeof(char));
    const int reqLen = 35;

    if (request == NULL){
        g_print("ERROR allocating memory for variable 'request'");
        if (utilFreeAll(*memoryStack) != FREE_SUCCESSFUL){
            g_print("Failed to free stack memory");
        }
        exit(EXIT_FAILURE);
    }
    if (utilPushStack((void *)request, memoryStack) != SUCCESSFULLY_PUSHED){
        g_print("ERROR: failed to push memory");
        if (utilFreeAll(*memoryStack) != FREE_SUCCESSFUL){
            g_print("Failed to free stack memory");
        }
        exit(EXIT_FAILURE);
    }

    if (label == NULL){
        g_print("ERROR: no label for button");
        if (utilFreeAll(*memoryStack) != FREE_SUCCESSFUL){
            g_print("Failed to free stack memory");
        }
        exit(EXIT_FAILURE);
    }

    void assignReq(char *temp){
        int tempLen = 0;
        while (temp[tempLen] != '\0'){
            tempLen++;
        }

        if (tempLen >= reqLen){
            g_print("Function data too large");
            if (utilFreeAll(*memoryStack) != FREE_SUCCESSFUL){
                g_print("Failed to free stack memory");
            }
            exit(EXIT_FAILURE);
        }
        strncpy(request, temp, tempLen);
    }

    if (strncmp(label, "Flow", sizeof("Flow"))){
        assignReq("func:flow\0");
    }else if (strncmp(label, "Collapse", sizeof("Collapse"))){
        assignReq("func:collapse\0");
    }else if (strncmp(label, "Alternate", sizeof("Alternate"))){
        assignReq("func:alternate\0");
    }else if (strncmp(label, "Pulse", sizeof("Pulse"))){
        assignReq("func:pulse\0");
    }else if (strncmp(label, "Night Light", sizeof("Night Light"))){
        assignReq("func:nightlight\0");
    }else if (strncmp(label, "Virgin Lights", sizeof("Virgin Lights"))){
        assignReq("func:virginlights\0");
    }else if (strncmp(label, "Red", sizeof("Red"))){
        assignReq("func:red\0");
    }else if (strncmp(label, "Green", sizeof("Green"))){
        assignReq("func:green\0");
    }else if (strncmp(label, "Blue", sizeof("Blue"))){
        assignReq("func:blue\0");
    }else if (strncmp(label, "White", sizeof("White"))){
        assignReq("func:white\0");
    }else if (strncmp(label, "Wait", sizeof("Wait"))){
        assignReq("func:wait\0");
    }else if(strncmp(label, "QUIT!", sizeof("QUIT!"))){
        assignReq("func:quit\0");
    }else{
        g_print("Unaccounted for buton label: %s", label);
        if (utilFreeAll(*memoryStack) != FREE_SUCCESSFUL){
            g_print("Failed to free stack memory");
        }
        exit(EXIT_FAILURE);
    }
    
    int length;
    // Get rid of garbage
    for (int i = 0; i < strlen(request); i++){
        if (request[i] == '\0'){
            request = (char *)realloc(request, (i + 1) * sizeof(char)); 
            length = strlen(request);
            break;
        }
    }
    clientSend(request, length);
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
