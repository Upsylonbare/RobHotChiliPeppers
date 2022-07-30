/**
 * @file NetworkC_Coder.h
 * @author Clément Le Goffic
 * @brief Header file of NetworkC_Coder.c
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
 */
#ifndef NETWORKC_CODER_H
#define NETWORKC_CODER_H

#include "../../Config/config.h"
#include "../../Carto/Carto.h"

/**
 * @brief Enumaration of all command that belongs to the protocol
 */
typedef enum
{
    A_PING = 1, ///< Applicative ping send by NirvanApp
    A_ASK4SCAN, ///< Ask for a scan command by NirvanApp
    A_ACKCARTO, ///< Ack for a carto send by NirvanApp
    A_SETCARTO, ///< SetCarto command send by NirvanApp
    C_SETCARTO, ///< SetCarto command send by ACDSoft
    C_ACK4SCAN, ///< Ack for scan send by ACDSoft
    C_ACK4SAVECARTO, ///< Ack for save a carto send by ACDSoft
    C_ACKCARTO ///< Ack for a carto send by ACDSoft
}e_command;

/**
 * @brief Structure of a message send to coder
 */
typedef struct 
{
    e_command command; ///< Command of a message
    s_carto carto; ///< Carto of a mesage
}s_message;

/**
 * @brief Structure of a log coming out of coder (packed to not depend on data alignement)
 */
typedef struct __attribute__((__packed__))
{
    uint32_t size; ///< Size of the rest of the lof
    e_command command; ///< Command that is send or received
    uint32_t id; ///< Id of the carto that is send or received
    char name[SIZE_NAME]; ///< Name of the carto that is send or received
    char carto[SIZE_CARTO]; ///< Carto datas that are send or received
}s_log;

/**
 * @brief Pepare a message in order to respect the protocol
 * @fn NetworkC_Coder_encode
 * @param myDataToCode s_message that need to be coded
 * @param myLog s_log that is coded 
 */
void NetworkC_Coder_encode(s_message* myDataToCode, s_log* myLog);

/**
 * @brief Prepare a message in order to be read correctly after being received on the socket
 * @fn NetworkC_Coder_decode
 * @param myReceivedData s_log that is coded
 * @param receivedMessage s_message that is decoded
 */
void NetworkC_Coder_decode(s_log* myReceivedData, s_message* receivedMessage);

#endif