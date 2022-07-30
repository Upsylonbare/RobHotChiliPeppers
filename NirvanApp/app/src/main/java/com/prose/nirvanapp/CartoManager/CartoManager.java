package com.prose.nirvanapp.CartoManager;
/**
 * @file CartoManager.java
 *
 * @brief this class manage Carto
 *
 * @author Loris BOUSQUET
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
 */
import android.Manifest;
import android.app.Activity;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.widget.EditText;

import androidx.appcompat.app.AlertDialog;
import androidx.core.app.ActivityCompat;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
/**
 * @brief This class manage the carto
 *
 */
public class CartoManager
{
     /**
      * Instance of CartoManager (singleton)
      */
     public static CartoManager INSTANCE = new CartoManager();

     /**
      * Private constructor
      */
     private CartoManager()
     {

     }
    /**
     * @brief Instance of CartoCourrante
     */
    private Carto currentCarto = new Carto(0,null,null,null);

    /**
     * @brief Instance of Storage Permission code
     */
    private static final int STORAGE_PERMISSION_CODE = 1;
    /**
     * @brief Instance of count
     */
    public int count = 0;
    /**
     * @brief Instance of the defined folder where we have to save cartography
     */
    private File subDirectory = new File(Environment.getExternalStorageDirectory().toString() + "/Pictures/Paint");
    /**
     * @brief Instance of the list of Files which already are in the folder
     */
    private File[] existing = subDirectory.listFiles();
    /**
     * @brief Instance of fileOutputStream
     */
    private FileOutputStream fileOutputStream;
    /**
     * @brief Instance of list of cartography saved
     */
    private ArrayList<Carto> cartoHistory = new ArrayList<>();

    /**
     * @brief Count the number of file in the given folder
     *
     */


    public int getCartoNumberInFile (File[] listfiles)
    {
        for (File file : listfiles)
        {
            if (file.getName().endsWith(".JPEG"))
            {
                count++;
            }
        }

        return count;
    }
    /**
     * @brief Request for storage permission
     *
     * @param activity
     *
     */
    public void requestStoragePermission (Activity activity) {
        if (ActivityCompat.shouldShowRequestPermissionRationale(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE))
        {
            new AlertDialog.Builder(activity)
                    .setTitle("Permission needed")
                    .setMessage("Needed to save image")
                    .setPositiveButton("OK", new DialogInterface.OnClickListener()
                    {
                        @Override
                        public void onClick(DialogInterface dialog, int which)
                        {
                            ActivityCompat.requestPermissions(activity, new String[] {Manifest.permission.WRITE_EXTERNAL_STORAGE}, STORAGE_PERMISSION_CODE);
                        }
                    })
                    .setNegativeButton("Cancel", new DialogInterface.OnClickListener()
                    {
                        @Override
                        public void onClick(DialogInterface dialog, int which)
                        {
                            dialog.dismiss();
                        }
                    })
                    .create()
                    .show();
        }
        else
        {
            ActivityCompat.requestPermissions(activity, new String[] {Manifest.permission.WRITE_EXTERNAL_STORAGE}, STORAGE_PERMISSION_CODE);
        }
    }

    /**
     * @brief Save the cartography
     *
     * @param setName - the name choiced by the user
     * @param currentCarto - the current carto to save
     * @param activity the activity on which the requestStoragePermission is used
     *
     */
    public void ask4SaveCarto(Activity activity,Bitmap currentCarto, EditText setName)
    {
        count = 0;
        requestStoragePermission(activity);
        if (subDirectory.exists())
        {
            count = getCartoNumberInFile(existing);
        }
        else
        {
            subDirectory.mkdir();
        }

        if (subDirectory.exists())
        {
            File image = new File(subDirectory, "/"+count+"_"+ setName.getText().toString()+".JPEG");
            try
            {
                fileOutputStream = new FileOutputStream(image);
                currentCarto.compress(Bitmap.CompressFormat.JPEG, 100, fileOutputStream);
                fileOutputStream.flush();
                fileOutputStream.close();
            }
            catch (FileNotFoundException e)
            {
            }
            catch (IOException e)
            {
            }
        }
    }

    /**
     * @brief Delete the oldest Carto
     *
     */
    public void deleteOldestCarto()
    {

    }

    /**
     * @brief This class is used to get Cartagraphys names and ids
     *
     */
    public ArrayList<Carto> createHistory()
    {
        count = 0;
        if (subDirectory.exists())
        {
            File[] existing = subDirectory.listFiles();
            for (File file : existing)
            {
                if (file.getName().endsWith(".JPEG"))
                {
                    cartoHistory.add(new Carto(count, existing[count].getName(), null, BitmapFactory.decodeFile(existing[count].getAbsolutePath())));
                    count++;
                }
            }
        }
        return cartoHistory;
    }

    public ArrayList<Carto> getHistory(){
        return cartoHistory;
    }
    /**
     * @brief This class is used to verifyName
     * @param name
     */
    public boolean verifyName(String name){
        return true;
}

    /**
     * @brief This class is the current Carto getter
     */
    public Carto getCurrentCarto(){
    return currentCarto;
}

    /**
     * @brief This class is the current Carto setter
     * @param id
     * @param name
     * @param treatedScan
     * @param rawScan
     */
    public void setCurrentCarto(int id,String name, Bitmap treatedScan, Bitmap rawScan){
        currentCarto.setName(name);
        currentCarto.setMyIdCarto(id);
        currentCarto.setRawScan(rawScan);
        currentCarto.setTreatedScan(treatedScan);
    }

}
