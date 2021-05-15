package com.example.music.database;

public class PlayListInfo {

    private final String artistsName;
    private String songName;
    private String songID;

    public PlayListInfo(String songName, String artistsName, String songID) {
        this.songName = songName;
        this.artistsName = artistsName;
        this.songID = songID;
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

    public String getSongID() {
        return songID;
    }

    public void setSongID(String songID) {
        this.songID = songID;
    }
}
