import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import java.util.stream.IntStream;

public class Pool {

  public static void main(String... args) {
    // Uma tarefa apenas com um hello
    Runnable task = () -> {
      String threadName = Thread.currentThread().getName();
      System.out.println("Hello " + threadName);
    };

    // Cria uma pool de 4 threads
    ExecutorService executor = Executors.newFixedThreadPool(4);

    // Submete 1000 tarefas
    IntStream.range(0, 1000).forEach(i -> executor.submit(task));

    executor.shutdown();
  }
}
