package demo;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStreamReader;

public class until {
    public static void close(Closeable... targets) {
        for (Closeable target : targets) {
            try {
                if (target != null)
                    target.close();
            } catch (
                    IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static String getStr() {
        BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
        try {
            return console.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return " ";
    }
}
