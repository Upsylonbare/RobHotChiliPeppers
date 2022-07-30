/**
 * @file Carto.h
 * @brief  This component describes the cartography's model. It also allow the user to modify it's parameters.
 * @author Milo KOSON
 * @date 02-05-2022
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

#ifndef CARTO_H
#define CARTO_H

#define RAW_SCAN_SIZE 1200

/**
 * @brief Library that declare sets of integer types having specified widths, and shall define corresponding sets of macros.
 * @include stdint.h
 */
#include <stdint.h>

/**
 * @brief Library that declares the boolean type and values
 * @include stdbool.h
 */
#include <stdbool.h>

/**
 * @brief Include config file, which contains all the global definitions
 * @include config.h
 */
#include "../Config/config.h"

/**
 * @brief Definition definition of the cartography based on its structure, it contains :
 *              - an ID represented by a number encoded on 32 bits
 *              - a name represented by a 20 characters long string
 *              - a raw scan represented by 2 arrays containing the associated coordinates [x][y]
 *              - a treated scan represented by 2 arrays containing the associated coordinates [x][y]
 * 
 * @typedef carto
 */
typedef struct
{
	uint32_t id;
	char name[SIZE_NAME];
	char rawCarto[SIZE_CARTO];
	char treatedCarto[SIZE_CARTO];
}s_carto;

#endif /*CARTO_H*/
