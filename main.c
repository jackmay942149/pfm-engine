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

Vertex tri_vertices[] = {
  -.5f, -.5f, 0.f,
   .5f, -.5f, 0.f,
   0.f,  .5f, 0.f
};
Vertex tri_2_vertices[] = {
  -.5f, -.5f, 0.f,
   .9f, -.6f, 0.f,
   0.1f,  .3f, 0.f
};

const char *vertex_shader_src = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0"; 

const char *fragment_shader_src = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "} \0";


int
main() {
  Allocator app_allocator = allocator_create(1000, false);
  Allocator frame_allocator = allocator_create(1000, false);

  Window *window = window_create(1920 / 2, 1080 / 2, "Window", &app_allocator);

  Renderer renderer = {
    .window = window
  };
  load_gl_funcs();
  
  Renderable tri2 = renderable_create(vertex_shader_src, fragment_shader_src, tri_2_vertices, sizeof(tri_2_vertices)/sizeof(Vertex));
  Renderable tri = renderable_create(vertex_shader_src, fragment_shader_src, tri_vertices, sizeof(tri_vertices)/sizeof(Vertex));

  while (!window_should_close(window)) {
    renderer_clear_colour(&renderer, &(Colour){0.f, 0.f, 0.f, 1.f});
    renderer_draw_renderable(&renderer, &tri2);
    renderer_draw_renderable(&renderer, &tri);
    window_poll_events(window);
    window_swap_buffers(window);
    allocator_free_all(&frame_allocator);
  }

  window_close(window);
  allocator_free_all(&app_allocator);
  printf("Window Close");
}
