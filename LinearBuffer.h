#ifndef _LINEAR_BUFFER
#define _LINEAR_BUFFER

#include <cstdint>
#include <stdlib.h>


namespace memtools {

  class LinearBuffer
  {
  public:
    // Ctor
    explicit LinearBuffer(size_t bytes);

    // Ctor on pre-allocated memory
    explicit LinearBuffer(void *, size_t bytes);

    // Dtor
    ~LinearBuffer();

    // Allocate memory
    void *allocate(size_t bytes);

    // Reset the whole buffer
    void reset();

  private:
    // Start address of the buffer
    uint8_t *memStart_;

    // Size of the buffer in bytes
    uint32_t size_;

    // Current size of the buffer
    uint32_t offset_;
  };
  // EO Class

}
// EO Namespace

#endif
