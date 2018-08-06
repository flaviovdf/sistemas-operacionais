# TP1c - Modules

Vamos usar as estrututuras de processos do kernel do linux para implementar um ps-tree.
O código abaixo faz uso do [sched.h](https://github.com/torvalds/linux/blob/master/include/linux/sched.h).
O mesmo imprime todas as tarefas em execução no momento.

Preste atenção:
  1. Leia o [sched.h](https://github.com/torvalds/linux/blob/master/include/linux/sched.h)
  2. Note que a iteração é feita com uma macro `for_each_process(task)`

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

int
ps_init(void)
{
  struct task_struct *task;
  printk(KERN_INFO "Loading module myps\n");
  for_each_process(task) {
    printk("Name: %s PID: [%d]\n", task->comm, task->pid);
  }
  return 0;
}

void
ps_exit(void)
{
  printk(KERN_INFO "Removing module myps\n");
}

module_init(ps_init);
module_exit(ps_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS Module");
```

Usando as macros abaixo tente criar o PSTree:

```c
struct task_struct *task;
struct list_head *list;
list_for_each(list, &init_task->children) {
  task = list_entry(list, struct task_struct, sibling);
  /* task points to the next child in the list */
}
```

A macro `list_for_each` recebe dois parâmetros, ambos do tipo `struct list_head`:
  1. Um ponteiro para onde vamos armazenar a cabeça da lista
  1. Um ponteiro para os filhos do init_task, vamos percorrer os mesmos

A macro `list_entry` retorna cada elemento da lista.

  1. [Código exemplo](https://github.com/flaviovdf/SO-2017-1/blob/master/tp1/kernel/)
  1. https://en.wikipedia.org/wiki/Printk
