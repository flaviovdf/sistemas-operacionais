**Universidade Federal de Minas Gerais**

**Disciplina: DCC065 - Sistemas Operacionais**

**Professor: Flavio Vinicius Diniz de Figueiredo**

# Lista de Exercícios

## Conceitos Básicos

1. [Silberschatz 2.1] Qual a finalidade das chamadas de sistema?

1. [Silberschatz 2.6] Que chamadas de sistema têm de ser executadas por um
   interpretador de comandos ou shell para iniciar um novo processo?

1. [Silberschatz 2.8 - Alterada] Qual a finalidade e vantagens da abordagem em
   camadas? Qual seriam os impactos de um sistema com apenas 2 camadas? E
   apenas 1?

1. [Follow - up da acima] Como garantimos que apenas o SO execute na camada 0?

1. Qual a diferença entre Traps e Interrupções?

## Processos e Threads

1. [Silberschatz 3.8] Qual a diferença entre escalonamento de curto prazo,
   médio prazo e longo prazo?

1. Como é feita a troca de contexto entre 2 processos?

1. Em um sistema sem múltiplos processadores (cores), existem vantagens em usar
   threads?

1. Em quais momentos um processo pode passar do estado RUNNING (Em Execução)
   para o estado WAITING (Em Espera)?

1. O Linux mantém um um novo estado de processos indicando que o mesmo não pode
   ser interrompido. Qual a vantagem deste novo estado?

1. Você consegue pensar em algum motivo pelo qual executamos um `fork` sem
   seguir um `exec`?

1. [Silberschatz 4.8 - Alterada] Pensando no estado de um processo. O mesmo
   cria uma thread. Quais informações são compartilhadas com a threads? Quais
   não são?

1. Qual a diferença entre paralelismo de dados e de processos?

## Escalonamento

1. [Silberschatz 6.2] Qual a diferença entre escalonamento com interrupções e
   sem interrupções?

1. [Silberschatz 6.10 - Alterado] Como vimos em aula, o tempo de execução (CPU)
   e o tempo de espera (IO) afetam a prioridade de um processo. Qual a
   importância de separar os 2 tempos?

1. Explique as métricas de avaliação de algoritmos de escalonamento. É possível
   maximizar todas elas de uma só vez?
   * Throughput
   * Turnaround time (tempo de término)
   * Tempo de Espera
   * Tempo de Resposta

1. [Silberschatz 6.16] Considere o conjunto de processos a seguir, com duração
   de pico de CPU dada em milissegundos:

   | Processo| Duração do Pico | Prioridade |
   | --------|-----------------|------------|
   | P1      | 2               | 2          |
   | P1      | 1               | 1          |
   | P3      | 8               | 4          |
   | P4      | 4               | 2          |
   | P5      | 5               | 3          |

   Assumimos que todos os processos chegaram em ordem (P1 até P5) no tempo 0.
   Desenhe gráficos de Gantt ilustrando a execução dos processos quando
   utilizamos: (a) FCFS; (b) SJF; (c) RR com quantum=2;

   Para cada processo. Compute as métricas da questão anterior.

1. Você foi contratado para desenvolver um algoritmo de escalonamento de um SO
   de uso específico. Tal SO vai executar em máquinas multi processadas. A
   máquina vai ser utilizada para servir uma máquina de busca como o Google.
   Isto é, uma parte dos processos vão coletar páginas da internet, outra parte
   vai servir as páginas para clientes via Web, enquanto a última parte vai
   cuidar de processar e indexar as páginas. Como pode ser visto, alguns
   processos têm mais uso de I/O enquanto outros são mais CPU intensive. Como
   você criaria filas de prioridades para estes processos? Quais algoritmos de
   escalonamento você utilizaria dentro das filas? Você acha que é necessário
   chavear processos entre filas?

## Sincronização e Deadlocks

1. Qual o menor programa que você consegue escrever que gera um deadlock?
   Pode utilizar pseudo código.

1. Faz sentido ter um programa com várias threads que precisa de sincronização
   constante?

1. A chamada `thread_yield` faz com que uma thread libere o uso de CPU para
   outra thread/processo. Em quais situações a mesma é útil? Como ela difere
   de mutexes?

1. Como podemos implementar um semáforo contador a partir de um semáforo
   binário?

1. Existem três requisitos para o problema da seção crítica. Explique os mesmos
   e motivos pelos quais precisamos dos três.

1. Message Passing Interface (MPI) é um sistema de troca de mensagens bastante
   utilizado para o desenvolvimento de aplicações de cluster. O mesmo define
   duas primitivas simples de `send` e `receive` para a troca de dados entre
   `n > 1` processos. Em algumas implementações de MPI, sempre que um processo
   chama `receive`, MPI espera por dados em um *spinlock*
   (ou seja, uma espera ocupada). Quais a vantagens de utilizar o spinlock e
   não outro mecanismo que libera a CPU?

1. Em sala de aula falamos que podemos resolver o problema dos filósofos com
   um garçom. Explique como implementar tal garçom. Quais são as vantagens e
   desvantagens desta solução?

## Memória: Hardware

1. [Silberschatz 8.1] Qual a diferença entre endereços lógicos e físicos?

1. [Silberschatz 8.3] Por que os tamanhos de página sempre são potência de 2?

1. Cite 2 vantagens de utilizar endereçamento hierárquico? Isto é, um diretório
   de páginas e uma tabela de páginas?

1. Qual o tamanho máximo de memória física possível em um sistema de 32 bits?
   E em um de 64 bits?

1. [Tanenbaum 3.4] Considere um sistema de troca de processos entre memória e
   disco no qual a memória é constituída de lacunas em ordem na memória:
   10 KB, 4 KB, 20KB, 18KB, 7KB,  9KB, 12KB e 15KB. Qual lacuna é ocupada
   quando solicitamos de forma sucessiva: 12, 10 e 9 KB respectivamente? Use
   os algoritmos: first fit, best fit, worst fit e next fit.

1. [Tanenbaum 3.18] Uma máquina tem um endereçamento virtual de 48 bits e um
   endereçamento físico de 32 bits. As páginas são de 8KB. Quantas entradas são
   necessárias na tabela de páginas?

1. [Silberschatz 8.13] Compare os esquemas de alocação contígua, segmentação
   pura e paginação pura com relação às questões a seguir:
   1. Fragmentação externa
   1. Fragmentação interna
   1. Compartilhamento

1. [Silberschatz 8.15] Explique por que sistemas operacionais móveis como iOS
   e Android não suportam permuta?

1. [Siberschatz 8.20] Supondo um tamanho de página de 1KB (2^10, com 2^22
   bits para tradução). Quais são os números de deslocamentos de página para as
   referências a seguir (fornecidas como decimais):
   1. 3085  (`0b00000000000000000000110000001101` --> `num = 0000000000000000000011 | off = 0000001101`)
   1. 42095
   1. 215201
   1. 650000
   1. 200001

1. [Siberschatz 8.24] Considera um sistema de computação com um endereço lógico
   de 32 bits e tamanho de página de 4KB. O sistema de 512MB de memória física.
   Quantas entradas haveria em cada um dos itens a seguir:
   1. Tabela de páginas de um único nível
   1. Tabela de páginas de dois níveis
   1. Tabela hash

1. [Siberschatz 8.25] Considera um sistema de paginação simples:
   1. Se uma referência para a memória gasta 50ns, quanto tempo leva uma
      referência para a memória paginada.
   1. Se a TLB tem 75% de acerto, qual será o tempo efetivo de acesso à
      memória? (Assuma que a TLB tem um custo de 2ns)

1. [Siberschatz 8.29] Qual a finalidade da paginação da tabela de páginas?

1. [Tanenbaum 3.10] Suponha que uma máquina tenha endereços virtuais de 48 bits
   e endereços físicos de 32 bits.
   1. Se as páginas são de 4KB, quantas entradas existem na tabela de páginas
      se a mesma for de 1 nível?
   1. Suponha que o mesmo sistema tenha uma TLB com 32 entradas. Assumindo
      um tempo de acesso de 10ns para a memória real e 2ns para a TLB, qual a
      eficácia do sistema?

## Memória: SO

1. [Siberschatz 9.1 - Resumida] Quando ocorrem os erros/faltas de pagina?
   Quais são os passos do SO para tratar as mesmas?

1. [Siberschatz 9.7 - Alterada] Considere o array bidimensional `A`:
   `int A[][] = new int[100][100]`. O programa inteiro (texto) que processa a matriz
   reside na página 0. Com 3 quadros de memória real e assumindo que cada linha
   da matriz cabe em 1 página, quantas faltas ocorrem ao ler a matriz das
   seguintes forma em um acesso FIFO:
   ```c
   for (int i = 0; i < 100; i++)
       for (int j = 0; j < 100; j++)
           // Lê A[i][j]
   ```
   ```c
   for (int j = 0; j < 100; j++)
       for (int i = 0; i < 100; i++)
           // Lê A[i][j]
   ```

1. [Siberschatz 9.10 - Alterada] Em um algoritmo ótimo pode ocorrer a anomalia
   de belady? Explique.

1. [Siberschatz 9.17 - Resumida] Quais as vantagens do copy on write? Como o SO
   e o hardware podem implementar o mesmo?

1. [Tanenbaum 3.20 - Reformulada] Imagine um compilador que vai observar todos
   os acessos de memória do código, gerando como saída as páginas que devem
   ser substituídas para implementar uma política de troca de páginas ótima.
   É possível gerar tal compilador? Explique por quê. O mesmo funciona quando
   o algoritmo de troca de páginas é global?

1. [Tanenbaum 3.22] Se o algoritmo FIFO é usado com quatro molduras de página
   e oito páginas virtuais, quantas faltas vão ocorrer para a sequência de
   acessos `01723277103`. Repita para LRU.

1. Um computador pequeno tem quatro molduras de página. No primeiro tique do
   relógio os bits R são `0111`. Os próximos tiques são: `1011`, `1010`,
   `1101`, `0010`, `1010`, `1100` e `0001`. Se o algoritmo de envelhecimento,
   aging, é usado com um contador de 8 bits. Quais os valores dos quatro
   contadores após o último tique.

1. [Tanenbaum 3.28] Um computador tem quatro molduras de página. O tempo de
   carregamento da página na memória, o instante do último acesso e os bits
   `R e M` para cada página são mostrados a seguir:

    | Página | Carregado | Última ref. | R | M |
    |--------|-----------|-------------|---|---|
    | 0      | 126       | 280         | 1 | 0 |
    | 1      | 230       | 265         | 0 | 1 |
    | 2      | 140       | 270         | 0 | 0 |
    | 3      | 110       | 285         | 1 | 1 |

    1. Qual página será trocada pelo NRU?
    1. FIFO?
    1. LRU
    1. Segunda chance?

1. [Silberschatz 9.14] Suponha que um programa tenha acabado de referenciar um
   endereço na memória virtual. Descreve se e qual o motivo de cada cenário
   ocorrer:
   a. Falta na TLB sem falta na tabela de páginas.
   b. Falta na TLB com falta na tabela de páginas.
   c. Sucesso na TLB sem falta de página na tabela.
   d. Sucesso na TLB com falta de página na tabela.

## Entrada e Saída

1. Existem cenários onde o POOLING é útil? Explique quais.

1. [Silberschatz 13.5] Como DMA aumenta a concorrência no sistema? Como
   ele complica o projeto de hardware?

1. [Silberschatz 13.9 - Alterada] Quais as vantagens de registradores de
   controle de dispositivos?

1. Faz sentido um dispositivo que tem controle com base em registradores
   e não faz uso de DMA?

1. [Silberschatz 13.12] Quais são os overheads de atender uma interupção?

1. Existem algum momento que é melhor usar I/O com pooling?

## Discos

1. Geralmente o scheduling do disco é jogado com tarefa do SO. Você
   consegue explicar os motivos?

1. [Siberschatz 10.1] O scheduling de disco, com execução de FCFS, é
   útil em um ambiente monousuário? Explique sua resposta.

1. [Silberschats 10.2] Explique por que o SSTF tende a favorecer o
   o "meio do disco".

1. Explique o motivo pelo qual FCFS é o único algoritmo justo de
   disco.

## Arquivos

1. Dê exemplos de aplicaçes que fazem uso de acesso sequencial.
   E de acesso randômico?

1. Faz sentido o SO ter um cache dos últimos arquivos abertos?
   Isto é, um cache de inodes->dados.

1. [Silberschatz 11.14] Se o sistema operacional souber que
   determinada aplicação vai fazer uso dos dados de um arquivo,
   domo tal informação pode ser explorada por desempenho?

1. Discuta e compara hard links e soft links em quesitos de
   vantagens e desvantagem.

## Sistema de Arquivos

1. [Tanenbaum 5.1 - Inspirada] Existem vantagens em identificar arquivos
   executáveis com um número mágico fixo? Quais as desvantagens?

1. [Tanenbaum 5.3 - Inspirada] É possível ter um SO que permite
   ler e escrever de arquivos sem uma chamada `open` (isto é, fazer um
   `read` direto), quais são as vantagens e desvantagens de tal
   abordagem?

1. [Tanenbaum 5.6 - Inspirada] Bole um mecanismo de comunicação entre
   processos utilizando `mmaps`. Você precisa mapear o arquivo inteiro
   em cada processo?

1. [Tanenbaum 5.11]

1. Quais são as vantagens e desvantagens de guardar i-nodes perto dos
   arquivos?

1. [Tanenbaum 5.33] Considerando um sistema de arquivos estilo FFS,
   no pior caso, quantas operaçes de ler i-nodes são necessárias
   para ler `/home/user/cursos/so/tp2.c`.

1. [Siberschatz 12.2] Qual são os motivos de manter o mapa de
   bits do sistema de arquivos no disco e não na memória?

1. [Silberschatz 12.6] Como os caches ajudam a melhora o desempenho?
   Por que sistemas não usam caches maiores ou em maior número?

1. Explique como funciona uma camada de arquivos virtual.

1. Explique qual o motivo de se utilizar inodes. Quais informações
   guardamos em iNodes geralmente?

1. Explique quais são as vantagens de inodes indireto.

1. Pensando em um disco em cilindro, como você faria a alocação de
   diretórios para ter um melhor desempenho? Como lidar com arquivos
   grandes.

1. [Silberschatz 12.13 - Inspirada] Similar à memória principal,
   sistemas de arquivos tem que escolher um tamanho de bloco. Quais
   são as vantagens e desvantagens de um tamanho de bloco maior ou
   menor. Existem vantagens e ter 2 tamanhos para um mesmo sistema
   de arquivos?

## Proteção e Segurança

São poucos problemas de proteção e segurança no livro, deem uma olhada
neles.
