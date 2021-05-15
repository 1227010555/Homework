package com.example.music.adapter;

import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.R;
import com.example.music.Song;
import com.example.music.database.SongInfo;
import com.example.music.view.ResultButton;

import org.jetbrains.annotations.NotNull;

import java.util.List;

public class ResultAdapter extends RecyclerView.Adapter<ResultAdapter.ViewHolder> {

    private final List<SongInfo> mSongInfos;
    private onClickText onClickText;

    public ResultAdapter(List<SongInfo> songInfos) {
        mSongInfos = songInfos;
    }

    public void setOnClick(onClickText onClick) {
        this.onClickText = onClick;
    }

    @NotNull
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.result_button, parent, false);
        final ViewHolder holder = new ViewHolder(view);
        //播放歌曲，启动活动Song
        holder.resultButton.setOnClickListener(v -> {
            int position = holder.getAdapterPosition();
            if (mSongInfos.get(position).getUrl() != null) {
                Intent intent = new Intent(parent.getContext(), Song.class);
                intent.putExtra("songName", mSongInfos.get(position).getSongName());
                intent.putExtra("artistsName", mSongInfos.get(position).getArtistsName());
                intent.putExtra("url", mSongInfos.get(position).getUrl());
                intent.putExtra("SongID", mSongInfos.get(position).getSongId());
                intent.putExtra("Check", 0);
                parent.getContext().startActivity(intent);
            } else {
                //否则，将点击事件返回Result,无法播放
                onClickText.TextClick();
            }
        });
        return holder;
    }

    //清空搜索结果
    public void clear() {
        mSongInfos.clear();
    }

    //将可播放与不可播放区分
    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        String songName = mSongInfos.get(position).getSongName();
        String songArtistsAlbum = mSongInfos.get(position).getArtistsName() + "-" + mSongInfos.get(position).getAlbumName();
        holder.resultButton.songName.setText(songName);
        holder.resultButton.songArtistsAlbum.setText(songArtistsAlbum);
        if (mSongInfos.get(position).getUrl() != null) {
            holder.songAvailable.setImageResource(R.drawable.available);
        }
    }

    @Override
    public int getItemCount() {
        return mSongInfos.size();
    }

    public interface onClickText {
        void TextClick();
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        View resultView;
        ResultButton resultButton;
        ImageView songAvailable;

        public ViewHolder(View view) {
            super(view);
            resultView = view;
            resultButton = view.findViewById(R.id.result_button);
            songAvailable = view.findViewById(R.id.song_available);
        }
    }
}
