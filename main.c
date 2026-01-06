#include <stdio.h>
#include <assert.h>

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
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82

typedef ptrdiff_t GLsizeiptr;
typedef char GLchar;

typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
GL_GENBUFFERS glGenBuffers;

typedef void (*GL_BINDBUFFER) (GLenum, GLuint);
GL_BINDBUFFER glBindBuffer;

typedef void (*GL_BUFFERDATA) (GLenum target, GLsizeiptr size, const void *, GLenum);
GL_BUFFERDATA glBufferData;

typedef GLuint (*GL_CREATESHADER) (GLenum shader_type);
GL_CREATESHADER glCreateShader;

typedef void (*GL_SHADERSOURCE) (GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
GL_SHADERSOURCE glShaderSource;

typedef void (*GL_COMPILESHADER) (GLuint shader);
GL_COMPILESHADER glCompileShader;

typedef void (*GL_GETSHADERIV) (GLuint shader, GLenum pname, GLint *params);
GL_GETSHADERIV glGetShaderiv;

typedef void (*GL_GETSHADERINFOLOG) (GLuint shader, GLsizei max_length, GLsizei *length, GLchar *info_log);
GL_GETSHADERINFOLOG glGetShaderInfoLog;

typedef GLuint (*GL_CREATEPROGRAM) (void);
GL_CREATEPROGRAM glCreateProgram;

typedef void (*GL_ATTACHSHADER) (GLuint program, GLuint shader);
GL_ATTACHSHADER glAttachShader;

typedef void (*GL_LINKPROGRAM) (GLuint program);
GL_LINKPROGRAM glLinkProgram;

typedef void (*GL_GETPROGRAMIV) (GLuint program, GLenum pname, GLint *params);
GL_GETPROGRAMIV glGetProgramiv;

typedef void (*GL_GETPROGRAMINFOLOG) (GLuint program, GLsizei max_length, GLsizei *length, GLchar *info_log);
GL_GETPROGRAMINFOLOG glGetProgramInfoLog;

typedef void (*GL_USEPROGRAM) (GLuint program);
GL_USEPROGRAM glUseProgram;

void
load_gl_funcs() {
  glGenBuffers = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
  glBindBuffer = (GL_BINDBUFFER)wglGetProcAddress("glBindBuffer");
  glBufferData = (GL_BUFFERDATA)wglGetProcAddress("glBufferData");
  glCreateShader = (GL_CREATESHADER)wglGetProcAddress("glCreateShader");
  glShaderSource = (GL_SHADERSOURCE)wglGetProcAddress("glShaderSource");
  glCompileShader = (GL_COMPILESHADER)wglGetProcAddress("glCompileShader");
  glGetShaderiv = (GL_GETSHADERIV)wglGetProcAddress("glGetShaderiv");
  glGetShaderInfoLog = (GL_GETSHADERINFOLOG)wglGetProcAddress("glGetShaderInfoLog");
  glCreateProgram = (GL_CREATEPROGRAM)wglGetProcAddress("glCreateProgram");
  glAttachShader = (GL_ATTACHSHADER)wglGetProcAddress("glAttachShader");
  glLinkProgram = (GL_LINKPROGRAM)wglGetProcAddress("glLinkProgram");
  glGetProgramiv = (GL_GETPROGRAMIV)wglGetProcAddress("glGetProgramiv");
  glGetProgramInfoLog = (GL_GETPROGRAMINFOLOG)wglGetProcAddress("glGetProgramInfoLog");
  glUseProgram = (GL_USEPROGRAM)wglGetProcAddress("glUseProgram");
}

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

void
setup_triangle() {
  load_gl_funcs();

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  unsigned int vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
  glCompileShader(vertex_shader);

  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    printf("%s", info_log);
    assert(false);
  }

  unsigned int fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    printf("%s", info_log);
    assert(false);
  }

  unsigned int shader_program;
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
  }

  glUseProgram(shader_program);
  // Delete program

}

int
main() {
  Allocator app_allocator = allocator_create(1000, false);
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
