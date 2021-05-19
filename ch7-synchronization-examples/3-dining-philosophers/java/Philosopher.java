
class Philosopher implements Runnable {
    int num;
    DiningPhilosophers diningPhilosophers;

    public Philosopher(int i, DiningPhilosophers dp) {
        num = i;
        diningPhilosophers = dp;
    }

    public void run() {
        while (true) {
            diningPhilosophers.takeForks(num);
            try {
                System.out.printf("Philosopher%d is eating.\n", num);
                Thread.sleep(3000);
            } catch (InterruptedException ie) {
            }
            diningPhilosophers.returnForks(num);
            try {
                System.out.printf("Philosopher%d is thinking.\n", num);
                Thread.sleep(3000);
            } catch (InterruptedException ie) {
            }
        }
    }
}
