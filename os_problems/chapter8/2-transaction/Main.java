
import java.util.concurrent.locks.*;

public class Main {
    public static void main(String[] args) {

        // Make accounts
        Account alice = new Account("Alice", 10000.0);
        Account brian = new Account("Brian", 10000.0);

        // Make transactions
        Thread threadA = new Thread(new Transaction(alice, brian, 1000.0));
        Thread threadB = new Thread(new Transaction(brian, alice, 500.0));

        threadA.start();
        threadB.start();

        try {
            threadA.join();
            threadB.join();
        } catch (InterruptedException ie) {
        }

        System.out.printf("Alice's balance: %.1f\n", alice.balance);
        System.out.printf("Brian's balance: %.1f\n", brian.balance);

    }
}

class Account {
    String name;
    double balance;
    Lock lock = new ReentrantLock();

    public Account(String name, double balance) {
        this.name = name;
        this.balance = balance;
    }

    public double withdraw(double amount) {
        balance -= amount;
        return balance;
    }

    public double deposit(double amount) {
        balance += amount;
        return balance;
    }
}

class Transaction implements Runnable {
    Account from, to;
    double amount;

    public Transaction(Account from, Account to, double amount) {
        this.from = from;
        this.to = to;
        this.amount = amount;
    }

    public void run() {
        try {
            // Get the hash code of account objects
            int hashFrom = System.identityHashCode(from);
            int hashTo = System.identityHashCode(to);

            // Get the lock of account with smaller hash code first.
            if (hashFrom < hashTo) {
                from.lock.lock();
                to.lock.lock();
            } else {
                to.lock.lock();
                from.lock.lock();
            }

            from.withdraw(amount);
            to.deposit(amount);

            System.out.printf("%s Sent $%.1f to %s.\n", from.name, amount, to.name);

        } finally {
            from.lock.unlock();
            to.lock.unlock();
        }
    }
}