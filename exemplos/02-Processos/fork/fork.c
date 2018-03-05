#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

  int pidChild;
  if ((pidChild = fork()) == -1) {
    perror("Bad Fork!");
    exit(1);
  }

  if (pidChild == 0) { //Sou o processo filho
      //Você também pode fazer execvp(argv[0], argv);
      char *argv[] = {"python", NULL};
      if (execvp("python", argv) < 0) {
        perror("Bad Exec");
        exit(1);
      }
  } else { //processo pai
      //Esperar o processo filho finalizar
      int status;
      waitpid(pidChild, &status, 0);
      printf("Filho terminou com status %d\n", status);
    }
}
