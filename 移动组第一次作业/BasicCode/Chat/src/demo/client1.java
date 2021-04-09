package demo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;

public class client1 {
    public static void main(String[] args) throws IOException {
        Socket client = new Socket("127.0.0.1", 1200);
        System.out.println("连接服务器成功！");
        Scanner sc = new Scanner(System.in);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String userName = null;
        int state = 0;
        String choice;
        while (true) {
            while (state == 0) {
                System.out.println("欢迎使用聊天软件");
                System.out.println("1.登录");
                System.out.println("2.退出");
                choice = sc.next();
                switch (choice) {
                    case "1": {
                        System.out.println("请输入用户名");
                        userName = br.readLine();
                        state = 1;
                        break;
                    }
                    case "2": {
                        System.out.println("退出");
                        client.close();//关闭套接字
                        return;
                    }
                }
            }
            if (state==1) {
                System.out.println("开始聊天吧!");
                System.out.println("聊天格式 xxx:abaaba");
                new Thread(new Send(client, userName)).start();
                new Thread(new Receive(client)).start();
            }
            while(true);
        }
    }
}





