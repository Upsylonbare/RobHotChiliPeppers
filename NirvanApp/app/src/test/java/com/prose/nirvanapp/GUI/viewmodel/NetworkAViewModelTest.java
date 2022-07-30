package com.prose.nirvanapp.GUI.viewmodel;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

import androidx.lifecycle.MutableLiveData;

import com.prose.nirvanapp.NetworkA.Communication.Communication;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

/**
 * NetworkAViewModel unit test
 *
 * @see NetworkAViewModel
 */
@RunWith (JUnit4.class)
public class NetworkAViewModelTest
{
    private NetworkAViewModel networkAViewModel;
    private MutableLiveData<Communication.ConnectionState> expectedValue;

    @Before
    public void setup ()
    {
        networkAViewModel = new NetworkAViewModel();
        expectedValue = new MutableLiveData<>();
    }

    @Test
    public void constructor_isCorrect ()
    {
        assertNotNull(networkAViewModel);
    }

    @Test
    public void getMyConnectionState_isCorrect ()
    {
        expectedValue.postValue(Communication.ConnectionState.WAITING);
        assertEquals(expectedValue.getValue(), networkAViewModel.getMyConnectionState().getValue());
    }

    @Test
    public void connected_isCorrect ()
    {
        expectedValue.postValue(Communication.ConnectionState.CONNECTED);
        networkAViewModel.connected();
        assertEquals(expectedValue.getValue(), networkAViewModel.getMyConnectionState().getValue());
    }

    @Test
    public void fail_isCorrect ()
    {
        expectedValue.postValue(Communication.ConnectionState.ERROR);
        networkAViewModel.fail();
        assertEquals(expectedValue.getValue(), networkAViewModel.getMyConnectionState().getValue());
    }

    @After
    public void tearDown()
    {
        networkAViewModel = null;
        expectedValue = null;
    }
}
