import java.net.*;
import java.io.*;
import java.util.Random;
import java.util.List;
import java.util.ArrayList;

public class HaikuServer {
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(5575);
            Haiku.loadHaiku();

            // Listen for the connections
            while (true) {
                Socket client = sock.accept();

                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

                // Write to the socket
                Haiku haiku = new Haiku();
                pout.println(haiku.randomHaiku());

                // Close the socket and resume listening for the connections
                client.close();
            }

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

class Haiku {

    static List<String> haikus = new ArrayList<String>();

    public static void loadHaiku() {
        try {
            BufferedReader bin = new BufferedReader(new FileReader("haiku.txt"));
            String haiku = "";
            String line;

            while ((line = bin.readLine()) != null) {
                if (line.isEmpty()) {
                    haikus.add(haiku);
                    haiku = "";
                } else {
                    haiku += line;
                    haiku += "\n";
                }
            }
            bin.close();

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }

    public String randomHaiku() {
        Random rand = new Random();
        return haikus.get(rand.nextInt(haikus.size()));
    }

}