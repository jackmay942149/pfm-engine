#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "window.h"

typedef struct {
  float r;
  float g;
  float b;
  float a;  
} Colour;

typedef struct {
  float position[3];
} Vertex;

typedef struct {
  uint vao;
  uint vbo;
  uint shader_program;
  uint vertex_count;
  Vertex *vertex_data;
} Renderable;

typedef struct {
  Window *window;
} Renderer;

void
renderer_clear_colour(const Renderer *renderer, const Colour *colour);

void
renderer_draw_renderable(const Renderer *renderer, const Renderable *triangle);

Renderable
renderable_create(const char *vert_shader_src, const char *frag_shader_src, Vertex *vertices, uint vertex_count);

#endif
