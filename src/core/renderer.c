#include "renderer.h"

#include <windows.h>
#include <gl/GL.h>
#include <assert.h>

#include "types.h"
#include "shader.h"
#include "opengl-functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
  glBindTexture(GL_TEXTURE_2D, object->texture_id);
  glBindVertexArray(object->vao);
  glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, object->ebo);
  glDrawElements(GL_TRIANGLES, object->index_count, GL_UNSIGNED_INT, 0);
  return;
}

u32
renderer_create_vao() {
  u32 vao;
  glGenVertexArrays(1, &vao);
  assert(vao != 0);
  glBindVertexArray(vao);
  return vao;
}

u32
renderer_create_vbo(const Vertex *vertices, u32 vertex_count) {
  assert(vertices != NULL);
  assert(vertex_count != 0);

  u32 vbo;
  glGenBuffers(1, &vbo);
  assert(vbo != 0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertex_count, vertices, GL_STATIC_DRAW);
  return vbo;
}

u32
renderer_create_ebo(const u32 *indicies, u32 index_count) {
  assert(indicies != NULL);
  assert(index_count != 0);
  
  u32 ebo;
  glGenBuffers(1, &ebo);
  assert(ebo != 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies[0]) * index_count, indicies, GL_STATIC_DRAW);
  return ebo;
}

u32
renderer_create_texture(const char *texture_filepath) {
  i32 width, height, channel_count;
  stbi_set_flip_vertically_on_load(true);
  u8 *data = stbi_load(texture_filepath, &width, &height, &channel_count, 0);
  if (data == NULL) {
    const char *err = stbi_failure_reason();
    printf("%s\n", err);
  }
  u32 texture_id;
  glGenTextures(1, &texture_id);
  assert(texture_id != 0);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  return texture_id;
}

Renderable
renderable_create(const char *vert_shader_src, const char *frag_shader_src, const char *texture_src, Vertex *vertices, u32 *indicies, u32 vertex_count, u32 index_count) {
  Shader shader = shader_register(vert_shader_src, frag_shader_src);

  u32 vao = renderer_create_vao();
  u32 vbo = renderer_create_vbo(vertices, vertex_count);
  u32 ebo = renderer_create_ebo(indicies, index_count);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
  glEnableVertexAttribArray(1);

  u32 texture_id = renderer_create_texture(texture_src);

  Renderable out = {};
  out.shader_program = shader.id;
  out.vao = vao;
  out.vbo = vbo;
  out.ebo = ebo;
  out.texture_id = texture_id;
  out.vertex_data = vertices;
  out.vertex_count = vertex_count;
  out.index_count = index_count;
  
  return out;
}

// Draw rectangle at any point
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
renderer_draw_rectangle(f32 pos_x, f32 pos_y, f32 width, f32 height) {
  // Run once to set up rectangle
  static Renderable rect = {};
  static Bool initialised = false;
  if (!initialised) {
    rect = renderable_create(rect_vert_shader_src, rect_frag_shader_src, "awesomeface.png", rect_vertices, rect_indicies, sizeof(rect_vertices)/sizeof(Vertex), sizeof(rect_indicies)/ sizeof(u32));
    initialised = true;
  }

  glUseProgram(rect.shader_program);
  int u_pos_location = glGetUniformLocation(rect.shader_program, "u_pos");
  // int u_texture = glGetUniformLocation(rect.shader_program, "texture1");
  int u_width_location = glGetUniformLocation(rect.shader_program, "u_width");
  int u_height_location = glGetUniformLocation(rect.shader_program, "u_height");
  glUniform2f(u_pos_location, pos_x, pos_y);
  glUniform1f(u_width_location, width);
  glUniform1f(u_height_location, height);
  renderer_draw_renderable(&rect);
}
