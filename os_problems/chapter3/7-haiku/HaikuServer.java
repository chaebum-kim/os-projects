import java.net.*;
import java.io.*;
import java.util.Random;
import java.util.List;
import java.util.ArrayList;

public class HaikuServer {
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(5575);

            // Listen for the connections
            while (true) {
                Socket client = sock.accept();

                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

                // Write to the socket
                Haiku.loadHaiku();
                Haiku haiku = new Haiku();
                List<String> rand = haiku.randomHaiku();
                rand.forEach((line) -> {
                    pout.println(line);
                });

                // Close the socket and resume listening for the connections
                client.close();
            }

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

class Haiku {

    static List<List<String>> haikus = new ArrayList<List<String>>();

    public static void loadHaiku() {
        try {
            BufferedReader bin = new BufferedReader(new FileReader("haiku.txt"));
            List<String> haiku = new ArrayList<String>();
            String line;

            while ((line = bin.readLine()) != null) {
                if (line.isEmpty()) {
                    haikus.add(haiku);
                    haiku = new ArrayList<String>();
                } else {
                    haiku.add(line);
                }
            }
            bin.close();

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }

    public List<String> randomHaiku() {
        Random rand = new Random();
        return haikus.get(rand.nextInt(haikus.size()));
    }

}