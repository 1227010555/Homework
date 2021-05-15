package com.example.music.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

//banner下方的圆点
public class Dots extends View {

    private final int number = 10;
    private final int r = 10;
    private final int bgColor = Color.GRAY;
    private final int foreColor = Color.BLACK;
    private Paint forePaint;
    private Paint bgPaint;
    private float offset;

    public Dots(Context context) {
        super(context);
        initPaint();
    }

    public Dots(Context context, AttributeSet attrs) {
        super(context, attrs);
        initPaint();
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        initPaint();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        for (int x = 0; x < number; x++) {
            canvas.drawCircle((getWidth() / 2) - (60 + 5 * r * 3) + (60 + x * r * 3), 10, r, bgPaint);

        }
        canvas.drawCircle((getWidth() / 2) - (60 + 3 * r * 3) + offset, 10, r, forePaint);
    }

    private void initPaint() {
        forePaint = new Paint();
        forePaint.setAntiAlias(true);
        forePaint.setStyle(Paint.Style.FILL);
        forePaint.setColor(foreColor);
        forePaint.setStrokeWidth(2);
        bgPaint = new Paint();
        bgPaint.setAntiAlias(true);
        bgPaint.setStyle(Paint.Style.STROKE);
        bgPaint.setColor(bgColor);
        bgPaint.setStrokeWidth(2);
    }

    public void setOffSet(int position, float positionOffset) {
        position %= number;
        offset = position * 3 * r + positionOffset * 3 * r;
        invalidate();
    }
}
