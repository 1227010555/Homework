package com.example.music.adapter;

import android.annotation.SuppressLint;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.R;
import com.example.music.database.NewSongInfo;

import org.jetbrains.annotations.NotNull;

import java.util.List;

public class NewSongAdapter extends RecyclerView.Adapter<NewSongAdapter.ViewHolder> {

    private final List<NewSongInfo> mNewSongInfos;
    private onClickText onClickText;

    public NewSongAdapter(List<NewSongInfo> newSongInfos) {
        this.mNewSongInfos = newSongInfos;
    }

    public void setOnClick(onClickText onClick) {
        this.onClickText = onClick;
    }

    @NotNull
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.new_song_item, parent, false);
        final ViewHolder holder = new ViewHolder(view);
        //由于新歌速递无法播放，返回点击事件给活动MainActivity
        holder.newSongButton.setOnClickListener(v -> onClickText.TextClick());
        return holder;
    }

    @SuppressLint("SetTextI18n")
    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        holder.newSongButton.setText(mNewSongInfos.get(position).getSongName() + "-" +
                mNewSongInfos.get(position).getArtistsName());
        holder.newSongImg.setImageBitmap(mNewSongInfos.get(position).getImg());
    }

    @Override
    public int getItemCount() {
        return mNewSongInfos.size();
    }

    public interface onClickText {
        void TextClick();
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        View newSongView;
        Button newSongButton;
        ImageView newSongImg;

        public ViewHolder(View view) {
            super(view);
            newSongView = view;
            newSongButton = view.findViewById(R.id.new_song);
            newSongImg = view.findViewById(R.id.new_song_img);
        }
    }
}
