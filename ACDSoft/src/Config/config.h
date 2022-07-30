/**
 * @file config.h
 * @brief Global definitions.
 * @author Thibault MALARY
 * @date 2022-05-11
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

#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

/**
 * @def Port of the socket
 */

#define SERVER_PORT "12345"

/**
 * @def Maximum number of client connected on the socket
 */
#define MAX_PENDING_CONNECTIONS 1


/**
 * @def RAW_DATA_SIZE
 * @brief The size of the table output by the LiDAR physical component
 * 
 */
#define SIZE_CARTO 4400000

/**
 * @def RAW_DATA_SIZE
 * @brief The size of the table output by the LiDAR physical component
 * 
 */
#define RAW_DATA_SIZE 2200

/**
 * @def TREATED_SCAN_SIZE
 * @brief The size of our treated scan
 * 
 */
#define RAW_SCAN_SIZE 1200

/**
 * @def RAW_SCAN_SIZE
 * @brief The size of our raw scan
 * 
 */
#define TREATED_SCAN_SIZE 1200

/**
 * @brief Represents the size of the cartography's name
 * @def SIZE_NAME
 */
#define SIZE_NAME 16

/**
 * @def SCAN_TIME
 * @brief The number of seconds we give to the physical LiDAR component to finish scanning
 *
 */
#define SCAN_TIME (5)

#endif /* CONFIG_H */