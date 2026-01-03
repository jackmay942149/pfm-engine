#include <stdio.h>
#include <windows.h>

#include <gl/GL.h> // Depends on windows.h

#include "window.h"
#include "renderer.h"
#include "allocator.h"

#include "window.c"
#include "renderer.c"
#include "allocator.c"

int
main() {
  Allocator app_allocator = allocator_create(1000, true);
  Allocator frame_allocator = allocator_create(1000, false);

  Window *window = window_create(1920 / 2, 1080 / 2, "Window", &app_allocator);

  Renderer renderer = {
    .window = window
  };

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
