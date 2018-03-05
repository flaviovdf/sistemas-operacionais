int imprime(char *s);
int somavect(int *v, int n);

char s[] = "Olá mundo, eu somei 1 2 3 que foi: ";
int  v[] = {1, 2, 3};
int main(void) {
  imprime(&s[0]);
  int soma = somavect(&v[0], 3);
  char somac[] = {(char)(soma + 48), '\0'}; // iota na mão
  imprime(&somac[0]);
  return 0;
}
