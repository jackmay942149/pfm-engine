#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

#include "boolean.h"
#include "allocator.h"

typedef HWND Window_Handle_Win;
typedef WNDCLASSA Window_Class_Info_Win;
typedef DWORD Window_Style_Win;
typedef MSG Message_Win;
typedef WPARAM Message_Param_U64ptr_Win;
typedef LPARAM Message_Param_I64ptr_Win;
typedef LRESULT Result_I64ptr_Win;
typedef HDC Device_Context_Win;

typedef struct {
  Window_Handle_Win handle;
  Device_Context_Win context;
  Bool should_close;

} Window;

LRESULT CALLBACK
main_window_callback(Window_Handle_Win hwnd, UINT uint, WPARAM wparam, LPARAM lparam);
  
Window*
window_create(int size_x, int size_y, const char *title, Allocator *allocator);

void
window_poll_events(Window *window);

Bool
window_should_close(Window *window);

void
window_close(Window *window);

void
window_swap_buffers(Window *window);

#endif
