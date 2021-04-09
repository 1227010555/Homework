package demo;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.CopyOnWriteArrayList;


public class serve {
    private static CopyOnWriteArrayList<Clients> clients = new CopyOnWriteArrayList<Clients>();

    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(1200);
        System.out.println("服务器启动成功，等待用户接入…");

        while (true) {
            Socket client = server.accept();        // 等待用户接入，直到有用户接入为止，Socket对象表示客户端
            System.out.println("客户端接入，客户IP：" + client.getInetAddress());// 获得接入客户端的IP地址
            Clients c = new Clients(client);
            clients.add(c);
            new Thread(c).start();
        }
    }

    static class Clients implements Runnable {
        private DataInputStream in;
        private DataOutputStream out;
        private Socket client;
        private boolean running = true;
        private String userName;

        public Clients(Socket client) {
            this.client = client;
            try {
                in = new DataInputStream(client.getInputStream());
                out = new DataOutputStream(client.getOutputStream());
                this.userName=receive();
            } catch (IOException e) {
                release();
            }
        }

        //接收消息
        private String receive() {
            String message = " ";
            try {
                message = in.readUTF();
            } catch (IOException e) {
                release();
            }
            return message;
        }

        private void send(String message) {
            try {
                out.writeUTF(message);
            } catch (IOException e) {
                release();
            }
        }

        //发送消息
        private void sendSomeone(String message) {
            String targetName = message.substring(0, message.indexOf(":"));
            message = message.substring(message.indexOf(":") + 1);
            for (Clients other : clients) {
                if (other.userName.equals(targetName)) {
                    other.send(this.userName + "对你说:" + message);
                }
            }
        }

        //释放资源
        private void release() {
            this.running = false;
            until.close(in, out, client);
        }

        public void run() {
            while (running) {
                String message = receive();
                if (!message.equals(" ")) {
                    sendSomeone(message);
                }
            }
        }
    }
}