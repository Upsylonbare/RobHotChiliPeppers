/**
 * @file Converter.h
 * @brief This component converts the raw data returned by the LiDAR physical component into a two-dimensional array of
 * boolean representing a raw scan. Here, "1" represent empty space, and "0" represent an obstacle.
 * @author Thibault MALARY
 * @date 2022-05-02
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

#ifndef CONVERTER_H
#define CONVERTER_H

#include "../Geographer/Geographer.h"

/**
 * @def FACTOR
 * @brief The factor to map the LiDAR output values.\n\n
 *  Old interval : {-6000 ; 6000}\n
 *  New interval : {-600 ; 600}
 */
#define FACTOR 0.1

/**
 * @brief Converts the raw data returned by the LiDAR physical component into a two-dimensional array of boolean representing a raw scan.
 * @param myRawData The one-dimensional int array in s_rawData structure representing the raw data returned by the LiDAR physical component. The rawData_a size is RAW_DATA_SIZE.
 * @param myRawScan The two-dimensional boolean array in s_rawScan structure representing a raw scan.  
 *  The rawScan_a size is RAW_SCAN_SIZE * RAW_SCAN_SIZE.
 */
void Converter_convert2RawScan(s_rawScan *myRawScan, s_rawData *myRawData);

/**
 * @brief Set all values in the rawScan array to 1.
 * @param myRawScan The two-dimensional boolean array in s_rawScan structure representing a raw scan.  
 *  array with size RAW_SCAN_SIZE * RAW_SCAN_SIZE.
 */
void Converter_resetRawScan(s_rawScan *myRawScan);

#endif /* CONVERTER_H */