#include <windows.h>
#include <gl/GL.h> // Requires windows.h

#include "opengl-enums.h"
#include "opengl-types.h"

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

typedef void (*GL_DELETESHADER) (GLuint shader);
GL_DELETESHADER glDeleteShader;

typedef void (*GL_VERTEXATTRIBPOINTER) (GLuint index, GLint size, GLenum type, GLboolean normalised, GLsizei stride, const void *pointer);
GL_VERTEXATTRIBPOINTER glVertexAttribPointer;

typedef void (*GL_ENABLEVERTEXATTRIBARRAY) (GLuint index);
GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;

typedef void (*GL_GENVERTEXARRAYS) (GLsizei n, GLuint *arrays);
GL_GENVERTEXARRAYS glGenVertexArrays;

typedef void (*GL_BINDVERTEXARRAY) (GLuint array);
GL_BINDVERTEXARRAY glBindVertexArray;
