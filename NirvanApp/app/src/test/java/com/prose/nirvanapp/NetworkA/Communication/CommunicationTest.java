package com.prose.nirvanapp.NetworkA.Communication;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.doNothing;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.reset;
import static org.mockito.Mockito.when;

import com.prose.nirvanapp.GUI.viewmodel.NetworkAViewModel;

/**
 * Communication unit test
 */
@RunWith (JUnit4.class)
public class CommunicationTest
{
    private final int timeout = 10000;
    private String ipAddress;
    private int portNumber;
    private Communication communication;

    @Mock
    private NetworkAViewModel networkAViewModel;

    @Mock
    private TCPConnection tcpConnection;

    @Before
    public void setup ()
    {
        MockitoAnnotations.initMocks(this);

        communication = Communication.INSTANCE;

        ipAddress = "127.0.0.1";
        portNumber = 12345;
    }

    @Test
    public void singleton_isCorrect ()
    {
        assertEquals(communication, Communication.INSTANCE);
    }

    @Test
    public void connect_isCorrect ()
    {
        communication.connect(ipAddress, portNumber);
        doNothing().when(tcpConnection).connect(ipAddress, portNumber, timeout);
    }

    @Test
    public void send_isCorrect ()
    {
        byte[] message2send = new byte[] {0,0,0,4,0,0,0,1};

        communication.send(message2send);

        doNothing().when(tcpConnection).write(message2send);
    }

    @After
    public void tearDown ()
    {
        // reset mock
        reset(tcpConnection);
        reset(networkAViewModel);
    }
}
