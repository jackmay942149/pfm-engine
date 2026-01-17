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
  float tex_coords[2];
} Vertex;

typedef struct {
  uint vao;
  uint vbo;
  uint ebo;
  uint texture_id;
  uint shader_program;
  uint vertex_count;
  uint index_count;
  Vertex *vertex_data;
} Renderable;

typedef struct {
  Window *window;
} Renderer;

void
renderer_clear_colour(const Renderer *renderer, const Colour *colour);

void
renderer_draw_renderable(const Renderable *triangle);

Renderable
renderable_create(const char *vert_shader_src, const char *frag_shader_src, const char *texture_src, Vertex *vertices, u32 *indicies, u32 vertex_count, u32 index_count);

void
renderer_draw_rectangle(f32 pos_x, f32 pos_y, f32 width, f32 height);

#endif
