#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Environment variables de uinstd.h. Não precisamos utilizar no
//exemplo abaixo. Sinalizando onde achar as mesmas.
extern char **environ;

#define READ_END 0
#define WRITE_END 1

int main(void) {
  // Armazena o pid=0 no processo filho. -1 quando temos um erro
  int pidChild;

  // Descritores de arquivo do PIPE. Um para cada "lado", in/read (0) e
  // out/write (1)
  int fd[2];

  pipe(fd); // Criei o Pipe. O mesmo será "clonado" no fork

  if ((pidChild = fork()) == -1) {
    perror("Bad Fork!");
    exit(1);
  }

  if (pidChild == 0) { //Sou o processo filho
    //clona o read do pipe do stdin para o processo do execvp
    dup2(fd[READ_END], STDIN_FILENO);

    //Já fiz o clone do READ_END para o STDIN.
    //Próximo processo apenas lê o mesmo
    close(fd[WRITE_END]);
    close(fd[READ_END]);

    //O primeiro argumento de um programa é o nome do mesmo
    char *argv[] = {"python", "meu_script.py", NULL};

    //Você também pode fazer execvp(argv[0], argv);
    if (execvp("python", argv) < 0) {
      perror("Bad Exec");
      exit(1);
    }
  } else { //processo pai
    close(fd[READ_END]); //o pai não lê de canto algum

    //Vamos pegar o arquivo para o descritor do PIPE
    FILE* fp = fdopen(fd[WRITE_END], "w");

    fprintf(fp, "%s\n", "Minha terra tem palmeiras");
    fprintf(fp, "%s\n", "Onde canta o sabiá");
    fprintf(fp, "%s\n", "<3 SOs");

    //Lembre-se de fechar os arquivos.
    //Espere o filho terminar depois apenas
    fclose(fp);
    close(fd[WRITE_END]);

    //Esperar o processo filho finalizar
    int status;
    waitpid(pidChild, &status, 0);

    printf("Filho terminou com status %d\n", status);
  }
}
