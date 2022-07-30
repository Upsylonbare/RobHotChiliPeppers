/**
 * @file SaveFragment.java
 *
 * @brief This fragment correspond to SAVE_SCREEN state
 *
 * @author Alfred VRIGNAUD and Loris BOUSQUET
 * @date 25/05/2022
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
package com.prose.nirvanapp.GUI.fragments;

import android.annotation.SuppressLint;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentResultListener;
import androidx.lifecycle.ViewModelProvider;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;

import com.prose.nirvanapp.CartoManager.CartoManager;
import com.prose.nirvanapp.GUI.popup.PopUp;
import com.prose.nirvanapp.GUI.viewmodel.DispatcherViewModel;
import com.prose.nirvanapp.NetworkA.Communication.Communication;
import com.prose.nirvanapp.NetworkA.Dispatcher;
import com.prose.nirvanapp.NetworkA.ProxyGeographer;
import com.prose.nirvanapp.R;
import com.prose.nirvanapp.GUI.activities.MainActivity;

import java.io.IOException;

/**
 * This fragment correspond to SAVE_SCREEN state
 *
 * @see MainActivity
 * @see Fragment
 * @see View
 */
public class SaveFragment extends Fragment implements View.OnClickListener
{
    /**
     * Carto To SaveResult Code
     */
    private static final String CARTO_TO_SAVE_RESULT = "CARTOTOSAVERESULT";
    /**
     * Carto To Save Code
     */
    private static final String CARTO_TO_SAVE = "CARTOTOSAVE";
    /**
     *  Instance of bitmap to Receive
     */
    private Bitmap currentTreatedScan;

    /**
     * Instance of namingCarto
     */
    private EditText namingCarto;

    /**
     * MainActivity instance
     */
    private MainActivity activity;

    /**
     * Root of the fragment layout View
     */
    private View root;

    /**
     * Dispatcher view model
     */
    private DispatcherViewModel dispatcherViewModel;

    /**
     * Instance of ProxyGeographer
     */
    private ProxyGeographer proxyGeographer;

    /**
     * Fragment constructor
     * Required empty public constructor
     */
    public SaveFragment ()
    {
    }

    /**
     * Called to have the fragment instantiate its user interface view.
     *
     * @param inflater LayoutInflater: The LayoutInflater object that can be used to inflate any views in the fragment,
     * @param container ViewGroup: If non-null, this is the parent view that the fragment's UI should be attached to. The fragment should not add the view itself, but this can be used to generate the LayoutParams of the view.
     * @param savedInstanceState Bundle: If non-null, this fragment is being re-constructed from a previous saved state as given here.
     * @return Return the View for the fragment's UI, or null.
     */
    @Override
    public View onCreateView (LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        this.root = inflater.inflate(R.layout.fragment_save, container, false);

        // get MainActivity
        this.activity = (MainActivity) getActivity();

        //get EditText
        namingCarto = root.findViewById(R.id.save_name_editText);

        // Set onClickListener
        ((Button) root.findViewById(R.id.save_save_button)).setOnClickListener(this); // save button

        // new
        dispatcherViewModel = new ViewModelProvider(this.activity).get(DispatcherViewModel.class);
        proxyGeographer = new ProxyGeographer();

        getParentFragmentManager().setFragmentResultListener(CARTO_TO_SAVE_RESULT, this, new FragmentResultListener() {
            @Override
            public void onFragmentResult(@NonNull String requestKey, @NonNull Bundle result) {
                currentTreatedScan = BitmapFactory.decodeByteArray(
                        result.getByteArray(CARTO_TO_SAVE),
                        0,
                        result.getByteArray(CARTO_TO_SAVE).length );
            }
        });

        return this.root;
    }
    /**
     *
     * @param view
     */
    @SuppressLint ("NonConstantResourceId")
    @Override
    public void onClick (View view)
    {
        if (view.getId() == R.id.save_save_button)
        {
            // put name in currentCarto
            CartoManager.INSTANCE.setCurrentCarto(
                    CartoManager.INSTANCE.getCurrentCarto().getMyIdCarto(),
                    namingCarto.toString(),
                    currentTreatedScan,
                    null);

            // send carto to acdsoft (doesn't work)
            // proxyGeographer.setCarto(CartoManager.INSTANCE.getCurrentCarto());

            // remove or comment this line if communication is ok
            CartoManager.INSTANCE.ask4SaveCarto(this.activity,currentTreatedScan,namingCarto);
            this.activity.displayScreen(MainActivity.IdScreen.MAIN_SCREEN);

            // observe ack
            /*
            dispatcherViewModel.getMyAckCarto().observe(this.activity, ack -> {
                if(ack)
                    CartoManager.INSTANCE.ask4SaveCarto(this.activity,currentTreatedScan,namingCarto);
            });

            dispatcherViewModel.getMyAck4SaveCarto().observe(this.activity, ack -> {
                if(ack)
                    this.activity.displayScreen(MainActivity.IdScreen.MAIN_SCREEN);
            });
            */
        }
    }
}