#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void
signal_callback_handler(int signum)
{
  printf("SIG %d\n",signum);
  exit(signum);
}

int
main()
{
  //SIGHUP tem valor 1: kill -1 PID
  signal(SIGHUP, signal_callback_handler);

  //SIGINT tem valor 2: kill -2 PID
  signal(SIGINT, signal_callback_handler);

  while(1)
  {
    sleep(1);
  }
  return EXIT_SUCCESS;
}
