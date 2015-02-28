// Includes
#include "alignment.h"
#include <cstdint>

namespace memtools {

  void *alignAddressUp(void *originalPtr, size_t alignment) {
    // Align the pointer
    void *ptr = (void *)(((uintptr_t)originalPtr + alignment - 1) 
                            & (~(alignment - 1)));

    return ptr;

  }

  void *alignAddressDown(void *originalPtr, size_t alignment) {
    // Align the pointer
    void *ptr = (void *)(((uintptr_t)originalPtr - alignment - 1)
      & (~(alignment - 1)));

    return ptr;

  }

}
// EO Namespace