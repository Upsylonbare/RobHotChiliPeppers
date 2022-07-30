/**
 * @file  Folder.h
 * @brief  Folder.c header file, which manages cartographies in storage, converts position_gtk.txt into integer array, 
 * raw scans into cartographies by using bitmap
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

#ifndef FOLDER_H
#define FOLDER_H

#include <stdbool.h>
#include "../Carto/Carto.h"
#include "../Converter/Converter.h"
#include "../Config/config.h"

#define PATH_MAX_SIZE 45
#define HYPHEN "-"
#define EXTENSION ".bmp"
#define TEMPORARY_RAW_NAME "raw_tmp"
#define RAW_NAME "raw"
#define LENGHT_ID 11
#define LENGHT_DIRECTORY 14

typedef enum {
	TEMPORARY,
	DEFINITIVE_RAW,
	DEFINITIVE_TREATED
} Carto_state;

/**
 * @brief Represents the directory where cartographies are stored
 * @def CARTOS_DIRECTORY
 */
#define CARTOS_DIRECTORY "cartos/"

/**
 * @brief Represents the directory where cartographies are temporary stored
 * @def TEMPORARY_DIRECTORY
 */
#define TEMPORARY_DIRECTORY "/tmp/"

/**
 * @brief Initialize a new cartography.
 * 
 */
s_carto * Folder_createNewCarto();

/**
 * @brief Save the raw cartography by moving the cartography from the temporary directory to the definitive one.
 * @param Carto carto to be saved
 */
void Folder_saveRawCarto(s_carto *myCarto);

/**
 * @brief Save the treated cartography.
 * @param Carto carto to be saved
 */
void Folder_saveTreatedCarto(s_carto *myCarto);

/**
 * @brief Converts a rawScanMerged to bitmap format (24 bits), creates a new carto and saves it.
 * @param rawScan scan to be converted.
 */
void Folder_convert2Bitmap(s_rawScan *rawScanMerged, char * buffer_rawCarto);

#endif