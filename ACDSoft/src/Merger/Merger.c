/**
 * @file Merger.c
 * @brief This component is the raw scan merger.
 * @author Thibault MALARY
 * @date 2022-06-08
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

#include "../Config/util.h"
#include "Merger.h"

#define MERGE_GAP   (100)

/**
 * @brief Merges the scan that has just been performed with the fusion scan, taking into account the marker used
 * 
 * @param myRawScanMerged The two-dimensional boolean array in s_rawScan structure representing the merging of multiple raw scans.  
 *  The myRawScanMerged size is RAW_SCAN_SIZE * RAW_SCAN_SIZE.
 * @param myRawScan The two-dimensional boolean array in s_rawScan structure representing a raw scan.  
 *  The myRawScan size is RAW_SCAN_SIZE * RAW_SCAN_SIZE.
 * @param myMarker The marker where the scan was taken. It is the e_marker enum from R0 to R4.
 */
void Merger_merge(s_rawScan *myRawScanMerged, s_rawScan *myRawScan, e_marker myMarker)
{
	//LOG_MERGER();
	
	switch (myMarker)
	{
	case R0:
		/* Do nothing */
		break;
	
	case R1:
		for(int i = 0; i < RAW_SCAN_SIZE; i++)
		{
			for(int j = 0; j < RAW_SCAN_SIZE; j++)
			{
				if(i < (RAW_SCAN_SIZE - MERGE_GAP) && j < (RAW_SCAN_SIZE - MERGE_GAP))
				{
					myRawScan->rawScan_a[RAW_SCAN_SIZE - 1 - i][j] = myRawScan->rawScan_a[RAW_SCAN_SIZE - 1 - i - MERGE_GAP][j + MERGE_GAP];
				}
				else
				{
					myRawScan->rawScan_a[RAW_SCAN_SIZE - 1 - i][j] = 1;
				}
			}
		}
		break;
	
	case R2:
		for(int i = 0; i < RAW_SCAN_SIZE; i++)
		{
			for(int j = 0; j < RAW_SCAN_SIZE; j++)
			{
				if(i < (RAW_SCAN_SIZE - MERGE_GAP) && j < (RAW_SCAN_SIZE - MERGE_GAP))
				{
					myRawScan->rawScan_a[RAW_SCAN_SIZE - 1 - i][RAW_SCAN_SIZE - 1 - j] = myRawScan->rawScan_a[RAW_SCAN_SIZE - 1 - i - MERGE_GAP][RAW_SCAN_SIZE - 1 - j - MERGE_GAP];
				}
				else
				{
					myRawScan->rawScan_a[RAW_SCAN_SIZE - 1 - i][RAW_SCAN_SIZE - 1 - j] = 1;
				}
			}
		}
		break;
	
	case R3:
		for(int i = 0; i < RAW_SCAN_SIZE; i++)
		{
			for(int j = 0; j < RAW_SCAN_SIZE; j++)
			{
				if(i < (RAW_SCAN_SIZE - MERGE_GAP) && j < (RAW_SCAN_SIZE - MERGE_GAP))
				{
					myRawScan->rawScan_a[i][RAW_SCAN_SIZE - 1 - j] = myRawScan->rawScan_a[i + MERGE_GAP][RAW_SCAN_SIZE - 1 - j - MERGE_GAP];
				}
				else
				{
					myRawScan->rawScan_a[i][RAW_SCAN_SIZE - 1 - j] = 1;
				}
			}
		}
		break;
	
	case R4:
		for(int i = 0; i < RAW_SCAN_SIZE; i++)
		{
			for(int j = 0; j < RAW_SCAN_SIZE; j++)
			{
				if(i < (RAW_SCAN_SIZE - MERGE_GAP) && j < (RAW_SCAN_SIZE - MERGE_GAP))
				{
					myRawScan->rawScan_a[i][j] = myRawScan->rawScan_a[i + MERGE_GAP][j + MERGE_GAP];
				}
				else
				{
					myRawScan->rawScan_a[i][j] = 1;
				}
			}
		}
		break;
	
	default:
		break;
	}

	// Merge
	for(int i = 0; i < RAW_SCAN_SIZE; i++)
	{
		for(int j = 0; j < RAW_SCAN_SIZE; j++)
		{
			myRawScanMerged->rawScan_a[i][j] = myRawScan->rawScan_a[i][j] && myRawScanMerged->rawScan_a[i][j];
		}
	}
}
