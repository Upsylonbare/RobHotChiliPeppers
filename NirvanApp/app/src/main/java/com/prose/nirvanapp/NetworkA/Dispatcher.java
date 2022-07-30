/**
 * @file Dispatcher.java
 *
 * @brief This class distribute message receive from the socket
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
package com.prose.nirvanapp.NetworkA;

import com.prose.nirvanapp.CartoManager.CartoManager;
import com.prose.nirvanapp.NetworkA.Communication.Communication;
import com.prose.nirvanapp.NetworkA.Communication.Protocol;

import java.util.ArrayList;
import java.util.List;

/**
 * This class distribute message receive from the socket
 */
public class Dispatcher
{
    /**
     * Instance of Dispatcher (singleton)
     */
    public static Dispatcher INSTANCE = new Dispatcher();

    /**
     * Listener interface
     */
    public interface AckListener
    {
        void ack4Scan(); // ack a scan
        void ackCarto(); // ack carto reception
        void ack4SaveCarto(); // ack carto save
    }

    /**
     * List of listener
     */
    private AckListener listener;

    /**
     * add a listener
     * @param listener - listener to add
     */
    public void addListener(AckListener listener)
    {
        this.listener = listener;
    }

    /**
     * delete a listener
     * @param listener - listener to delete
     */
    public void deleteListener(AckListener listener)
    {
        this.listener = null;
    }

    /**
     * dispatch a message
     * @param message
     */
    public void dispatch(Protocol.Message message)
    {
        switch (message.getCommand())
        {
            case Protocol.C_SETCARTO:
                CartoManager.INSTANCE.setCurrentCarto(
                        message.getId(),
                        message.getName(),
                        null,
                        message.getFile());
                break;
            case Protocol.C_ACK4SCAN:
                listener.ack4Scan();
                break;
            case Protocol.C_ACK4SAVECARTO:
                listener.ack4SaveCarto();
                break;
            case Protocol.C_ACKCARTO:
                listener.ackCarto();
                break;
            default:
                // unknown command
                break;
        }
    }
}
