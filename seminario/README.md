# Seminários de SO

## Datas, Entregas e Alunos

1. Escolha do tema: Até 31 de Outubro
1. Entrega do relatório: Até 28 de Novembro
1. Apresentações: A definir (até o dia 02 de Novembro)

## Objetivos

1. Discutir tópicos relacionados à Sistemas Operacionais que, embora não
   cobertos no curso, empreguem técnicas abordadas na disciplina (casos de
   estudo, sistemas distribuídos, computação em nuvem etc.).

1. Desenvolver a capacidade do aluno investigar um novo tópico, entendendo seus
   fundamentos de sistemas e aplicações, e transmitir o conhecimento aos colegas
   em sala de aula.

1. Divertir-se explorando assuntos novos e intrigantes.

## Organização do seminário e avaliação

1. Cada seminário será realizado por um grupo de 2 alunos.

1. O seminário será avaliado em 20 pontos pontos e é dividido em duas partes:
   * A entrega de um relatório escrito de no máximo 5 páginas incluindo a
     capa e referências, se houver. (10 pontos.)
   * Uma apresentação oral em sala de aula, não devendo passar de 12 minutos,
     seguidos de mais 3 minutos dedicados à discussão com o professor e os
     colegas. (10 pontos.)

1. Tanto o relatório escrito quanto a apresentação oral serão avaliados de
   acordo com os seguintes critérios:
   * profundidade e relevância da pesquisa realizada;
   * clareza na apresentação dos resultados;
   * concisão na apresentação dos resultados;
   * capacidade de transmissão dos conhecimentos obtidos.

## Tópicos de Seminários

**Estruturas e Casos de Usos**

  1. Microkernel OSes:
     * https://homes.cs.washington.edu/~bershad/590s/papers/towards-ukernels.pdf
     * https://en.wikipedia.org/wiki/Tanenbaum%E2%80%93Torvalds_debate
  1. Caso de Estudo: Windows
     * Material do Tanenbaum e Silberschatz
     * Os dois livros descrevem o Windows
  1. Caso de Estudo: Linux
     * Material do Tanenmbaum e Silberschatz
     * Os dois livros descrevem o Windows
  1. Sistemas de Tempo Real
     * Material do Tanenmbaum e Silberschatz
  1. Caso de Estudo: FreeBSD
     * Livro Design and Implementation of the FreeBSD System
     * Disponível com o Professor
  1. Caso de Estudo OpenBSD
     * Considerado um dos SOs mais seguros do mundo
     * Explicar como garantir tal segurança
  1. Microsoft Singularity
     * https://www.microsoft.com/en-us/research/project/singularity/
     * https://en.wikipedia.org/wiki/Singularity_(operating_system)

**Tópicos em Proteção**
  
  1. Linux NameSpaces e CGroups
     * Novas abordagens de proteção do Linux
     * https://www.youtube.com/watch?v=sK5i-N34im8

**Sistemas de Arquivos**

  1. ext3/4
     * Explicar o ext3 e ext4 em detalhes
     * Ponto de partida no OStep
     * http://pages.cs.wisc.edu/~remzi/OSTEP/file-journaling.pdf
     * http://pages.cs.wisc.edu/~remzi/OSTEP/file-lfs.pdf
  1. NTFS
     * Sistemas de arquivos do windows
     * https://en.wikipedia.org/wiki/NTFS
  1. UnionFS 
     * Sistema de arquivos feito pensando em versionamento (e.g., ala git)
     * Uma das bases do docker
     * http://unionfs.filesystems.org/
  1. Ceph
     * Sistemas de arquivos distribuídos
     * http://docs.ceph.com/docs/master/architecture/
  1. GlusterFS
     * Sistemas de arquivos distribuídos
     * http://docs.gluster.org/en/latest/Quick-Start-Guide/Architecture/
  1. AFS
     * Andrew File System. Sistema tried and tested de arquivos distribuídos
     * O material do OStep deve ser um bom starting point
     * http://pages.cs.wisc.edu/~remzi/OSTEP/dist-afs.pdf

**Containers**

  1. Docker
     * Fazer uma palestra hands on seguindo as dicas da aula de virtualização
     * Comandos, migração, casos de uso
  1. Kubernetes e/ou Puppet
     * Fazer uma palestra hands on seguindo as dicas da aula de virtualização
     * Comandos, migração, casos de uso

**Mobile**

  1. Caso de Estudo Android
     * Falar das limitações
     * Explicar paginação e escalonamento
     * Explicar gerência do disco
  1. Caso de Estudo iOS
     * Falar das limitações
     * Explicar paginação e escalonamento
     * Explicar gerência do disco

**Nuvem e BDs na Nuvem (um pouco mais avançado)**
  
  1. EC2 Elastic Resource Manager
     * Entender recursos elásticos na nuvem
     * Formas de pricing
     * http://www.cs.technion.ac.il/~ladypine/spotprice-acmsmall.pdf
  1. Google Spanner
     * https://research.google.com/archive/spanner.html
  1. Amazon Dynamo
     * https://aws.amazon.com/pt/dynamodb/
  1. Facebook TAO
     * https://www.usenix.org/node/174510

**Artigos Clássicos**

  1. Communicating Sequential Processes by C. A. R. Hoare
     * Artigo Clássico de Comunicação Entre Processos
     * https://spinroot.com/courses/summer/Papers/hoare_1978.pdf
  1. Xen and the Art of Virtualization
     * www.cs.yale.edu/homes/yu-minlan/teach/csci599-fall12/papers/xen.pdf
  
**Emulação**

  1. Emulation of Nintendo Game Boy
      * PyBoy paper
      * https://github.com/Baekalfen/PyBoy
      * https://github.com/Baekalfen/PyBoy/blob/master/PyBoy.pdf
  1. CHIP 8 Emulation
      * http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf
      * http://mattmik.com/files/chip8/mastering/chip8.html
      * Procure por CHIP8 Emulator. Diversos código e tutoriais
