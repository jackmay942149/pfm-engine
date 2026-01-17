#include "opengl-functions.h"

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
  glDeleteShader = (GL_DELETESHADER)wglGetProcAddress("glDeleteShader");
  glVertexAttribPointer = (GL_VERTEXATTRIBPOINTER)wglGetProcAddress("glVertexAttribPointer");
  glEnableVertexAttribArray = (GL_ENABLEVERTEXATTRIBARRAY)wglGetProcAddress("glEnableVertexAttribArray");
  glGenVertexArrays = (GL_GENVERTEXARRAYS)wglGetProcAddress("glGenVertexArrays");
  glBindVertexArray = (GL_BINDVERTEXARRAY)wglGetProcAddress("glBindVertexArray");
  glGetUniformLocation = (GL_GETUNIFORMLOCATION)wglGetProcAddress("glGetUniformLocation");
  glUniform1f = (GL_UNIFORM1F)wglGetProcAddress("glUniform1f");
  glUniform2f = (GL_UNIFORM2F)wglGetProcAddress("glUniform2f");
  glUniform1i = (GL_UNIFORM1I)wglGetProcAddress("glUniform1i");
  glGenerateMipmap = (GL_GENERATEMIPMAP)wglGetProcAddress("glGenerateMipmap");
  glActiveTexture = (GL_ACTIVETEXTURE)wglGetProcAddress("glActiveTexture");
}
