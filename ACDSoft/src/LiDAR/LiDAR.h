/**
 * @file  LiDAR.h
 * @brief  This is the header file of LiDAR.c which communicates with the physical LiDAR to get a scan in a txt format 
 * and converts it to an integer array
 * @author Jean-Théophane Deschard, Marin BONSERGENT
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

#ifndef LIDAR_H
#define LIDAR_H

#include "../Config/config.h"
#include "../Geographer/Geographer.h"
#include "LiDAR_A1M8.hpp"

#define RAW_DATA_FILE "lidar_output/position_gtk.txt"

/* Définition de la macro EXTERN_C pour C ou C++ */
#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif
 
 
EXTERN_C void LiDAR_endScan();

/* ----------------------- PUBLIC FUNCTIONS PROTOTYPES -----------------------*/

/**
 * @brief Public function to start scan : launch the LiDAR script
 * @param void void
 */
void LiDAR_startScan();



/**
 * @brief Public function to get scan data : converts the txt file into an array of integers
 * @param myRawData The one-dimensional int array in s_rawData structure representing the raw data returned by the LiDAR physical component.
 *  The rawData_a size is RAW_DATA_SIZE.
 */
void LiDAR_getScan(s_rawData *myRawData);

/* ----------------------- NEW START STOP FREE -----------------------*/

/**
 * @fn void LiDAR_new()
 * @brief LiDAR class constructor
 */
void LiDAR_new();


/**
 * @fn void LiDAR_start()
 * @brief LiDAR class starter
 *
 * Starts the LiDAR and the gtk window object
 */
void LiDAR_start();


/**
 * @fn void LiDAR_stop ()
 * @brief LiDAR singleton stopper
 *
 */

void LiDAR_stop ();

/**
 * @fn void LiDAR_free ()
 * @brief LiDAR singleton destructor
 *
 */

void LiDAR_free ();
#endif