#include <stdio.h>
#include <stdlib.h>

void internal_func() {
  printf("internal func location of code  : %p\n", (void*) internal_func);
  printf("internal func location of heap  : %p\n", (void*) malloc(1));
  int x = 3;
  printf("internal func location of stack : %p\n", (void*) &x);
}

int main() {
  printf("location of code  : %p\n", (void*) main);
  printf("location of heap  : %p\n", (void*) malloc(1));
  int x = 3;
  printf("location of stack : %p\n\n", (void*) &x);
  internal_func();
  return 0;
}
