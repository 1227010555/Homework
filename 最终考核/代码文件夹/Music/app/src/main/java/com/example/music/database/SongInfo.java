package com.example.music.database;

public class SongInfo {

    private final String artistsName;
    private final String albumName;
    private String songName;
    private String songId;
    private String url;

    public SongInfo(String songName, String artistsName, String albumName, String songId, String url) {
        this.songName = songName;
        this.artistsName = artistsName;
        this.albumName = albumName;
        this.songId = songId;
        this.url = url;
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

    public String getAlbumName() {
        return albumName;
    }

    public String getSongId() {
        return songId;
    }

    public void setSongId(String songId) {
        this.songId = songId;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }
}
