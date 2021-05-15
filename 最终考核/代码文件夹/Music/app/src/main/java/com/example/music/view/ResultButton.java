package com.example.music.view;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.example.music.R;

//搜索结果的button，为了实现大小不一的字体
public class ResultButton extends RelativeLayout {

    public TextView songName;
    public TextView songArtistsAlbum;

    public ResultButton(Context context) {
        super(context, null);
    }

    public ResultButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        LayoutInflater.from(context).inflate(R.layout.result_song, this, true);

        this.songName = findViewById(R.id.song_name);
        this.songArtistsAlbum = findViewById(R.id.song_artists_album);

        this.setClickable(true);
        this.setFocusable(true);
    }
}
