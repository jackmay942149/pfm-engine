#include "renderer.h"

#include <windows.h>
#include <gl/GL.h>
#include <assert.h>

#include "shader.h"
#include "opengl-functions.h"

void
renderer_clear_colour(const Renderer *renderer, const Colour* colour) {
  assert(renderer != NULL);
  assert(colour != NULL);
  glClearColor(colour->r, colour->g, colour->b, colour->a);
  glClear(GL_COLOR_BUFFER_BIT);
  return;
}

void
renderer_draw_renderable(const Renderable *object) {
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

// Draw rectangle at any point
const char rect_vert_shader_src[] = {
  #embed  "../shaders/rectangle.vert"
};

const char rect_frag_shader_src[] = {
  #embed  "../shaders/red.frag"
};

Vertex rect_vertices[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
  -1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
  -1.0f,  1.0f, 0.0f
};

void
renderer_draw_rectangle(f32 pos_x, f32 pos_y, f32 width, f32 height) {
  static Renderable rect = {};
  static bool initialised = false;
  if (!initialised) {
    rect = renderable_create(rect_vert_shader_src, rect_frag_shader_src, rect_vertices, sizeof(rect_vertices)/sizeof(Vertex));
    initialised = true;
  }
  glUseProgram(rect.shader_program);
  int u_pos_location = glGetUniformLocation(rect.shader_program, "u_pos");
  int u_width_location = glGetUniformLocation(rect.shader_program, "u_width");
  int u_height_location = glGetUniformLocation(rect.shader_program, "u_height");
  glUniform2f(u_pos_location, pos_x, pos_y);
  glUniform1f(u_width_location, width);
  glUniform1f(u_height_location, height);
  renderer_draw_renderable(&rect);
}
