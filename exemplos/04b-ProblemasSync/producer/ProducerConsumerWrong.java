import java.util.concurrent.Semaphore;
import java.util.ArrayList;
import java.util.List;

public class ProducerConsumerWrong {

  private static final int N = 100;

  //true == fifo == fair
  private static final Semaphore available = new Semaphore(N, true);
  //ERRO1: Semaforo 0 em java não sincroniza no UP
  //(UP adiciona + 1 sempre)! Ler API!!!!
  private static final Semaphore sync = new Semaphore(0);
  private static final List<Object> queue = new ArrayList<>();

  private static final class Consumer implements Runnable {
    public void run() {
      while(true) {
        if (queue.size() > 0) {
          //ERRO2: Lista não é protegida por mutex!!!
          System.out.println(queue.remove(0) + " " + queue.size());
          sync.release();
        }
      }
    }
  }

  private static final class Producer implements Runnable {
    public void run() {
      try {
        while(true) {
          available.acquire();
          if (queue.size() == N) {
            sync.acquire();
          }
          Object item = new Object();
          //ERRO2: Lista não é protegida por mutex!!!
          queue.add(item);
          available.release();
        }
      } catch (InterruptedException e) {
        throw new RuntimeException(e);
      }
    }
  }

  public static void main(String... args) {
    for (int i = 0; i < 4; i++) {
      new Thread(new Consumer()).start();
      new Thread(new Producer()).start();
    }
  }
}
