#include "renderer.h"

#include <windows.h>
#include <gl/GL.h>
#include <assert.h>

#include "shader.h"
#include "opengl-functions.h"

void
renderer_clear_colour(Renderer *renderer, Colour* colour) {
  assert(renderer != NULL);
  assert(colour != NULL);
  glClearColor(colour->r, colour->g, colour->b, colour->a);
  glClear(GL_COLOR_BUFFER_BIT);
  return;
}

void
renderer_draw_renderable(Renderer *renderer, Renderable *object) {
  assert(renderer != NULL);
  assert(object != NULL);
  glUseProgram(object->shader_program);
  glBindVertexArray(object->vao);
  glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
  glDrawArrays(GL_TRIANGLES, 0, object->vertex_count);
  return;
}


Renderable
renderable_create(const char *vert_shader_src, const char *frag_shader_src, Vertex *vertices, uint vertex_count) {
  Shader orange_shader = shader_register(vert_shader_src, frag_shader_src);

  uint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertex_count, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  Renderable out = {};
  out.shader_program = orange_shader.id;
  out.vao = vao;
  out.vbo = vbo;
  out.vertex_data = vertices;
  out.vertex_count = vertex_count;
  
  return out;
}
