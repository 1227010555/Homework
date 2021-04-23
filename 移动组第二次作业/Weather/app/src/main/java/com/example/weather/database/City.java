package com.example.weather.database;

public class City {
    private String cityName;
    private String update_time;
    private String wea;
    private String wea_img;
    private String tem;
    private String tem_day;
    private String tem_night;
    private String win;
    private String win_speed;
    private String win_meter;
    private String air;

    public City(String cityName, String update_time, String wea, String wea_img, String tem, String tem_day, String tem_night, String win, String win_speed, String win_meter, String air) {
        this.cityName = cityName;
        this.update_time = update_time;
        this.wea = wea;
        this.wea_img = wea_img;
        this.tem = tem;
        this.tem_day = tem_day;
        this.tem_night = tem_night;
        this.win = win;
        this.win_speed = win_speed;
        this.win_meter = win_meter;
        this.air = air;
    }

    public String getCityName() {
        return cityName;
    }

    public String getUpdate_time() {
        return update_time;
    }

    public String getWea() {
        return wea;
    }

    public String getWea_img() {
        return wea_img;
    }

    public String getTem() {
        return tem;
    }

    public String getTem_day() {
        return tem_day;
    }

    public String getTem_night() {
        return tem_night;
    }

    public String getWin() {
        return win;
    }

    public String getWin_speed() {
        return win_speed;
    }

    public String getWin_meter() {
        return win_meter;
    }

    public String getAir() {
        return air;
    }
}
