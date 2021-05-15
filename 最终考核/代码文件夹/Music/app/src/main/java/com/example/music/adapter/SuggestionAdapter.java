package com.example.music.adapter;

import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.R;
import com.example.music.Result;

import org.jetbrains.annotations.NotNull;

import java.util.List;

public class SuggestionAdapter extends RecyclerView.Adapter<SuggestionAdapter.ViewHolder> {

    private final List<String> mSuggestion;
    private final String songAddress = "http://neteasemusic.heyanle.com:3000/search?limit=15&keywords=";
    private onClickText onClickText;

    public SuggestionAdapter(List<String> suggestion) {
        mSuggestion = suggestion;
    }

    public void setOnClick(onClickText onClick) {
        this.onClickText = onClick;
    }

    @NotNull
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.suggestion_item, parent, false);
        final ViewHolder holder = new ViewHolder(view);
        //搜索建议，启动活动Result，并将点击的suggestion返回,以从来保存历史搜索
        holder.suggestionButton.setOnClickListener(v -> {
            int position = holder.getAdapterPosition();
            String suggestion = mSuggestion.get(position);
            onClickText.TextClick(suggestion);
            Intent intent = new Intent(parent.getContext(), Result.class);
            intent.putExtra("address", songAddress + suggestion);
            parent.getContext().startActivity(intent);
        });
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        String suggestion = mSuggestion.get(position);
        holder.suggestionButton.setText(suggestion);
    }

    public void clear() {
        mSuggestion.clear();
    }

    @Override
    public int getItemCount() {
        return mSuggestion.size();
    }

    public interface onClickText {
        void TextClick(String suggestion);
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        View suggestionView;
        Button suggestionButton;

        public ViewHolder(View view) {
            super(view);
            suggestionView = view;
            suggestionButton = view.findViewById(R.id.suggestion);
        }
    }
}
