import java.net.*;
import java.io.*;

public class HaikuClient {
    public static void main(String[] args) {
        try {
            // Make connection to server socket
            Socket sock = new Socket("127.0.0.1", 5575);

            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));

            // Read the data from the socket
            String line;
            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }

            // Close buffer
            bin.close();
            // CLose the socket connection
            sock.close();

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
