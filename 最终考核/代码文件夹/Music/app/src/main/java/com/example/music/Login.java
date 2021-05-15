package com.example.music;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class Login extends AppCompatActivity {
    private Button phoneLogin;
    private Button emailLogin;
    private String nickName;
    private byte[] responseText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        phoneLogin = findViewById(R.id.phone_login);
        emailLogin = findViewById(R.id.email_login);
        Intent intent = new Intent(Login.this, Password.class);
        phoneLogin.setOnClickListener(v -> {
            intent.putExtra("LoginWay", 1);
            startActivityForResult(intent, 1);
        });
        emailLogin.setOnClickListener(v -> {
            intent.putExtra("LoginWay", 2);
            startActivityForResult(intent, 2);
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            nickName = data.getStringExtra("NickName");
            responseText = data.getByteArrayExtra("ResponseText");
            Intent intent = new Intent();
            intent.putExtra("NickName", nickName);
            intent.putExtra("ResponseText", responseText);
            setResult(RESULT_OK, intent);
            finish();
        }
    }
}