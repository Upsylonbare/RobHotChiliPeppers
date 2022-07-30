/**
 * @file Communication.java
 *
 * @brief This class has the role of managing the communication of the NirvanApp application
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

import com.prose.nirvanapp.NetworkA.Dispatcher;

import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * This class has the role of managing the communication of the NirvanApp application
 */
public class Communication implements TCPConnection.Listener
{
    /**
     * Timeout connection
     */
    private static final int CONNECTION_TIMEOUT = 10000; // ms

    /**
     * Listener interface
     */
    public interface Listener
    {
        void connected();
        void fail();
    }

    /**
     * Enable state of ConnectionState
     */
    public enum ConnectionState
    {
        WAITING,
        CONNECTED,
        ERROR
    }

    /**
     * Instance of TCPConnection
     */
    private final TCPConnection connection;

    /**
     * Instance of Communication (Singleton)
     */
    public static Communication INSTANCE = new Communication();

    /**
     * Instance of Listener
     */
    private Listener listener;

    /**
     * Ping task
     */
     private final Ping ping;

    /**
     * Reader task
     */
    private final Reader reader;

    /**
     * Constructor
     */
    private Communication()
    {
        this.connection = new TCPConnection();
        this.connection.addListener(this);

        // new thread
        ping = new Ping();
        reader = new Reader();
    }

    /**
     * ask a connection to a server
     * @param ip - ip address of the server
     * @param port - port number of the server
     */
    public void connect(String ip, int port)
    {
        connection.connect(ip, port, CONNECTION_TIMEOUT);
    }

    /**
     * ask to send a message to the socket
     * @param message - message to send
     */
    public void send(byte[] message)
    {
        connection.write(message);
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

    /**
     * Call if client is connected to a server
     */
    @Override
    public void onConnection ()
    {
        ping.start();
        // not start cause of reading problem
        // reader.start();

        if (listener != null)
            listener.connected();
    }

    /**
     * Call if client can't be connected to a server
     * @param info - error message
     */
    @Override
    public void onConnectionFail (String info)
    {
        ping.end();
        reader.end();

        if (listener != null)
            listener.fail();
    }

    /**
     * Call if client can't write on the socket
     * @param info - error message
     */
    @Override
    public void onWriteFail (String info)
    {
        ping.end();
        reader.end();

        if (listener != null)
            listener.fail();
    }

    /**
     * Call if client can't read from the socket
     * @param info - error message
     */
    @Override
    public void onReadFail (String info)
    {
        ping.end();
        reader.end();

        if (listener != null)
            listener.fail();
    }

    /**
     * Ping task class
     */
    static class Ping extends Thread
    {
        boolean running = true;

        @Override
        public void run ()
        {
            super.run();
            while (running)
            {
                Communication.INSTANCE.send(new Protocol.Message(Protocol.A_PING,-1,null,null).encodeMessage());
                try {
                    Thread.sleep(Protocol.PING_FREQ);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        /**
         * stop ping thread
         */
        void end()
        {
            running = false;
        }
    }

    /**
     * Reader task class
     */
    static class Reader extends Thread
    {
        boolean running = true;

        @Override
        public void run ()
        {
            super.run();
            while (running)
            {
                try {
                    // read 4 first byte (size of the complet message)
                    byte[] bSize = Communication.INSTANCE.connection.read(Protocol.SIZE_OF_SIZE);

                    // convert byte[] to int
                    int iSize = ByteBuffer.wrap(bSize).getInt();

                    // read message
                    byte[] data = Communication.INSTANCE.connection.read(iSize);
                    if (data != null) {
                        Protocol.Message message = new Protocol.Message(data);
                        Dispatcher.INSTANCE.dispatch(message);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        /**
         * stop reader thread
         */
        void end()
        {
            running = false;
        }
    }
}
