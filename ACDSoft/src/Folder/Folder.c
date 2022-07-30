/**
 * @file  Folder.c
 * @brief  This component manages cartographies in storage, converts position_gtk.txt into integer array, converts raw
 * scans into cartographies by using bitmap
 * @author Marin BONSERGENT
 * @date 2022
 * @version 1
 * @copyright Redistribution and use in source and binary forms, with or without modification, are permitted provided   * that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 * thefollowing disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <assert.h>
#include "../Config/util.h"
#include "Folder.h"
#include "../Geographer/Geographer.h"
#include "libbmp.h"


/**
 * @brief Returns number of cartos in a directory
 * @param void void
 */
static int Folder_getNumberOfCartosSaved();

/**
 * @brief Delete the 2 oldest cartos saved (1 raw carto and its associated treated carto)
 * @param void void
 */
static void Folder_deleteOldestCarto();

/**
 * @brief Return a new id for a cartography
 * @param void void
 */
static int Folder_getNewId();

/**
 * @brief Build filename for a cartography following models detailed in the function
 * @param void void
 */
static void Folder_buildFilename(s_carto *this, Carto_state state, char * filename);


void Folder_saveRawCarto(s_carto *myCarto)
{
    LOG_FOLDER();
    // rename the carto to cartos/id-name.bmp
    char * rawCartoPath = malloc (sizeof (char) * PATH_MAX_SIZE);
    assert(rawCartoPath != NULL);
    Folder_buildFilename(myCarto, TEMPORARY, rawCartoPath); // build the path of the carto in tmp file, to locate it

    char * newPath = malloc (sizeof (char) * PATH_MAX_SIZE);
    assert(newPath != NULL);
    Folder_buildFilename(myCarto,DEFINITIVE_RAW,newPath); // build the definitive filename
    rename(rawCartoPath, newPath); // rename the carto to cartos/id-raw.bmp
    
    free(newPath);
    free(rawCartoPath);
}

void Folder_saveTreatedCarto(s_carto *myCarto)
{
    LOG_FOLDER();
    int numberCartos = Folder_getNumberOfCartosSaved();

    // if there are 20 cartos saved, delete the 2 oldest ones
    if (numberCartos > 18) {
        Folder_deleteOldestCarto();
    }

    char * treatedCartoPath = malloc (sizeof (char) * PATH_MAX_SIZE);
    assert(treatedCartoPath != NULL);
    Folder_buildFilename(myCarto, DEFINITIVE_TREATED, treatedCartoPath); // build the path of the carto in tmp file, to locate it

    FILE * fp = fopen(treatedCartoPath, "wb");
    assert(fp != NULL);
    fwrite(myCarto->treatedCarto, 1, sizeof(myCarto->treatedCarto), fp);
    fclose(fp);

    free(treatedCartoPath);

    Folder_saveRawCarto(myCarto);
    free(myCarto);
}

void Folder_convert2Bitmap(s_rawScan *rawScanMerged, char * buffer_rawCarto)
{
    LOG_FOLDER();

	// Draw the whole image in white for initialization :
	bmp_img img;
	bmp_img_init_df (&img, RAW_SCAN_SIZE, RAW_SCAN_SIZE);

	for (int x = 0; x < RAW_SCAN_SIZE; x++)
	{
		for (int y = 0; y < RAW_SCAN_SIZE; y++)
		{
			bmp_pixel_init (&img.img_pixels[x][y], 255, 255, 255);
		}
	}

	// Draw RawScan in black :

	for (int x = 0; x < RAW_SCAN_SIZE; x++)
	{
		for (int y = 0; y < RAW_SCAN_SIZE; y++)
		{
			if (rawScanMerged->rawScan_a[x][y] == 0)
			{
				bmp_pixel_init (&img.img_pixels[x][y], 0, 0, 0);
			}
		}
	}

    s_carto * myCarto = Folder_createNewCarto();

    char * rawCartoPath = malloc (sizeof (char) * PATH_MAX_SIZE);
    assert(rawCartoPath != NULL);
    Folder_buildFilename(myCarto,TEMPORARY,rawCartoPath);

	bmp_img_write (&img,rawCartoPath);
	bmp_img_free (&img);

    FILE *fp = fopen(rawCartoPath, "r");
    assert(fp != NULL);
    fread(buffer_rawCarto, 1, RAW_SCAN_SIZE*RAW_SCAN_SIZE, fp);
    fclose(fp);
    free(rawCartoPath);
    free(myCarto);
}


static void Folder_buildFilename(s_carto *myCarto, Carto_state state, char * filename)
{
    LOG_FOLDER();
    
	char id[LENGHT_ID];
	char destination[LENGHT_DIRECTORY];

	if (state == TEMPORARY) // It is a raw scan -> scan will be saved in tmp directory
	{
		strcpy(destination, TEMPORARY_DIRECTORY);
        strcpy(myCarto->name, TEMPORARY_RAW_NAME);
	}
	else if (state == DEFINITIVE_TREATED) // It is a treated carto -> cartography will be saved in cartos directory
    {
		strcpy(destination, CARTOS_DIRECTORY);
	}
    else if (state == DEFINITIVE_RAW) // Raw carto to be definitively saved in cartos directory : name is raw to make it different from treated carto
    {
        strcpy(destination, CARTOS_DIRECTORY);
        strcpy(myCarto->name, RAW_NAME);
    }

    // Convert the id to a string
    sprintf(id, "%d", myCarto->id);

    // Concatenate id, hyphen, name and extension into filename
    strcpy(filename, destination);

    strcat(filename, id);
    strcat(filename, HYPHEN);
    strcat(filename, myCarto->name);
    strcat(filename, EXTENSION);
}


static int Folder_getNumberOfCartosSaved()
{
    LOG_FOLDER();
    int cartosNumber = 0;

    struct dirent *dir;
    DIR *d = opendir(CARTOS_DIRECTORY);
    // opendir() returns a  DIR pointer 

    if (d)
    {
        // Reads the content of the Cartos directory
        while ((dir = readdir(d)) != NULL)
        {
            // Does not take into account files not starting with a digit
            if (isdigit(dir->d_name[0]))
            {
                // Increments the number of cartos
                cartosNumber++;
            }

        }
        closedir(d);
    }
    return cartosNumber;
}



static void Folder_deleteOldestCarto()
{
    LOG_FOLDER();

    // Structure to store the name and id of the files together
    // Used to find the oldest carto
    typedef struct {
        int id;
        char name[PATH_MAX_SIZE];
    } NameAndId;

    NameAndId namesAndId[11];

    struct dirent *dir;
    DIR *d = opendir(CARTOS_DIRECTORY);
    // opendir() returns a  DIR pointer 

    int filenamesAnalyzed = 0; // Number of cartos analyzed

    if (d)
    {
        // Reads the content of the Cartos directory
        while ((dir = readdir(d)) != NULL)
        {
            // Does not take into account the . and .. directories
            if (isdigit(dir->d_name[0]))
            {
                char id[9] = {0};

                // Extracts the id from the filename
                // stores first char of the filename (= only the id)
                memccpy(id, dir->d_name,'-', sizeof(id));      

                // converts the id (str) to an int
                int value = atoi(id);
                
                // stores the id and the name of the file together
                namesAndId[filenamesAnalyzed].id = value;
                strcpy(namesAndId[filenamesAnalyzed].name, dir->d_name);
                // carto has been analyzed
                filenamesAnalyzed++;
            }

        }
        closedir(d);
    }

    if (filenamesAnalyzed == 0)
    {
        // Exception catched : No cartos saved
        return;
    }


    // sorts the id to get the 2 oldest cartos
    int lowest_id = namesAndId[0].id;
    char oldest_rawCarto[PATH_MAX_SIZE] = "";
    char oldest_treatedCarto[PATH_MAX_SIZE] = "";
    
    strcpy(oldest_rawCarto, namesAndId[0].name);
    strcpy(oldest_treatedCarto, namesAndId[1].name);

    for (int i = 1; i < filenamesAnalyzed; i++)
    {
        if (namesAndId[i].id == lowest_id)
        {
            lowest_id = namesAndId[i].id;
            strcpy(oldest_treatedCarto, namesAndId[i].name);
        }
        else if (namesAndId[i].id < lowest_id)
        {
            lowest_id = namesAndId[i].id;
            strcpy(oldest_rawCarto, namesAndId[i].name);
        }
    }

    // Concatenates the path and the filename to have cartos/oldestId-name.bmp
    char fullFirstPath[PATH_MAX_SIZE] = CARTOS_DIRECTORY;
    strcat(fullFirstPath, oldest_rawCarto);

    char fullSecondPath[PATH_MAX_SIZE] = CARTOS_DIRECTORY;
    strcat(fullSecondPath, oldest_treatedCarto);

    // Deletes the files
    remove(fullFirstPath);
    printf("Deleted first : %s\n", fullFirstPath);
    if (filenamesAnalyzed > 1)
    {
        remove(fullSecondPath);
        printf("Deleted second : %s\n", fullSecondPath);
    }
}


static int Folder_getNewId()
{
    LOG_FOLDER();
    struct dirent *dir;
    DIR *d = opendir(CARTOS_DIRECTORY);
    // opendir() returns a  DIR pointer 

    int highest_id = 0;

    if (d)
    {
        // Reads the content of the Cartos directory
        while ((dir = readdir(d)) != NULL)
        {
            // Does not take into account files not starting with a digit
            if (isdigit(dir->d_name[0]))
            {
                char id[9] = {0};

                // Extracts the id from the filename
                // stores first char of the filename (= only the id)
                memccpy(id, dir->d_name,'-', sizeof(id));                
                // converts the id (str) to an int
                int value = atoi(id);
                
                if (value > highest_id)
                {
                    highest_id = value;
                }
            }

        }
        closedir(d);
    }
    return highest_id + 1;
}

s_carto * Folder_createNewCarto()
{
    LOG_FOLDER();
    s_carto * carto = malloc(sizeof(s_carto));
    carto->id = Folder_getNewId();
    return carto;
}

