# DCC605 File System Checker (DCC-FSCK).

1. Pode ser feito em dupla
1. 05 de Novembro de 2017

Neste trabalho você vai implementar um FSCK para o sistema ext2. Para
realizar seu TP recomendo um bom entendimento do
[Fast File System](http://pages.cs.wisc.edu/~remzi/OSTEP/file-ffs.pdf). O mesmo
é a base do ext2. Além disto, a seção 42.2 do OSTEP deve ser útil, leia a mesma
[aqui](http://pages.cs.wisc.edu/~remzi/OSTEP/file-journaling.pdf).

## Sobre o ext2

O Extended File System 2 (ext2) é um sistema de arquivos criados para sistemas
Linux em meados de 1993. Visando corrigir alguns problemas da primeira versão
do Extended File System (simplesmente ext), o sistema de arquivos ext2 tem um
esquema de implementação mais próximo ao Berkley Fast File System (FFS).

Embora já tenha caído um pouco em desuso, o ext2 é um sistema de arquivos com
bastante influência. O desenvolvimento do ext2 teve como um dos principais
objetivos a extensibilidade do sistema, sendo assim o mesmo serviu como base
para o ext3 e ext4 que são mais populares hoje em dia.

**Layout dos inodes, grupos e blocos**

Seguindo o modelo do FFS, um disco formatado com um sistema de arquivos ext2
terá um layout de blocos similar ao da figura abaixo (note que existem
problemas de escala na mesma, é apenas um esquema):

```
Layout geral:
  * Bloco de Boot         --> Utilizado para iniciar o sistema, sempre ocupa
                              uma posição fixa no ínicio do disco.
  * Grupo de Blocos i     --> Cada grupo de blocos é utilizado para guardar
                              arquivos. Fazemos uso de mais de um grupo pois
                              discos tem vários cílindros. Então guardar
                              artigos relacionados em um mesmo bloco ajuda.

  1-bloco
 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-----
 | bloco |                               |                               |
 | de    |       grupo de blocos 0       |       grupo de blocos 1       | ...
 | boot  |                               |                               |
 +-------+-------+-------+-------+-------+-------+-------+-------+-------+-----
        /                                 \
       /                                   \
      /                                     \
     /                                       \
    /                                         \
   /                                           \
  /                                             \
 /               grupo de blocos i               \
+-------+-------+-------+-------+-------+-------+-------+-------+-------+------
| super |  descritores  |       |       | tabela        |
| bloco |      do       |d-bmap |i-bmap | de inode      |  blocos de dados...
| const |     grupo     |       |       | inodes        |
+-------+-------+-------+-------+-------+-------+-------+-------+-------+------
 1-bloco    n-blocos     1-bloco 1-bloco     n-blocos          n-blocos

Layout de um grupo:
  * Super Bloco           --> Contém meta-dados do sistema de arquivos. Uma
                              cópia em cada grupo.
  * Descritores do Grupo  --> Meta-dados do grupo.
  * Data Bitmap (d-bmap)  --> Mapa de bits de dados livres
  * Inode Bitmap (i-bmap) --> Mapa de bits de inodes livres
  * Tabela de Inodes      --> Contém os inodes (metadados) do sistema de
                              arquivos. Cada arquivo tem 1 apenas 1 inode.
                              Através de links, um mesmo inode pode aparecer
                              mapear para 2 caminhos.
  * Bloco de Dados        --> Os dados do arquivos e diretórios em si.
```

## Structs úteis

Para entender melhor o ext2, vamos dar uma olhada no cabeçalho do Linux
que descreve o sistema de arquivos. O mesmo pode ser encontrado
[aqui](http://github.com/torvalds/linux/blob/master/fs/ext2/ext2.h).

Antes de iniciar, temos que entender os tipos `__le32` e `__le16`. Como o Linux
é cross-platform, tipos genéricos para qualquer arquitetura são necessários.
Esses dois em particular são *unsigned ints* de 32 e 16 bits. Os mesmos sempre
vão ser representados em *little endian*.

Como o PC que vai corrigir o TP é little endian (o seu tamnbém deve ser),
pode usar um atalho como:

```c
typedef int __le32;
```

**Super bloco**

```c
struct ext2_super_block {
  __le32 s_inodes_count;          /* Inodes count */
  __le32 s_blocks_count;          /* Blocks count */
  __le32 s_r_blocks_count;        /* Reserved blocks count */
  __le32 s_free_blocks_count;     /* Free blocks count */
  __le32 s_free_inodes_count;     /* Free inodes count */
  __le32 s_first_data_block;      /* First Data Block */
  __le32 s_log_block_size;        /* Block size */
  // . . .
  __le32 s_blocks_per_group;      /* # Blocks per group */
  // . . .
  __le32 s_inodes_per_group;      /* # Inodes per group */
  // . . .
  __le16 s_magic;                 /* Magic signature */
  __le32 s_first_ino;             /* First non-reserved inode */
  __le16 s_inode_size;            /* size of inode structure */
  // . . .
}
```

**Descritores de Grupo**

```c
struct ext2_group_desc
{
  __le32 bg_block_bitmap;         /* Blocks bitmap block */
  __le32 bg_inode_bitmap;         /* Inodes bitmap block */
  __le32 bg_inode_table;          /* Inodes table block */
  __le16 bg_free_blocks_count;    /* Free blocks count */
  __le16 bg_free_inodes_count;    /* Free inodes count */
  __le16 bg_used_dirs_count;      /* Directories count */
  __le16 bg_pad;
  __le32 bg_reserved[3];
};
```

Para saber o número de grupos no ext2 usamos a seguinte abordagem. A mesma faz
uso dos campos do superbloco.

```c
/* calculate number of block groups on the disk */
unsigned int group_count = 1 + (super.s_blocks_count-1) / super.s_blocks_per_group;

/* calculate size of the group descriptor list in bytes */
unsigned int descr_list_size = group_count * sizeof(struct ext2_group_descr);
```

Para ler os descritores do grupo, primeiramente você deve calcular o offset do
inicio do disco. Como o disco tem 1024 bytes reservados no inicio e o primeiro
bloco é um superbloco, o código é para ler o descrito é tal como:

```c
struct ext2_group_descr group_descr;
/* position head above the group descriptor block */
/* sd --> storage device, no nosso caso um arquivo */
lseek(sd, 1024 + block_size, SEEK_SET);
read(sd, &group_descr, sizeof(group_descr));
```

O descritor do grupo vai conter meta-dados para identificar o data e inode
bitmap daquele grupo. Uma macro boa de se ter indica qual o local do disco de
um dado bloco:

```c
/* location of the super-block in the first group */
#define BASE_OFFSET 1024
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*block_size)
```

**INodes**

```c
/*
 * Structure of an inode on the disk
 */
struct ext2_inode {
  __le16 i_mode;                 /* File mode */
  __le16 i_uid;                  /* Low 16 bits of Owner Uid */
  __le32 i_size;                 /* Size in bytes */
  __le32 i_atime;                /* Access time */
  __le32 i_ctime;                /* Creation time */
  __le32 i_mtime;                /* Modification time */
  __le32 i_dtime;                /* Deletion Time */
  __le16 i_gid;                  /* Low 16 bits of Group Id */
  __le16 i_links_count;          /* Links count */
  __le32 i_blocks;               /* Blocks count */
  __le32 i_flags;                /* File flags */
  __le32 i_block[EXT2_N_BLOCKS]; /* Pointers to blocks */
  // . . .
};
```

**Diretórios**

```c
struct ext2_dir_entry {
  __le32  inode;         /* Inode number */
  __le16  rec_len;       /* Directory entry length */
  __le16  name_len;      /* Name length */
  char    name[];        /* File name, up to EXT2_NAME_LEN */
};
```

## Criando imagens

O script de teste já cria as imagens que você deve trabalhar em cima.  O mesmo
faz uso dos comandos `dd` e `mkfs` discutidos em sala. Segue alguns exemplos:

**Comando dd - criando imagem zerada**

```
$ filename=fs-0x00dcc605-ext2-10240.img
$ dd if=/dev/zero of=$filename bs=1024 count=10240
```

```
1024+0 records in
1024+0 records out
1048576 bytes (1.0 MB, 1.0 MiB) copied, 0.0242941 s, 43.2 MB/s
```

**Comando mkfs.ext2 - criando um disco de 1mb sem superblock backup**

```
$ mkfs.ext2 fs-0x00dcc605-ext2-10240.img
```

```
mke2fs 1.42.13 (17-May-2015)
Creating filesystem with 10240 1k blocks and 2560 inodes
Filesystem UUID: 24c464b5-2e6c-4b6f-8309-d3454d683858
Superblock backups stored on blocks:
	8193

Allocating group tables: done
Writing inode tables: done
Writing superblocks and filesystem accounting information: done
```

## Erros que vamos causar

O seu fsck vai resolver 4 erros que causaremos no ext2.  Os erros e soluções
foram adaptados
[daqui](https://www.ece.cmu.edu/~ganger/746.spring10/projects/proj1_fsck/18746-s10-proj1.pdf)
e [daqui](https://www.linux.com/blog/fun-e2fsck-and-debugfs).

Dê um olhada nos 2 materiais acima e resolva os erros indicados.

1. **Fun 1: Attack the superblock** O primeiro erro que você deve tratar é um
ataque ao superbloco. Ao criar uma imagem o ext2 tem backups de super blocos
em cada grupo. Então, quando o primeiro superbloco for atacado você deve
caminhar até um grupo e recuperar o backup. Para saber se é um erro de
superbloco a montagem do disco vai falhar. Indique o erro para o usuário e peça
para o mesmo confirmar a operação.

1. **Fun 2: Blocos pertecentes a mais de um inode** No segundo ataque, 2 inodes
vão indicar que são donos de um mesmo bloco. Isto não pode ocorrer. Ache um dos
inodes e apague o mesmo. Note que não podemos fazer muito mais do que isto
nesse momento. Indique o erro para o usuário e peça para o mesmo confirmar a
operação.

1. **Fun 3: Permissão Corrompida** No terceiro ataque vamos zerar as permissões
de um arquivo. Caso ache algum inode sem permissões coloque um valor correto.
Qual valor?! Talvez seja uma boa ideia indicar para o usuário e pedir para o
mesmo decidir.

1. **Fun 4: Órfãos** Por fim, vamos criar inodes de arquivos que não pertencem
a nenhum diretório. Os mesmos podem ser considerados órfãos. Então, no seu
sistema de arquivos vão existir inodes que não pertecem a nenhum diretório.
Ache os mesmos e mova para uma pasta `/lost+found` na raiz da imagem do disco.
Coloque como nome do arquivo o número do inode (`/lost+found/#1074`). Assim
como nos cases anteriores, confirme a ação com o usuário.

## Imagens de Erro

As imagens com os 4 erros acima estão na pasta [tests](./tests). A única
diferença entre as imagens é o tamanho das mesmas.

## Script de corrupção

**[Cuidado] O Script precisa de root e caso você mude o mesmo pode causar erros no seu pc**

**Rode o mesmo com cuidado. Recomendo usar as imagens pre-prontas.**

Criamos um script para causar os erros descritos acima. Para cada imagem
gerada, rode seu programa. Para cada erro indique para o usuário o erro e a
solução. Peça uma confirmação para prosseguir.

[Script](https://gist.github.com/anonymous/31686fc7a8aa920acf2dc17753a1a80f)

Note que o script causa os 4 erros para cada uma das imagens! Seu trabalho tem
que identificar os erros sozinho.

Para rodar o script, instale o `debugfs`

**O script roda apenas com sudo/root**

## Entrega

Um .c e um .h (caso precise) que roda o fsck corrigindo os 4 casos acima. Chame
seu programa de `dcc_os_fsck`.

A entrega será pelo moodle. Desta vez como é um único arquivo faz menos sentido
um repositório no git. Porém, caso deseje utilizar, pode fazer a entrega pelo
git.

## Pontos Extra

1. Crie mais tipos de erros de acordo com os vários links desta documentação.
   Isto é, caso você tenha lido o material pode achar mais erros para adicionar
   no `fs_creator`.
2. Resolva o erro criado no passo anterior.
3. Dicas de melhorias na documentação.
