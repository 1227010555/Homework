package com.example.music;

import android.animation.ObjectAnimator;
import android.annotation.SuppressLint;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.view.animation.LinearInterpolator;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.example.music.database.PlayListInfo;
import com.example.music.service.MusicService;

public class Song extends AppCompatActivity {

    @SuppressLint("StaticFieldLeak")
    private static SeekBar songSeekBar;
    @SuppressLint("StaticFieldLeak")
    private static TextView songProgress;
    @SuppressLint("StaticFieldLeak")
    private static TextView songTotal;
    //歌曲播放状况
    @SuppressLint("HandlerLeak")
    public static Handler handler = new Handler() {
        @SuppressLint("SetTextI18n")
        @Override
        public void handleMessage(Message msg) {
            Bundle bundle = msg.getData();
            int duration = bundle.getInt("duration");
            int currentPosition = bundle.getInt("currentPosition");
            songSeekBar.setMax(duration);
            songSeekBar.setProgress(currentPosition);
            int minute = duration / 1000 / 60;
            int second = duration / 1000 % 60;
            String strMinute;
            String strSecond;
            if (minute < 10) {
                strMinute = "0" + minute;
            } else {
                strMinute = minute + "";
            }
            if (second < 10) {
                strSecond = "0" + second;
            } else {
                strSecond = second + "";
            }
            songTotal.setText(strMinute + ":" + strSecond);
            minute = currentPosition / 1000 / 60;
            second = currentPosition / 1000 % 60;
            if (minute < 10) {
                strMinute = "0" + minute;
            } else {
                strMinute = minute + " ";
            }
            if (second < 10) {
                strSecond = "0" + second;
            } else {
                strSecond = second + " ";
            }
            songProgress.setText(strMinute + ":" + strSecond);
        }
    };
    PlayListInfo playListInfo;
    private ImageButton titleDown;
    private TextView titleSongName;
    private TextView titleArtistsName;
    private ImageView songCD;
    private ImageButton musicStartPause;
    private ImageButton musicNext;
    private ImageButton musicBefore;
    private ImageButton songPlayMode;
    private ObjectAnimator animator;
    private MusicService.MusicControl musicControl;
    private int i = 0;
    private final ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            musicControl = (MusicService.MusicControl) service;
            if (getIntent().getIntExtra("Check", 0) == 0) {
                musicControl.play(getIntent().getStringExtra("url"));
                musicControl.setPosition(i);
            }
            musicControl.addTimer();
            musicControl.addSong(playListInfo);
            if (musicControl.getPlayMode() == 0) {
                songPlayMode.setImageResource(R.drawable.circleplay);
            } else if (musicControl.getPlayMode() == 1) {
                songPlayMode.setImageResource(R.drawable.listplay);
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
        }
    };
    private int same = 0;

    @RequiresApi(api = Build.VERSION_CODES.KITKAT)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_song);
        //初始化
        songSeekBar = findViewById(R.id.song_seek_bar);
        songProgress = findViewById(R.id.song_progress);
        songTotal = findViewById(R.id.song_total);
        titleDown = findViewById(R.id.title_down);
        titleSongName = findViewById(R.id.title_song_name);
        titleArtistsName = findViewById(R.id.title_artists_name);
        songCD = findViewById(R.id.song_cd);
        musicStartPause = findViewById(R.id.music_control);
        musicNext = findViewById(R.id.music_next);
        musicBefore = findViewById(R.id.music_before);
        songPlayMode = findViewById(R.id.song_play_mode);
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(Song.this);
        SharedPreferences.Editor editor = prefs.edit();
        //绑定服务
        Intent intent = new Intent(Song.this, MusicService.class);
        bindService(intent, connection, MusicService.BIND_AUTO_CREATE);
        //退出
        titleDown.setOnClickListener(v -> finish());
        //设置标题
        titleSongName.setText(getIntent().getStringExtra("songName"));
        titleArtistsName.setText(getIntent().getStringExtra("artistsName"));
        //由活动Result启动Song,存储歌曲信息
        if (getIntent().getIntExtra("Check", 0) == 0) {
            for (i = 0; i < prefs.getInt("SongCount", 0); i++) {
                if (prefs.getString("SongID" + i, null).equals(getIntent().getStringExtra("SongID"))) {
                    same = 1;
                    break;
                }
            }
            if (same == 0) {
                i = 0;
                while (prefs.getString("SongID" + i, null) != null) {
                    i++;
                }
                editor.putString("SongName" + i, getIntent().getStringExtra("songName"));
                editor.putString("SongArtistsName" + i, getIntent().getStringExtra("artistsName"));
                editor.putString("SongID" + i, getIntent().getStringExtra("SongID"));
                editor.putInt("SongCount", prefs.getInt("SongCount", 0) + 1);
                editor.apply();
            }
        }
        playListInfo = new PlayListInfo(getIntent().getStringExtra("songName"), getIntent().getStringExtra("artistsName"), getIntent().getStringExtra("SongID"));
        //唱片动画
        animator = ObjectAnimator.ofFloat(songCD, "rotation", 0f, 360.0f);
        animator.setDuration(5000);
        animator.setInterpolator(new LinearInterpolator());
        animator.setRepeatCount(-1);
        animator.start();
        //拉动进度条播放
        songSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                musicControl.seekTo(progress);
            }
        });
        //音乐播放暂停
        musicStartPause.setOnClickListener(v -> {
            if (musicControl.getPlayerStatus() == 1) {
                musicControl.continuePlay();
                animator.start();
                musicStartPause.setImageResource(R.drawable.pause);
            } else if (musicControl.getPlayerStatus() == 0) {
                musicControl.pausePlay();
                animator.pause();
                musicStartPause.setImageResource(R.drawable.start);
            }
        });
        //下一首
        musicNext.setOnClickListener(v -> {
            musicControl.nextSong();
            animator.start();
            musicStartPause.setImageResource(R.drawable.pause);
        });
        //上一首
        musicBefore.setOnClickListener(v -> {
            musicControl.beforeSong();
            animator.start();
            musicStartPause.setImageResource(R.drawable.pause);
        });
        //切换播放模式
        songPlayMode.setOnClickListener(v -> {
            if (musicControl.getPlayMode() == 0) {
                musicControl.setPlayMode(1);
                songPlayMode.setImageResource(R.drawable.listplay);
            } else if (musicControl.getPlayMode() == 1) {
                musicControl.setPlayMode(0);
                songPlayMode.setImageResource(R.drawable.circleplay);
            }
        });
    }

    //解绑服务
    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(connection);
    }
}