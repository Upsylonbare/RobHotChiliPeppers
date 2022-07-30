/**
 * @file Converter.c
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

#include <stdlib.h>
#include "../Config/util.h"
#include "Converter.h"

void Converter_convert2RawScan(s_rawScan *myRawScan, s_rawData *myRawData)
{
	LOG_CONVERTER();

	int x, y;

	for (int i = 0; i < RAW_DATA_SIZE; i++)
	{
		myRawData->rawData_a[i] = FACTOR * myRawData->rawData_a[i] + (RAW_SCAN_SIZE / 2);
	}

	Converter_resetRawScan(myRawScan);

	for (int k = 0; k < RAW_DATA_SIZE; k += 2)
	{
		x = myRawData->rawData_a[k];
		y = myRawData->rawData_a[k + 1];
		if (x >= 0 && x < RAW_SCAN_SIZE && y >= 0 && y < RAW_SCAN_SIZE && !(x == (RAW_SCAN_SIZE / 2) && y == (RAW_SCAN_SIZE / 2)))
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					myRawScan->rawScan_a[x + i - 1][y + j - 1] = 0;
				}
			}
		}
	}

}

void Converter_resetRawScan(s_rawScan *myRawScan)
{
	for (int i = 0; i < RAW_SCAN_SIZE; i++)
	{
		for (int j = 0; j < RAW_SCAN_SIZE; j++)
		{
			myRawScan->rawScan_a[i][j] = 1;
		}
	}
}
