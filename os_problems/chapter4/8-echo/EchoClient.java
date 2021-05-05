import java.net.*;
import java.io.*;
import java.util.Scanner;

public class EchoClient {
    public static void main(String[] args) {
        try {
            // Make connection to the server socket
            Socket sock = new Socket("127.0.0.1", 4828);

            Scanner scanner = new Scanner(System.in);

            while (scanner.hasNextLine()) {

                String input = scanner.nextLine();

                // Wrtie the user input to the socket
                PrintWriter pout = new PrintWriter(sock.getOutputStream(), true);
                pout.println(input);

                // Read the data from the socket
                InputStream in = sock.getInputStream();
                BufferedReader bin = new BufferedReader(new InputStreamReader(in));
                System.out.println(bin.readLine());
            }

            scanner.close();

            // Close the socket connection
            sock.close();

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
