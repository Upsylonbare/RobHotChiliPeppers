package com.prose.nirvanapp.NetworkA;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.reset;

import android.graphics.Bitmap;

import com.prose.nirvanapp.CartoManager.CartoManager;
import com.prose.nirvanapp.GUI.viewmodel.DispatcherViewModel;
import com.prose.nirvanapp.NetworkA.Communication.Protocol;

/**
 * Dispatcher unit test
 *
 * @see Dispatcher
 * @see DispatcherViewModel
 * @see CartoManager
 * @see Protocol.Message
 */
public class DispatcherTest
{
    private Dispatcher dispatcher;

    @Mock
    private DispatcherViewModel dispatcherViewModel;

    private Protocol.Message message;

    @Before
    public void setup ()
    {
        MockitoAnnotations.initMocks(this);

        dispatcher = Dispatcher.INSTANCE;
    }

    @Test
    public void singleton_isCorrect ()
    {
        assertEquals(dispatcher, Dispatcher.INSTANCE);
    }

    // TODO: implement test
    /*
    @Test(expected = Exception.class)
    public void dispatch_SetCarto_isCorrect ()
    {
        int expectedId = 1;
        String expectedName = null;
        Bitmap expectedFile = Bitmap.createBitmap(1200, 1200, Bitmap.Config.ALPHA_8);

        message = new Protocol.Message(Protocol.C_SETCARTO, expectedId, expectedName, expectedFile);

        dispatcher.dispatch(message);
    }
    */

    @Test(expected = Exception.class)
    public void dispatch_Ack4Scan_isCorrect ()
    {
        message = new Protocol.Message(Protocol.C_ACK4SCAN, Protocol.NO_ID, null, null);

        dispatcher.dispatch(message);

        doThrow().when(dispatcherViewModel).ack4Scan();
    }

    @Test(expected = Exception.class)
    public void dispatch_Ack4SaveCarto_isCorrect ()
    {
        message = new Protocol.Message(Protocol.C_ACK4SAVECARTO, Protocol.NO_ID, null, null);

        dispatcher.dispatch(message);

        doThrow().when(dispatcherViewModel).ack4SaveCarto();
    }

    @Test(expected = Exception.class)
    public void dispatch_AckCarto_isCorrect ()
    {
        message = new Protocol.Message(Protocol.C_ACKCARTO, Protocol.NO_ID, null, null);

        dispatcher.dispatch(message);

        doThrow().when(dispatcherViewModel).ackCarto();
    }

    @After
    public void tearDown ()
    {
        // reset mock
        reset(dispatcherViewModel);

        dispatcher = null;
        message = null;
    }

}
