/**
 * @file NetworkA.java
 *
 * @brief This class give the connection state between NirvanApp and ACDSoft
 *
 * @author Alfred VRIGNAUD
 * @date 07/06/2022
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

import com.prose.nirvanapp.NetworkA.Communication.Communication;

/**
 * This class give the connection state between NirvanApp and ACDSoft
 */
public class NetworkAViewModel extends ViewModel implements Communication.Listener
{
    /**
     * Connection state between NirvanApp and ACDSoft
     */
    private MutableLiveData<Communication.ConnectionState> myConnectionState;

    /**
     * Get connection state
     * @return myConnectionState
     */
    public LiveData<Communication.ConnectionState> getMyConnectionState ()
    {
        return myConnectionState;
    }

    /**
     * Constructor
     */
    public NetworkAViewModel ()
    {
        myConnectionState = new MutableLiveData<>();
        myConnectionState.postValue(Communication.ConnectionState.WAITING);
        Communication.INSTANCE.addListener(this);
    }

    /**
     * Call if client is connected to the server
     */
    @Override
    public void connected ()
    {
        myConnectionState.postValue(Communication.ConnectionState.CONNECTED);
    }

    /**
     * Call if there is a connection error
     */
    @Override
    public void fail ()
    {
        myConnectionState.postValue(Communication.ConnectionState.ERROR);
    }
}
