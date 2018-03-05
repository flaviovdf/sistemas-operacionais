int somavect(int *v, int n) {
  int soma = 0;
  int i = 0;
  for (; i < n; i++) soma += v[i];
  return soma;
}
