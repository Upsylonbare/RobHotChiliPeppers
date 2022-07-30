/**
 * @file NetworkA.java
 *
 * @brief This class dispatch acknowledge
 *
 * @author Alfred VRIGNAUD
 * @date 11/06/2022
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
package com.prose.nirvanapp.GUI.viewmodel;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import com.prose.nirvanapp.NetworkA.Dispatcher;

/**
 * This class dispatch acknowledge
 */
public class DispatcherViewModel extends ViewModel implements Dispatcher.AckListener
{
    /**
     * Acknowledge of a scan
     */
    private MutableLiveData<Boolean> myAck4Scan;

    /**
     * Acknowledge of a carto reception
     */
    private MutableLiveData<Boolean> myAckCarto;

    /**
     * Acknowledge of a carto save
     */
    private MutableLiveData<Boolean> myAck4SaveCarto;

    /**
     * Gets acknowledge of a scan
     * @return myAck4Scan
     */
    public LiveData<Boolean> getMyAck4Scan ()
    {
        return myAck4Scan;
    }

    /**
     * Gets acknowledge of a carto reception
     * @return myAckCarto
     */
    public LiveData<Boolean> getMyAckCarto ()
    {
        return myAckCarto;
    }

    /**
     * Gets acknowledge of a carto save
     * @return myAck4SaveCarto
     */
    public LiveData<Boolean> getMyAck4SaveCarto ()
    {
        return myAck4SaveCarto;
    }

    /**
     * Constructor
     */
    public DispatcherViewModel ()
    {
        // new
        myAck4Scan = new MutableLiveData<>();
        myAckCarto = new MutableLiveData<>();
        myAck4SaveCarto = new MutableLiveData<>();

        // init
        myAck4Scan.postValue(false);
        myAckCarto.postValue(false);
        myAck4SaveCarto.postValue(false);

        // set as listener
        Dispatcher.INSTANCE.addListener(this);
    }

    /**
     *
     */
    @Override
    public void ack4Scan ()
    {
        myAck4Scan.postValue(true);
    }

    /**
     *
     */
    @Override
    public void ackCarto ()
    {
        myAckCarto.postValue(true);
    }

    /**
     *
     */
    @Override
    public void ack4SaveCarto ()
    {
        myAck4SaveCarto.postValue(true);
    }
}
