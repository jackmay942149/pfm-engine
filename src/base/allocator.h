#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "boolean.h"

typedef struct {
  char* data;  
  int   bytes_allocated;
  bool  successful;
  bool  expanded_allocator;
} Allocation;

typedef struct {
  char* data;
  int   offset;
  int   capacity;
  Bool  allow_expansion;
} Allocator;

Allocator
allocator_create(int initial_size, bool allow_expansion);

Allocation
allocator_push(Allocator *allocator, int num_bytes);

void
allocator_free_all(Allocator *allocator);

#endif
