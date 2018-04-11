#include "types.h"
#include "user.h"
#include "date.h"

#define TRUE  1
#define FALSE 0
#define N     10

int stdout = 1;
int stderr = 2;

const int GLOBAL1_RO = 0xdcc605;
int GLOBAL2_RW = 0xdcc606;


// testa o fork normal. garante que não quebramos nada
// N forks e waits consecutivos. existe um limite de 64
// processos no xv6, então temos que garantir que N <= 64
int caso1fork(void) {
  int n;
  int pid;

  printf(stdout, "[--Caso 1.1] Testando %d chamadas fork\n", N);

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0) {
      printf(stdout, "[--Caso 1.1 - ERROR] Fork %d falhou!\n", n);
      return FALSE;
    }
    if(pid == 0)
      exit();   // fecha filho
    else
      if (wait() < 0) return FALSE;
  }
  return TRUE;
}


// mesmo do caso 1 só que com o novo forkcow
// testa o fork cow. garante que não quebramos nada
// N forks e waits consecutivos. existe um limite de 64
// processos no xv6, então temos que garantir que N <= 64
int caso2forkcow(void) {
  int n;
  int pid;

  printf(stdout, "[--Caso 2.1] Testando %d chamadas forkcow\n", N);

  for(n=0; n<N; n++){
    pid = forkcow();
    if(pid < 0) {
      printf(stdout, "[--Caso 2.1 - ERROR] Fork %d falhou!\n", n);
      return FALSE;
    }
    if(pid == 0)
      exit();   // fecha filho
    else
      if (wait() < 0) return FALSE;
  }
  return TRUE;
}


// testa que o processo parent e child tem o mesmo num de pgs
// embora durante o forkcow algumas páginas são escrita, os
// 2 processos não crescem nem em pilha nem em heap.
// pipes, wait e exit para comunicação e sync
int caso3numpgs(void) {
  int fd[2];
  pipe(fd);
  int np = num_pages();
  char answer[20];     // com certeza menos de 99999999999999999999 pgs
  int pid = forkcow();
  if (pid == 0) { // child manda número de páginas de da exit
    printf(stdout, "[--Caso 3.1] Child write num_pages %d\n", num_pages());
    close(fd[0]);
    printf(fd[1], "%d\0", num_pages());
    printf(stdout, "[--Caso 3.2] Child indo embora\n");
    close(fd[1]);
    exit();
  } else { // parent espera filho acabar e lê o fd
    close(fd[1]);
    wait();
    printf(stdout, "[--Caso 3.3] Parent lendo num_pages\n");
    read(fd[0], answer, 20);
    printf(stdout, "[--Caso 3.4] Parent leu %d == %d\n", np, atoi(answer));
    close(fd[0]);
    return atoi(answer) == np;
  }
  return TRUE;
}


// testa que o processo parent e child tem o mesmo addr real
// para uma constante. usamos a GLOBAL1_RO
// pipes, wait e exit para comunicação e sync
int caso4mesmoaddr(void) {
  int fd[2];
  pipe(fd);
  char answer[20];
  int pid = forkcow();
  if (pid == 0) { // child manda addr de GLOBAL1_RO
    int addr = (int)virt2real((char*)&GLOBAL1_RO);
    if (addr < 0) addr = -addr; // atoi falha quando <0, nao sei pq
    printf(stdout, "[--Caso 4.1] Child write %d\n", addr);
    close(fd[0]);
    printf(fd[1], "%d\0", addr);
    printf(stdout, "[--Caso 4.2] Child indo embora\n");
    close(fd[1]);
    exit();
  } else { // parent espera filho acabar e lê o fd
    int addr = (int)virt2real((char*)&GLOBAL1_RO);
    if (addr < 0) addr = -addr; // atoi falha quando <0, nao sei pq
    close(fd[1]);
    wait();
    printf(stdout, "[--Caso 4.3] Parent lendo addr\n");
    read(fd[0], answer, 20);
    printf(stdout, "[--Caso 4.4] Parent leu %d == %d\n",
           addr,
           atoi(answer));
    close(fd[0]);
    return addr == atoi(answer);
  }
  return TRUE;
}


// testa que o processo parent e child tem o mesmo addr real
// para uma GLOBAL. usamos a GLOBAL1_RW
// pipes, wait e exit para comunicação e sync
int caso5mesmoaddr(void) {
  int fd[2];
  pipe(fd);
  char answer[20];
  int pid = forkcow();
  if (pid == 0) { // child manda addr de GLOBAL1_RO
    int addr = (int)virt2real((char*)&GLOBAL2_RW);
    if (addr < 0) addr = -addr; // atoi falha quando <0, nao sei pq
    printf(stdout, "[--Caso 5.1] Child write %d\n", addr);
    close(fd[0]);
    printf(fd[1], "%d\0", addr);
    printf(stdout, "[--Caso 5.2] Child indo embora\n");
    close(fd[1]);
    exit();
  } else { // parent espera filho acabar e lê o fd
    int addr = (int)virt2real((char*)&GLOBAL2_RW);
    if (addr < 0) addr = -addr; // atoi falha quando <0, nao sei pq
    close(fd[1]);
    wait();
    printf(stdout, "[--Caso 5.3] Parent lendo addr\n");
    read(fd[0], answer, 20);
    printf(stdout, "[--Caso 5.4] Parent leu %d == %d\n",
           addr,
           atoi(answer));
    close(fd[0]);
    return addr == atoi(answer);
  }
  return TRUE;
}


// testa que o processo parent e child tem o addr diferentes
// após um write em uma GLOBAL. usamos a GLOBAL1_RW
// pipes, wait e exit para comunicação e sync
int caso6cow(void) {
  int fd[2];
  pipe(fd);
  char answer[20];
  int pid = forkcow();
  if (pid == 0) { // child manda addr de GLOBAL2_RW
    GLOBAL2_RW--;
    int addr = (int)virt2real((char*)&GLOBAL2_RW);
    if (addr < 0) addr = -addr; // atoi falha quando <0, nao sei pq
    printf(stdout, "[--Caso 6.1] Child write %d\n", addr);
    close(fd[0]);
    printf(fd[1], "%d\0", addr);
    printf(stdout, "[--Caso 6.2] Child indo embora\n");
    close(fd[1]);
    exit();
  } else { // parent espera filho acabar e lê o fd
    int addr = (int)virt2real((char*)&GLOBAL2_RW);
    if (addr < 0) addr = -addr; // atoi falha quando <0, nao sei pq
    close(fd[1]);
    wait();
    printf(stdout, "[--Caso 6.3] Parent lendo addr\n");
    read(fd[0], answer, 20);
    printf(stdout, "[--Caso 6.4] Parent leu %d != %d\n",
           addr,
           atoi(answer));
    close(fd[0]);
    return addr != atoi(answer);
  }
  return TRUE;
}

// testa a chamada date
int get_date(struct rtcdate *r) {
  if (date(r)) {
    printf(stderr, "[ERROR] Erro na chamada de sistema date\n");
    return FALSE;
  }
  return TRUE;
}


void print_date(struct rtcdate *r) {
  printf(stdout, "%d/%d/%d %d:%d:%d\n", r->day,
                                        r->month,
                                        r->year,
                                        r->hour,
                                        r->minute,
                                        r->second);
}


int main(int argc, char *argv[]) {
  struct rtcdate r;
  int call_ok = 1;

  printf(stdout, "[Caso 0] Testando o date\n");
  call_ok = get_date(&r);
  if (call_ok == FALSE) {
    printf(stdout, "[Caso 0 - ERROR] Falhou!\n");
    exit();
  }
  print_date(&r);
  printf(stdout, "[Caso 0] OK\n");

  get_date(&r);
  print_date(&r);
  printf(stdout, "[Caso 1] Testando o fork\n");
  call_ok = caso1fork();
  if (call_ok == FALSE) {
    printf(stdout, "[Caso 1 - ERROR] Falhou!\n");
    exit();
  }
  printf(stdout, "[Caso 1] OK\n");

  get_date(&r);
  print_date(&r);
  printf(stdout, "[Caso 2] Testando o forkcow\n");
  call_ok = caso2forkcow();
  if (call_ok == FALSE) {
    printf(stdout, "[Caso 2 - ERROR] Falhou!\n");
    exit();
  }
  printf(stdout, "[Caso 2] OK\n");

  get_date(&r);
  print_date(&r);
  printf(stdout, "[Caso 3] Testando se o número de páginas é igual\n");
  call_ok = caso3numpgs();
  if (call_ok == FALSE) {
    printf(stdout, "[Caso 3 - ERROR] Falhou!\n");
    exit();
  }
  printf(stdout, "[Caso 3] OK\n");

  get_date(&r);
  print_date(&r);
  printf(stdout, "[Caso 4] Testando se o endereço de uma constante é =\n");
  call_ok = caso4mesmoaddr();
  if (call_ok == FALSE) {
    printf(stdout, "[Caso 4 - ERROR] Falhou!\n");
    exit();
  }
  printf(stdout, "[Caso 4] OK\n");

  get_date(&r);
  print_date(&r);
  printf(stdout, "[Caso 5] Testando se o endereço de uma global é =\n");
  call_ok = caso5mesmoaddr();
  if (call_ok == FALSE) {
    printf(stdout, "[Caso 5 - ERROR] Falhou!\n");
    exit();
  }
  printf(stdout, "[Caso 5] OK\n");

  get_date(&r);
  print_date(&r);
  printf(stdout, "[Caso 6] Testando o COW\n");
  call_ok = caso6cow();
  if (call_ok == FALSE) {
    printf(stdout, "[Caso 6 - ERROR] Falhou!\n");
    exit();
  }
  printf(stdout, "[Caso 6] OK\n");
  printf(stdout, "\n");
  printf(stdout, "         (__)        \n");
  printf(stdout, "         (oo)        \n");
  printf(stdout, "   /------\\/        \n");
  printf(stdout, "  / |    ||          \n");
  printf(stdout, " *  /\\---/\\        \n");
  printf(stdout, "    ~~   ~~          \n");
  printf(stdout, "....\"Congratulations! You have mooed!\"...\n");
  printf(stdout, "\n");
  printf(stdout, "[0xDCC605 - COW] ALL OK!!!\n");
  exit();
}
