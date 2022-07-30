/**
 * @file Protocol.java
 *
 * @brief This class is used to gather all the data concerning the protocol of communication used.
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

import android.graphics.Bitmap;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * This class is used to gather all the data concerning the protocol of communication used.
 */
public class Protocol
{
    /**
     * Ping frequence
     */
    static final int PING_FREQ = 1000; // ms

    /**
     * No id value
     */
    public static final int NO_ID = -1;

    /**
     * Size of size
     */
    public static final int SIZE_OF_SIZE = 4;

    /**
     * Size of command
     */
    public static final int SIZE_OF_COMMAND = 4;

    /**
     * Size of id
     */
    public static final int SIZE_OF_ID = 4;

    /**
     * Command to send a ping
     */
    public static final int A_PING = 1;

    /**
     * Command to ask for a scan
     */
    public static final int A_ASK4SCAN = 2;

    /**
     * Command to acknowledge carto reception
     */
    public static final int A_ACKCARTO = 3;

    /**
     * Command to set a carto
     */
    public static final int A_SETCARTO = 4;

    /**
     * Command to receive a carto
     */
    public static final int C_SETCARTO = 5;

    /**
     * Command to acknowledge for a scan
     */
    public static final int C_ACK4SCAN = 6;

    /**
     * Command to acknowledge carto save
     */
    public static final int C_ACK4SAVECARTO = 7;

    /**
     * Command to acknowledge a carto reception
     */
    public static final int C_ACKCARTO = 8;

    /**
     * this class represent a message
     */
    public static class Message
    {
        /**
         * Size of ping message
         */
        static final int SIZE_OF_PING = SIZE_OF_COMMAND; // command

        /**
         * Size of ask4scan message
         */
        static final int SIZE_OF_ASK4SCAN = SIZE_OF_COMMAND + SIZE_OF_ID ; // command | id

        /**
         * Size of ack message
         */
        static final int SIZE_OF_ACK = SIZE_OF_COMMAND; // command

        /**
         * Size of the message
         */
        int size;

        /**
         * Command
         */
        int command;

        /**
         * Carto id
         */
        int id;

        /**
         * Carto name
         */
        String name;

        /**
         * Carto bitmap file
         */
        Bitmap file;

        /**
         * Encode a message
         *
         * @param command - command
         * @param id - id (marker or carto id)
         * @param name - carto name
         * @param file - carto file
         */
        public Message (int command, int id, String name, Bitmap file)
        {
            this.command = command;
            this.id = id;
            this.name = name;
            this.file = file;

            switch (command)
            {
                case A_PING:
                    this.size = SIZE_OF_PING;
                    break;
                case A_ASK4SCAN:
                    this.size = SIZE_OF_ASK4SCAN;
                    break;
                case A_ACKCARTO:
                    this.size = SIZE_OF_ACK;
                    break;
                case A_SETCARTO:
                    this.size =     SIZE_OF_COMMAND // command size
                               +    SIZE_OF_ID // id size
                               +    this.name.length() // name size
                               +    this.file.getAllocationByteCount(); // file size
                    break;
                default:
                    this.size = 0;
                    break;
            }
        }

        /**
         * Decode a message
         * @param message - message to decode
         */
        public Message (byte[] message) throws IOException
        {
            ByteBuffer byteBuffer = ByteBuffer.wrap(message);

            this.command = byteBuffer.getInt();

            if(command == C_SETCARTO)
            {
                /*
                // decode carto id
                this.id = byteBuffer.getInt();

                // decode carto name -> null (ACDSOFT doesn't send carto name)
                this.name = null;

                // set buffer position to 24 (size of cmd (4) + size of id (4) + max size name (16))
                byteBuffer.position(24);

                // TODO: decode bitmap file
                    // create byte[]
                    // get byte from buffer
                    // create bitmap file with bytesFile

                 */
            }


        }

        /**
         * Encode a message
         * @return a encoded message
         */
        public byte[] encodeMessage()
        {
            // COMMAND : 4 bytes
            // ID : 4 bytes
            // NAME : 32 bytes max ends with '\0'
            // FILE : rest

            byte[] data = new byte[this.size + SIZE_OF_SIZE];
            ByteBuffer byteBuffer = ByteBuffer.wrap(data);


            byteBuffer  .putInt(this.size)
                        .putInt(this.command);

            if(this.command == A_ASK4SCAN)
                byteBuffer.putInt(this.id);

            if(this.command == A_SETCARTO)
            {
                byteBuffer  .putInt(this.id)
                            .asCharBuffer()
                                .put(this.name);

                // convert bitmap to bytearray
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                this.file.compress(Bitmap.CompressFormat.PNG, 100, baos);

                byteBuffer.put(baos.toByteArray());
            }

            return data;
        }

        /**
         * Gets command of the message
         * @return command
         */
        public int getCommand ()
        {
            return command;
        }

        /**
         * Gets carto id of the message
         * @return carto id
         */
        public int getId ()
        {
            return id;
        }

        /**
         * Gets carto name of the message
         * @return carto name
         */
        public String getName ()
        {
            return name;
        }

        /**
         * Gets carto file of the message
         * @return carto file
         */
        public Bitmap getFile ()
        {
            return file;
        }
    }
}
