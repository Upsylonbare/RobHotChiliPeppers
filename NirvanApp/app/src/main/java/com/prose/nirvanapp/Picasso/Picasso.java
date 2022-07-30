/**
 * @file Picasso.java
 *
 * @brief this class manage Drawing
 *
 * @author Loris BOUSQUET
 * @date 2022
 *
 * @version 0.1
 *
 * @copyright Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its contributors
 *  may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package com.prose.nirvanapp.Picasso;


import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.util.AttributeSet;

import android.util.TypedValue;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

import java.util.ArrayList;

/**
 * This activity correspond to Picasso
 *
 * @see View
 * @see Paint
 * @see Draw
 * @see Path
 * @see Canvas
 * @see Bitmap
 */

public class Picasso extends View  {
    /**
     * starting brush size correspond to 0
     */
    private static int DEFAULT_BRUSH_SIZE = 0;
    /**
     * Default color correspond to TRANSPARENT
     */
    private static final int DEFAULT_COLOR = Color.TRANSPARENT;
    /**
     * touch tolerance correspond to 4
     */
    private static final float TOUCH_TOLERANCE = 4;
    /**
     * default background correspond to transparent
     */
    private static final int DEFAULT_BG_COLOR = Color.WHITE;
    /**
     * default bitmap Height to 349
     */
    private static final float DEFAULT_HEIGHT_SIZE = 221f;
    /**
     * default bitmap Height to 221
     */
    private static final float DEFAULT_WIDTH_SIZE = 349f;
    /**
     *  definition of variables that store previous positions
     */
    private float mX, mY;
    /**
     *  definition of variable that store the actual path
     */
    private Path mPath;
    /**
     *  definition of variable that store the actual paint
     */
    private Paint mPaint;
    /**
     *  definition of variable that store the actual color of brush
     */
    private int currentColor;
    /**
     *  definition of variable that store the actual width of stroke
     */
    private int strokeWidth;
    /**
     *  definition of variable that store the actual bitmap
     */
    private Bitmap mBitmap ;
    /**
     *  definition of variable that store the actual canvas
     */
    private Canvas mCanvas;
    /**
     *  definition of the bitmap paint
     */
    private Paint mBitmapPaint = new Paint(Paint.DITHER_FLAG);
    /**
     *  definition of the actual background color
     */
    private int backgroundColor = DEFAULT_BG_COLOR;
    /**
     *  instantiation of a list that contain the paths
     */
    private ArrayList<Draw> paths = new ArrayList<>();
    /**
     *  instantiation of a list that contain the undos
     */
    private ArrayList<Draw> undo = new ArrayList<>();


    /**
     *  Instantiation of picasso
     * @param context
     */
    public Picasso(Context context)
    {

        super(context, null);

    }
    /**
     *  Instantiation of picasso
     * @param context
     * @param attrs
     */
    public Picasso(Context context, AttributeSet attrs)
    {

        super(context, attrs);

        mPaint = new Paint();
        mPaint.setAntiAlias(true);
        mPaint.setDither(true);
        mPaint.setColor(DEFAULT_COLOR);
        mPaint.setStyle(Paint.Style.STROKE);
        mPaint.setStrokeJoin(Paint.Join.ROUND);
        mPaint.setStrokeCap(Paint.Cap.ROUND);
        mPaint.setXfermode(null);
        mPaint.setAlpha(0xff);

    }
    /**
     *  Initialisation Function
     */
    public void initialise ()
    {

        int height = (int) convertDptoPxHeight();
        int width = (int) convertDptoPxWidth();

        mBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);


        mCanvas = new Canvas(mBitmap);

        currentColor = DEFAULT_COLOR;
        strokeWidth = DEFAULT_BRUSH_SIZE;

    }

    /**
     *  Drawing Fonction
     * @param canvas
     */
    @Override
    protected void onDraw(Canvas canvas)
    {

        canvas.save();
        mCanvas.drawColor(backgroundColor);

        for (Draw draw : paths) {

            mPaint.setColor(draw.color);
            mPaint.setStrokeWidth(draw.strokeWidth);
            mPaint.setMaskFilter(null);

            mCanvas.drawPath(draw.path, mPaint);
        }
        canvas.drawBitmap(mBitmap, 0, 0, mBitmapPaint);
        canvas.restore();

    }

    /**
     *  Dp to pixel Converter
     */
    private float convertDptoPxHeight()
    {
        float dpHeight = DEFAULT_HEIGHT_SIZE;
        Resources r = getResources();
        float pxHeight = TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                dpHeight,
                r.getDisplayMetrics()
        );
        return pxHeight;
    }
    /**
     *  Dp to pixel Converter
     */
    private float convertDptoPxWidth()
    {
        float dpWidth = DEFAULT_WIDTH_SIZE;
        Resources r2 = getResources();
        float pxWidth = TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                dpWidth,
                r2.getDisplayMetrics()

        );
        return pxWidth;
    }

    /**
     *  start touching screen function
     * @param x
     * @param y
     */
    private void touchStart (float x, float y) {

        mPath = new Path();

        Draw draw = new Draw(currentColor, strokeWidth, mPath);
        paths.add(draw);

        mPath.reset();
        mPath.moveTo(x, y);

        mX = x;
        mY = y;

    }
    /**
     *  moving touch screen function
     * @param x
     * @param y
     */
    private void touchMove (float x, float y) {

        float dx = Math.abs(x - mX);
        float dy = Math.abs(y - mY);

        if (dx >= TOUCH_TOLERANCE || dy >= TOUCH_TOLERANCE) {

            mPath.quadTo(mX, mY, (x + mX) / 2, (y + mY) / 2);

            mX = x;
            mY = y;

        }

    }
    /**
     *  up touch screen function
     */
    private void touchUp () {

        mPath.lineTo(mX, mY);

    }
    /**
     *  on touch event function
     * @param event
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        float x = event.getX();
        float y = event.getY();

        switch (event.getAction()) {

            case MotionEvent.ACTION_DOWN:
                touchStart(x, y);
                invalidate();
                break;
            case MotionEvent.ACTION_UP:
                touchUp();
                invalidate();
                break;
            case MotionEvent.ACTION_MOVE:
                touchMove(x, y);
                invalidate();
                break;

        }
        return true;
    }

    /**
     *  Undo the last draw
     *
     */
    public void undo () {

        if (paths.size() > 0) {

            undo.add(paths.remove(paths.size() - 1));
            invalidate();

        } else {

            Toast.makeText(getContext(), "Rien à defaire", Toast.LENGTH_LONG).show();

        }

    }

    /**
     *  Stroke setter
     * @param width
     */
    public void setStrokeWidth (int width) {

        strokeWidth = width;

    }
    /**
     *  Color setter
     * @param color
     */
    public void setColor (int color) {

        currentColor = color;

    }
    /**
     *  Bitmap getter
     */
    public Bitmap getBitmap (){

        return mBitmap;

    }
    /**
     *  Stroke getter
     */
    public int getStrokeWidth (){
        return strokeWidth;
    }
    /**
     *  Color getter
     */
    public int getColor() {
        return currentColor;
    }

}
