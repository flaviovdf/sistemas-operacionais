// foo5.c
#include <stdio.h>
void f(void);

int x = 0xdcc605;
int y = 0xdcc606;

int main(void) {
  int a = 1;
  double b = 1.0;
  printf("tamanho de int=%lu; tamanho de double=%lu\n", sizeof(a), sizeof(b));
  f();
  printf("x=0x%x; y=0x%x\n", x, y);
}
