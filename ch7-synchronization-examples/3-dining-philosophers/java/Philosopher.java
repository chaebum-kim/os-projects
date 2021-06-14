
class Philosopher implements Runnable {
    int num;
    DiningTable table;

    public Philosopher(int i, DiningTable table) {
        this.num = i;
        this.table = table;
    }

    public void run() {
        while (true) {
            table.takeForks(num);
            try {
                System.out.printf("Philosopher%d is eating.\n", num);
                Thread.sleep(3000);
            } catch (InterruptedException ie) {
            }
            table.returnForks(num);
            try {
                System.out.printf("Philosopher%d is thinking.\n", num);
                Thread.sleep(3000);
            } catch (InterruptedException ie) {
            }
        }
    }
}
