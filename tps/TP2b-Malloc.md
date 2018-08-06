# TP2: Malloc

## Parte 1: Malloc

Neste TP você vai implementar uma biblioteca de gerenciamento de alocações
Na sua biblioteca você deve usar a função `mmap` para alocar e desalocar espaços
de memória.

Funções a serem implementadas:

```c
#ifndef SO605_GC
#define SO605_GC

// 4096*1024
// Processo tem 4096 MB de memória
#define MEMSIZE 4194304

//Nó da lista de memória livre
typedef struct free_node {
 size_t free;
 size_t size;
 struct free_node *next;
} free_node_t;

typedef struct {
  free_node_t *head;
  free_node_t *lastAlloca; // Usado para next fit
} free_list_t;

void *aloca(size_t size);
void libera(void *ptr);

#endif
```

Cada `aloca` deve gerencia a memória livre com uma lista encadeada
representando espaços contínuos de memória:

```
{size, next} -> {size, next} -> {size, next} -> ...
```

As funções não devem chamar `malloc` nem `free`.

```c
//Alocando memória com mmap
//PROT_READ: podemos ler do espaço
//PROT_WRITE: podemos escrever no espaço
//MAP_PRIVATE: Copy on write
//MAP_SHARED: Compartilhe memória com outros processos no fork
mmap(init, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
```

Você pode fazer uso da função `sbrk` para definir o primeiro endereço de
memória:

```c
void *init = sbrk(0);
```

Ou simplesmente passando `NULL` para o init.
```c
mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
```

Existem duas abordagem para fazer o TP.
  1. Pre alocar os 4mb em 1 único mmap e seguir daí
  2. Ir alocando com mmap a cada aloca e munmap a cada libera.

A primeira é melhor pois é determinística. Note na documentação do `mmap` que
o mesmo não garante que vai utilizar a posição `init`. Se no seu TP você não
usar nenhuma outra primitiva de alocação (o malloc do c), deveria funcionar.

### Entrada

Sua entrada será uma lista de identificadores e tamanhos. Para cada um destes,
você deve alocar a memória. Também vamos fazer operações de free. Os free's
são identificados de acordo com os ids anteriores:

| ID   | Mem Size | Op  |
|------|----------|-----|
| nops |          |     |
| 0    | 512      | a   |
| 1    | 128      | a   |
| 0    | -1       | f   |
| ...  | ...      | ... |

O -1 indica que não é uma operação de alocação. Deve ser ignorado.

A primeira linha indica o esquema de alocação a ser utilizado. Você deve
implementar:

  1. Best fit (bf)
  2. Worst fit (wf)
  3. First fit (ff)
  4. Next fit (nf)

A segunda linha indica o número de operações que serão realizadas, assim você
pode gerenciar os ids das operações. Tal linha é um int. Os ids são de `[0,
nops)` (no pior caso, fazemos nops alocas distintos sem frees).

Por fim, entrada acima aloca 2 regiões de memória, uma de 512bytes e outra de
128bytes. Após as alocações, a mesma libera 512bytes da região 0.

As entradas vão ser lidas de `stdin`.

### Saída

Para cada entrada, seu algoritmo deve mensurar a fragmentação, isto é a
quantidade de espaço livre entre blocos de memória. Caso os `aloca`s passem do
tamanho máximo de memória, definido no header, seu código deve retornar NULL
igual a biblioteca malloc.

A saída é mensurada pela fragmentação externa, podendo ser um número apenas:

![](http://wikimedia.org/api/rest_v1/media/math/render/svg/718dd9727b3c8db3a8b733a9558608e16fcf5434)

Então, uma saída possível seria:

``0.67``

### Experimentos

A ser disponibilizado

### Recursos Interessantes

  1. http://pages.cs.wisc.edu/~remzi/OSTEP/vm-freespace.pdf

### Nome do Executável Final

`aloca`

### Executando

Veja o esqueleto no link:

https://github.com/flaviovdf/SO-2017-1/blob/master/tp2/esqueletos/ahloka/

```
$ ./aloca bf < alocacoes.dat
0.67
```

O único parâmetro indica qual algoritmo será utilizado.

## Parte 2: Garbage Collection

**Simule** um coletor de memória simples por contagem de referências.  Não se
preocupe com referências cíclicas, não vamos ter casos como esse.  Para
implementar o GC, você vai ler uma entrada similar a anterior. A mesma terá
operações novas de dependencias entre ids de alocação (imagine como referências
entre objetos em C++/Java/Python).

  1. Cada `aloca` cria uma nova referência para o id.
  2. Cada dependencia entre 2 ids cria uma nova referência para o destino

### Entrada

| ID   | Mem Size/Ref | Op  |
|------|--------------|-----|
| nops |              |     |
| 0    | 512          | a   |
| 1    | 128          | a   |
| 2    | 64           | a   |
| 3    | 0            | r   |
| 4    | 3            | r   |
| 4    | -1           | f   |
| 0    | -1           | f   |
| 3    | -1           | f   |
| ...  | ...          | ... |

As operações de referência são identificadas por `r`.

### Funcionamento

Cada free deve liberar o espaço de memória e reduzir por 1 as referências.
Quando qualquer espaço tem tamanho 0, seu GC pode liberar aquele espaço também.

No exemplo acima, liberamos o id (ponteiro) 4. O mesmo tinha uma referência
para 3. Note que 3 nunca foi alocado por `a`, então neste momento seu contador
é 0. O mesmo pode ser liberado.

### Saída

   1. **Assuma que operações r tem uma custo de 4bytes, criar um ponteiro**
   2. Indique a quantidade de bytes ainda residentes na memória no fim do
      do seu programa.

Ex: `192` (sem contar os ponteiros)

### Dicas

Embora não seja necessário para ter um TP correto, você pode imaginar que seu
GC vai ser utilizado por uma linguagem de alto nível tipo Python/Go/Java.
Nestes casos, a contagem de referências são feitas ao realizar um `=`

```java
Object obj = new Object(); //aloca
Object new_ref = obj;      //aumenta em 1 a referência
```

Uma forma simples de contar as referências é criar uma função:

```c
void set_ptr(void **ptr, void *object);
```

Tal função é utilizada para setar as referências e aumentar os contadores.

Em tempo de compilação, o compilador da sua linguagem pode traduzir todos os
`=` para um `set_ptr`.

Uma outra função:

```c
void unset_ptr(void **ptr);
```

Poderia ser utilizada quando se faz `= NULL`. O post abaixo fala um pouco
de como a contagem é feita em Python:

https://intopython.com/2016/12/13/memory-management/

### Nome do Executável Final

`garbagec`
