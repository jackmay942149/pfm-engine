#include "allocator.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Allocator
allocator_create(int initial_size, bool allow_expansion) {
  Allocator out = {};

  out.data = malloc(initial_size);
  assert(out.data != NULL);

  out.offset = 0;
  out.capacity = initial_size;
  out.allow_expansion = allow_expansion;

  return out;
}

Allocation
allocator_push(Allocator *allocator, int num_bytes) {
  assert(allocator != NULL);
  Allocation out = {};

  // Overflow allocator
  if (num_bytes + allocator->offset > allocator->capacity) {
    if (!allocator->allow_expansion) {
      out.successful = false;
      return out;
    }
    printf("Allocator allows expansion but expansion not defined");
    assert(false);
  }

  out.data = &allocator->data[allocator->offset];
  allocator->offset += num_bytes;
  out.bytes_allocated = num_bytes;
  out.successful = true;
  return out;
}

void
allocator_free_all(Allocator *allocator) {
  allocator->offset = 0;
}

