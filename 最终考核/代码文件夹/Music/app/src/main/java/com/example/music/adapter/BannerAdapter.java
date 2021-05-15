package com.example.music.adapter;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.music.R;
import com.example.music.database.BannerInfo;

import org.jetbrains.annotations.NotNull;

import java.util.List;

public class BannerAdapter extends RecyclerView.Adapter<BannerAdapter.ViewHolder> {

    private final List<BannerInfo> mBannerInfos;
    private onClickText onClickText;

    public BannerAdapter(List<BannerInfo> bannerInfo) {
        mBannerInfos = bannerInfo;
    }

    public void setOnClick(onClickText onClick) {
        this.onClickText = onClick;
    }

    @NotNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.banner_item, parent, false);
        final ViewHolder holder = new ViewHolder(view);
        //打开浏览器，浏览banner内容
        holder.banner.setOnClickListener(v -> {
            int position = holder.getAdapterPosition();
            if (!mBannerInfos.get(position).getUrl().equals("null")) {
                Uri uri = Uri.parse(mBannerInfos.get(position).getUrl());
                Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                parent.getContext().startActivity(intent);
            } else {
                onClickText.TextClick();
            }
        });
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Bitmap img = mBannerInfos.get(position % mBannerInfos.size()).getImg();
        holder.banner.setImageBitmap(img);
    }

    @Override
    public int getItemCount() {
        return Integer.MAX_VALUE;
    }

    public interface onClickText {
        void TextClick();
    }

    static class ViewHolder extends RecyclerView.ViewHolder {
        View bannerView;
        ImageView banner;

        public ViewHolder(View view) {
            super(view);
            bannerView = view;
            banner = view.findViewById(R.id.banner);
        }
    }
}
