
// Includes
#include "PoolBuffer.h"


namespace memtools {

  PoolBuffer::PoolBuffer(size_t bytes, size_t chunkBytes) : 
    memStart_(NULL),
    head_(NULL),
    size_(bytes)
  {
    memStart_ = (uint8_t*)::operator new(bytes);

    const uint32_t chunkCount = (bytes / chunkBytes) - 1;
    for (uint32_t chunkIndex = 0; chunkIndex < chunkCount; ++chunkIndex) {
      
      //union
      //{
      //  uint8_t *as_u8p;
      //  uint32_t *as_u32p;
      //};

      //// Write the address of the next pointer in the node
      //as_u8p = memStart_ + (chunkIndex * chunkBytes);
      //*as_u32p = (uint32_t)as_u8p + chunkBytes;

      uint8_t* currChunk = memStart_ + (chunkIndex * chunkBytes);
      *((uint8_t**)currChunk) = currChunk + chunkBytes;
    }
    

    /*union
    {
    uint8_t *as_u8p;
    uint32_t *as_u32p;
    };

    as_u8p = memStart_ + size_;
    *as_u32p = NULL;*/

    *((uint8_t**)&memStart_[chunkCount * chunkBytes]) = NULL; /* terminating NULL */
    
    head_ = memStart_;
  }

  PoolBuffer::PoolBuffer(void *ptr, size_t bytes, size_t chunkBytes) :
    memStart_(NULL),
    head_(NULL),
    size_(bytes)
  {
    memStart_ = (uint8_t *)ptr;

    const uint32_t chunkCount = (bytes / chunkBytes) - 1;
    for (uint32_t chunkIndex = 0; chunkIndex < chunkCount; ++chunkIndex) {

      //union
      //{
      //  uint8_t *as_u8p;
      //  uint32_t *as_u32p;
      //};

      //// Write the address of the next pointer in the node
      //as_u8p = memStart_ + (chunkIndex * chunkBytes);
      //*as_u32p = (uint32_t)as_u8p + chunkBytes;

      uint8_t* currChunk = memStart_ + (chunkIndex * chunkBytes);
      *((uint8_t**)currChunk) = currChunk + chunkBytes;
    }


    /*union
    {
    uint8_t *as_u8p;
    uint32_t *as_u32p;
    };

    as_u8p = memStart_ + size_;
    *as_u32p = NULL;*/

    *((uint8_t**)&memStart_[chunkCount * chunkBytes]) = NULL; /* terminating NULL */

    head_ = memStart_;
  }

  PoolBuffer::~PoolBuffer() {
    // Delete the allocated memory
    ::operator delete(memStart_);
  }

  void *PoolBuffer::allocate() {
    // If there isn't any memory left 
    if (!head_) {
      return NULL;
    }

    //union
    //{
    //  void *as_void;
    //  uint8_t *as_u8p;
    //  uint32_t *as_u32p;
    //};

    //// Access the first available chunk
    //as_u8p = head_;

    //// Move the head to the next one
    //head_ = (uint8_t *)(*as_u32p);


    uint8_t* currPtr = head_;
    head_ = (*((uint8_t**)(head_)));
    return currPtr;
  }

  void PoolBuffer::deallocate(void *ptr) {
    // If ptr is invalid
    if (!ptr)
      return;
    }

    *((uint8_t**)ptr) = head_;
    head_ = (uint8_t*)ptr;
    return;
  }

  void PoolBuffer::reset() {

  }

}