#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"

typedef struct {
  float r;
  float g;
  float b;
  float a;  
} Colour;

typedef struct {
  Window *window;
} Renderer;

void
renderer_clear_colour(Renderer *renderer, Colour* colour);
  

#endif
