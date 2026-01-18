#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "window.h"

typedef struct {
  f32 r;
  f32 g;
  f32 b;
  f32 a;  
} Colour;

typedef struct {
  f32 position[3];
  f32 tex_coords[2];
} Vertex;

typedef struct {
  u32 vao;
  u32 vbo;
  u32 ebo;
  u32 texture_id;
  u32 shader_program;
  u32 vertex_count;
  u32 index_count;
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

u32
renderer_create_vao();

u32
renderer_create_vbo(const Vertex *vertices, u32 vertex_count);

u32
renderer_create_ebo(const u32 *indicies, u32 index_count);

u32
renderer_create_texture(const char *texture_filepath);
#endif
