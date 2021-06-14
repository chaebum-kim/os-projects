import java.util.concurrent.*;

public class test {
    public static void main(String[] args) {

        ExecutorService pool = Executors.newFixedThreadPool(5);

        // Create DiningTable object
        DiningTable table = new DiningTable();

        // Submit the tasks
        for (int i = 0; i < 5; i++) {
            Philosopher philosopher = new Philosopher(i, table);
            pool.execute(philosopher);
        }
    }
}
