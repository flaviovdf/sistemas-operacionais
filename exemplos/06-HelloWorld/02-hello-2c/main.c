int imprime(char *s);
char s[] = "Hello world";
int main(void) {
  imprime(&s[0]);
  char fim = '!';
  imprime(&fim);
  return 0;
}
