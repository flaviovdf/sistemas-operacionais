#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
  pthread_mutex_t *mutex;
  pthread_cond_t *cond_empty;
  pthread_cond_t *cond_max;
  int max;
  int n;
  int *buffer;
} args_t;

void *producer_f(void *argsv) {
  args_t *args = (args_t*) argsv;
  do {
    pthread_mutex_lock(args->mutex);
    while (args->n == args->max) {
      pthread_cond_wait(args->cond_max, args->mutex);
    }

    args->buffer[args->n] = (rand() % 20) + 1;
    printf("Produced: [%d] %d\n", args->n, args->buffer[args->n]);

    args->n++;
    pthread_cond_broadcast(args->cond_empty);
    pthread_mutex_unlock(args->mutex);
  } while(1);
  pthread_exit(NULL);
}

void *consumer_f(void *argsv) {
  args_t *args = (args_t*) argsv;
  do {
    pthread_mutex_lock(args->mutex);
    while (args->n == 0) {
      pthread_cond_wait(args->cond_empty, args->mutex);
    }

    printf("Consumed: [%d] %d\n", args->n-1, args->buffer[args->n-1]);
    args->n--;
    pthread_cond_broadcast(args->cond_max);
    pthread_mutex_unlock(args->mutex);
  } while(1);
  pthread_exit(NULL);
}

void start_producer(args_t *args) {
  int rc;
  pthread_t producer;
  rc = pthread_create(&producer, NULL, producer_f, args);
  assert(rc == 0);
}

void start_consumer(args_t *args) {
  int rc;
  pthread_t consumer;
  rc = pthread_create(&consumer, NULL, consumer_f, args);
  assert(rc == 0);
}


int main(void) {
  srand(time(NULL));

  int max = 100;
  int *buffer = (int*) calloc(100 * sizeof(int), 0);

  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  pthread_cond_t cond_empty;
  pthread_cond_init(&cond_empty, NULL);

  pthread_cond_t cond_max;
  pthread_cond_init(&cond_max, NULL);

  args_t args = {.mutex = &mutex,
                 .cond_empty = &cond_empty,
                 .cond_max = &cond_max,
                 .buffer = buffer,
                 .max = max,
                 .n = 0};
  start_producer(&args);
  start_consumer(&args);
  for (;;) pause();
  free(buffer);
  return 0;
}
