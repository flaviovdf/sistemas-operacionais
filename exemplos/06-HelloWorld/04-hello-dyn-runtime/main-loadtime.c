int imprime(char *s);

char s[] = "Hello World!";
int main(void) {
  imprime(&s[0]);
  return 0;
}
