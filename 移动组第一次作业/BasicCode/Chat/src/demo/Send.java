package demo;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

//发送端
class Send implements Runnable {
    private DataOutputStream out;
    private Socket client;
    private boolean running = true;
    private String userName;

    public Send(Socket client,String userName) {
        this.client = client;
        this.userName=userName;
        try {
            out = new DataOutputStream(client.getOutputStream());
            send(userName);
        } catch (IOException e) {
            release();
        }
    }

    public void run() {
        while(true){
            String message = until.getStr();
            if (!message.equals(" ")) {
                send(message);
            }
        }
    }

    private void send(String message) {
        try {
            out.writeUTF(message);
            out.flush();
        } catch (IOException e) {
            release();
        }
    }

    private void release() {
        this.running = false;
        until.close(out, client);
    }
}
