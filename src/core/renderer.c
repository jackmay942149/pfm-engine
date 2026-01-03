#include "renderer.h"

#include <gl/GL.h>
#include <assert.h>

void
renderer_clear_colour(Renderer *renderer, Colour* colour) {
  glClearColor(colour->r, colour->g, colour->b, colour->a);
  glClear(GL_COLOR_BUFFER_BIT);
  return;
}
  

