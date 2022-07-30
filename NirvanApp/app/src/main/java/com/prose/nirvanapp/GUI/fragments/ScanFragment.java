/**
 * @file ScanFragment.java
 *
 * @brief This fragment correspond to SCAN_SCREEN state
 *
 * @author Alfred VRIGNAUD
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
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;

import com.prose.nirvanapp.GUI.popup.PopUp;
import com.prose.nirvanapp.NetworkA.Communication.Communication;
import com.prose.nirvanapp.NetworkA.ProxyGeographer;
import com.prose.nirvanapp.R;
import com.prose.nirvanapp.GUI.activities.MainActivity;

/**
 * This fragment correspond to SCAN_SCREEN state
 *
 * @see MainActivity
 * @see Fragment
 * @see View
 * @see Spinner
 */
public class ScanFragment extends Fragment implements View.OnClickListener
{
    /**
     * MainActivity instance
     */
    private MainActivity activity;

    /**
     * Root of the fragment layout View
     */
    private View root;

    /**
     * Spinner
     */
    private Spinner markSpinner;

    /**
     * Proxy
     */
    private ProxyGeographer proxyGeographer;

    /**
     * Marker
     */
    private int marker;

    /**
     * Fragment constructor
     * Required empty public constructor
     */
    public ScanFragment ()
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
        this.root = inflater.inflate(R.layout.fragment_scan, container, false);

        // get MainActivity
        this.activity = (MainActivity) getActivity();

        // Spinner
        markSpinner = (Spinner) root.findViewById(R.id.scan_mark_spinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this.getContext(),
                R.array.marks_array,
                android.R.layout.simple_spinner_item);

        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        markSpinner.setAdapter(adapter);

        // When user select a List-Item.
        markSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {

            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                onItemSelectedHandler(parent, view, position, id);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        // Set onClickListener
        ((Button) root.findViewById(R.id.scan_scan_button)).setOnClickListener(this); // scan button
        ((Button) root.findViewById(R.id.scan_back_button)).setOnClickListener(this); // back button

        // new
        proxyGeographer = new ProxyGeographer();

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
            case R.id.scan_scan_button:
                // call ask4Scan from proxy
                proxyGeographer.ask4Scan(marker);
                this.activity.displayScreen(MainActivity.IdScreen.WAIT_SCAN_SCREEN);
                break;
            case R.id.scan_back_button:
                this.activity.displayScreen(MainActivity.IdScreen.MAIN_SCREEN);
                break;
            default:
                break;
        }
    }

    private void onItemSelectedHandler(AdapterView<?> adapterView, View view, int position, long id) {
        Adapter adapter = adapterView.getAdapter();

        String sItem = (String) adapter.getItem(position);
        try
        {
            marker = Integer.parseInt(sItem.substring(1));
        }
        catch (NumberFormatException e)
        {
            marker = -1;
        }
    }
}