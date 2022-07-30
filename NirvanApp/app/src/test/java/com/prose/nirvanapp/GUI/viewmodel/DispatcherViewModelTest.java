package com.prose.nirvanapp.GUI.viewmodel;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import androidx.lifecycle.MutableLiveData;

import com.prose.nirvanapp.NetworkA.Communication.Communication;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

/**
 * DispatcherViewModel unit test
 *
 * @see DispatcherViewModel
 */
@RunWith(JUnit4.class)
public class DispatcherViewModelTest
{
    private DispatcherViewModel dispatcherViewModel;

    @Before
    public void setup ()
    {
        dispatcherViewModel = new DispatcherViewModel();
    }

    @Test
    public void constructor_isCorrect ()
    {
        assertNotNull(dispatcherViewModel);
    }

    @Test
    public void getMyAck4Scan_isCorrect ()
    {
        assertNotEquals(Boolean.TRUE, dispatcherViewModel.getMyAck4Scan().getValue());
    }

    @Test
    public void getMyAckCarto_isCorrect ()
    {
        assertNotEquals(Boolean.TRUE, dispatcherViewModel.getMyAckCarto().getValue());

    }

    @Test
    public void getMyAck4SaveCarto_isCorrect ()
    {
        assertNotEquals(Boolean.TRUE, dispatcherViewModel.getMyAck4SaveCarto().getValue());
    }

    @Test
    public void ack4Scan_isCorrect ()
    {
        dispatcherViewModel.ack4Scan();
        assertNotEquals(Boolean.FALSE, dispatcherViewModel.getMyAck4Scan().getValue());
    }

    @Test
    public void ackCarto_isCorrect ()
    {
        dispatcherViewModel.ackCarto();
        assertNotEquals(Boolean.FALSE, dispatcherViewModel.getMyAckCarto().getValue());
    }

        @Test
    public void ack4SaveCarto_isCorrect ()
    {
        dispatcherViewModel.ack4SaveCarto();
        assertNotEquals(Boolean.FALSE, dispatcherViewModel.getMyAck4SaveCarto().getValue());
    }

    @After
    public void tearDown()
    {
        dispatcherViewModel = null;
    }
}
