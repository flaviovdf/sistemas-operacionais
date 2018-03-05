import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;
import java.util.ArrayList;
import java.util.List;

public class ProducerConsumer {

  private static final int N = 100;

  //true == fifo == fair
  private static final Semaphore available = new Semaphore(N, true);
  private static final ReentrantLock mutex = new ReentrantLock();
  private static final List<Object> queue = new ArrayList<>();

  private static final class Consumer implements Runnable {
    public void run() {
      while(true) {
        mutex.lock();
        if (queue.size() > 0) {
          System.out.println(queue.remove(0) + " " + queue.size());
          available.release();
        }
        mutex.unlock();
      }
    }
  }

  private static final class Producer implements Runnable {
    public void run() {
      try {
        while(true) {
          available.acquire();
          mutex.lock();
          Object item = new Object();
          queue.add(item);
          mutex.unlock();
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
