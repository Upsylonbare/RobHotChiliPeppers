/**
 * @file ProxyGeographer.java
 *
 * @brief This class acts as a proxy for all NirvanApp objects wishing send a message to the ACDSoft Geographer class.
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

import com.prose.nirvanapp.CartoManager.Carto;
import com.prose.nirvanapp.NetworkA.Communication.Communication;
import com.prose.nirvanapp.NetworkA.Communication.Protocol;

/**
 * This class acts as a proxy for all NirvanApp objects wishing send a message to the ACDSoft Geographer class.
 */
public class ProxyGeographer
{
    /**
     * Sends a scan request to ACDSoft
     * @param marker - LiDAR position
     */
    public void ask4Scan(int marker)
    {
        Communication.INSTANCE.send(new Protocol.Message(Protocol.A_ASK4SCAN, marker, null, null).encodeMessage());
    }

    /**
     * Sends a treated carto to ACDSoft
     * @param myCarto - treated carto
     */
    public void setCarto(Carto myCarto)
    {
        Communication   .INSTANCE
                        .send(new Protocol.Message(
                            Protocol.A_SETCARTO,
                            myCarto.getMyIdCarto(),
                            myCarto.getName(),
                            myCarto.getTreatedScan())
                        .encodeMessage());

    }

    /**
     * Acknowledges the receipt of a raw carto
     */
    public void ackCarto()
    {
        Communication.INSTANCE.send(new Protocol.Message(Protocol.A_ACKCARTO, Protocol.NO_ID, null, null).encodeMessage());
    }
}
