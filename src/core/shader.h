#ifndef SHADER_H
#define SHADER_H
#include "types.h"

typedef struct {
  uint id;
} Shader;

Shader
shader_register(const char *vertex_shader_src, const char *fragment_shader_src);
#endif
