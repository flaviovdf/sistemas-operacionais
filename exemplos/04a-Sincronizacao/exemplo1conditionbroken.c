#include <stdio.h>
#include <assert.h>
#include <pthread.h>

typedef struct {
  char *c;
  pthread_mutex_t *mutex;
  pthread_cond_t *cond;
} ab_arguments_t;

void *mythread(void* arguments) {
  ab_arguments_t *args = (ab_arguments_t*)arguments;
  pthread_mutex_lock(args->mutex);
  if (args->c[0] == 'B') {
    pthread_cond_wait(args->cond, args->mutex);
  }
  printf("%s\n", args->c);
  pthread_cond_signal(args->cond);
  pthread_mutex_unlock(args->mutex);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2;
  int rc;
  printf("main: begin\n");

  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  pthread_cond_t cond;
  pthread_cond_init(&cond, NULL);

  ab_arguments_t args_a = {.c = "A", .mutex = &mutex, .cond = &cond};
  rc = pthread_create(&p1, NULL, mythread, &args_a);
  assert(rc == 0);

  ab_arguments_t args_b = {.c = "B", .mutex = &mutex, .cond = &cond};
  rc = pthread_create(&p2, NULL, mythread, &args_b);
  assert(rc == 0);

  // join waits for the threads to finish
  rc = pthread_join(p1, NULL); assert(rc == 0);
  rc = pthread_join(p2, NULL); assert(rc == 0);
  printf("main: end\n");
  return 0;
}
