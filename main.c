#include <stddef.h>
#include <stdio.h>

#include <windows.h>
#include <gl/GL.h>
#include <wingdi.h>

#include "window.h"
#include "renderer.h"
#include "allocator.h"

#include "window.c"
#include "renderer.c"
#include "allocator.c"


float vertices[] = {
  -.5f, -.5f, 0.f,
   .5f, -.5f, 0.f,
   0.f,  .5f, 0.f
};

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4

typedef ptrdiff_t GLsizeiptr;

typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
GL_GENBUFFERS glGenBuffers;
typedef void (*GL_BINDBUFFER) (GLenum, GLuint);
GL_BINDBUFFER glBindBuffer;
typedef void (*GL_BUFFERDATA) (GLenum target, GLsizeiptr size, const void *, GLenum);
GL_BUFFERDATA glBufferData;

void
load_gl_funcs() {
  glGenBuffers = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
  glBindBuffer = (GL_BINDBUFFER)wglGetProcAddress("glBindBuffer");
  glBufferData = (GL_BUFFERDATA)wglGetProcAddress("glBufferData");
}
 
void
setup_triangle() {
  load_gl_funcs();

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

int
main() {
  Allocator app_allocator = allocator_create(1000, true);
  Allocator frame_allocator = allocator_create(1000, false);

  Window *window = window_create(1920 / 2, 1080 / 2, "Window", &app_allocator);

  Renderer renderer = {
    .window = window
  };

  setup_triangle();

  while (!window_should_close(window)) {
    renderer_clear_colour(&renderer, &(Colour){0.f, 0.f, 0.f, 1.f});
    window_poll_events(window);
    window_swap_buffers(window);
    allocator_free_all(&frame_allocator);
  }

  window_close(window);
  allocator_free_all(&app_allocator);
  printf("Window Close");
}
