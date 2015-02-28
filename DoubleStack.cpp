#include "DoubleStack.h"

namespace memtools {

  DoubleStackBuffer::DoubleStackBuffer(size_t bytes) :
    memStart_(NULL),
    size_(bytes),
    leftOffset_(0),
    rightOffset_(0),
    kSizeOfAllocationOffset(4)
  {
    memStart_ = (uint8_t*)::operator new(bytes);
  }

  DoubleStackBuffer::DoubleStackBuffer(void *ptr, size_t bytes) :
    memStart_(NULL),
    size_(bytes),
    leftOffset_(0),
    rightOffset_(0),
    kSizeOfAllocationOffset(4)
  {
    memStart_ = (uint8_t *)ptr;
  }

  DoubleStackBuffer::~DoubleStackBuffer() {
    // Delete the allocated memory
    ::operator delete(memStart_);
  }

  void *DoubleStackBuffer::allocate(size_t bytes, size_t aligment, size_t offset, const uint32_t side) {
    // If the size of memory requested is zero
    if (!bytes) {
      return NULL;
    }

    // Increase the size of the allocation to account for storing of the offset
    bytes += kSizeOfAllocationOffset;
    offset += kSizeOfAllocationOffset;

    // Create a new pointer
    uint8_t *ptrCurrent = NULL;

    // If allocation is on left side
    if (side == kAllocationSideLeft) {
      // Allocate like in a normal stack buffer
      ptrCurrent = (uint8_t *)alignAddressUp(memStart_ + leftOffset_ + offset,
        aligment) - offset;

      // Calculate the new offset based on the alignment
      uint32_t newOffset = (ptrCurrent + bytes) - memStart_;

      // If the new offset does not exceed the buffer's size and does not
      // exceed into the area of the opposite side
      if ((newOffset <= size_) && 
          (newOffset < size_ - rightOffset_)) {
        union
        {
          void* as_void;
          uint8_t* as_u8;
          uint32_t* as_u32;
        };

        // Select the current offset
        as_u8 = ptrCurrent;

        // Store the offset previous to allocation in the first 4 bytes
        *as_u32 = leftOffset_;
        // ... then move forward to the user memory
        as_u8 += kSizeOfAllocationOffset;

        // Update the buffer's offset
        leftOffset_ = newOffset;

        return as_void;
      }
      else {
        return NULL;
      }
    }
    // If allocation is on right side
    else if (side == kAllocationSideRight) {
      // Allocate on right side
      ptrCurrent = (uint8_t *)alignAddressDown(memStart_ + size_ - rightOffset_ 
        - bytes + offset, aligment) - offset;

      // Calculate the new offset based on the alignment
      uint32_t newOffset = (memStart_ + size_) - ptrCurrent;

      // If the new offset does not exceed the buffer's size and does not
      // exceed into the area of the opposite side
      if ((newOffset <= size_) &&
        (size_ - newOffset > leftOffset_)) {
        union
        {
          void* as_void;
          uint8_t* as_u8;
          uint32_t* as_u32;
        };

        // Select the current offset
        as_u8 = ptrCurrent;

        // Store the offset previous to allocation in the first 4 bytes
        *as_u32 = rightOffset_;
        // ... then move forward to the user memory
        as_u8 += kSizeOfAllocationOffset;

        // Update the buffer's offset
        rightOffset_ = newOffset;

        return as_void;
      }
      else {
        return NULL;
      }

    }
  }

  void DoubleStackBuffer::deallocate(void *ptr, const uint32_t side) {
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
    if (side == kAllocationSideLeft) {
      leftOffset_ = newOffset;
    }
    else if (side == kAllocationSideRight) {
      rightOffset_ = newOffset;
    }

   
  }

  void DoubleStackBuffer::reset() {
    // Set the offset to zero
    leftOffset_ = 0;
    rightOffset_ = 0;

    #ifdef DEBUG
        memset(memStart_, 0xcd, size_);
    #endif // DEBUG
  }
}
// EO Namespace