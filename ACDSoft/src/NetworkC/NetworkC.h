/**
 * @file NetworkC.h
 * @author Clément Le Goffic
 * @brief Header file of NetworkC.c
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

#ifndef NETWORKC_H
#define NETWORKC_H

/**
 * @brief Connection State
 * @enum e_connectionState
 */

typedef enum 
{
	E_WAITING, 	///< State E_WAITING when ACDSoft is waiting a connection
	E_CONNECTED,///< State E_CONNECTED when ACDSoft is connected to NirvanApp
    E_ERROR, 	///< State E_ERROR when an error occurs after a connection
	E_KILL,     ///< Kills the state machine
	NB_EVENT	///< Number of State
}e_connectionState;

/**
 * @brief Modify the private attribute myConnectionState with the new value given in parameter
 * @fn NetworkC_setConnectionState
 * @param newConnectionSet The new connection state to set to networkC
 */
void NetworkC_setConnectionState(e_connectionState newConnectionState);

/**
 * @brief Return the private attribute myConnectionState of networkC
 * @fn NetworkC_getConnectionState
 */
e_connectionState NetworkC_getConnectionState(void);

#endif