# TP1 : Utilizando /proc/ para fazer um TOP + Ssinals

Vamos aprender um pouco sobre arquivos especiais e o comando top. Dê uma
olhada nos arquivos `/proc/*/stat`.  O `/proc` é um diretório de arquivos
especiais do linux que lista os processos em execuções. Este arquivo embora
possa ser lido como um arquivo normal, na verdade não é um arquivo em disco
e sim um file handle para um arquivo especial que lista informações do kernel.

Crie um programa que gera um executável `meutop`. Tal programa deve imprimir os
processos sendo executados em sequência.  Para cada programa, identifique o PID
do programa, o usuário que está executando o mesmo e o estado do processo. Com
isto, imprima os programas em execução em uma tabela como a abaixo. Tal tabela
deve ser atualizada a cada 1 segundo.

Seu comando deve se chamar `meutop`.

```
PID    | User    | PROCNAME | Estado |
-------|---------|----------|--------|
1272   | flavio  | yes      | S      |
1272   | root    | init     | S      |
```

**Dica** Você pode limitar seu top para imprimir apenas os 20 primeiros
processos que encontrar.

Dê uma olhada no manpage do /proc:
[Manpage](http://man7.org/linux/man-pages/man5/proc.5.html)

Outra fonte de dados é o código do ps:
[PS](https://github.com/thlorenz/procps/blob/master/deps/procps/proc/readproc.c)

Vamos agora nos inspirar no comando `top` ou `htop` para aprender um pouco mais
sobre sinais. O htop é um top avançado no linux que permite o envio de sinais
para processos em execução.

Permita que seu comando TOP envie sinais. Isto é, crie uma função no seu TOP
que enviar sinais para um PID. Tal função pode ser apenas digitar um "PID
SINAL". Por exemplo, se o signaltester tem PID 2131, o código abaixo deve
enviar o sinal SIGHUP para o mesmo.

```
PID    | User    | PROCNAME     | Estado |
-------|---------|--------------|--------|
2131   | flavio  | signaltester | S      |
> 2131 1
```

Com este sinal o processo deve morrer e sair da sua lista.

**Dica 1:** Possivelmente o signaltester não vai aparecer entre os 20 primeiros.
Use o comando abaixo para descobrir o PID do mesmo e testar seu topzera.

**Dica 2:** O usuário que é dono do processo é o usuário dono do arquivo no /proc.
A biblioteca `dirent.h` pode lhe ajudar.

**Dica 3:** A biblioteca `sys/stat.h` também pode ser de ajuda.

**Dica 4:** Para enviar o sinal use a função [kill](https://linux.die.net/man/2/kill)

```
$ ps | grep signalteste
```

**Código de Teste:** Disponibilizei um código
[signaltester](https://github.com/flaviovdf/SO-2017-2/blob/master/tp1/signaltester/tester.c)
para você testar o seu trabalho. O mesmo faz um tratamento simples de sinais em
C.

Compile o teste com a linha

```
$ gcc signaltester.c -o signaltester
```

Uma forma de permitir a leitura da entrada e a impressão da lista de processos
é utilizando `pthreads`. Tente fazer isto.
