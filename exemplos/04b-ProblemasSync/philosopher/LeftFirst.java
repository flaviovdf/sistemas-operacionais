public class LeftFirst implements PhilosopherHands {
  public Fork[] selectForkOrder(Fork forkLeft, Fork forkRight) {
    Fork[] returnVal = {forkLeft, forkRight};
    return returnVal;
  }
}
