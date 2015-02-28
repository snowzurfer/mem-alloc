#include "StackBuffer.h"

namespace memtools {

  StackBuffer::StackBuffer(size_t bytes) :
    memStart_(NULL),
    size_(bytes),
    offset_(0),
    kSizeOfAllocationOffset(4)
  {
    memStart_ = (uint8_t*)::operator new(bytes);
  }

  StackBuffer::StackBuffer(void *ptr, size_t bytes) :
    memStart_(NULL),
    size_(bytes),
    offset_(0),
    kSizeOfAllocationOffset(4)
  {
    memStart_ = (uint8_t *)ptr;
  }

  StackBuffer::~StackBuffer() {
    // Delete the allocated memory
    ::operator delete(memStart_);
  }

  void *StackBuffer::allocate(size_t bytes, size_t aligment, size_t offset) {
    // If the size of memory requested is zero
    if (!bytes) {
      return NULL;
    }

    // Increase the size of the allocation to account for storing of offset
    bytes += kSizeOfAllocationOffset;
    offset += kSizeOfAllocationOffset;

    // Create a new aligned pointer
    uint8_t *ptrCurrent = (uint8_t *)alignAddressUp(memStart_ + offset_ + offset,
                          aligment) - offset;

    // Calculate the new offset based on the alignment
    uint32_t newOffset = (ptrCurrent + bytes) - memStart_;

    // If the new offset does not exceed the buffer's size
    if (newOffset <= size_) {
      union
      {
        void* as_void;
        uint8_t* as_u8;
        uint32_t* as_u32;
      };

      // Select the current offset
      as_u8 = ptrCurrent;
      
      // Store the offset previous to allocation in the first 4 bytes
      *as_u32 = offset_;
      // ... then move forward to the user memory
      as_u8 += kSizeOfAllocationOffset;

      // Update the buffer's offset
      offset_ = newOffset;

      return as_void;
    }
  }

  void StackBuffer::deallocate(void *ptr) {
    union
    {
      void* as_void;
      uint8_t* as_u8;
      uint32_t* as_u32;
    };

    // Select the memory location pointed by ptr
    as_void = ptr;

    // Read the offset previous to this allocation
    as_u8 -= kSizeOfAllocationOffset;
    uint32_t newOffset = *as_u32;

    // Update the buffer's offset
    offset_ = newOffset;
  }

  void StackBuffer::reset() {
    // Set the offset to zero
    offset_ = 0;

    #ifdef DEBUG
        memset(memStart_, 0xcd, size_);
    #endif // DEBUG
  }
}
// EO Namespace