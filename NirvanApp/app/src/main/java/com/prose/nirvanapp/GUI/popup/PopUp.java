/**
 * @file PopUp.java
 *
 * @brief This class centralize PopUp data
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
package com.prose.nirvanapp.GUI.popup;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;

import com.prose.nirvanapp.R;
import com.prose.nirvanapp.GUI.activities.MainActivity;

/**
 * This class centralize PopUp data
 *
 * @see IdPopUp
 * @see MainActivity
 * @see AlertDialog
 */
public class PopUp
{
    /**
     * Values corresponding to popUp id
     */
    public enum IdPopUp
    {
        /**
         * Quit pop up
         */
        QUIT_POPUP,

        /**
         * Connection error pop up
         */
        CONNECTION_ERROR_POPUP,

        /**
         * Error pop up
         */
        ERROR_POPUP
    }

    /**
     * Display a pop up
     *
     * @param idPopUp - id of the pop up
     * @param context - context to display
     */
    public void showPopUp(IdPopUp idPopUp, Context context)
    {
        switch (idPopUp)
        {
            case QUIT_POPUP:
                new AlertDialog.Builder(context)
                        .setTitle(context.getString(R.string.popup_quit_title))
                        .setMessage(context.getString(R.string.popup_quit_message))
                        .setNegativeButton(context.getString(R.string.close_popup),
                                new DialogInterface.OnClickListener()
                                {
                                    public void onClick(DialogInterface dialog, int which)
                                    {
                                    }
                                })
                        .setPositiveButton(context.getString(R.string.confirm_popup),
                                new DialogInterface.OnClickListener()
                                {
                                    public void onClick(DialogInterface dialog, int which)
                                    {
                                        // quit app
                                        System.exit(0);
                                    }
                                })
                        .create()
                        .show();
                break;
            case CONNECTION_ERROR_POPUP:
                new AlertDialog.Builder(context)
                        .setTitle(context.getString(R.string.popup_connectionError_title))
                        .setMessage(context.getString(R.string.popup_connectionError_message))
                        .setPositiveButton(context.getString(R.string.ok_popup),
                                new DialogInterface.OnClickListener()
                                {
                                    public void onClick(DialogInterface dialog, int which)
                                    {
                                    }
                                })
                        .create()
                        .show();
                break;
            case ERROR_POPUP:
                new AlertDialog.Builder(context)
                        .setTitle(context.getString(R.string.default_popup_error_title))
                        .setMessage(context.getString(R.string.default_popup_error_message))
                        .setPositiveButton(context.getString(R.string.ok_popup),
                                new DialogInterface.OnClickListener()
                                {
                                    public void onClick(DialogInterface dialog, int which)
                                    {
                                    }
                                })
                        .create()
                        .show();
                break;
            default:
                break;
        }
    }
}
