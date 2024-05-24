#include"utillib.h"

#include <unistd.h>

void utilLightWait(LightDisplayArea *lda){
    int stripe_width = lda->width / 100;

    for (int i = 0; i < NUMLIGHTS; ++i){
        cairo_set_source_rgb(lda->cr, 0.1, 0.1, 0.1);
        cairo_rectangle(lda->cr, i * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }
}

void utilLightWhite(LightDisplayArea *lda){
    int stripe_width = lda->width / 100;

    double color[3] = {1.0, 1.0, 1.0};

    utilLightUpdateColor(&color, lda->brightness);

    for (int i = 0; i < NUMLIGHTS; ++i){
        cairo_set_source_rgb(lda->cr, color[0], color[1], color[2]);
        cairo_rectangle(lda->cr, i * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }
}

void utilLightUpdateColor(double (*color)[], double brightness){
    for (int i = 0; i < 3; i++){
        (*color)[i] *= brightness;
    }
}
