package com.example.music.database;

import android.graphics.Bitmap;

public class NewSongInfo {

    private final String artistsName;
    Bitmap img;
    String id;
    private String songName;

    public NewSongInfo(Bitmap img, String id, String songName, String artistsName) {
        this.img = img;
        this.id = id;
        this.songName = songName;
        this.artistsName = artistsName;
    }

    public Bitmap getImg() {
        return img;
    }

    public void setImg(Bitmap img) {
        this.img = img;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getSongName() {
        return songName;
    }

    public void setSongName(String songName) {
        this.songName = songName;
    }

    public String getArtistsName() {
        return artistsName;
    }

}
