package com.example.weather;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

public class SearchButton extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search_button);
        ImageView background=(ImageView) findViewById(R.id.background);
        background.setImageResource(R.drawable.search);
        ImageButton button =(ImageButton) findViewById(R.id.search);
        EditText editText=(EditText)findViewById(R.id.edit_text);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                String contain=editText.getText().toString();
                intent.putExtra("cityName",contain);
                setResult(RESULT_OK,intent);
                finish();
            }
        });

    }
}