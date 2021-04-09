package demo;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;

//接受端
class Receive implements Runnable {
    private DataInputStream in;
    private Socket client;
    private boolean running = true;

    public Receive(Socket client) {
        this.client = client;
        try {
            in = new DataInputStream(client.getInputStream());
        } catch (IOException e) {
            release();
        }
    }

    public void run() {
        while(true){
            String message = receive();
            if (!message.equals(" ")) {
                System.out.println(message);
            }
        }
    }

    private String receive() {
        String message = " ";
        try {
            message = in.readUTF();
        } catch (IOException e) {
            release();
        }
        return message;
    }

    private void release() {
        this.running = false;
        until.close(in, client);
    }
}