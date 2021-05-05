import java.net.*;
import java.io.*;
import java.util.concurrent.*;

public class EchoServer {
    public static void main(String[] args) {
        ExecutorService pool = Executors.newFixedThreadPool(5);

        try {
            ServerSocket sock = new ServerSocket(4828);

            // Listen for the connections
            while (true) {
                Socket client = sock.accept();
                // Service each client in a separate request
                pool.execute(new Echo(client));
            }

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

class Echo implements Runnable {
    private final Socket client;

    public Echo(Socket socket) {
        this.client = socket;
    }

    public void run() {
        try {
            int data;
            InputStream in = client.getInputStream();
            OutputStream out = client.getOutputStream();

            // Write to the socket
            while ((data = in.read()) != -1) {
                out.write(data);
            }
            // Close the socket
            client.close();

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}