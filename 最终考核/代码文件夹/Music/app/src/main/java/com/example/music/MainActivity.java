package com.example.music;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.SystemClock;
import android.text.TextUtils;
import android.util.Base64;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.StaggeredGridLayoutManager;
import androidx.viewpager2.widget.ViewPager2;

import com.example.music.adapter.BannerAdapter;
import com.example.music.adapter.NewSongAdapter;
import com.example.music.database.BannerInfo;
import com.example.music.database.NewSongInfo;
import com.example.music.service.MusicService;
import com.example.music.util.HttpUtil;
import com.example.music.view.Dots;

import org.jetbrains.annotations.NotNull;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity {

    private Button searchFrame;
    private Button userName;
    private Button exitLogin;
    private Button closeApp;
    private ImageView userImg;
    private ImageButton menu;
    private ImageButton musicRecognition;
    private ViewPager2 banners;
    private RecyclerView newSong;
    private DrawerLayout drawerLayout;
    private Dots dot;
    private List<BannerInfo> bannerInfos = new ArrayList<>();
    private List<NewSongInfo> newSongInfos = new ArrayList<>();
    private BannerAdapter bannerAdapter = new BannerAdapter(bannerInfos);
    private NewSongAdapter newSongadapter = new NewSongAdapter(newSongInfos);
    private String bannerAddress = "http://neteasemusic.heyanle.com:3000/banner?type=1";
    private String newSongAddress = "http://neteasemusic.heyanle.com:3000/top/song";
    private String nickName;
    private byte[] responseText;
    private Bitmap img;
    private int i;
    private int currentItem = 0;
    private boolean isTouching = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //初始化
        searchFrame = findViewById(R.id.title_search_frame);
        userName = findViewById(R.id.user_name);
        exitLogin = findViewById(R.id.exit_login);
        closeApp = findViewById(R.id.close_app);
        userImg = findViewById(R.id.user_img);
        menu = findViewById(R.id.title_menu);
        musicRecognition = findViewById(R.id.title_music_recognition);
        banners = findViewById(R.id.banners);
        newSong = findViewById(R.id.new_song);
        drawerLayout = findViewById(R.id.drawer_layout);
        dot = findViewById(R.id.dot);
        dot.setVisibility(View.INVISIBLE);
        exitLogin.setVisibility(View.INVISIBLE);
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(MainActivity.this);
        SharedPreferences.Editor editor = prefs.edit();
        //读取登录信息
        if (prefs.getString("NickName", null) != null) {
            userName.setText(prefs.getString("NickName", null));
            responseText = Base64.decode(prefs.getString("Img", null).getBytes(), Base64.DEFAULT);
            img = BitmapFactory.decodeByteArray(responseText, 0, responseText.length);
            userImg.setImageBitmap(img);
            exitLogin.setVisibility(View.VISIBLE);
        }
        //打开菜单
        menu.setOnClickListener(v -> drawerLayout.openDrawer(GravityCompat.START));
        userName.setOnClickListener(v -> {
            if (userName.getText().equals("立即登录 >")) {
                Intent intent = new Intent(MainActivity.this, Login.class);
                startActivityForResult(intent, 1);
            }
        });
        //退出登录
        exitLogin.setOnClickListener(v -> {
            if (!userName.getText().equals("立即登录 >")) {
                editor.remove("NickName");
                editor.remove("Img");
                editor.apply();
                userImg.setImageResource(R.drawable.user);
                userName.setText("立即登录 >");
                exitLogin.setVisibility(View.INVISIBLE);
            }
        });
        //关闭应用
        closeApp.setOnClickListener(v -> finish());
        //搜索，启动活动search
        searchFrame.setOnClickListener(v -> {
            Intent intent = new Intent(this, Search.class);
            startActivityForResult(intent, 1);
        });
        //功能开发中...
        musicRecognition.setOnClickListener(v -> Toast.makeText(MainActivity.this,
                "功能尚未开放，敬请期待", Toast.LENGTH_SHORT).show());
        //获取banner和新歌速递
        queryForBanner(bannerAddress);
        queryForNewSong(newSongAddress);
        //判断滑动，来确定是否自动轮播
        banners.registerOnPageChangeCallback(new ViewPager2.OnPageChangeCallback() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
                super.onPageScrolled(position, positionOffset, positionOffsetPixels);
                isTouching = true;
                dot.setOffSet(position, positionOffset);
            }

            @Override
            public void onPageSelected(int position) {
                super.onPageSelected(position);
                isTouching = false;
            }

            @Override
            public void onPageScrollStateChanged(int state) {
                super.onPageScrollStateChanged(state);
                isTouching = false;
            }
        });
        //自动轮播
        autoPlay();
        //无法播放的歌曲提示
        newSongadapter.setOnClick(() -> Toast.makeText(MainActivity.this,
                "歌曲暂时无法播放", Toast.LENGTH_SHORT).show());
        bannerAdapter.setOnClick(() -> Toast.makeText(MainActivity.this,
                "暂时无法打开", Toast.LENGTH_SHORT).show());
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            nickName = data.getStringExtra("NickName");
            responseText = data.getByteArrayExtra("ResponseText");
            img = BitmapFactory.decodeByteArray(responseText, 0, responseText.length);
            userImg.setImageBitmap(img);
            userName.setText(nickName);
            exitLogin.setVisibility(View.VISIBLE);
            String imageString = new String(Base64.encode(responseText, Base64.DEFAULT));
            SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(MainActivity.this);
            SharedPreferences.Editor editor = prefs.edit();
            editor.putString("NickName", nickName);
            editor.putString("Img", imageString);
            editor.apply();
        }
    }

    //获取banner
    private void queryForBanner(String bannerAddress) {
        HttpUtil.sendOkHttpRequest(bannerAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String responseText = response.body().string();
                handleBannerJSON(responseText);
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForBanner(bannerAddress));
            }
        });
    }

    //处理banner的JSON数据
    private void handleBannerJSON(String JSON) {
        runOnUiThread(() -> {
            JSONObject jsonBannerObject;
            if (!TextUtils.isEmpty(JSON)) {
                try {
                    JSONObject jsonObject = new JSONObject(JSON);
                    if (!TextUtils.isEmpty(jsonObject.getString("banners"))) {
                        JSONArray jsonBannersArray = new JSONArray(jsonObject.getString("banners"));
                        for (i = 0; i < jsonBannersArray.length(); i++) {
                            jsonBannerObject = jsonBannersArray.getJSONObject(i);
                            queryForImg(jsonBannerObject.getString("pic"), jsonBannerObject.getString("url"));
                        }
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    //获取banner的图片并处理，然后在屏幕加载
    private void queryForImg(String imgAddress, String url) {
        HttpUtil.sendOkHttpRequest(imgAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                byte[] responseText = response.body().bytes();
                Bitmap bitmap = BitmapFactory.decodeByteArray(responseText, 0, responseText.length);
                BannerInfo bannerInfo = new BannerInfo(bitmap, url);
                bannerInfos.add(bannerInfo);
                runOnUiThread(() -> {
                    banners.setAdapter(bannerAdapter);
                    dot.setVisibility(View.VISIBLE);
                });
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForImg(imgAddress, url));
            }
        });
    }

    //获取新歌速递
    private void queryForNewSong(String newSongAddress) {
        HttpUtil.sendOkHttpRequest(newSongAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String responseText = response.body().string();
                handleNewSongJSON(responseText);
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForBanner(newSongAddress));
            }
        });
    }

    //处理新歌速递的JSON数据
    private void handleNewSongJSON(String JSON) {
        runOnUiThread(() -> {
            JSONObject jsonNewSongObject;
            if (!TextUtils.isEmpty(JSON)) {
                try {
                    JSONObject jsonObject = new JSONObject(JSON);
                    if (!TextUtils.isEmpty(jsonObject.getString("data"))) {
                        JSONArray jsonNewSongsArray = new JSONArray(jsonObject.getString("data"));
                        for (i = 0; i < 4; i++) {
                            jsonNewSongObject = jsonNewSongsArray.getJSONObject(i);
                            JSONArray jsonArtistsArray = new JSONArray(jsonNewSongObject.getString("artists"));
                            JSONObject jsonimgObject = new JSONObject(jsonNewSongObject.getString("album"));
                            queryForNewSongImg(jsonimgObject.getString("blurPicUrl"),
                                    jsonNewSongObject.getString("id"),
                                    jsonNewSongObject.getString("name")
                                    , jsonArtistsArray.getJSONObject(0).getString("name"));
                        }
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    //获取新歌速递的图片并处理，然后在屏幕加载
    private void queryForNewSongImg(String imgAddress, String id, String songName, String artistsName) {
        HttpUtil.sendOkHttpRequest(imgAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                byte[] responseText = response.body().bytes();
                Bitmap bitmap = BitmapFactory.decodeByteArray(responseText, 0, responseText.length);
                NewSongInfo newSongInfo = new NewSongInfo(bitmap, id, songName, artistsName);
                newSongInfos.add(newSongInfo);
                runOnUiThread(() -> {
                    StaggeredGridLayoutManager layoutManager = new StaggeredGridLayoutManager(2, StaggeredGridLayoutManager.HORIZONTAL);
                    newSong.setLayoutManager(layoutManager);
                    newSong.setAdapter(newSongadapter);
                });
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForNewSongImg(imgAddress, id, songName, artistsName));
            }
        });
    }

    //通过Thread的sleep从而实现轮播
    private void autoPlay() {
        new Thread() {
            @Override
            public void run() {
                super.run();
                //轮播间隔时间
                while (true) {
                    if (!isTouching) {
                        SystemClock.sleep(5 * 1000);
                        runOnUiThread(() -> {
                            currentItem = banners.getCurrentItem() + 1;
                            if (bannerInfos.size() != 0 && !isTouching)
                                banners.setCurrentItem(currentItem % bannerInfos.size());
                        });
                    }
                }
            }
        }.start();
    }

    //当主界面Stop，即程序关闭，结束service，以节省内存
    @Override
    protected void onStop() {
        super.onStop();
        Intent intent = new Intent(this, MusicService.class);
        stopService(intent);
    }
}