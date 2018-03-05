import java.util.Random;

public class RandomFork implements PhilosopherHands {
  public Fork[] selectForkOrder(Fork forkLeft, Fork forkRight) {
    Fork[] returnVal = new Fork[2]; 
    Random rng = new Random();
    if (rng.nextBoolean()) {
      returnVal[0] = forkLeft; 
      returnVal[1] = forkRight; 
    } else {
      returnVal[0] = forkRight; 
      returnVal[1] = forkLeft; 
    }
    return returnVal;
  }
}
