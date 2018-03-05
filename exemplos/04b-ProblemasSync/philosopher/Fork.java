import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class Fork {
  
  private static final int NO_ONE = -1;
  
  private final int id;
  private int whoHasMe;

  public Fork(int id) {
    this.id = id;
    this.whoHasMe = NO_ONE;
  }

  public synchronized void acquire(int philosopherID) {
      while (this.whoHasMe != NO_ONE) {
        try {
          this.wait();
        } catch (InterruptedException e) {
          throw new RuntimeException(e);
        }
      }
      this.whoHasMe = philosopherID;
  }

  public synchronized void release(int philosopherID) {
    if (this.whoHasMe != philosopherID) {
      throw new RuntimeException("Somebody coded wrong!");
    }
    this.whoHasMe = NO_ONE;
    this.notify();
  }
  
  public int getID() {
    return this.id;
  }

  public String toString() {
    return "" + this.id;
  }
}
