package com.example.music;

import android.animation.ObjectAnimator;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.animation.LinearInterpolator;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.adapter.ResultAdapter;
import com.example.music.database.SongInfo;
import com.example.music.util.HttpUtil;

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

public class Result extends AppCompatActivity {

    private final List<SongInfo> songInfos = new ArrayList<>();
    private final LinearLayoutManager layoutManager = new LinearLayoutManager(Result.this);
    private final ResultAdapter adapter = new ResultAdapter(songInfos);
    private final String mp3Address = "http://neteasemusic.heyanle.com:3000/song/url?id=";
    private ImageView resultFlush;
    private Button resultTitleEdit;
    private ImageButton titleLeftArrow;
    private RecyclerView resultView;
    private ObjectAnimator animator;
    private int i = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);
        //初始化
        resultFlush = findViewById(R.id.result_flush);
        resultTitleEdit = findViewById(R.id.result_title_edit);
        titleLeftArrow = findViewById(R.id.title_left_arrow);
        resultView = findViewById(R.id.recyclerview);
        //退出
        titleLeftArrow.setOnClickListener(v -> finish());
        //获取搜索结果
        queryForSong(getIntent().getStringExtra("address"));
        //重新搜索，启动活动Suggestion,获取搜索内容
        resultTitleEdit.setOnClickListener(v -> {
            Intent intent = new Intent(Result.this, Suggestion.class);
            intent.putExtra("classname", "Result");
            startActivityForResult(intent, 1);
        });
        //加载
        animator = ObjectAnimator.ofFloat(resultFlush, "rotation", 0f, 360.0f);
        animator.setDuration(1000);
        animator.setInterpolator(new LinearInterpolator());
        animator.setRepeatCount(-1);
        animator.start();
        //音乐无法播放
        adapter.setOnClick(() -> Toast.makeText(Result.this, "歌曲暂时无法播放", Toast.LENGTH_SHORT).show());
    }

    //清空适配器，将得到的搜索内容进行搜索
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            adapter.clear();
            queryForSong(data.getStringExtra("address"));
        }
    }

    //获取歌曲信息
    private void queryForSong(String songAddress) {
        HttpUtil.sendOkHttpRequest(songAddress, new Callback() {
            @RequiresApi(api = Build.VERSION_CODES.KITKAT)
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String responseText = response.body().string();
                handleJSON(responseText);
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForSong(songAddress));
            }
        });
    }

    //处理歌曲信息的JSON数据
    @RequiresApi(api = Build.VERSION_CODES.KITKAT)
    private void handleJSON(String Json) {
        runOnUiThread(() -> {
            if (!TextUtils.isEmpty(Json)) {
                String songName;
                String artistsName = null;
                String albumName = null;
                String songId;
                String url = null;
                try {
                    JSONObject jsonObject = new JSONObject(Json);
                    if (!TextUtils.isEmpty(jsonObject.getString("result"))) {
                        JSONObject jsonResultObject = new JSONObject(jsonObject.getString("result"));
                        if (!TextUtils.isEmpty(jsonResultObject.getString("songs"))) {
                            JSONArray jsonSongsArray = new JSONArray(jsonResultObject.getString("songs"));
                            for (i = 0; i < jsonSongsArray.length(); i++) {
                                JSONObject jsonSongObject = jsonSongsArray.getJSONObject(i);
                                songName = jsonSongObject.getString("name");
                                songId = jsonSongObject.getString("id");
                                if (!TextUtils.isEmpty(jsonSongObject.getString("artists")) &&
                                        !TextUtils.isEmpty(jsonSongObject.getString("album"))) {
                                    JSONArray jsonArtistsObject = new JSONArray(jsonSongObject.getString("artists"));
                                    JSONObject jsonAlbumObject = new JSONObject(jsonSongObject.getString("album"));
                                    artistsName = jsonArtistsObject.getJSONObject(0).getString("name");
                                    albumName = jsonAlbumObject.getString("name");
                                }
                                SongInfo songInfo = new SongInfo(songName, artistsName, albumName, songId, url);
                                songInfos.add(songInfo);
                                animator.pause();
                                resultFlush.setVisibility(View.INVISIBLE);
                            }
                            for (i = 0; i < songInfos.size(); i++) {
                                queryForMp3(mp3Address + songInfos.get(i).getSongId());
                            }
                        }
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    //获取歌曲url
    private void queryForMp3(String mp3Address) {
        HttpUtil.sendOkHttpRequest(mp3Address, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String responseText = response.body().string();
                handleMp3JSON(responseText);
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForSong(mp3Address));
            }
        });
    }

    //处理歌曲url的JSON数据
    private void handleMp3JSON(String JSON) {
        runOnUiThread(() -> {
            if (!TextUtils.isEmpty(JSON)) {
                try {
                    JSONObject jsonObject = new JSONObject(JSON);
                    if (!TextUtils.isEmpty(jsonObject.getString("data"))) {
                        JSONArray jsonDataArray = new JSONArray(jsonObject.getString("data"));
                        if (!jsonDataArray.getJSONObject(0).getString("url").equals("null"))
                            for (i = 0; i < songInfos.size(); i++)
                                if (jsonDataArray.getJSONObject(0).getString("id").equals(songInfos.get(i).getSongId())) {
                                    songInfos.get(i).setUrl(jsonDataArray.getJSONObject(0).getString("url"));
                                    resultView.setLayoutManager(layoutManager);
                                    resultView.setAdapter(adapter);
                                    break;
                                }
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }
}