
#include <iostream>
#include <stdint.h>
#include "LinearBuffer.h"
#include "StackBuffer.h"
#include "DoubleStack.h"
#include "PoolBuffer.h"
using std::iostream;

class MemoryTestClass
{
public:
  MemoryTestClass(uint8_t A, uint8_t B);

  // Dtor
  ~MemoryTestClass() {
    int something = 0;
  }

  uint8_t a;
  uint8_t b;
};

MemoryTestClass::MemoryTestClass(uint8_t A, uint8_t B) :
  a(A), b(B)
  {

}



int main()
{
  memtools::LinearBuffer linearBuffer(32);
  memtools::StackBuffer stackBuffer(32);
  memtools::DoubleStackBuffer doubleStackbuffer(32);
  memtools::PoolBuffer poolBuffer(128, sizeof(MemoryTestClass));

  MemoryTestClass *testPtr = new (linearBuffer.allocate(sizeof(MemoryTestClass))) MemoryTestClass(10, 20);
  
  MemoryTestClass *testPtrA = new (stackBuffer.allocate(sizeof(MemoryTestClass), 4, 0)) MemoryTestClass(30, 40);
  MemoryTestClass *testPtrB = new (stackBuffer.allocate(sizeof(MemoryTestClass), 16, 0)) MemoryTestClass(31, 41);

  MemoryTestClass *testPtrC = new (doubleStackbuffer.allocate(sizeof(MemoryTestClass), 4, 0, memtools::kAllocationSideRight)) MemoryTestClass(32, 42);

  std::cout << testPtrC->a << " " << testPtrC->b << std::endl;

  MemoryTestClass *testPtrD = new (doubleStackbuffer.allocate(sizeof(MemoryTestClass), 4, 0, memtools::kAllocationSideRight)) MemoryTestClass(32, 42);

  std::cout << testPtrC->a << " " << testPtrC->b << std::endl;
  std::cout << testPtrD->a << " " << testPtrD->b << std::endl;

  MemoryTestClass *testPtrE = new (poolBuffer.allocate()) MemoryTestClass(32, 42);
  MemoryTestClass *testPtrF = new (poolBuffer.allocate()) MemoryTestClass(56, 3);

  std::cout << testPtrE->a << " " << testPtrE->b << std::endl;
  std::cout << testPtrF->a << " " << testPtrF->b << std::endl;

  testPtrB->~MemoryTestClass();
  stackBuffer.deallocate(testPtrB);

  
 
	return 0;
}