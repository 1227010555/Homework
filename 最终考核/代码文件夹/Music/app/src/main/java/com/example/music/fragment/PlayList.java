package com.example.music.fragment;

import android.annotation.SuppressLint;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.IBinder;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.R;
import com.example.music.Song;
import com.example.music.adapter.PlayFragmentAdapter;
import com.example.music.database.PlayListInfo;
import com.example.music.service.MusicService;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.List;

public class PlayList extends Fragment {

    private final List<PlayListInfo> playListInfos = new ArrayList<>();
    private final LinearLayoutManager layoutManager = new LinearLayoutManager(getActivity());
    private final PlayFragmentAdapter adapter = new PlayFragmentAdapter(playListInfos);
    private TextView playModeName;
    private Button songInfo;
    private ImageButton control;
    private ImageButton openList;
    private ImageButton playDelete;
    private ImageButton playMode;
    private RecyclerView playList;
    private MusicService.MusicControl musicControl;
    private int listStatus = 0;
    private int playModeStatus;
    //连接服务调用
    private final ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            musicControl = (MusicService.MusicControl) service;
            //将播放列表交给服务
            musicControl.setPlayList(playListInfos);
            musicControl.setSongInfo(songInfo);
            //根据播放状况设置
            if (playModeStatus == 0) {
                musicControl.setPlayMode(0);
                playMode.setImageResource(R.drawable.circleplay);
                playModeName.setText("单曲循环");
            } else if (playModeStatus == 1) {
                musicControl.setPlayMode(1);
                playMode.setImageResource(R.drawable.listplay);
                playModeName.setText("列表播放");
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
        }
    };
    private int i;
    private int position;

    public View onCreateView(@NonNull @NotNull LayoutInflater inflater, @Nullable @org.jetbrains.annotations.Nullable ViewGroup container, @Nullable @org.jetbrains.annotations.Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.play_list, container, false);
    }

    @SuppressLint("SetTextI18n")
    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(getActivity());
        SharedPreferences.Editor editor = prefs.edit();
        //初始化
        playModeName = getActivity().findViewById(R.id.play_mode_name);
        songInfo = getActivity().findViewById(R.id.song_info);
        control = getActivity().findViewById(R.id.control);
        openList = getActivity().findViewById(R.id.open_list);
        playDelete = getActivity().findViewById(R.id.play_delete);
        playMode = getActivity().findViewById(R.id.play_mode);
        playList = getActivity().findViewById(R.id.play_list);
        playModeName.setVisibility(View.INVISIBLE);
        playDelete.setVisibility(View.INVISIBLE);
        playMode.setVisibility(View.INVISIBLE);
        playList.setVisibility(View.INVISIBLE);
        //读取播放列表
        for (i = 0; i < prefs.getInt("SongCount", 0); i++) {
            if (prefs.getString("SongName" + i, null) != null) {
                PlayListInfo playListInfo = new PlayListInfo(prefs.getString("SongName" + i, null),
                        prefs.getString("SongArtistsName" + i, null),
                        prefs.getString("SongID" + i, null));
                playListInfos.add(playListInfo);
            }
        }
        //获取上次关闭的状态
        playModeStatus = prefs.getInt("PlayMode", 0);
        position = prefs.getInt("Position", 0);
        if (position != 0)
            songInfo.setText(playListInfos.get(position).getSongName() + "-"
                    + playListInfos.get(position).getArtistsName());
        //连接服务
        Intent intent = new Intent(getActivity(), MusicService.class);
        getActivity().bindService(intent, connection, MusicService.BIND_AUTO_CREATE);
        //音乐播放暂停
        control.setOnClickListener(v -> {
            if (musicControl.getPlayerStatus() == 0) {
                control.setImageResource(R.drawable.start);
                musicControl.pausePlay();
            } else if (musicControl.getPlayerStatus() == 1) {
                control.setImageResource(R.drawable.pause);
                musicControl.continuePlay();
            }
        });
        //点歌
        adapter.setOnClick((position, songInfo) -> {
            this.songInfo.setText(songInfo);
            musicControl.playList(position);
            control.setImageResource(R.drawable.pause);
            if (songInfo == null) {
                playListInfos.remove(position);
                musicControl.setPlayList(playListInfos);
            }
        });
        //打开播放列表
        openList.setOnClickListener(v -> {
            if (listStatus == 0) {
                playList.setVisibility(View.VISIBLE);
                playMode.setVisibility(View.VISIBLE);
                playDelete.setVisibility(View.VISIBLE);
                playModeName.setVisibility(View.VISIBLE);
                playList.setLayoutManager(layoutManager);
                playList.setAdapter(adapter);
                listStatus = 1;
            } else if (listStatus == 1) {
                playList.setVisibility(View.INVISIBLE);
                playMode.setVisibility(View.INVISIBLE);
                playModeName.setVisibility(View.INVISIBLE);
                playDelete.setVisibility(View.INVISIBLE);
                listStatus = 0;
            }
        });
        //清除播放列表
        playDelete.setOnClickListener(v -> {
            for (i = 0; i < prefs.getInt("SongCount", 0); i++) {
                if (prefs.getString("SongName" + i, null) != null) {
                    editor.remove("SongName" + i);
                    editor.remove("SongArtistsName" + i);
                    editor.remove("SongID" + i);
                }
            }
            editor.remove("SongCount");
            editor.putInt("Position", 0);
            editor.apply();
            playListInfos.clear();
            musicControl.clear();
            musicControl.stopPlay();
            songInfo.setText("");
            playList.setLayoutManager(layoutManager);
            playList.setAdapter(adapter);
        });
        //切换播放模式
        playMode.setOnClickListener(v -> {
            if (musicControl.getPlayMode() == 0) {
                musicControl.setPlayMode(1);
                playMode.setImageResource(R.drawable.listplay);
                playModeName.setText("列表播放");
            } else if (musicControl.getPlayMode() == 1) {
                musicControl.setPlayMode(0);
                playMode.setImageResource(R.drawable.circleplay);
                playModeName.setText("单曲循环");
            }
        });
        //查看歌曲详情
        songInfo.setOnClickListener(v -> {
            Intent intent1 = new Intent(getActivity(), Song.class);
            if (!songInfo.getText().equals("")) {
                position = musicControl.getPosition();
                intent1.putExtra("songName", playListInfos.get(position).getSongName());
                intent1.putExtra("artistsName", playListInfos.get(position).getArtistsName());
                intent1.putExtra("Check", 1);
                startActivity(intent1);
            }
        });
    }

    @Override
    public void onResume() {
        super.onResume();
        //搜索完读取播放列表并设置底部信息
        if (musicControl != null)
            if (musicControl.getPlayerStatus() == 0) {
                playListInfos.clear();
                SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(getActivity());
                for (i = 0; i < prefs.getInt("SongCount", 0); i++) {
                    if (prefs.getString("SongName" + i, null) != null) {
                        PlayListInfo playListInfo = new PlayListInfo(prefs.getString("SongName" + i, null),
                                prefs.getString("SongArtistsName" + i, null),
                                prefs.getString("SongID" + i, null));
                        playListInfos.add(playListInfo);
                    }
                }
                musicControl.setPlayList(playListInfos);
                control.setImageResource(R.drawable.pause);
                songInfo.setText(musicControl.getSongNameArtists());
            }
        if (musicControl != null) {
            if (musicControl.getPlayMode() == 0) {
                playMode.setImageResource(R.drawable.circleplay);
            } else if (musicControl.getPlayMode() == 1) {
                playMode.setImageResource(R.drawable.listplay);
            }
        }
    }

    @Override
    public void onStop() {
        super.onStop();
        //保存播放模式和播放位置且关闭服务
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(getActivity());
        SharedPreferences.Editor editor = prefs.edit();
        position = musicControl.getPosition();
        editor.putInt("PlayMode", musicControl.getPlayMode());
        editor.apply();
    }
}