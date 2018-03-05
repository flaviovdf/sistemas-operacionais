#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void) {
  void *handle;
  void (*imprime)(char *);
  char *error;

  /* Dynamically load the shared library that contains addvec() */
  handle = dlopen("./libprinter.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  /* Get a pointer to the addvec() function we just loaded */
  imprime = dlsym(handle, "imprime");
  if ((error = dlerror()) != NULL) {
	  fprintf(stderr, "%s\n", error);
  	exit(1);
  }

  /* Now we can call addvec() just like any other function */
  imprime("Hello World!");

  /* Unload the shared library */
  if (dlclose(handle) < 0) {
	  fprintf(stderr, "%s\n", dlerror());
  	exit(1);
  }
  return 0;
}
