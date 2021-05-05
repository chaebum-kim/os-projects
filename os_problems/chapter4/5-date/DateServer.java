import java.net.*;
import java.util.concurrent.*;
import java.io.*;

public class DateServer {
    public static void main(String[] args) {

        ExecutorService pool = Executors.newFixedThreadPool(5);

        try {
            ServerSocket sock = new ServerSocket(6013);
            // Listen for the connections
            while (true) {
                Socket client = sock.accept();
                // Services the client's request in a seperate thread
                pool.execute(new Date(client));
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

class Date implements Runnable {
    private final Socket client;

    public Date(Socket socket) {
        this.client = socket;
    }

    public void run() {
        try {
            PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
            // Write the Date to the socket
            pout.println(new java.util.Date().toString());

            client.close();
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}