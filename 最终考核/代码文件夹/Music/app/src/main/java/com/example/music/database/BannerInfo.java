package com.example.music.database;

import android.graphics.Bitmap;

public class BannerInfo {

    private final String url;
    private Bitmap img;

    public BannerInfo(Bitmap img, String url) {
        this.img = img;
        this.url = url;
    }

    public Bitmap getImg() {
        return img;
    }

    public void setImg(Bitmap img) {
        this.img = img;
    }

    public String getUrl() {
        return url;
    }

}
