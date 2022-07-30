/**
 * @file TCPConnection.java
 *
 * @brief This class interact with the socket
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
package com.prose.nirvanapp.NetworkA.Communication;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * This class interact with the socket
 */
public class TCPConnection
{
    /**
     * Listener interface
     */
    interface Listener {
        void onConnection();
        void onConnectionFail(String info);
        void onWriteFail(String info);
        void onReadFail(String info);
    }

    /**
     * signal read fail.
     * @param exception
     * @return
     */
    private IOException signalOnReadFail(IOException exception) {
        if (this.listener != null) {
            this.listener.onReadFail(exception.getMessage());
        }
        return exception;
    }

    /**
     * Instance of Listener
     */
    private Listener listener;

    /**
     * Instance of Socket
     */
    private Socket socket;

    /**
     * Instance of ExecutorService
     */
    private ExecutorService executorService;

    /**
     * Connection constructor
     */
    public TCPConnection ()
    {
        this.executorService = Executors.newSingleThreadExecutor();
    }

    /**
     * Establish the connection
     *
     * @param ip - server ip address
     * @param port - server port
     */
    public void connect(String ip, int port, int timeout)
    {
        Runnable runnable = () -> {
            socket = new Socket();

            try
            {
                SocketAddress socketAddress = new InetSocketAddress(InetAddress.getByName(ip), port);
                socket.connect(socketAddress, timeout);

                if (listener != null)
                    listener.onConnection();

            } catch (IOException e) {
                if (listener != null)
                    listener.onConnectionFail(e.getMessage());

                e.printStackTrace();
            }
        };

        executorService.execute(runnable);
    }

    /**
     * Write data to the socket
     *
     * @param message - data to write
     */
    public void write(byte[] message)
    {
        Runnable runnable = () -> {
            try
            {
                if (socket != null)
                    socket.getOutputStream().write(message);

            } catch (IOException e) {
                if (listener != null)
                    listener.onWriteFail(e.getMessage());
            }
        };

        executorService.execute(runnable);
    }

    /**
     * Read data from the socket
     *
     * @return data read
     */
    public byte[] read(int size) throws IOException
    {
        try {
            byte[] msg = new byte[size];

            if (socket != null)
                socket.getInputStream().read(msg);

            return msg;

        } catch (IOException e) {
            throw signalOnReadFail(e);
        }
    }

    /**
     * add a listener
     * @param listener - listener to add
     */
    public void addListener(Listener listener)
    {
        this.listener = listener;
    }

    /**
     * delete a listener
     * @param listener - listener to delete
     */
    public void deleteListener(Listener listener)
    {
        this.listener = null;
    }

}
