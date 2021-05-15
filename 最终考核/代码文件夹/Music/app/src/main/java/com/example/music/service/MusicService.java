package com.example.music.service;

import android.annotation.SuppressLint;
import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.text.TextUtils;
import android.widget.Button;

import com.example.music.Song;
import com.example.music.database.PlayListInfo;
import com.example.music.util.HttpUtil;

import org.jetbrains.annotations.NotNull;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class MusicService extends Service {

    private final String mp3Address = "http://neteasemusic.heyanle.com:3000/song/url?id=";
    private Button mSongInfo;
    private MediaPlayer player;
    private MusicControl mMusicControl;
    private Timer timer;
    private List<PlayListInfo> mPlayList;
    private String mSongNameArtists = null;
    private int mPosition;
    private int playerStatus = -1;
    private int mPlayMode = 0;

    //生成播放器和音乐控制器
    @Override
    public void onCreate() {
        super.onCreate();
        player = new MediaPlayer();
        mMusicControl = new MusicControl();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mMusicControl;
    }

    @Override
    //释放播放器资源
    public void onDestroy() {
        super.onDestroy();
        if (player == null) return;
        if (player.isPlaying()) player.stop();
        mPlayList.clear();
        player.release();
        player = null;
    }

    public class MusicControl extends Binder {
        //获取播放列表
        public void setSongInfo(Button songInfo) {
            mSongInfo = songInfo;
        }

        //播放
        @SuppressLint("SetTextI18n")
        public void play(String url) {
            try {
                player.reset();
                player.setDataSource(url);
                player.prepareAsync();
                player.setOnPreparedListener(mp -> player.start());
                if (mPlayMode == 0) {
                    player.setLooping(true);
                }
                if (mPlayMode == 1) {
                    player.setLooping(false);
                    player.setOnCompletionListener(mp -> {
                        mPosition++;
                        if (mPlayList.size() != 0) {
                            queryForMp3(mp3Address + mPlayList.get(mPosition % mPlayList.size()).getSongID());
                            mSongInfo.setText(mPlayList.get(mPosition % mPlayList.size()).getSongName() + "-" + mPlayList.get(mPosition % mPlayList.size()).getArtistsName());
                        }
                    });
                }
                playerStatus = 0;
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        //播放当前歌曲
        public void playList(int position) {
            mPosition = position;
            queryForMp3(mp3Address + mPlayList.get(position).getSongID());
        }

        //暂停播放
        public void pausePlay() {
            player.pause();
            playerStatus = 1;
        }

        //继续播放
        public void continuePlay() {
            player.start();
            playerStatus = 0;
        }

        //拖动进度条
        public void seekTo(int progress) {
            player.seekTo(progress);
        }

        //停止播放
        public void stopPlay() {
            player.stop();
        }

        //放回播放状态
        public int getPlayerStatus() {
            return playerStatus;
        }

        //获得歌曲信息
        public String getSongNameArtists() {
            mSongNameArtists = mPlayList.get(mPosition % mPlayList.size()).getSongName() + "-" + mPlayList.get(mPosition % mPlayList.size()).getArtistsName();
            return mSongNameArtists;
        }

        //获取播放列表
        public void setPlayList(List<PlayListInfo> playList) {
            mPlayList = playList;
        }

        //获取当前歌曲
        public int getPosition() {
            if (mPlayList.size() != 0) {
                return mPosition % mPlayList.size();
            }
            return 0;
        }

        //设置当前歌曲
        public void setPosition(int position) {
            mPosition = position;
        }

        public void addSong(PlayListInfo playListInfo) {
            mPlayList.add(playListInfo);
        }

        //下一首
        public void nextSong() {
            mPosition++;
            if (mPlayList.size() != 0) {
                stopPlay();
                queryForMp3(mp3Address + mPlayList.get(mPosition % mPlayList.size()).getSongID());
            }
        }

        //上一首
        public void beforeSong() {
            stopPlay();
            if (mPosition != 0)
                mPosition--;
            if (mPlayList.size() != 0)
                queryForMp3(mp3Address + mPlayList.get(mPosition % mPlayList.size()).getSongID());
        }

        //获取播放模式
        public int getPlayMode() {
            return mPlayMode;
        }

        //更换播放模式
        public void setPlayMode(int playMode) {
            mPlayMode = playMode;
        }

        //清空播放列表
        public void clear() {
            stopPlay();
            mPlayList.clear();
        }

        //歌曲总时长
        public void addTimer() {
            if (timer == null) {
                timer = new Timer();
                TimerTask task = new TimerTask() {
                    @Override
                    public void run() {
                        if (player == null) return;
                        int duration = player.getDuration();
                        int currentPosition = player.getCurrentPosition();
                        Message msg = Song.handler.obtainMessage();
                        Bundle bundle = new Bundle();
                        bundle.putInt("duration", duration);
                        bundle.putInt("currentPosition", currentPosition);
                        msg.setData(bundle);
                        Song.handler.sendMessage(msg);
                    }
                };
                timer.schedule(task, 5, 500);
            }
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
                    queryForMp3(mp3Address);
                }
            });
        }

        //处理歌曲url
        private void handleMp3JSON(String JSON) {
            if (!TextUtils.isEmpty(JSON)) {
                try {
                    JSONObject jsonObject = new JSONObject(JSON);
                    if (!TextUtils.isEmpty(jsonObject.getString("data"))) {
                        JSONArray jsonDataArray = new JSONArray(jsonObject.getString("data"));
                        if (!jsonDataArray.getJSONObject(0).getString("url").equals("null"))
                            play(jsonDataArray.getJSONObject(0).getString("url"));
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }
    }

}

