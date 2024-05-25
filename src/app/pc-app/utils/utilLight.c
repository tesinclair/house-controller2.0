#include"utillib.h"

#include <unistd.h>

void utilLightWait(LightDisplayArea *lda){
    int stripe_width = lda->width / NUM_LIGHTS;

    for (int i = 0; i < NUM_LIGHTS; ++i){
        cairo_set_source_rgb(lda->cr, 0.1, 0.1, 0.1);
        cairo_rectangle(lda->cr, i * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }
}

void utilLightWhite(LightDisplayArea *lda){
    int stripe_width = lda->width / NUM_LIGHTS;

    double color[3] = {1.0, 1.0, 1.0};

    utilLightUpdateColor(&color, lda->brightness);

    for (int i = 0; i < NUM_LIGHTS; ++i){
        cairo_set_source_rgb(lda->cr, color[0], color[1], color[2]);
        cairo_rectangle(lda->cr, i * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }
}

void utilLightVirginLights(LightDisplayArea *lda){
    int stripe_width = lda->width / NUM_LIGHTS;
    size_t offset = lda->iter;
    size_t redL, redR, greenL, greenR, blueL, blueR;

    redL = 0 + offset;
    redR = (NUM_LIGHTS / 3 + offset) - 1;
    greenL = NUM_LIGHTS / 3 + offset;
    greenR = ((NUM_LIGHTS * 2) / 3 + offset) - 1;
    blueL = (NUM_LIGHTS * 2) / 3 + offset;
    blueR = (NUM_LIGHTS + offset) - 1;

    double color[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    for (int i = 0; i < 3; ++i){
        utilLightUpdateColor(&color[i], lda->brightness);
    }
    
    for (size_t i = redL; i < redR; ++i){
        size_t temp = i % NUM_LIGHTS;
        cairo_set_source_rgb(lda->cr, color[0][0], color[0][1], color[0][2]);
        cairo_rectangle(lda->cr, temp * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }
    for (size_t i = greenL; i < greenR; ++i){
        size_t temp = i % NUM_LIGHTS;
        cairo_set_source_rgb(lda->cr, color[1][0], color[1][1], color[1][2]);
        cairo_rectangle(lda->cr, temp * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }
    for (size_t i = blueL; i < blueR; ++i){
        size_t temp = i % NUM_LIGHTS;
        cairo_set_source_rgb(lda->cr, color[2][0], color[2][1], color[2][2]);
        cairo_rectangle(lda->cr, temp * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }

}

void utilLightFlow(LightDisplayArea *lda){
    int stripe_width = lda->width / NUM_LIGHTS;
    size_t offset = lda->iter;

    double color[3] = {1.0, 1.0, 1.0};

    utilLightUpdateColor(&color, lda->brightness);

    for (int i = 0; i < NUM_LIGHTS; ++i){
        cairo_set_source_rgb(lda->cr, 0.1, 0.1, 0.1);
        cairo_rectangle(lda->cr, i * stripe_width, 10, lda->height, stripe_width);
        cairo_fill(lda->cr);
    }
    
    cairo_set_source_rgb(lda->cr, color[0], color[1], color[2]);
    cairo_rectangle(lda->cr, offset * stripe_width, 10, lda->height, stripe_width);
    cairo_fill(lda->cr);
}
void utilLightUpdateColor(double (*color)[], double brightness){
    for (int i = 0; i < 3; i++){
        (*color)[i] *= brightness;
    }
}
