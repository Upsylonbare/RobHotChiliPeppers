package com.prose.nirvanapp.Picasso;

import android.graphics.Path;
/**
 * This class centralized Draw data
 */
public class Draw {

    /**
     * Draw color : int
     */
    public int color;
    /**
     * Draw strokeWidth : int
     */
    public int strokeWidth;
    /**
     * Draw path : Path
     */
    public Path path;


    /**
     * Draw constructor
     *
     * @param color - color to use for the draw
     * @param strokeWidth - strokewidth to use for the draw
     * @param path - path to use for the draw
     */
    public Draw(int color, int strokeWidth, Path path) {
        this.color = color;
        this.strokeWidth = strokeWidth;
        this.path = path;
    }

}
