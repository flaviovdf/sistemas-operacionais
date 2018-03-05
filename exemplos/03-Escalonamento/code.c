#include <stdio.h>
#include <time.h>
#include <unistd.h>

void minhaFuncao() {
  //Faz algo bem complicado aqui!!
  sleep(20);
  //Fim!
}

int main () {
  clock_t inicio;
  clock_t fim;

  inicio = clock();
  minhaFuncao();
  fim = clock();
  double execTime = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("A função minhaFuncao executou em %f segundos\n", execTime);

  return 0;
}
