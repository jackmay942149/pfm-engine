#include "allocator.h"

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

    // Resize allocator (not ideal)
    out.expanded_allocator = true;
    char *old_data = allocator->data;
    allocator->data = malloc(allocator->capacity*2);
    assert(allocator->data != NULL);

    // Copy old array
    for (int i = 0; i < allocator->offset; i++) {
      allocator->data[i] = old_data[i];
    }
    allocator->capacity *= 2;
    free(old_data);
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

