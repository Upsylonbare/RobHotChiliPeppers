/**
 * @file NetworkC_Coder.c
 * @author Clément Le Goffic
 * @brief Coder encode end decode message to be send or received
 * @version 1
 * @date 2022-05-07
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
 * 
 */

#include <stdio.h>
#include <arpa/inet.h>
#include "../../Config/util.h"
#include "../../Config/config.h"

#include "NetworkC_Coder.h"

void NetworkC_Coder_encode(s_message* myDataToCode, s_log* myLog)
{
    LOG_NETWORKC();
    myLog->command = htonl(myDataToCode->command);
    if(myDataToCode->command == C_SETCARTO)
    {
        myLog->id = htonl(myDataToCode->carto.id);
        memcpy(myLog->name, myDataToCode->carto.name, SIZE_NAME);
        memcpy(myLog->carto, myDataToCode->carto.treatedCarto, SIZE_CARTO);
        myLog->size = htonl(sizeof(myLog->id) + sizeof(myLog->name) + sizeof(myLog->carto) + sizeof(myLog->command));
    }
    else
    {
        myLog->size = htonl(sizeof(myLog->command) + sizeof(uint32_t));
    }
    
}

void NetworkC_Coder_decode(s_log* myReceivedData, s_message* receivedMessage)
{
    LOG_NETWORKC();
    receivedMessage->command = ntohl(myReceivedData->command);
    if(receivedMessage->command == A_SETCARTO)
    {
        receivedMessage->carto.id = ntohl(myReceivedData->id);
        memcpy(receivedMessage->carto.name, myReceivedData->name, SIZE_NAME);
        memcpy(receivedMessage->carto.treatedCarto, myReceivedData->carto, SIZE_CARTO);
    }
    if(receivedMessage->command == A_ASK4SCAN)
    {
        receivedMessage->carto.id = ntohl(myReceivedData->id);
    }

}