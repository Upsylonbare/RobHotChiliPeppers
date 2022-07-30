/**
 * @file MainActivity.java
 *
 * @brief This activity is the main activity of the app
 *
 * @author Alfred VRIGNAUD
 * @date 24/05/2022
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
 *
 */
package com.prose.nirvanapp.GUI.activities;

import android.os.Bundle;
import android.os.Handler;
import android.view.KeyEvent;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.NavController;
import androidx.navigation.fragment.NavHostFragment;

import com.prose.nirvanapp.GUI.popup.PopUp;
import com.prose.nirvanapp.GUI.viewmodel.NetworkAViewModel;
import com.prose.nirvanapp.R;

/**
 * This activity is the main activity of the app
 *
 * @see PopUp
 * @see NavController
 * @see NavHostFragment
 */
public class MainActivity extends AppCompatActivity
{
    /**
     * Server ip address
     */
    private static final String IP_ADDRESS = "192.168.72.1";

    /**
     * Server port number
     */
    private static final int PORT_NUMBER = 12345;

    /**
     * screen id
     */
    public enum IdScreen
    {
        START_SCREEN,
        CONNECTION_SCREEN,
        MAIN_SCREEN,
        HISTORY_SCREEN,
        VISUALIZE_CARTOGRAPHY_SCREEN,
        SCAN_SCREEN,
        WAIT_SCAN_SCREEN,
        VISUALIZE_SCREEN,
        MODIFY_SCREEN,
        SAVE_SCREEN
    }

    /**
     * starting time correspond to 3 seconds
     */
    private final static int STARTING_TIME = 3000;

    /**
     * Navigation controller for fragments navigation
     */
    private NavController navController;
    /**
     * PopUp
     */
    private PopUp myPopUp;

    /**
     * Connection state
     */
    private NetworkAViewModel networkAViewModel;

    /**
     * @brief This method initialize MainActivity, it is called when the activity is starting
     *
     * @param savedInstanceState - If the activity is being re-initialized after previously being shut down then this Bundle
     *                           contains the data it most recently supplied in onSaveInstanceState(Bundle).
     *                           Note: Otherwise it is null.
     */
    @Override
    protected void onCreate (Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // fragment navigation
            NavHostFragment navHostFragment =
                (NavHostFragment) getSupportFragmentManager().findFragmentById(R.id.fragment_nav_host);
        assert navHostFragment != null;
        navController = navHostFragment.getNavController();

        // splash screen delay
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                displayScreen(IdScreen.CONNECTION_SCREEN);
            }
        }, STARTING_TIME);

        // new
        myPopUp = new PopUp();

        // connection state
        networkAViewModel = new ViewModelProvider(this).get(NetworkAViewModel.class);

        // Observe connection
        networkAViewModel.getMyConnectionState().observe(this, connectionState -> {
            switch (connectionState)
            {
                case CONNECTED:
                    displayScreen(IdScreen.MAIN_SCREEN);
                    break;
                case WAITING:
                    // do nothing
                    break;
                case ERROR:
                    myPopUp.showPopUp(PopUp.IdPopUp.CONNECTION_ERROR_POPUP, this);
                    displayScreen(IdScreen.CONNECTION_SCREEN);
                    break;
                default:
                    break;
            }
        });
    }

    /**
     * @brief display screen
     *
     * @param idScreen - id of the screen we want to display
     */
    public void displayScreen(IdScreen idScreen)
    {
        switch (idScreen)
        {
            case START_SCREEN:
                navController.navigate(R.id.startFragment);
                break;
            case CONNECTION_SCREEN:
                navController.navigate(R.id.connectionFragment);
                break;
            case MAIN_SCREEN:
                navController.navigate(R.id.mainFragment);
                break;
            case HISTORY_SCREEN:
                navController.navigate(R.id.historyFragment);
                break;
            case VISUALIZE_CARTOGRAPHY_SCREEN:
                navController.navigate(R.id.visualizeCartographyFragment);
                break;
            case SCAN_SCREEN:
                navController.navigate(R.id.scanFragment);
                break;
            case WAIT_SCAN_SCREEN:
                navController.navigate(R.id.waitScanFragment);
                break;
            case VISUALIZE_SCREEN:
                navController.navigate(R.id.visualizeFragment);
                break;
            case MODIFY_SCREEN:
                navController.navigate(R.id.modifyFragment);
                break;
            case SAVE_SCREEN:
                navController.navigate(R.id.saveFragment);
                break;
            default:
                break;
        }
    }


    /**
     * Gets port number
     *
     * @return value of port number
     */
    public static int getPortNumber ()
    {
        return PORT_NUMBER;
    }

    /**
     * Gets ip address
     *
     * @return values of ip address
     */
    public static String getIpAddress ()
    {
        return IP_ADDRESS;
    }

    /**
     * Gets connection state
     *
     * @return connection state
     */
    public NetworkAViewModel getNetworkA ()
    {
        return networkAViewModel;
    }

    /**
     * @brief This method manage quit pop up window
     *
     * @param keyCode - The value in event.getKeyCode().
     * @param event - Description of the key event.
     * @return If you handled the event, return true. If you want to allow the event to be handled by the next receiver, return false.
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if (keyCode == KeyEvent.KEYCODE_BACK)
        {
            myPopUp.showPopUp(PopUp.IdPopUp.QUIT_POPUP, this);
            return true;
        }
        return false;
    }
}