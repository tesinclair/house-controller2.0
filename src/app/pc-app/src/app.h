#ifndef APP_H
#define APP_H

#include <ctype.h>
#include <math.h>
#include <lights-dsl.h>

#include "utils/utillib.h"

/// @params:
///     button: The preset button
/// @purpose: 
///     Change the p[en window to the presets
///     window
void presetButtonClicked(GtkButton *button, __attribute__((unused)) gpointer pointer);

/// @params:
///     widget: the setbrightness button
/// @purpose:
///     get the current brightness, and send a req to 
///     the server
void setBrightnessClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);

/// @param:
///     the custom color button
/// @purpose:
///     get the current color and send it 
///     to the server
void customColorButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);

/// @param:
///     the search button
/// @purpose:
///     open a new window in the scripts/ directory
///     for the user to select a script
void searchScriptButtonClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);

/// @param:
///     the save button
/// @purpose:
///     open up the save new window
///     in the scripts/ dir. automatiically save as .lts
void saveButtonClicked(GtkWidget *widget, gpointer text_view);

/// @param:
///     the open button
/// @purpose:
///     opens the open new window in the
///     scripts/ dir
void openButtonClicked(GtkWidget *widget, gpointer text_view);

/// @param:
///     the run btn
/// @purpose:
///     runs a compiler that transpiles the code
///     to controll a light sim on the screen
void runBtnClicked(GtkWidget *widget, __attribute__((unused)) gpointer pointer);

/// @params:
///     widget: the light vis
///     cr: the cairop object to draw
/// @purpose:
///     draws the light sim
gboolean drawLightVis(GtkWidget *widget, cairo_t *cr, __attribute__((unused)) gpointer pointer);

/// @params:
///     widget: the light vis
///     cr: the cairo obkect to draw
/// @purpose:
///     draws the lights compiled in run (defaults to grey)
gboolean drawLightCompiled(GtkWidget *widget, cairo_t *cr, __attribute__((unused)) gpointer pointer);

/// @purpose:
///     destroy the window
void windowDelete(__attribute__((unused)) GtkWidget *widget, 
        __attribute__((unused)) GdkEvent *event, __attribute__((unused)) gpointer data);

/// @params:
///     func: the function name to change to
///     len: the length of the function name
/// @purpose:
///     updates the lightsim state to be the currently
///     running function
void updateState(const gchar *func, size_t len);

/// @purpose:
///     the light visualisation callback
static gboolean lightVisCallback(gpointer data);

/// @attributes:
///     activeFunction: pointer to the light drawing function
///     brightness: the brightness
/// @purpose:
///     holds the state of the light simulator
typedef struct{
    void (*activeFunction)(LightDisplayArea *lda); 
    double brightness;
} State;

/// @GLOBALS
MemoryStack *memoryStack;
GtkBuilder *builder = NULL;
size_t iter;
State state;

#endif
