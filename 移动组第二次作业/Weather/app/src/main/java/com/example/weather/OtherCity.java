package com.example.weather;

import android.annotation.SuppressLint;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.IBinder;
import android.os.SystemClock;
import android.preference.PreferenceManager;
import android.text.TextUtils;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.weather.database.City;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;

public class OtherCity extends AppCompatActivity implements View.OnTouchListener, GestureDetector.OnGestureListener {

    private GestureDetector mGestureDetector;
    private ImageView background;
    private ScrollView weatherLayout;
    private TextView titleCity;
    private TextView titleUpdateTime;
    private TextView degreeText;
    private TextView weatherInfoText;
    private TextView airText;
    private TextView winText;
    private TextView maxText;
    private TextView minText;
    private ImageView page;
    String weatherUrl = "https://www.tianqiapi.com/free/day?appid=17657664&appsecret=2B0832mZ&city=";
    String JSON = null;
    String cityName = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //滑动手势
        findView();

        //初始化
        background = (ImageView) findViewById(R.id.background);
        weatherLayout = (ScrollView) findViewById(R.id.weather_layout);
        titleCity = (TextView) findViewById(R.id.title_city);
        titleUpdateTime = (TextView) findViewById(R.id.title_update_time);
        ImageButton titleSearch = (ImageButton) findViewById(R.id.title_search);
        degreeText = (TextView) findViewById(R.id.degree_text);
        weatherInfoText = (TextView) findViewById(R.id.weather_info_text);
        airText = (TextView) findViewById(R.id.air_text);
        winText = (TextView) findViewById(R.id.win_text);
        maxText = (TextView) findViewById(R.id.max_text);
        minText = (TextView) findViewById(R.id.min_text);
        page=(ImageView) findViewById(R.id.page);

        page.setImageResource(R.drawable.right);

        //搜索城市
        titleSearch.setOnClickListener(v -> {
            Intent intent = new Intent(OtherCity.this, SearchButton.class);
            startActivityForResult(intent, 1);
        });

        //读取城市天气
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(OtherCity.this);
        JSON = prefs.getString("weather_JSON_other", null);
        if (JSON != null) {
            receiveJSON(JSON);
        } else {
            weatherLayout.setVisibility(View.INVISIBLE);
            sendHTTPRequest(weatherUrl);
        }
    }

    //获取搜索结果
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 1) {
            if (resultCode == RESULT_OK) {
                cityName = data.getStringExtra("cityName");
                if (cityName != null)
                    sendHTTPRequest(weatherUrl + cityName);
            }
        }
    }

    //更新UI界面
    @SuppressLint("SetTextI18n")
    private void showWeatherInfo(City cityweather) {
        String city = cityweather.getCityName();
        String update_time = cityweather.getUpdate_time();
        String wea = cityweather.getWea();
        String wea_img = cityweather.getWea_img();
        String tem = cityweather.getTem();
        String tem_day = cityweather.getTem_day();
        String tem_night = cityweather.getTem_night();
        String air = cityweather.getAir();
        String win = cityweather.getWin();
        String win_speed = cityweather.getWin_speed();
        String win_meter = cityweather.getWin_meter();
        titleCity.setText(city);
        titleUpdateTime.setText(update_time);
        degreeText.setText(tem + "℃");
        weatherInfoText.setText(wea);
        maxText.setText(tem_day + "℃/");
        minText.setText(tem_night + "℃");
        airText.setText(air);
        winText.setText("风向：" + win + '\n' + "风力：" + win_speed + '\n' + "风速：" + win_meter + '\n');
        switch (wea_img) {
            case "xue":
                background.setImageResource(R.drawable.xue);
                break;
            case "lei":
                background.setImageResource(R.drawable.lei);
                break;
            case "shachen":
                background.setImageResource(R.drawable.shachen);
                break;
            case "wu":
                background.setImageResource(R.drawable.wu);
                break;
            case "bingbao":
                background.setImageResource(R.drawable.bingbao);
                break;
            case "yun":
                background.setImageResource(R.drawable.yun);
                break;
            case "yu":
                background.setImageResource(R.drawable.yu);
                break;
            case "yin":
                background.setImageResource(R.drawable.yin);
                break;
            case "qing":
                background.setImageResource(R.drawable.qing);
                break;
        }
        weatherLayout.setVisibility(View.VISIBLE);
    }

    //发送请求
    public void sendHTTPRequest(String address) {
        new Thread(() -> {
            HttpURLConnection connection = null;
            BufferedReader reader = null;
            URL url;
            try {
                url = new URL(address);
                try {
                    connection = (HttpURLConnection) url.openConnection();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                try {
                    assert connection != null;
                    connection.setRequestMethod("GET");
                } catch (ProtocolException e) {
                    e.printStackTrace();
                }
                InputStream in = null;
                try {
                    in = connection.getInputStream();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                reader = new BufferedReader(new InputStreamReader(in));
                StringBuilder response = new StringBuilder();
                String line;
                try {
                    while ((line = reader.readLine()) != null)
                        response.append(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                receiveJSON(response.toString());
            } catch (MalformedURLException e) {
                e.printStackTrace();
            } finally {
                if (reader != null) {
                    try {
                        reader.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                if (connection != null) {
                    connection.disconnect();
                }
            }
        }).start();
    }

    //接受JSON数据
    public void receiveJSON(String JSON) {
        runOnUiThread(() -> {
            City cityInfo = handleCityResponse(JSON);
            if (cityInfo != null) {
                SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(OtherCity.this).edit();
                editor.putString("weather_JSON_other", JSON);
                editor.putString("weather_cityname_other", cityInfo.getCityName());
                editor.apply();
                showWeatherInfo(cityInfo);
            } else {
                Toast.makeText(OtherCity.this, "获取天气信息失败", Toast.LENGTH_SHORT).show();
            }
        });
    }

    //处理JSON数据
    public City handleCityResponse(String response) {
        if (!TextUtils.isEmpty(response)) {
            JSONObject jsonObject;
            try {
                jsonObject = new JSONObject(response);
                String cityName = jsonObject.getString("city");
                String update_time = jsonObject.getString("update_time");
                String wea = jsonObject.getString("wea");
                String wea_img = jsonObject.getString("wea_img");
                String tem = jsonObject.getString("tem");
                String tem_day = jsonObject.getString("tem_day");
                String tem_night = jsonObject.getString("tem_night");
                String win = jsonObject.getString("win");
                String win_speed = jsonObject.getString("win_speed");
                String win_meter = jsonObject.getString("win_meter");
                String air = jsonObject.getString("air");
                return new City(cityName, update_time, wea, wea_img, tem, tem_day, tem_night, win, win_speed, win_meter, air);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        return null;
    }

    //实现滑动切换城市
    @SuppressLint("ClickableViewAccessibility")
    private void findView() {
        weatherLayout = (ScrollView) findViewById(R.id.weather_layout);
        weatherLayout.setOnTouchListener(OtherCity.this);
        weatherLayout.setLongClickable(true);
        mGestureDetector = new GestureDetector(OtherCity.this, OtherCity.this);
    }

    @Override
    public boolean onDown(MotionEvent e) {
        return false;
    }

    @Override
    public void onShowPress(MotionEvent e) {

    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        return false;
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        return false;
    }

    @Override
    public void onLongPress(MotionEvent e) {

    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        final int FLING_MIN_X_DISTANCE = 100;
        final int FLING_MIN_Y_DISTANCE = 10;
        if (((int) (e2.getX() - e1.getX())) > FLING_MIN_X_DISTANCE) { //左滑右滑皆可
            Intent intent = new Intent(OtherCity.this, MainActivity.class);
            startActivity(intent);
            overridePendingTransition(android.R.anim.slide_in_left, android.R.anim.slide_out_right);
            finish();
        } else if
        (((int) (e2.getY() - e1.getY())) > FLING_MIN_Y_DISTANCE && ((int) (e2.getX() - e1.getX())) < FLING_MIN_X_DISTANCE) {
            weatherLayout.setVisibility(View.INVISIBLE);
            SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(OtherCity.this);
            cityName = prefs.getString("weather_cityname_other", null);
            sendHTTPRequest(weatherUrl + cityName);
            Toast.makeText(OtherCity.this, "刷新成功", Toast.LENGTH_SHORT).show();
        }
        return false;
    }

    @SuppressLint("ClickableViewAccessibility")
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        return mGestureDetector.onTouchEvent(event);
    }

    //1小时更新天气(没有测试，也许可以)
    public class AutoUpdateService extends Service {

        @Override
        public IBinder onBind(Intent intent) {
            return null;
        }

        public int onStartCommand(Intent intent, int flags, int startId) {
            updateWeather();
            AlarmManager manager = (AlarmManager) getSystemService(ALARM_SERVICE);
            int anHour = 60 * 60 * 1000;
            long triggerAtTime = SystemClock.elapsedRealtime() + anHour;
            Intent i = new Intent(OtherCity.this, AutoUpdateService.class);
            PendingIntent pendingIntent = PendingIntent.getService(OtherCity.this, 0, i, 0);
            manager.cancel(pendingIntent);
            manager.set(AlarmManager.ELAPSED_REALTIME_WAKEUP, triggerAtTime, pendingIntent);
            return super.onStartCommand(intent, flags, startId);
        }

        private void updateWeather() {
            SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(OtherCity.this);
            cityName = preferences.getString("weather_cityname_other", null);
            if (cityName != null) {
                weatherLayout.setVisibility(View.INVISIBLE);
                sendHTTPRequest(weatherUrl + cityName);
            }
        }
    }
}

