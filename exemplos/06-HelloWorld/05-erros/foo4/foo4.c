// foo4.c
#include <stdio.h>
void f(void);

int x;

int main(void) {
  x = 0xdcc606;
  f();
  printf("0x%x\n", x);
  return 0;
}
