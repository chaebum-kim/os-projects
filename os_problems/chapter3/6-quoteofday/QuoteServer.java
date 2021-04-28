import java.net.*;
import java.io.*;
import java.util.Random;
import java.util.ArrayList;

public class QuoteServer {
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(6017);

            // Listen for connections
            while (true) {
                Socket client = sock.accept();

                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

                // Write the quote of the day to the socket
                Quote.loadQuote();
                Quote quoteOfDay = new Quote();
                pout.println(quoteOfDay.randomQuote());

                // Close the socket and resume listening for the connections
                client.close();
            }

        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

class Quote {

    static ArrayList<String> quotes = new ArrayList<String>();

    public static void loadQuote() {
        try {
            BufferedReader bin = new BufferedReader(new FileReader("quotes.txt"));
            String line;

            while ((line = bin.readLine()) != null) {
                quotes.add(line);
            }
            bin.close();
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }

    public String randomQuote() {
        Random rand = new Random();
        return quotes.get(rand.nextInt(quotes.size()));
    }
}