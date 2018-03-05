#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHARED_SIZE sizeof(char) * 32

void *create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it.
  // MAP_ANONYMOUS | MAP_SHARED implies on no copy on write, truly shared.
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, 0, 0);
}

void parent(void *shmem) {
  char *parent_message = "hey kid!";  // parent process will write this message
  printf("[P] Parent sending: %s\n", parent_message);
  memcpy(shmem, parent_message, strlen(parent_message) + 1);
  printf("[P] Sleeping for 1s\n");
  sleep(10);

  char *parent_receive_buffer = malloc(sizeof(char) * SHARED_SIZE);
  assert(parent_receive_buffer != NULL);

  memcpy(parent_receive_buffer, shmem, sizeof(SHARED_SIZE));
  printf("[P] Parent read: %s\n", parent_receive_buffer);
  free(parent_receive_buffer);
}

void child(void *shmem) {
  printf("[C] Child Begins Sleeping... 1s\n");
  sleep(1);
  char *child_receive_buffer = malloc(sizeof(char) * SHARED_SIZE);
  assert(child_receive_buffer != NULL);
  memcpy(child_receive_buffer, shmem, sizeof(SHARED_SIZE));
  printf("[C] Child read: %s\n", child_receive_buffer);

  char *child_message = "hi dad!"; // child process will write this
  memcpy(shmem, child_message, strlen(child_message) + 1);
  free(child_receive_buffer);
}

int main() {
  void *shmem = create_shared_memory(SHARED_SIZE);
  assert(shmem != NULL);

  int pid = fork();
  if (pid == 0) {
    child(shmem);
    printf("[C] exit\n");
  } else {
    parent(shmem);
    printf("[P] exit\n");
  }
  munmap(shmem, SHARED_SIZE);
}
