package com.example.music;

import android.content.Intent;
import android.graphics.ImageFormat;
import android.os.Bundle;
import android.text.InputType;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.music.util.HttpUtil;

import org.jetbrains.annotations.NotNull;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class Password extends AppCompatActivity {
    private ImageButton leftArrow;
    private TextView loginWay;
    private EditText loginName;
    private EditText loginPassword;
    private Button login;
    private String loginAddress;
    private String userName;
    private String password;
    private String nickName;
    private int loginWayStatus;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_password);
        leftArrow = findViewById(R.id.left_arrow);
        loginWay = findViewById(R.id.login_way);
        loginName = findViewById(R.id.login_name);
        loginPassword = findViewById(R.id.login_password);
        login = findViewById(R.id.login);
        leftArrow.setOnClickListener(v -> finish());
        loginWayStatus = getIntent().getIntExtra("LoginWay", 0);
        if (loginWayStatus == 1) {
            loginWay.setText("手机登录");
            loginName.setHint("请输入手机号");
            loginAddress = "http://neteasemusic.heyanle.com:3000/login/cellphone?phone=";
        } else if (loginWayStatus == 2) {
            loginWay.setText("网易邮箱登录");
            loginName.setHint("请输入邮箱账号");
            loginAddress = "http://neteasemusic.heyanle.com:3000/login?email=";
        }
        login.setOnClickListener(v -> {
            userName = loginName.getText().toString();
            password = loginPassword.getText().toString();
            if (loginWayStatus == 1) {
                queryForUser(loginAddress + userName + "&password=" + password);
            } else if (loginWayStatus == 2) {
                queryForUser(loginAddress + userName + "&password=" + password);
            }
        });
    }

    //获取用户信息
    private void queryForUser(String bannerAddress) {
        HttpUtil.sendOkHttpRequest(bannerAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String responseText = response.body().string();
                handleUserJSON(responseText);
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForUser(bannerAddress));
            }
        });
    }

    //处理用户信息的JSON数据
    private void handleUserJSON(String JSON) {
        runOnUiThread(() -> {
            if (!TextUtils.isEmpty(JSON)) {
                try {
                    JSONObject jsonObject = new JSONObject(JSON);
                    if (jsonObject.getString("code").equals("502")) {
                        Toast.makeText(Password.this,
                                "密码错误", Toast.LENGTH_SHORT).show();
                    } else if (jsonObject.getString("code").equals("400")) {
                        Toast.makeText(Password.this,
                                "用户不存在或请输入密码", Toast.LENGTH_SHORT).show();
                    } else if (!TextUtils.isEmpty(jsonObject.getString("profile"))) {
                        JSONObject jsonProfileObject = new JSONObject(jsonObject.getString("profile"));
                        nickName = jsonProfileObject.getString("nickname");
                        queryForImg(jsonProfileObject.getString("avatarUrl"));
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    //获取用户信息的图片并处理，然后返回
    private void queryForImg(String imgAddress) {
        HttpUtil.sendOkHttpRequest(imgAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                byte[] responseText = response.body().bytes();
                runOnUiThread(() -> {
                    Intent intent = new Intent();
                    intent.putExtra("NickName", nickName);
                    intent.putExtra("ResponseText", responseText);
                    setResult(RESULT_OK, intent);
                    finish();
                });
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForImg(imgAddress));
            }
        });
    }
}