#ifndef _DOUBLESTACKBUFFER_H
#define _DOUBLESTACKBUFFER_H

#include <cstdint>
#include <stdlib.h>
#include "alignment.h"

namespace memtools {

  // Sides of buffer, used in allocate()
  const uint32_t kAllocationSideLeft = 0;
  const uint32_t kAllocationSideRight = 1;

  class DoubleStackBuffer
  {
  public:
    // Ctor
    explicit DoubleStackBuffer(size_t bytes);

    // Ctor on pre-allocated memory
    explicit DoubleStackBuffer(void *ptr, size_t bytes);

    // Dtor
    ~DoubleStackBuffer();

    // Allocate memory on a given side of the stack buffer
    void *allocate(size_t bytes, size_t aligment, size_t offset, const uint32_t side);

    // Deallocate memory
    void deallocate(void *ptr, const uint32_t side);

    // Reset the whole buffer
    void reset();

  private:
    // Start address of the buffer
    uint8_t *memStart_;

    // Size of the buffer in bytes
    uint32_t size_;

    // Current size of the buffer on the left side
    uint32_t leftOffset_;

    // Current size of the buffer on the right side
    uint32_t rightOffset_;

    // Bytes used to save the allocation offset
    const uint32_t kSizeOfAllocationOffset;
  };
  // EO Class

}
// EO Namespace

#endif // !_STACKBUFFER_H



