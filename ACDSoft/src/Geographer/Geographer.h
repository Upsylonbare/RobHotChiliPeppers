/**
 * @file Geographer.h
 * @brief This component is the active object of ACDSoft
 * @author Thibault MALARY inspired by Thomas CRAVIC's work
 * @date 2022-05-06
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

#ifndef GEOGRAPHER_H
#define GEOGRAPHER_H

#include "../Config/config.h"
#include "../Carto/Carto.h"

typedef struct geographer s_geographer;

typedef struct
{
    int rawData_a[RAW_DATA_SIZE]; /*!< The one-dimensional boolean array rawData_a. The rawData_a size is RAW_DATA_SIZE. */
} s_rawData;

/**
 * @struct s_rawScan [Geographer.h]
 * @brief The s_rawScan structure represents the raw scan.
 *
 */
typedef struct
{
    bool rawScan_a[RAW_SCAN_SIZE][RAW_SCAN_SIZE]; /*!< The two-dimensional boolean array rawScan_a. The rawScan_a size is RAW_SCAN_SIZE * RAW_SCAN_SIZE. */
} s_rawScan;

typedef enum
{
    NONE = 0,	///< Mark None
    R0,			///< Mark R0
    R1,			///< Mark R1
    R2,			///< Mark R2
    R3,			///< Mark R3
    R4,			///< Mark R4
} e_marker;

/**
 * @fn void Geographer_new(void)
 * @brief Initialize in memory the object Geographer.
 */
void Geographer_new(void);

/**
 * @fn void Geographer_free(void)
 * @brief Destruct the object Geographer from memory.
 */
void Geographer_free(void);

/**
 * @fn void Geographer_start(void)
 * @brief Start Geographer .
 */
void Geographer_start(void);

/**
 * @fn void Geographer_stop(void)
 * @brief Stop Geographer.
 */
void Geographer_stop(void);

/**
 * @fn void Geographer_ask4Scan(e_marker myMarker)
 * @brief Function dedicated to request the process to take a new scan
 */
void Geographer_ask4Scan(e_marker myMarker);

/**
 * @fn void Geographer_endScan(void)
 * @brief Function dedicated to request the process to take a new scan
 */
void Geographer_endScan(void);

/**
 * @fn void Geographer_ackCarto(void)
 * @brief Function dedicated to confirm the recieve of the cartography
 */
void Geographer_ackCarto(void);

/**
 * @fn void Geographer_setCarto(s_carto *carto)
 * @brief Fonction dedicated to set the cartography into Geographer
 * @param carto The cartography to set
 */
void Geographer_setCarto(s_carto *carto);

/**
 * @fn void Geographer_ackSave(void)
 * @brief Function dedicated to confirm the saving of the cartography
 */
void Geographer_ackSave(void);

#endif /* GEOGRAPHER_H */