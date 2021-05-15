package com.example.music;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.widget.EditText;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.adapter.SuggestionAdapter;
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

public class Suggestion extends AppCompatActivity {
    private final String suggestionAddress = "http://neteasemusic.heyanle.com:3000/search/suggest?type=mobile&keywords=";
    private final String searchAddress = "http://neteasemusic.heyanle.com:3000/search?limit=15&keywords=";
    private ImageButton titleLeftArrow;
    private EditText suggestionTitleEdit;
    private RecyclerView suggestionView;
    private List<String> suggestionList = new ArrayList<>();
    private LinearLayoutManager layoutManager = new LinearLayoutManager(Suggestion.this);
    private SuggestionAdapter adapter = new SuggestionAdapter(suggestionList);
    private String search = "";
    private int i, temp = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_suggestion);
        titleLeftArrow = findViewById(R.id.title_left_arrow);
        suggestionTitleEdit = findViewById(R.id.suggestion_title_edit);
        suggestionView = findViewById(R.id.recyclerview);
        //退出
        titleLeftArrow.setOnClickListener(v -> finish());
        //将搜索建议保存至search中,从而得以存储至历史搜索
        adapter.setOnClick(suggestion -> search = suggestion);
        //监听搜索键，打开活动Result，进行搜索
        suggestionTitleEdit.setOnKeyListener((v, keyCode, event) -> {
            if (keyCode == KeyEvent.KEYCODE_ENTER && event.getAction() == KeyEvent.ACTION_UP) {
                Intent intent = new Intent(Suggestion.this, Result.class);
                search = suggestionTitleEdit.getText().toString();
                intent.putExtra("address", searchAddress + search);
                if (!search.equals("")) {
                    if (getIntent().getStringExtra("classname").equals("Search"))
                        startActivity(intent);
                    if (getIntent().getStringExtra("classname").equals("Result")) {
                        setResult(RESULT_OK, intent);
                        finish();
                    }
                }
                return true;
            }
            return false;
        });
        //监听输入，从而实现搜索建议
        suggestionTitleEdit.addTextChangedListener(new TextWatcher() {

            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                adapter.clear();
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
            }

            @Override
            public void afterTextChanged(Editable s) {
                queryForSuggestion(suggestionAddress + suggestionTitleEdit.getText().toString());
            }
        });
    }

    //保存搜索数据并销毁活动
    @Override
    protected void onPause() {
        super.onPause();
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(Suggestion.this);
        if (!search.equals(prefs.getString("Status_0", null)))
            if (!search.equals(""))
                saveHistory();
        finish();
    }

    //获取搜索建议
    private void queryForSuggestion(String suggestionAddress) {
        HttpUtil.sendOkHttpRequest(suggestionAddress, new Callback() {
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String responseText = response.body().string();
                handleJSON(responseText);
            }

            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
            }
        });
    }

    //处理搜索建议的JSON数据
    private void handleJSON(String Json) {
        runOnUiThread(() -> {
            adapter.clear();
            if (!TextUtils.isEmpty(Json)) {
                try {
                    String keyword;
                    JSONObject jsonObject = new JSONObject(Json);
                    if (!TextUtils.isEmpty(jsonObject.getString("result"))) {
                        JSONObject jsonResultObject = new JSONObject(jsonObject.getString("result"));
                        if (!TextUtils.isEmpty(jsonResultObject.getString("allMatch"))) {
                            JSONArray jsonKeywordsArray = new JSONArray(jsonResultObject.getString("allMatch"));
                            for (i = 0; i < jsonKeywordsArray.length(); i++) {
                                JSONObject jsonKeywordObject = jsonKeywordsArray.getJSONObject(i);
                                keyword = jsonKeywordObject.getString("keyword");
                                suggestionList.add(keyword);
                            }
                            suggestionView.setLayoutManager(layoutManager);
                            suggestionView.setAdapter(adapter);
                        }
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    //存储历史记录
    private void saveHistory() {
        SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(Suggestion.this);
        SharedPreferences.Editor editor = prefs.edit();
        int size = prefs.getInt("Status_size", 0);
        for (i = 0; i < size; i++) {
            if (search.equals(prefs.getString("Status_" + i, null))) {
                temp = i;
                break;
            }
        }
        editor.remove("Status_" + 0);
        editor.putString("Status_" + 0, search);
        for (i = 0; i < size; i++) {
            if (i != temp) {
                editor.remove("Status_" + (i + 1));
                editor.putString("Status_" + (i + 1), prefs.getString("Status_" + i, null));
            }
        }
        if (temp == -1) {
            editor.putInt("Status_size", prefs.getInt("Status_size", 0) + 1);
        }
        editor.apply();
    }
}