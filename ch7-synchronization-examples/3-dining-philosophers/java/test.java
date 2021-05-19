import java.util.concurrent.*;

public class test {
    public static void main(String[] args) {

        ExecutorService pool = Executors.newFixedThreadPool(5);

        // Create DiningPhilosophers object
        DiningPhilosophers dp = new DiningPhilosophers();

        // Submit the tasks
        for (int i = 0; i < 5; i++) {
            pool.execute(new Philosopher(i, dp));
        }
    }
}
