/**
 * @file HistoryFragment.java
 *
 * @brief This fragment correspond to HISTORY_SCREEN state
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
import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;


import com.prose.nirvanapp.CartoManager.CartoManager;
import com.prose.nirvanapp.CartoManager.ItemClickSupport;
import com.prose.nirvanapp.CartoManager.Carto;
import com.prose.nirvanapp.GUI.adapter.CartographyAdapter;

import com.prose.nirvanapp.R;
import com.prose.nirvanapp.GUI.activities.MainActivity;

import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

/**
 * This fragment correspond to HISTORY_SCREEN state
 *
 * @see MainActivity
 * @see Fragment
 * @see View
 */
public class HistoryFragment extends Fragment implements View.OnClickListener
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
     * Current Treated Scan Code
     */
    private static final String CURRENT_TREATED_SCAN_CODE_RESULT = "CURRENTTREATEDSCAN";
    /**
     * Current Treated Scan Code
     */
    private static final String CURRENT_TREATED_SCAN_CODE = "CurrentTreatedScanCode";
    /**
     *  Instance of bitmap to send to visualize cartography
     */
    private Bitmap bitmapToSendToVisualizeCartography;
    /**
     *  Instance of byte array to send to visualize cartography
     */
    private ByteArrayOutputStream byteArrayToSendToVisualizeCartography;

    /**
     * @brief Instance of currentCarto
     */
    private Carto currentCarto = new Carto(0,"",null,null);
    /**
     * @brief Instance of list of cartography saved
     */
    private ArrayList<Carto> history = new ArrayList<>();
    /**
     * Cartography adapter instance
     */
     CartographyAdapter cartographyAdapter;
    /**
    * RecyclerView instance
    */
    RecyclerView recyclerView;
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
    public HistoryFragment ()
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
        this.root = inflater.inflate(R.layout.fragment_history, container, false);
        //get history
        history = CartoManager.INSTANCE.getHistory();

        //create history
        if (history.isEmpty()){
            history = CartoManager.INSTANCE.createHistory();
        }

        //get recyclerview
        recyclerView = root.findViewById(R.id.myRecyclerView);

        //initialize recyclerView
        recyclerView.setLayoutManager(new LinearLayoutManager(root.getContext()));
        cartographyAdapter = new CartographyAdapter(root.getContext(),history);
        recyclerView.setAdapter(cartographyAdapter);
        this.configureOnClickRecyclerView();

        // get MainActivity
        this.activity = (MainActivity) getActivity();


        // Set onClickListener
        ((Button) root.findViewById(R.id.history_back_button)).setOnClickListener(this); // back button
        ((Button) root.findViewById(R.id.history_visualize_button)).setOnClickListener(this); // visualize button

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
            case R.id.history_visualize_button:
                bitmap2ByteArray();
                Bundle treatedScan = new Bundle();
                treatedScan.putByteArray(CURRENT_TREATED_SCAN_CODE,byteArrayToSendToVisualizeCartography.toByteArray());
                getParentFragmentManager().setFragmentResult(CURRENT_TREATED_SCAN_CODE_RESULT,treatedScan);
                Bundle nameOfCarto = new Bundle();
                nameOfCarto.putString(CURRENT_NAME_CODE,currentCarto.getName());
                getParentFragmentManager().setFragmentResult(CURRENT_NAME_CODE_RESULT,nameOfCarto);
                this.activity.displayScreen(MainActivity.IdScreen.VISUALIZE_CARTOGRAPHY_SCREEN);
                break;
            case R.id.history_back_button:
                this.activity.displayScreen(MainActivity.IdScreen.MAIN_SCREEN);
                break;
            default:
                break;
        }
    }
    /**
     * @brief configure the on click recycler view
     *
     */
    private void configureOnClickRecyclerView(){

        ItemClickSupport.addTo(recyclerView, R.layout.fragment_history)
                .setOnItemClickListener(new ItemClickSupport.OnItemClickListener() {
                    @Override
                    public void onItemClicked(RecyclerView recyclerView, int position, View v) {

                        currentCarto = history.get(position);


                        Log.e("TAG", "Position : "+position);
                        Toast.makeText(root.getContext(), history.get(position).getName()+" clicked", Toast.LENGTH_SHORT).show();
                    }
                });
    }


    /**
     * Called to convert bitmap to byte Array.
     */
    public void bitmap2ByteArray()
    {
        bitmapToSendToVisualizeCartography= currentCarto.getTreatedScan();
        byteArrayToSendToVisualizeCartography = new ByteArrayOutputStream();
        bitmapToSendToVisualizeCartography.compress(Bitmap.CompressFormat.PNG,100,byteArrayToSendToVisualizeCartography);
    }


}