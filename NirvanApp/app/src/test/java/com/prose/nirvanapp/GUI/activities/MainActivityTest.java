package com.prose.nirvanapp.GUI.activities;

import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

/**
 * MainActivity unit test
 *
 * @see MainActivity
 */
public class MainActivityTest
{
    /**
     * Gets port number method OK
     */
    @Test
    public void getPortNumber_isCorrect ()
    {
        assertEquals(12345, MainActivity.getPortNumber());
    }

    /**
     * Gets port number method KO
     */
    @Test
    public void getPortNumber_isNotCorrect ()
    {
        assertNotEquals(7800, MainActivity.getPortNumber());
    }

    /**
     * Gets port number method OK
     */
    @Test
    public void getIpAddress_isCorrect ()
    {
        assertEquals("192.168.72.1", MainActivity.getIpAddress());
    }

    /**
     * Gets port number method KO
     */
    @Test
    public void getIpAddress_isNotCorrect ()
    {
        assertNotEquals("127.0.0.1", MainActivity.getIpAddress());
    }
}

