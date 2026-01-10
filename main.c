#include <stdio.h>
#include <assert.h>

#include <windows.h>
#include <gl/GL.h>

#include "window.h"
#include "renderer.h"
#include "allocator.h"
#include "opengl-loader.h"
#include "opengl-functions.h"

#include "shader.c"
#include "window.c"
#include "renderer.c"
#include "allocator.c"

const char vertex_shader_src[] = {
  #embed "./src/shaders/default.vert"
};
const char fragment_shader_src[] = {
  #embed "./src/shaders/red.frag"
};

Vertex tri_vertices[] = {
  -.10f, -.10f, 0.0f,
   .10f, -.10f, 0.0f,
   0.0f,  .10f, 0.0f
};

typedef struct {
  float x,y;
} Vector2f32;

typedef struct {
  Vector2f32 position;
  Renderable *render_data;
} Entity;

void
draw_entity(const Entity *entity) {
  assert(entity != NULL);
  assert(entity->render_data != NULL);
  glUseProgram(entity->render_data->shader_program);
  int uniform_location = glGetUniformLocation(entity->render_data->shader_program, "u_pos");
  glUniform2f(uniform_location, entity->position.x, entity->position.y);
  
  glBindVertexArray(entity->render_data->vao);
  glBindBuffer(GL_ARRAY_BUFFER, entity->render_data->vbo);
  glDrawArrays(GL_TRIANGLES, 0, entity->render_data->vertex_count);
  return;
}

int
main() {
  Allocator app_allocator = allocator_create(1000, false);
  Allocator frame_allocator = allocator_create(1000, false);

  Window *window = window_create(1920 / 2, 1080 / 2, "Window", &app_allocator);

  Renderer renderer = {
    .window = window
  };
  load_gl_funcs();
  
  Renderable tri = renderable_create(vertex_shader_src, fragment_shader_src, tri_vertices, sizeof(tri_vertices)/sizeof(Vertex));
  Entity scene[100];
  for (int i = 0; i < 100; i++) {
    Entity* entity = &scene[i];
    int x_coord = i % 10;
    int y_coord = i / 10;
    entity->position = (Vector2f32){.x = x_coord/5.f - 1.f, .y = y_coord/5.f - 1.f};
    entity->render_data = &tri;
  }

  while (!window_should_close(window)) {
    renderer_clear_colour(&renderer, &(Colour){0.f, 0.f, 0.f, 1.f});
    for (int i = 0; i < 100; i++) {
      draw_entity(&scene[i]);
    }
    // renderer_draw_renderable(&renderer, &tri);
    window_poll_events(window);
    window_swap_buffers(window);
    allocator_free_all(&frame_allocator);
  }

  window_close(window);
  allocator_free_all(&app_allocator);
  printf("Window Close");
}
