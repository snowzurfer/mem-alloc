#ifndef _STACKBUFFER_H
#define _STACKBUFFER_H

#include <cstdint>
#include <stdlib.h>
#include "alignment.h"

namespace memtools {

  

  class StackBuffer
  {
  public:
    // Ctor
    explicit StackBuffer(size_t bytes);
   
    // Ctor on pre-allocated memory
    explicit StackBuffer(void *ptr, size_t bytes);

    // Dtor
    ~StackBuffer();

    // Allocate memory
    void *allocate(size_t bytes, size_t aligment, size_t offset);

    // Deallocate memory
    void deallocate(void *ptr);

    // Reset the whole buffer
    void reset();

  private:
    // Start address of the buffer
    uint8_t *memStart_;

    // Size of the buffer in bytes
    uint32_t size_;

    // Current size of the buffer
    uint32_t offset_;

    // Bytes used to save the allocation offset
    const uint32_t kSizeOfAllocationOffset;
  };
  // EO Class

}
// EO Namespace

#endif // !_STACKBUFFER_H



