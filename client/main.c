#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<GL/gl.h>

#inlcude"network/client.h"
#include"assistant/ai.h"
#include"l-script/lscript.h"
#include"utils/utillib.h"

void presetButtonClicked(GtkWidget *widget, gpointer pointer);
void setBrightnessClicked(GtkWidget *widget, gpointer pointer);

void **memoryStack = mem_stack_init();

int main(int argc, char *argv[]){
    if (memoryStack == FAILED_ALLOCATION_ERROR){
        printf("ERROR: failed to allocate memory to memory_allocations");
        return EXIT_FAILURE;
    }

    GtkBuilder *builder;

    gkt_init(&argc, &argv);

    builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, "gui.glade", NULL) == 0){
        printf("gtk_builder_add_from_file FAILED\n");
        return EXIT_FAILURE;
    }

    gtk_builder_connect_signals(builder, NULL);

    gtk_main();
    return EXIT_SUCCESS;
}

void presetButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer){
    gchar *label = get_label(widget);

    if (label == NULL){
        printf("ERROR: no label for button");
        if (free_all(memoryStack) != FREE_SUCCESSFUL){
            printf("Failed to free memory in stack");
        }
    }

    if (strncmp(label, "Flow", sizeof("Flow"))){
        char request[] = "func:flow";
    }else if (strncmp(label, "Collapse", sizeof("Collapse"))){
        char request[] = "func:collapse";
    }else if (strncmp(label, "Alternate", sizeof("Alternate"))){
        char request[] = "func:alternate";
    }else if (strncmp(label, "Pulse", sizeof("Pulse"))){
        char request[] = "func:pulse";
    }else if (strncmp(label, "Night Light", sizeof("Night Light"))){
        char request[] = "func:nightlight";
    }else if (strncmp(label, "Virgin Lights", sizeof("Virgin Lights"))){
        char request[] = "func:virginlights";
    }else if (strncmp(label, "Red", sizeof("Red"))){
        char request[] = "func:red";
    }else if (strncmp(label, "Green", sizeof("Green"))){
        char request[] = "func:green";
    }else if (strncmp(label, "Blue", sizeof("Blue"))){
        char request[] = "func:blue";
    }else if (strncmp(label, "White", sizeof("White"))){
        char request[] = "func:white";
    }else if (strncmp(label, "Wait", sizeof("Wait"))){
        char request[] = "func:wait";
    }else if(strncmp(label, "QUIT!", sizeof("QUIT!"))){
        char request[] = "func:quit";
    }else{
        char request = NULL;
        printf("Unaccounted for buton label: %s", label);
    }
    
    if (request != NULL){
        client_send(&request);
    }
}

void setBrightnessClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer){
    GtkWidget brightnessScale = gtk_widget_get_template_child()
}
