import java.net.*;
import java.io.*;

public class EchoServer {
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(4828);

            // Listen for the connections
            while (true) {
                Socket client = sock.accept();

                int data;
                InputStream in = client.getInputStream();
                OutputStream out = client.getOutputStream();

                // Write to the socket
                while ((data = in.read()) != -1) {
                    out.write(data);
                }

                // Close the socket and resume listening for the connections
                client.close();
            }

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
