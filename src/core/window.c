#include <assert.h>
#include <windows.h>
#include <stdio.h>

#include <gl/GL.h>
#include <wingdi.h>
#include <winuser.h>

#include "types.h"
#include "window.h"
#include "allocator.h"

Result_I64ptr_Win CALLBACK
main_window_callback(Window_Handle_Win handle, uint message, Message_Param_U64ptr_Win param_1, Message_Param_I64ptr_Win param_2) {
  Window* window = GetProp(handle, ("WindowStruct"));
  switch (message) {
    case WM_CREATE: return 0;
    case WM_PAINT: return 0;
    case WM_CLOSE:  {
      window->should_close = true;
      return 0;
    }
    case WM_SIZE: {
      uint width = LOWORD(param_2);
      uint height = HIWORD(param_2);
      glViewport(0, 0, width, height);
      return 0;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
    default: return DefWindowProc(handle, message, param_1, param_2);
  }
  return 0;
};

Window*
window_create(int size_x, int size_y, const char *title, Allocator *allocator) {
  Window* window;
  if (allocator == NULL) {
    window = malloc(sizeof(Window));
  } else {
    Allocation allocation = allocator_push(allocator, sizeof(Window));
    assert(allocation.successful);
    window = (Window*) allocation.data;
  }
  Window_Style_Win window_style = WS_OVERLAPPEDWINDOW;
  int window_pos_x = 0;
  int window_pos_y = 0;

  // Register class on first window creation TODO(Jack): Pull this out with error handling
  static int registered_class = 0;
  if (registered_class == 0) {
    Window_Class_Info_Win window_class = {.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW, .lpfnWndProc = main_window_callback, .hInstance = NULL, .hIcon = LoadIcon(NULL, IDI_APPLICATION), .hCursor = LoadCursor(NULL, IDC_ARROW), .hbrBackground = GetStockObject(BLACK_BRUSH), .lpszMenuName = "MainMenu", .lpszClassName = "MainWClass"};

    int registered = RegisterClass(&window_class);
    if (!registered) {
      return NULL; 
    }
    registered_class = registered;
  }

  Window_Handle_Win window_handle = CreateWindow("MainWClass", title, window_style, window_pos_x, window_pos_y, size_x, size_y, NULL, NULL, NULL, NULL);
  if (window_handle == NULL) {
    printf("Failed to create window");
    return NULL;
  }
  window->handle = window_handle;

  // Setup Opengl
  PIXELFORMATDESCRIPTOR pfd = {
    .nSize = sizeof(PIXELFORMATDESCRIPTOR),
    .nVersion = 1,
    .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    .iPixelType = PFD_TYPE_RGBA,
    .cColorBits = 32,
    .cDepthBits = 24,
    .cStencilBits = 8,
    .iLayerType = PFD_MAIN_PLANE,
  };

  window->context = GetDC(window->handle);
  int pixel_format = ChoosePixelFormat(window->context, &pfd);
  BOOL err = SetPixelFormat(window->context, pixel_format, &pfd);
  assert(err != FALSE);
  HGLRC hglrc = wglCreateContext(window->context);
  err = wglMakeCurrent(window->context, hglrc);
  assert(err != FALSE);
 
  window->should_close = false;
  
  SetProp(window_handle, "WindowStruct", window);
  ShowWindow(window_handle, 1);
  UpdateWindow(window_handle);
  return window;
}

void window_poll_events(const Window* window) {
  int got_message;
  Message_Win message;
  while (PeekMessage(&message, window->handle, 0, 0, PM_REMOVE) != 0) {
    if (message.message == WM_QUIT) {
      break;
    } else {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    if (message.message == WM_PAINT) {
      break;
    }
  }
}

Bool
window_should_close(const Window* window) {
  return window->should_close;
}

void
window_close(const Window* window) {
  DestroyWindow(window->handle);
  return;
}

void
window_swap_buffers(const Window* window) {
  SwapBuffers(window->context);
  return;
}
