
namespace memtools {

  // Align an address to aligment bytes
  void *alignAddressUp(void *originalPtr, size_t aligment);

  // Align an address from back of buffer to bytes alignment
  void *alignAddressDown(void *originalPtr, size_t alignment);

}
// EO namespace