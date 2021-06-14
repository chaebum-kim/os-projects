import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

interface DiningServer {
    enum State {
        thinking, hungry, eating
    };

    public void takeForks(int philosopherNumber);

    public void returnForks(int philosopherNumber);
}

class DiningTable implements DiningServer {
    private Condition[] self = new Condition[5];
    private Lock lock = new ReentrantLock();
    private State[] state = new State[5];

    public DiningTable() {
        for (int i = 0; i < 5; i++) {
            self[i] = lock.newCondition();
        }
    }

    public void takeForks(int i) {
        lock.lock();
        try {
            state[i] = State.hungry;
            test(i);
            if (state[i] != State.eating)
                self[i].await();
        } catch (InterruptedException ie) {
        } finally {
            lock.unlock();
        }
    }

    public void returnForks(int i) {
        lock.lock();
        state[i] = State.thinking;
        test((i + 4) % 5);
        test((i + 1) % 5);
        lock.unlock();
    }

    public void test(int i) {
        if ((state[(i + 4) % 5] != State.eating) && (state[i] == State.hungry)
                && (state[(i + 1) % 5] != State.eating)) {
            state[i] = State.eating;
            self[i].signal();
        }
    }
}