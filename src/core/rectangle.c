#include "rectangle.h"

#include "boolean.h"
#include "renderer.h"
#include "opengl-functions.h"

const char rect_vert_shader_src[] = {
  #embed  "../shaders/rectangle.vert"
};

const char rect_frag_shader_src[] = {
  #embed  "../shaders/rectangle.frag"
};

Vertex rect_vertices[] = {
  // Position          // Tex Coords
  -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
   1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
  -1.0f,  1.0f, 0.0f,  0.0f, 1.0f
};

u32 rect_indicies[] = {
  0, 1, 2,
  0, 2, 3
};

void
rectangle_draw(f32 pos_x, f32 pos_y, f32 width, f32 height) {
  // Run once to set up rectangle
  static Renderable rect = {};
  static Bool initialised = false;
  if (!initialised) {
    rect = renderable_create(rect_vert_shader_src, rect_frag_shader_src, "src/textures/awesomeface.png", rect_vertices, rect_indicies, sizeof(rect_vertices)/sizeof(Vertex), sizeof(rect_indicies)/ sizeof(u32));
    initialised = true;
  }

  glUseProgram(rect.shader_program);
  i32 u_pos_location = glGetUniformLocation(rect.shader_program, "u_pos");
  // int u_texture = glGetUniformLocation(rect.shader_program, "texture1");
  i32 u_width_location = glGetUniformLocation(rect.shader_program, "u_width");
  i32 u_height_location = glGetUniformLocation(rect.shader_program, "u_height");
  glUniform2f(u_pos_location, pos_x, pos_y);
  glUniform1f(u_width_location, width);
  glUniform1f(u_height_location, height);
  renderer_draw_renderable(&rect);
}
