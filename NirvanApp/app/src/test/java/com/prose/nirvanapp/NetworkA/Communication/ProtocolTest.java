package com.prose.nirvanapp.NetworkA.Communication;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.when;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.prose.nirvanapp.CartoManager.Carto;
import com.prose.nirvanapp.R;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;

import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * Protocol unit test
 */
@RunWith (JUnit4.class)
public class ProtocolTest
{
    private Protocol.Message defaultMessage;
    private Protocol.Message aPingMessage;
    private Protocol.Message aAsk4ScanMessage;
    private Protocol.Message aAckCartoMessage;
    // private Protocol.Message aSetCartoMessage;
    // private Protocol.Message cSetCartoMessage;
    private Protocol.Message cAck4ScanMessage;
    private Protocol.Message cAck4SaveCartoMessage;
    private Protocol.Message cAckCartoMessage;

    // default data
    private int defaultCommand;
    private int defaultId;
    private String defaultName;
    private Bitmap defaultFile;

    // @Mock
    // private Carto currentCarto;

    @Before
    public void setup ()
    {
        MockitoAnnotations.initMocks(this);

        // init default values
        defaultCommand = 1;
        defaultId = 5;
        defaultName = "default_test_name";
        defaultFile = Bitmap.createBitmap(1200, 1200, Bitmap.Config.ARGB_8888);

        // set carto data
        // bitmap is null
        // when(currentCarto.getMyIdCarto()).thenReturn(defaultId);
        // when(currentCarto.getName()).thenReturn(defaultName);
        // when(currentCarto.getTreatedScan()).thenReturn(defaultFile);

        // create default message
        defaultMessage = new Protocol.Message(  defaultCommand,
                                                defaultId,
                                                defaultName,
                                                defaultFile);
    }

    @Test
    public void constructor_defaultMessage_isCorrect ()
    {
        assertNotNull(defaultMessage);
    }

    @Test
    public void constructor_aPingMessage_isCorrect ()
    {
        aPingMessage = new Protocol.Message(Protocol.A_PING,
                Protocol.NO_ID,
                null,
                null);

        assertNotNull(aPingMessage);
    }

    @Test
    public void constructor_aAsk4ScanMessage_isCorrect ()
    {
        aAsk4ScanMessage = new Protocol.Message(Protocol.A_ASK4SCAN,
                2,
                null,
                null);

        assertNotNull(aAsk4ScanMessage);
        assertEquals(Protocol.A_ASK4SCAN, aAsk4ScanMessage.getCommand());
        assertEquals(2, aAsk4ScanMessage.getId());
    }

    @Test
    public void constructor_aAckCartoMessage_isCorrect ()
    {
        aAckCartoMessage = new Protocol.Message(Protocol.A_ACKCARTO,
                Protocol.NO_ID,
                null,
                null);

        assertNotNull(aAckCartoMessage);
        assertEquals(Protocol.A_ACKCARTO, aAckCartoMessage.getCommand());
        assertEquals(Protocol.NO_ID, aAckCartoMessage.getId());
    }

    @Test
    public void constructor_aSetCartoMessage_isCorrect ()
    {
        /*
        aSetCartoMessage = new Protocol.Message(Protocol.A_SETCARTO,
                                                currentCarto.getMyIdCarto(),
                                                currentCarto.getName(),
                                                currentCarto.getTreatedScan());
        assertNotNull(aSetCartoMessage);
        */
    }

    @Test
    public void constructor_cSetCartoMessage_isCorrect ()
    {
        /*
        cSetCartoMessage = Protocol.Message(byte[]);
        assertNotNull(cSetCartoMessage);
        */
    }

    @Test
    public void constructor_cAck4ScanMessage_isCorrect ()
    {
        byte[] bMessage = new byte[] {0,0,0,6};

        cAck4ScanMessage = new Protocol.Message(bMessage);

        assertNotNull(cAck4ScanMessage);
        assertEquals(Protocol.C_ACK4SCAN, cAck4ScanMessage.getCommand());
    }

    @Test
    public void constructor_cAck4SaveCartoMessage_isCorrect ()
    {
        byte[] bMessage = new byte[] {0,0,0,7};

        cAck4SaveCartoMessage = new Protocol.Message(bMessage);

        assertNotNull(cAck4SaveCartoMessage);
        assertEquals(Protocol.C_ACK4SAVECARTO, cAck4SaveCartoMessage.getCommand());
    }

    @Test
    public void constructor_cAckCartoMessage_isCorrect ()
    {
        byte[] bMessage = new byte[] {0,0,0,8};

        cAckCartoMessage = new Protocol.Message(bMessage);

        assertNotNull(cAckCartoMessage);
        assertEquals(Protocol.C_ACKCARTO, cAckCartoMessage.getCommand());
    }

    @Test
    public void encodeMessage_aPing_isCorrect ()
    {
        byte[] expected = new byte[] {0,0,0,4,0,0,0,1};

        aPingMessage = new Protocol.Message(Protocol.A_PING,
                Protocol.NO_ID,
                null,
                null);

        assertArrayEquals(expected, aPingMessage.encodeMessage());
    }

    @Test
    public void encodeMessage_aAsk4Scan_isCorrect ()
    {
        byte[] expected = new byte[] {0,0,0,8,0,0,0,2,0,0,0,2};

        aAsk4ScanMessage = new Protocol.Message(Protocol.A_ASK4SCAN,
                2,
                null,
                null);

        assertArrayEquals(expected, aAsk4ScanMessage.encodeMessage());
    }

    @Test
    public void encodeMessage_aSetCarto_isCorrect ()
    {
        // byte[] expected = new byte[] {};

        // aSetCartoMessage.encodeMessage();
    }

    @Test
    public void encodeMessage_aAckCarto_isCorrect ()
    {
        byte[] expected = new byte[] {0,0,0,4,0,0,0,3};

        aAckCartoMessage = new Protocol.Message(Protocol.A_ACKCARTO,
                Protocol.NO_ID,
                null,
                null);

        assertArrayEquals(expected, aAckCartoMessage.encodeMessage());
    }

    @Test
    public void getCommand_isCorrect ()
    {
        assertEquals(defaultCommand, defaultMessage.getCommand());
    }

    @Test
    public void getCommand_isNotCorrect ()
    {
        assertNotEquals(defaultCommand + 5, defaultMessage.getCommand());
    }

    @Test
    public void getId_isCorrect ()
    {
        assertEquals(defaultId, defaultMessage.getId());
    }

    @Test
    public void getId_isNotCorrect ()
    {
        assertNotEquals(defaultId + 5, defaultMessage.getId());
    }

    @Test
    public void getName_isCorrect ()
    {
        assertEquals(defaultName, defaultMessage.getName());
    }

    @Test
    public void getName_isNotCorrect ()
    {
        assertNotEquals("not_" + defaultName, defaultMessage.getName());
    }

    @Test
    public void getFile_isCorrect ()
    {
        assertEquals(defaultFile, defaultMessage.getFile());
    }

    @After
    public void tearDown()
    {
        defaultMessage = null;
        aPingMessage = null;
        aAsk4ScanMessage = null;
        aAckCartoMessage = null;
        // aSetCartoMessage = null;
        // cSetCartoMessage = null;
        cAck4ScanMessage = null;
        cAck4SaveCartoMessage = null;
        cAckCartoMessage = null;

        defaultName = null;
        defaultFile = null;

        // reset(currentCarto);
    }
}
