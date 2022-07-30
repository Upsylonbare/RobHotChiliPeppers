package com.prose.nirvanapp.CartoManager;

import static org.junit.Assert.*;

import android.graphics.Bitmap;

import org.junit.Before;
import org.junit.Test;

public class CartoTest {

    private Carto carto;
    private Bitmap bmp;
    private Bitmap bmp2;

    @Before
    public void setup ()
    {
        bmp = Bitmap.createBitmap(1200, 1200, Bitmap.Config.ARGB_8888);
        bmp2 = Bitmap.createBitmap(1200, 1200, Bitmap.Config.ARGB_8888);
        carto = new Carto(7,"Salon",bmp,bmp2);
    }

    @Test
    public void getMyIdCarto_IsCorrect ()
    {
        assertEquals(7,carto.getMyIdCarto());
    }

    @Test
    public void getName ()
    {
        assertEquals("Salon",carto.getName());
    }

    @Test
    public void getRawScan ()
    {
        assertEquals(Bitmap.createBitmap(1200, 1200, Bitmap.Config.ARGB_8888),bmp);
    }


    @Test
    public void getTreatedScan ()
    {
        assertEquals(Bitmap.createBitmap(1200, 1200, Bitmap.Config.ARGB_8888),bmp2);
    }
}