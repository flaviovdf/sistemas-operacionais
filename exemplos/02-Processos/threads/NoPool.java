import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import java.util.stream.IntStream;

public class NoPool {

  public static void main(String... args) {
    // Uma tarefa apenas com um hello
    Runnable task = () -> {
      String threadName = Thread.currentThread().getName();
      System.out.println("Hello " + threadName);
    };

    // Cria 1000 threads
    IntStream.range(0, 1000).forEach(i -> new Thread(task).start());
  }
}
