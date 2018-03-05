// foo3.c
#include <stdio.h>
void f(void);

int x = 0xdcc606;
int main(void) {
  f();
  printf("0x%x\n", x);
  return 0;
}
