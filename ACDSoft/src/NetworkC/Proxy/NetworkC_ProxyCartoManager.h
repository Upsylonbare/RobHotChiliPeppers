/**
 * @file NetworkC_ProxyCartoManager.h
 * @author Clément Le Goffic
 * @brief Header file of NetworkC_ProxyCartoManager.c
 * @version 1
 * @date 2022-05-11
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

#ifndef NETWORKC_PROXYCARTOMANAGER_H
#define NETWORKC_PROXYCARTOMANAGER_H

#include "../../Carto/Carto.h"

/**
 * @brief Proxy function to setCarto in NirvanApp
 * @fn NetworkC_ProxyCartoManager_setCarto
 * @param cartoToSend 
 */
void NetworkC_ProxyCartoManager_setCarto(s_carto *cartoToSend);

/**
 * @brief Proxy function to ack the Carto to NirvanApp
 * @fn NetworkC_ProxyCartoManager_ackCarto
 */
void NetworkC_ProxyCartoManager_ackCarto(void);

#endif