/**
 * @file MainFragment.java
 *
 * @brief This fragment correspond to MAIN_SCREEN state
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
package com.prose.nirvanapp.GUI.fragments;

import android.annotation.SuppressLint;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.prose.nirvanapp.GUI.popup.PopUp;
import com.prose.nirvanapp.NetworkA.Communication.Communication;
import com.prose.nirvanapp.R;
import com.prose.nirvanapp.GUI.activities.MainActivity;

/**
 * This fragment correspond to MAIN_SCREEN state
 *
 * @see MainActivity
 * @see Fragment
 * @see View
 */
public class MainFragment extends Fragment implements View.OnClickListener
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
     * Fragment constructor
     * Required empty public constructor
     */
    public MainFragment ()
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
        this.root = inflater.inflate(R.layout.fragment_main, container, false);

        // get MainActivity
        this.activity = (MainActivity) getActivity();

        // Set onClickListener
        ((Button) root.findViewById(R.id.main_visualizeCartography_button)).setOnClickListener(this); // visualise button
        ((Button) root.findViewById(R.id.main_makeCartography_button)).setOnClickListener(this); // scan button

        return this.root;
    }

    @SuppressLint ("NonConstantResourceId")
    @Override
    public void onClick (View view)
    {
        switch (view.getId())
        {
            case R.id.main_visualizeCartography_button:
                this.activity.displayScreen(MainActivity.IdScreen.HISTORY_SCREEN);
                break;
            case R.id.main_makeCartography_button:
                this.activity.displayScreen(MainActivity.IdScreen.SCAN_SCREEN);
                break;
            default:
                break;
        }
    }
}