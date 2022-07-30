/**
 * @file VisualizeFragment.java
 *
 * @brief This fragment correspond to VISUALIZE_SCREEN state
 *
 * @author Alfred VRIGNAUD et Loris BOUSQUET
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
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentResultListener;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;

import com.prose.nirvanapp.CartoManager.CartoManager;
import com.prose.nirvanapp.R;
import com.prose.nirvanapp.GUI.activities.MainActivity;

import java.io.ByteArrayOutputStream;


/**
 * This fragment correspond to VISUALIZE_SCREEN state
 *
 * @see MainActivity
 * @see Fragment
 * @see View
 */
public class VisualizeFragment extends Fragment implements View.OnClickListener
{
    /**
     * Return Result Code
     */
    private static final String FROM_SCAN_RESULT = "FROMSCANRESULT";
    /**
     * Return Code
     */
    private static final String FROM_SCAN = "FROM_SCAN";

    /**
     * Carto To SaveResult Code
     */
    private static final String CARTO_TO_SAVE_RESULT = "CARTOTOSAVERESULT";
    /**
     * Carto To Save Code
     */
    private static final String CARTO_TO_SAVE = "CARTOTOSAVE";
    /**
     * Return Result Code
     */
    private static final String RETURN_RESULT = "RETURNRESULT";
    /**
     * Return Code
     */
    private static final String RETURN = "RETURN";

    /**
     * Carto Result Code
     */
    private static final String CARTO_RESULT = "CARTORESULT";
    /**
     * Carto Code
     */
    private static final String CARTO = "CARTO";
    /**
     *  Instance of continueButton
     */
    private Button continueButton;
    /**
     *  Instance of bitmap to send
     */
    private Bitmap bitmapToSendToVisualize;
    /**
     *  Instance of byte array to send
     */
    private ByteArrayOutputStream byteArrayToSendToVisualize;
    /**
     * @brief Instance of receivedTreatedCarto
     */
    private Bitmap receivedTreatedCarto;
    /**
     * cartographyVisual instance
     */
    private ImageView cartographyVisual;
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
    public VisualizeFragment ()
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
        this.root = inflater.inflate(R.layout.fragment_visualize, container, false);
        //get ImageView
        cartographyVisual = root.findViewById(R.id.visualize_image_imageView);
        // get MainActivity
        this.activity = (MainActivity) getActivity();
        //get continueButton
        continueButton = root.findViewById(R.id.visualize_continue_button);
        // Set onClickListener
        ((Button) root.findViewById(R.id.visualize_modify_button)).setOnClickListener(this); // modify button
        ((Button) root.findViewById(R.id.visualize_cancel_button)).setOnClickListener(this); // cancel button
        ((Button) root.findViewById(R.id.visualize_save_button)).setOnClickListener(this);   // save button
        ((Button) root.findViewById(R.id.visualize_continue_button)).setOnClickListener(this);   // save button


        // set cartographyVisual
       getParentFragmentManager().setFragmentResultListener(CARTO_RESULT, this, new FragmentResultListener() {
            @Override
            public void onFragmentResult(@NonNull String requestKey, @NonNull Bundle result) {

                receivedTreatedCarto = BitmapFactory.decodeByteArray(result.getByteArray(CARTO),0, result.getByteArray(CARTO).length );
                cartographyVisual.setImageBitmap(receivedTreatedCarto);
            }
        });

        getParentFragmentManager().setFragmentResultListener(RETURN_RESULT, this, new FragmentResultListener() {
            @Override
            public void onFragmentResult(@NonNull String requestKey, @NonNull Bundle result) {
                if (result.getInt(RETURN) == 1 ){
                    continueButton.setEnabled(false);
                }
            }
        });


        getParentFragmentManager().setFragmentResultListener(FROM_SCAN_RESULT, this, new FragmentResultListener() {
            @Override
            public void onFragmentResult(@NonNull String requestKey, @NonNull Bundle result) {
                if (result.getString(FROM_SCAN) == "OKAY" ){
                   cartographyVisual.setImageBitmap(CartoManager.INSTANCE.getCurrentCarto().getRawScan());
                }
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
        switch (view.getId())
        {
            case R.id.visualize_modify_button:
                this.activity.displayScreen(MainActivity.IdScreen.MODIFY_SCREEN);
                break;
            case R.id.visualize_cancel_button:
                this.activity.displayScreen(MainActivity.IdScreen.SCAN_SCREEN);
                break;
            case R.id.visualize_save_button:
                bitmap2ByteArray();
                Bundle result = new Bundle();
                result.putByteArray(CARTO_TO_SAVE,byteArrayToSendToVisualize.toByteArray());
                getParentFragmentManager().setFragmentResult(CARTO_TO_SAVE_RESULT,result);
                this.activity.displayScreen(MainActivity.IdScreen.SAVE_SCREEN);
                break;
            case R.id.visualize_continue_button:
                this.activity.displayScreen(MainActivity.IdScreen.SCAN_SCREEN);
                // TODO: new scan
            default:
                break;
        }
    }

    /**
     * @brief enable to convert bitmap 2 byte
     */
    public void bitmap2ByteArray()
    {
        bitmapToSendToVisualize= receivedTreatedCarto;
        byteArrayToSendToVisualize = new ByteArrayOutputStream();
        bitmapToSendToVisualize.compress(Bitmap.CompressFormat.PNG,100,byteArrayToSendToVisualize);
    }

}