package com.example.music;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.RelativeLayout;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.adapter.HistoryAdapter;
import com.example.music.util.HttpUtil;

import org.jetbrains.annotations.NotNull;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class Search extends AppCompatActivity {

    private final List<String> historyList = new ArrayList<>();
    private final HistoryAdapter adapter = new HistoryAdapter(historyList);
    private final String hotAddress = "http://neteasemusic.heyanle.com:3000/search/hot";
    private final String searchAddress = "http://neteasemusic.heyanle.com:3000/search?limit=15&keywords=";
    private ImageButton titleLeftArrow;
    private Button searchTitleEdit;
    private ImageButton historyDelete;
    private RecyclerView historyView;
    private RelativeLayout searchHistory;
    private int i = 0;
    private int temp = -1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);
        //初始化
        titleLeftArrow = findViewById(R.id.title_left_arrow);
        searchTitleEdit = findViewById(R.id.search_title_edit);
        historyDelete = findViewById(R.id.history_delete);
        historyView = findViewById(R.id.history_view);
        searchHistory = findViewById(R.id.search_history);
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(Search.this);
        SharedPreferences.Editor editor = prefs.edit();
        //退出
        titleLeftArrow.setOnClickListener(v -> finish());
        //搜索，启动活动Suggestion,来获取搜索建议
        searchTitleEdit.setOnClickListener(v -> {
            Intent intent = new Intent(Search.this, Suggestion.class);
            intent.putExtra("classname", "Search");
            startActivity(intent);
        });
        //获取点击的历史搜索并存储
        adapter.setOnClick(history -> {
            if (!history.equals(historyList.get(0))) {
                historyList.add(history);
                saveHistory(0);
            }
        });
        //删除历史记录
        historyDelete.setOnClickListener(v -> {
            for (i = 0; i < prefs.getInt("Status_size", 0); i++)
                editor.remove("Status_" + (i + 1));
            editor.remove("Status_size");
            editor.apply();
            searchHistory.setVisibility(View.INVISIBLE);
        });
        //获取热搜
        queryForHot(hotAddress);
    }

    //加载读取历史记录
    protected void onResume() {
        super.onResume();
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(Search.this);
        if (prefs.getInt("Status_size", 0) > 0) {
            historyList.clear();
            for (i = 0; i < prefs.getInt("Status_size", 0); i++) {
                historyList.add(prefs.getString("Status_" + i, null));
            }
            searchHistory.setVisibility(View.VISIBLE);
        } else
            searchHistory.setVisibility(View.INVISIBLE);
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        layoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        historyView.setLayoutManager(layoutManager);
        historyView.setAdapter(adapter);
    }

    //存储历史记录
    private void saveHistory(int Status) {
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(Search.this);
        SharedPreferences.Editor editor = prefs.edit();
        if (Status == 1)
            editor.putInt("Status_size", prefs.getInt("Status_size", 0) + 1);
        for (i = 0; i < historyList.size() - 1; i++) {
            if (historyList.get(historyList.size() - 1).equals(historyList.get(i))) {
                temp = i;
                break;
            }
        }
        editor.remove("Status_" + 0);
        editor.putString("Status_" + 0, historyList.get(historyList.size() - 1));
        for (i = 0; i < historyList.size() - 1; i++) {
            if (i != temp) {
                editor.remove("Status_" + (i + 1));
                editor.putString("Status_" + (i + 1), historyList.get(i));
            }
        }
        editor.apply();
    }

    //获取热搜
    private void queryForHot(String hotAddress) {
        HttpUtil.sendOkHttpRequest(hotAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String responseText = response.body().string();
                handleHotJSON(responseText);
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                runOnUiThread(() -> queryForHot(hotAddress));
            }
        });
    }

    //处理热搜的JSON数据
    private void handleHotJSON(String JSON) {
        runOnUiThread(() -> {
            if (!TextUtils.isEmpty(JSON)) {
                try {
                    JSONObject jsonObject = new JSONObject(JSON);
                    if (!TextUtils.isEmpty(jsonObject.getString("result"))) {
                        JSONObject jsonResultObject = new JSONObject(jsonObject.getString("result"));
                        if (!TextUtils.isEmpty(jsonResultObject.getString("hots"))) {
                            JSONArray jsonHotsArray = new JSONArray(jsonResultObject.getString("hots"));
                            setHot(findViewById(R.id.hot_1), jsonHotsArray.getJSONObject(0).getString("first"));
                            setHot(findViewById(R.id.hot_2), jsonHotsArray.getJSONObject(1).getString("first"));
                            setHot(findViewById(R.id.hot_3), jsonHotsArray.getJSONObject(2).getString("first"));
                            setHot(findViewById(R.id.hot_4), jsonHotsArray.getJSONObject(3).getString("first"));
                            setHot(findViewById(R.id.hot_5), jsonHotsArray.getJSONObject(4).getString("first"));
                            setHot(findViewById(R.id.hot_6), jsonHotsArray.getJSONObject(5).getString("first"));
                            setHot(findViewById(R.id.hot_7), jsonHotsArray.getJSONObject(6).getString("first"));
                            setHot(findViewById(R.id.hot_8), jsonHotsArray.getJSONObject(7).getString("first"));
                            setHot(findViewById(R.id.hot_9), jsonHotsArray.getJSONObject(8).getString("first"));
                            setHot(findViewById(R.id.hot_10), jsonHotsArray.getJSONObject(9).getString("first"));
                        }
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    //设置每一个搜索
    private void setHot(Button hot, String hotName) {
        hot.setText(hotName);
        hot.setOnClickListener(v -> {
            historyList.add(hot.getText().toString());
            saveHistory(1);
            Intent intent = new Intent(Search.this, Result.class);
            intent.putExtra("address", searchAddress + hot.getText().toString());
            startActivity(intent);
        });
    }
}

