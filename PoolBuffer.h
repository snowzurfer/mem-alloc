#ifndef _POOL_BUFFER_H
#define _POOL_BUFFER_H

//////////////////////////////////////////////////////////////////////////
// Current implementation of Pool Buffer uses code by Steven Tovey.
// http://www.spuify.co.uk/?p=454
// I'm in the process of writing my own version. Stay tuned!
//////////////////////////////////////////////////////////////////////////

// Includes
#include <cstdint>
#include <stdlib.h>
#include "alignment.h"

namespace memtools {

  class PoolBuffer
  {
  public:
    // Ctor
    explicit PoolBuffer(size_t bytes, size_t chunkBytes);

    // Ctor on pre-allocated memory
    explicit PoolBuffer(void *ptr, size_t bytes, size_t chunkBytes);

    // Dtor
    ~PoolBuffer();

    // Allocate memory
    void *allocate();

    // Deallocate memory
    void deallocate(void *ptr);

    // Reset the whole buffer
    void reset();

  private:
    // Start address of the buffer
    uint8_t *memStart_;

    // Pointer to first available memory chunk
    uint8_t *head_;

    // Size of the buffer in bytes
    uint32_t size_;

  };

}

#endif