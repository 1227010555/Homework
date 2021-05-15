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

import java.util.List;

public class HistoryAdapter extends RecyclerView.Adapter<HistoryAdapter.ViewHolder> {

    private final List<String> mHistoryList;
    private final String address = "http://neteasemusic.heyanle.com:3000/search?limit=15&keywords=";
    private onClickText onClickText;

    public HistoryAdapter(List<String> HistoryList) {
        mHistoryList = HistoryList;
    }

    public void setOnClick(onClickText onClick) {
        this.onClickText = onClick;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.history_item, parent, false);
        final ViewHolder holder = new ViewHolder(view);
        //历史搜索，将点击的历史搜索返回给活动Search，启动活动Result
        holder.historyButton.setOnClickListener(v -> {
            int position = holder.getAdapterPosition();
            String history = mHistoryList.get(position);
            onClickText.TextClick(history);
            Intent intent = new Intent(parent.getContext(), Result.class);
            intent.putExtra("address", address + history);
            parent.getContext().startActivity(intent);
        });
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        String data = mHistoryList.get(position);
        holder.historyButton.setText(data);
    }

    @Override
    public int getItemCount() {
        return mHistoryList.size();
    }

    public interface onClickText {
        void TextClick(String history);
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        View historyView;
        Button historyButton;

        public ViewHolder(View view) {
            super(view);
            historyView = view;
            historyButton = view.findViewById(R.id.history_button);
        }
    }
}
