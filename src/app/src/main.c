#include "app.h"

MemoryStack *memoryStack;
GtkBuilder *builder = NULL;

// Used for light display (the current iterations)
size_t iter;
State state;

// The important directories
char scripts_dir[MAX_PATH_LEN];
char hc_app_dir[MAX_PATH_LEN];

int main(int argc, char *argv[]){
    GtkWidget *window;
    GtkWidget *lightVis;
    GtkWidget *colorPicker;
    FILE *fptr;

    // Define the directories
    fptr = fopen(HC_DIRECTORY_PATH_LOC, "r");
    fgets(hc_app_dir, MAX_PATH_LEN - 1, fptr);
    fptr = fopen(HC_SCRIPTS_PATH_LOC, "r");
    fgets(scripts_dir, MAX_PATH_LEN - 1, fptr);

    memoryStack = malloc(sizeof *memoryStack);
    utilErrorAssert(memoryStack != NULL, "No memory\n", (int *)NO_MEMORY, memoryStack);
    utilStackInit(memoryStack);

    iter = 1;
    state.activeFunction = utilLightWait;
    state.brightness = 1.0;
    state.num_req = 0;
    state.prevColor.red = 0;
    state.prevColor.green = 0;
    state.prevColor.blue = 0;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "gui.glade", NULL) == 0){
        utilErrorPanic(EXIT_FAILURE, "failed to get gtk builder\n", memoryStack);
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mWindow"));
    gtk_builder_connect_signals(builder, NULL);

    lightVis = GTK_WIDGET(gtk_builder_get_object(builder, "lightVis"));

    colorPicker = GTK_WIDGET(gtk_builder_get_object(builder, "colorPicker"));

    g_timeout_add(10, lightVisCallback, lightVis);
    g_timeout_add(100, G_SOURCE_FUNC(colorStream), colorPicker);
    g_timeout_add(100, G_SOURCE_FUNC(recursionResetCallback), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    utilStackEmpty(memoryStack);
    free(memoryStack);

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
    utilErrorAssert(req.data != NULL, "No memory\n", (int *)NO_MEMORY, memoryStack);

    utilStackPush(memoryStack, (void *)req.data);

    strncpy(req.data, reqMsg, reqMsgLen + 1);
    strncat(req.data, func, funcLen);

    utilClientSend(&req, memoryStack);
    state.num_req++;

    utilStackFree(memoryStack, req.data);

    updateState(func, funcLen);
}

void setBrightnessClicked(__attribute__((unused)) GtkWidget *widget,
                            __attribute__((unused)) gpointer pointer){
    GtkWidget *brightnessSlider = GTK_WIDGET(gtk_builder_get_object(builder, "brightnessAdjustment"));
    
    utilErrorAssert(brightnessSlider != NULL, "No brightness slider\n", NULL, memoryStack);

    int brightnessValue = (int)gtk_adjustment_get_value(GTK_ADJUSTMENT(brightnessSlider));
    char brightnessValStr[10];
    snprintf(brightnessValStr, 10, "%d", brightnessValue);

    const char reqMsg[] = "brightness:";
    const size_t reqMsgLen = strlen(reqMsg);
    const size_t brightnessValLen = strlen(brightnessValStr);
    Request req;

    req.length = reqMsgLen + brightnessValLen;
    req.data = malloc(req.length + 1);

    utilErrorAssert(req.data != NULL, "No memory\n", (int *)NO_MEMORY, memoryStack);
    utilStackPush(memoryStack, (void *)req.data);

    strncpy(req.data, reqMsg, reqMsgLen);
    strncat(req.data, brightnessValStr, brightnessValLen);

    utilClientSend(&req, memoryStack);
    state.num_req++;

    state.brightness = (double)brightnessValue / 100;

    utilStackFree(memoryStack, req.data);
}

void saveButtonClicked(GtkWidget *widget, gpointer text_view){
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Save File",
                                        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                        GTK_FILE_CHOOSER_ACTION_SAVE,
                                        "_Cancel", GTK_RESPONSE_CANCEL,
                                        "_Save", GTK_RESPONSE_ACCEPT,
                                        NULL
                                        );

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), scripts_dir);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
    
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename;
        GtkTextBuffer *buf;
        GtkTextIter start, end;
        char *contents;

        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_get_bounds(buf, &start, &end);
        contents = gtk_text_buffer_get_text(buf, &start, &end, FALSE);

        g_file_set_contents(filename, contents, -1, NULL);

        g_free(contents);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void openButtonClicked(GtkWidget *widget, gpointer text_view){
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Open File", 
                                        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        "_Cancel", GTK_RESPONSE_CANCEL,
                                        "_Open", GTK_RESPONSE_ACCEPT,
                                        NULL
                                        );

    gtk_file_chooser_set_current_folder(
                                    GTK_FILE_CHOOSER(dialog),
                                    scripts_dir 
                                    );

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename;
        char *contents;
        gsize length;
        GtkTextBuffer *buf;

        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (g_file_get_contents(filename, &contents, &length, NULL)){
            buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            gtk_text_buffer_set_text(buf, contents, length);
            g_free(contents);
        }
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

/// TODO: 
///     - Create and implement an interpreter for the light sim
///     - Override errors to stop crashes. Or integrate a 
///         new parser with red squigglies
///     - Syntax highlighting
void runBtnClicked(GtkWidget *widget, gpointer text_view){
    lexer *l;
    parser *p;
    token **tokenStream;
    GtkTextBuffer *buf;
    GtkTextIter start, end;
    char *contents;

    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_get_bounds(buf, &start, &end);
    contents = gtk_text_buffer_get_text(buf, &start, &end, FALSE);

    l = lexer_new_lexer(contents);
    tokenStream = lexer_lex(l);
    p = parser_new_parser(tokenStream);
    parser_parse(p);

    g_free(contents);
    
    printf("Code parses\n");
}

gboolean colorStream(gpointer color_picker){
    GdkRGBA customColor;
    Request req;

    size_t max_length = 51; // Data will max at: func:colorwheel,(123, 456, 789)
    
    req.data = malloc(max_length);

    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(color_picker), &customColor);

    // Don't waste resources by sending repetetive data
    if (customColor.red == state.prevColor.red && 
            customColor.green == state.prevColor.green && 
            customColor.blue == state.prevColor.blue){
        return TRUE;
    }
    state.prevColor.red = customColor.red;
    state.prevColor.green = customColor.green;
    state.prevColor.blue = customColor.blue;
    
    snprintf(req.data, max_length - 1, "func:colorwheel#(%d, %d, %d)", 
            (int) round(customColor.red * 255), 
            (int) round(customColor.green * 255), 
            (int) round(customColor.blue * 255)
            );
    req.length = strlen(req.data);
    utilClientSend(&req, memoryStack);
    state.num_req++;

    return TRUE;
}

gboolean recursionResetCallback(){
    if (state.num_req > 50){
        Request req;
        req.data = "func:wait";
        req.length = 9;

        utilClientSend(&req, memoryStack);
        state.num_req = 0;

        return TRUE;
    }
    return TRUE;
}

gboolean drawLightVis(GtkWidget *widget, cairo_t *cr, __attribute__((unused)) gpointer pointer){
    guint width, height;

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    LightDisplayArea lda = {
        .width = width, 
        .height = height, 
        .cr = cr, 
        .brightness = state.brightness,
        .iter = iter
    };

    state.activeFunction(&lda);
    
    return FALSE;
}

gboolean drawLightCompiled(GtkWidget *widget, cairo_t *cr, __attribute__((unused)) gpointer pointer){
    return FALSE;
}

gboolean lightVisCallback(gpointer data){
    iter++;
    iter = iter % NUM_LIGHTS;
    GtkWidget *widget = GTK_WIDGET(data);
    gtk_widget_queue_draw(widget);
    return TRUE;
}

void windowDelete(__attribute__((unused)) GtkWidget *widget, 
        __attribute__((unused)) GdkEvent *event, __attribute__((unused)) gpointer data){
    gtk_main_quit();
}

void updateState(const gchar *func, size_t len){
    // I will fix this later, but i need something working for now, so I will do a big strncmp

    if (strncmp(func, "wait", len) == 0){
        state.activeFunction = utilLightWait;
    }else if (strncmp(func, "white", len) == 0){
        state.activeFunction = utilLightWhite;
    }else if (strncmp(func, "virginLights", len) == 0){
        state.activeFunction = utilLightVirginLights;
    }else if (strncmp(func, "flow", len) == 0){
        state.activeFunction = utilLightFlow;
    }
}
