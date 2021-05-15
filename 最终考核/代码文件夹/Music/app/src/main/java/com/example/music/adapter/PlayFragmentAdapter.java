package com.example.music.adapter;

import android.annotation.SuppressLint;
import android.content.SharedPreferences;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.R;
import com.example.music.database.PlayListInfo;

import org.jetbrains.annotations.NotNull;

import java.util.List;

public class PlayFragmentAdapter extends RecyclerView.Adapter<PlayFragmentAdapter.ViewHolder> {

    private final List<PlayListInfo> mPlayListInfos;
    private PlayFragmentAdapter.onClickText onClickText;

    public PlayFragmentAdapter(List<PlayListInfo> playListInfos) {
        mPlayListInfos = playListInfos;
    }

    public void setOnClick(PlayFragmentAdapter.onClickText onClick) {
        this.onClickText = onClick;
    }

    @NotNull
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.play_list_item, parent, false);
        final ViewHolder holder = new ViewHolder(view);
        //将底部的歌曲更改为点击的歌曲
        holder.song.setOnClickListener(v -> {
            int position = holder.getAdapterPosition();
            onClickText.TextClick(position,
                    mPlayListInfos.get(position).getSongName() + "-"
                            + mPlayListInfos.get(position).getArtistsName());
        });
        //删除播放列表中的歌曲
        holder.cancel.setOnClickListener(v -> {
            int position = holder.getAdapterPosition();
            SharedPreferences prefs = androidx.preference.PreferenceManager.getDefaultSharedPreferences(parent.getContext());
            SharedPreferences.Editor editor = prefs.edit();
            editor.remove("SongName" + position);
            editor.remove("SongArtistsName" + position);
            editor.remove("SongID" + position);
            onClickText.TextClick(position, null);
            editor.apply();
            holder.song.setVisibility(View.INVISIBLE);
            holder.cancel.setVisibility(View.INVISIBLE);
        });
        return holder;
    }

    //清空播放列表
    public void clear() {
        mPlayListInfos.clear();
    }

    @SuppressLint("SetTextI18n")
    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        String songName = mPlayListInfos.get(position).getSongName();
        String artistsName = mPlayListInfos.get(position).getArtistsName();
        holder.song.setText(songName + "-" + artistsName);
    }

    @Override
    public int getItemCount() {
        return mPlayListInfos.size();
    }

    public interface onClickText {
        void TextClick(int position, String songInfo);
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        View playFragmentAdapterView;
        Button song;
        ImageButton cancel;

        public ViewHolder(View view) {
            super(view);
            playFragmentAdapterView = view;
            song = view.findViewById(R.id.song);
            cancel = view.findViewById(R.id.cancel);
        }
    }
}
