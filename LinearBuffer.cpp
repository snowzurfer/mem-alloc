#include "LinearBuffer.h"


namespace memtools {

  LinearBuffer::LinearBuffer(size_t bytes) :
    memStart_(NULL),
    size_(bytes),
    offset_(0) 
  {
    memStart_ = (uint8_t*)::operator new(bytes);
  }

  LinearBuffer::LinearBuffer(void *ptr, size_t bytes) :
    memStart_(NULL),
    size_(bytes),
    offset_(0) 
  {
    memStart_ = (uint8_t *)ptr;
  }

  void *LinearBuffer::allocate(size_t size) {
    // If the size of memory requested is zero
    if (!size) {
      return NULL;
    }

    // Calculate the new offset
    uint32_t newOffset = offset_ + size;
    
    // If the new offset does not exceed the buffer's size
    if (newOffset <= size_) {
      // Create a pointer to the current offset memory address
      void *ptr = memStart_ + offset_;

      // Increment the buffer's offset
      offset_ = newOffset;

      return ptr;
    }

    // Else if the buffer has run out of memory
    return NULL;
  }

  void LinearBuffer::reset() {
    // Set the offset to zero
    offset_ = 0;

    // If in DEBUG mode, fill memory with garbage to check for dangling pointers
    #ifdef DEBUG
        memset(memStart_, 0xcd, size_);
    #endif // DEBUG

  }

  LinearBuffer::~LinearBuffer() {
    // Delete the allocated memory
    ::operator delete(memStart_);
  }

}
// EO Namespace