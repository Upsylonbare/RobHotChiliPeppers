/**
 * @file Carto.java
 *
 * @brief This class centralized Carto data
 *
 * @author Alfred VRIGNAUD and Loris BOUSQUET
 * @date 2022
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
package com.prose.nirvanapp.CartoManager;

import android.graphics.Bitmap;

/**
 * @brief This class centralized Carto data
 *
 * @see Bitmap
 */
public class Carto
{
    /**
     * @brief Carto id : int
     */
    private int myIdCarto;

    /**
     * @brief Carto name : String
     */
    private String name;

    /**
     * @brief Carto rawScan : Bitmap
     */
    private Bitmap rawScan;

    /**
     * @brief Carto treatedScan : Bitmap
     */
    private Bitmap treatedScan;

    /**
     * @brief Carto constructor
     *
     * @param id - int
     * @param name - String
     * @param rawScan - Bitmap
     * @param treatedScan - Bitmap
     */
    public Carto(int id, String name, Bitmap rawScan, Bitmap treatedScan)
    {
        this.myIdCarto = id;
        this.name = name;
        this.rawScan = rawScan;
        this.treatedScan = treatedScan;
    }



    /**
     * @brief Gets Carto by is id
     * @param idCarto
     * @return
     */
    public Carto load(int idCarto)
    {
        // TODO:
        return this;
    }

    /**
     * @brief Gets myIdCarto
     * @return myIdCarto
     */
    public int getMyIdCarto ()
    {
        return myIdCarto;
    }

    /**
     * @brief Sets myIdCarto
     * @param myIdCarto - id
     */
    public void setMyIdCarto (int myIdCarto)
    {
        this.myIdCarto = myIdCarto;
    }

    /**
     * @brief Gets name
     * @return name
     */
    public String getName ()
    {
        return name;
    }

    /**
     * @brief Sets name
     * @param name - the name
     */
    public void setName (String name)
    {
        this.name = name;
    }

    /**
     * @brief Gets rawScan
     * @return rawScan
     */
    public Bitmap getRawScan ()
    {
        return rawScan;
    }

    /**
     * @brief Sets rawScan
     * @param rawScan - the raw scan
     */
    public void setRawScan (Bitmap rawScan)
    {
        this.rawScan = rawScan;
    }

    /**
     * @brief Gets treatedScan
     * @return treatedScan
     */
    public Bitmap getTreatedScan ()
    {
        return treatedScan;
    }

    /**
     * @brief Sets treatedScan
     * @param treatedScan - the treated scan
     */
    public void setTreatedScan (Bitmap treatedScan)
    {
        this.treatedScan = treatedScan;
    }

    public String toString()
    {
        return "Carto:" + this.myIdCarto + "_" + this.name + "_" + this.rawScan + "_" + this.treatedScan;
    }
}
