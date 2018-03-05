#include <assert.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>

#define SHARED_SIZE sizeof(char) * 256

void *create_shared_memory(size_t size, int fd) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it.
  // MAP_ANONYMOUS | MAP_SHARED implies on no copy on write, truly shared.
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, fd, 0);
}

void parent(void *shmem, sem_t *parentWrite, sem_t *childWrite) {
  char *parent_message = "hey kid!";  // parent process will write this message
  printf("[P] Parent sending: %s\n", parent_message);
  memcpy(shmem, parent_message, strlen(parent_message) + 1);
  sem_post(parentWrite);
  int semval;
  sem_getvalue(parentWrite, &semval);
  printf("[P] Added a token, size=%d\n", semval);

  char *parent_receive_buffer = malloc(sizeof(char) * SHARED_SIZE);
  assert(parent_receive_buffer != NULL);

  sem_getvalue(childWrite, &semval);
  printf("[P] Waiting for child, size=%d\n", semval);
  sem_wait(childWrite);
  memcpy(parent_receive_buffer, shmem, sizeof(SHARED_SIZE));
  printf("[P] Parent read: %s\n", parent_receive_buffer);
  free(parent_receive_buffer);
  sem_close(parentWrite);
  sem_unlink("parent");
}

void child(void *shmem, sem_t *parentWrite, sem_t *childWrite) {
  char *child_receive_buffer = malloc(sizeof(char) * SHARED_SIZE);
  assert(child_receive_buffer != NULL);

  int semval;
  sem_getvalue(parentWrite, &semval);
  printf("[C] Waiting for parent, size=%d\n", semval);
  sem_wait(parentWrite);
  memcpy(child_receive_buffer, shmem, sizeof(SHARED_SIZE));
  printf("[C] Child read: %s\n", child_receive_buffer);

  char *child_message = "hi dad!"; // child process will write this
  printf("[C] Child sending: %s\n", child_message);
  memcpy(shmem, child_message, strlen(child_message) + 1);
  sem_post(childWrite);
  sem_getvalue(childWrite, &semval);
  printf("[C] Added a token, size=%d\n", semval);
  free(child_receive_buffer);
  sem_close(childWrite);
  sem_unlink("child");
}

int main() {
  // Creates read write buffers
  void *shmem = create_shared_memory(SHARED_SIZE, -1);
  assert(shmem != NULL);

  // Create semaphores
  // name, flags, protection, value
  sem_unlink("parent");
  sem_t *parentWrite = sem_open("parent", O_CREAT,
                                PROT_READ | PROT_WRITE, 0);
  assert(parentWrite != NULL);

  sem_unlink("child");
  sem_t *childWrite = sem_open("child", O_CREAT,
                               PROT_READ | PROT_WRITE, 0);
  assert(childWrite != NULL);

  int pid = fork();
  assert(pid >= 0);

  if (pid == 0) {
    child(shmem, parentWrite, childWrite);
    printf("[C] exit\n");
  } else {
    parent(shmem, parentWrite, childWrite);
    printf("[P] exit\n");
  }
  munmap(shmem, SHARED_SIZE);
}
