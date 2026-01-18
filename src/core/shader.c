#include "shader.h"

#include <stdio.h>
#include <assert.h>

#include "boolean.h"
#include "opengl-functions.h"

#define SHADER_ERROR_SIZE 512
Shader
shader_register(const char *vertex_shader_src, const char *fragment_shader_src) {
  u32 vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
  glCompileShader(vertex_shader);

  i32 success;
  char info_log[SHADER_ERROR_SIZE];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, SHADER_ERROR_SIZE, NULL, info_log);
    printf("%s", info_log);
    assert(false);
  }

  u32 fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, SHADER_ERROR_SIZE, NULL, info_log);
    printf("%s", info_log);
    assert(false);
  }

  u32 shader_program;
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, SHADER_ERROR_SIZE, NULL, info_log);
  }

  glUseProgram(shader_program);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return (Shader) {shader_program};
}
