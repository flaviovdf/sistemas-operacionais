import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Philosopher implements Runnable {

  private final int id;
  private final Fork forkLeft;
  private final Fork forkRight;
  private final PhilosopherHands hands;

  public Philosopher(int id, Fork forkLeft, Fork forkRight,
      PhilosopherHands hands) {
    this.id = id;
    this.forkLeft = forkLeft;
    this.forkRight = forkRight;
    this.hands = hands;
  }

  private void getForks(Fork firstFork, Fork secondFork) {
    firstFork.acquire(this.id);
    System.out.println("Philosopher " + this.id + " picked up " + firstFork);
    secondFork.acquire(this.id);
    System.out.println("Philosopher " + this.id + " picked up " + secondFork);
  }

  private void releaseForks(Fork firstFork, Fork secondFork) {
    firstFork.release(this.id);
    System.out.println("Philosopher " + this.id + " released " + firstFork);
    secondFork.release(this.id);
    System.out.println("Philosopher " + this.id + " released " + secondFork);
  }

  private void eat() {
    try {
      Random rng = new Random();
      System.out.println("Philosopher " + this.id + " eating!");
      Thread.sleep(rng.nextInt(1000)); //Sleep for at most 1 seconds
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }

  private void think() {
    try {
      Random rng = new Random();
      System.out.println("Philosopher " + this.id + " thinking!");
      Thread.sleep(rng.nextInt(1000)); //Sleep for at most 1 seconds
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }

  public void run() {
    while (true) {
      Fork[] forks = this.hands.selectForkOrder(this.forkLeft, this.forkRight);
      getForks(forks[0], forks[1]);
      eat();
      releaseForks(forks[0], forks[1]);
      think();
    }
  }

  public static void main(String... args) {
    int n = 5;
    List<Philosopher> philosophers = new ArrayList<>();
    List<Fork> forks = new ArrayList<>();

    for (int i = 0; i < n; i++) {
      forks.add(new Fork(i));
    }
    for (int i = 0; i < n; i++) {
      if (i == 0)
        philosophers.add(new Philosopher(i, forks.get(n-1), forks.get(i),
            new LeftFirst()));
      else
        philosophers.add(new Philosopher(i, forks.get(i-1), forks.get(i),
            new LeftFirst()));
    }

    for (int i = 0; i < n; i++) {
      new Thread(philosophers.get(i)).start();
    }
  }
}
