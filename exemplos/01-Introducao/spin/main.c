#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void spin(char *text) {
  printf("%s\n", text);
  sleep(1);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s %s\n", argv[0], "<text>");
    exit(1);
  }

  for (;;) {
    spin(argv[1]);
  }

  return 0;
}
