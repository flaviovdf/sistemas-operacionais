// bar3.c
#include<stdio.h>
int x;
void f(void) {
  printf("dentro de f() 0x%x\n", x);
  x--;
}
