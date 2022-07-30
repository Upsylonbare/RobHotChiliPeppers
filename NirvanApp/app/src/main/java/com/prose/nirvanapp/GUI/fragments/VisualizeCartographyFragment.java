/**
 * @file VisualizeCartographyFragment.java
 *
 * @brief This fragment correspond to VISUALIZE_CARTOGRAPHY_SCREEN state
 *
 * @author Alfred VRIGNAUD and Loris BOUSQUET
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
package com.prose.nirvanapp.GUI.fragments;

import android.annotation.SuppressLint;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentResultListener;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.prose.nirvanapp.GUI.popup.PopUp;
import com.prose.nirvanapp.NetworkA.Communication.Communication;
import com.prose.nirvanapp.R;
import com.prose.nirvanapp.GUI.activities.MainActivity;

/**
 * This fragment correspond to VISUALIZE_CARTOGRAPHY_SCREEN state
 *
 * @see MainActivity
 * @see Fragment
 * @see View
 */
public class VisualizeCartographyFragment extends Fragment implements View.OnClickListener
{
    /**
     * Current Name Result Code
     */
    private static final String CURRENT_NAME_CODE_RESULT = "CURRENTNAME";
    /**
     * Current Name Code
     */
    private static final String CURRENT_NAME_CODE = "CurrentName";
    /**
     * Current Treated Scan Result Code
     */
    private static final String CURRENT_RECEIVED_TREATED_SCAN_CODE_RESULT = "CURRENTTREATEDSCAN";
    /**
     * Current Treated Scan Code
     */
    private static final String CURRENT_RECEIVED_TREATED_SCAN_CODE = "CurrentTreatedScanCode";
    /**
     * cartographyName instance
     */
    private TextView cartographyName;
    /**
     * treatedCartographyVisual instance
     */
    private ImageView treatedCartographyVisual;
    /**
     * receivedTreatedCarto instance
     */
    private Bitmap receivedTreatedCarto;
    /**
     * receivedNameinstance
     */
    private String receivedName;

    /**
     * MainActivity instance
     */
    private MainActivity activity;

    /**
     * Root of the fragment layout View
     */
    private View root;

    /**
     * Fragment constructor
     * Required empty public constructor
     */
    public VisualizeCartographyFragment ()
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
        this.root = inflater.inflate(R.layout.fragment_visualize_cartography, container, false);
        // get treatedCartographyVisual
        treatedCartographyVisual =  root.findViewById(R.id.visualizeCarto_treatedScan_imageView);
        // get cartographyName
        cartographyName = root.findViewById(R.id.visualizeCarto_name_texteView);
        // get MainActivity
        this.activity = (MainActivity) getActivity();

        // Set onClickListener
        ((Button) root.findViewById(R.id.visualizeCarto_back_button)).setOnClickListener(this); // back button

        getParentFragmentManager().setFragmentResultListener(CURRENT_NAME_CODE_RESULT, this, new FragmentResultListener() {
                    @Override
                    public void onFragmentResult(@NonNull String requestKey, @NonNull Bundle result) {

                        receivedName = result.getString(CURRENT_NAME_CODE);
                        cartographyName.setText(receivedName);
                    }
                });
        getParentFragmentManager().setFragmentResultListener(CURRENT_RECEIVED_TREATED_SCAN_CODE_RESULT, this, new FragmentResultListener() {
            @Override
            public void onFragmentResult(@NonNull String requestKey, @NonNull Bundle result) {

                receivedTreatedCarto = BitmapFactory.decodeByteArray(result.getByteArray(CURRENT_RECEIVED_TREATED_SCAN_CODE),0, result.getByteArray(CURRENT_RECEIVED_TREATED_SCAN_CODE).length );
                treatedCartographyVisual.setImageBitmap(receivedTreatedCarto);
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
        if (view.getId() == R.id.visualizeCarto_back_button)
        {
            this.activity.displayScreen(MainActivity.IdScreen.HISTORY_SCREEN);
        }
    }
}