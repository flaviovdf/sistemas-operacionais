import java.util.Random;

public class MinFirst implements PhilosopherHands {
  public Fork[] selectForkOrder(Fork forkLeft, Fork forkRight) {
    Fork[] returnVal = new Fork[2]; 
    if (forkLeft.getID() < forkRight.getID()) {
      returnVal[0] = forkLeft; 
      returnVal[1] = forkRight; 
    } else {
      returnVal[0] = forkRight; 
      returnVal[1] = forkLeft; 
    }
    return returnVal;
  }
}
