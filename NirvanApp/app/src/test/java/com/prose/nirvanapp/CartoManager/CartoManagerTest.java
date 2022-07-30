package com.prose.nirvanapp.CartoManager;



import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;

import java.io.File;


public class CartoManagerTest {

    private File[] testfile = new File[2];


    @Before
    public void setup(){
    testfile[0] = new File("dd.JPEG");
    testfile[1] = new File("ddd.JPEG");
    }

    @Test
    public void getCartoNumberInFile_IsCorrect() {
        assertEquals(2,CartoManager.INSTANCE.getCartoNumberInFile(testfile));
    }

    @Test
    public void ask4SaveCarto() {

    }

    @Test
    public void createHistory() {
    }

    @Test
    public void getCurrentCarto() {
    }
}