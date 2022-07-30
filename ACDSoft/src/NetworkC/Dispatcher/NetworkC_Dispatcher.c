/**
 * @file NetworkC_Dispatcher.c
 * @author Clément Le Goffic
 * @brief NetworkC_Dispatcher dispatch the received message
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

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Config/util.h"

#include "NetworkC_Dispatcher.h"

#include "../NetworkC.h"
#include "../Coder/NetworkC_Coder.h"
#include "../Postman/NetworkC_Postman.h"

#include "../../Geographer/Geographer.h"

/**
 * @brief dispatcherThread
 */
static pthread_t dispatchThread;

/**
 * @brief Boolean that control the while for the reading
 */
static bool running;

/**
 * @brief mutex that protect the running boolean
 */
static pthread_mutex_t dispatcherMutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief Buffer that contains the readen datas
 */
static uint8_t * buffer;

/**
 * @brief Dispatcher class runer
 * Socket reader thread launcher
 * @fn NetworkC_Dispatcher_run
 * @param dataSocket Socket nedded to read on it
 * @return void * 
 */
static void * NetworkC_Dispatcher_run(void * dataSocket);

/**
 * @brief Dispatcher class dispatcher
 * Dispatch a received message to its recipient
 * @fn NetworkC_Dispatcher_dispatch
 * @param dataToDispatch 
 */
static void NetworkC_Dispatcher_dispatch(s_message* dataToDispatch);

void NetworkC_Dispatcher_new(void)
{
    LOG_NETWORKC();
    running = true;
    buffer = calloc(1, sizeof(s_log));
}

void NetworkC_Dispatcher_start(int dataSocket)
{
    LOG_NETWORKC();
    pthread_create(&dispatchThread, NULL, &NetworkC_Dispatcher_run,(void *) (intptr_t) dataSocket);
}

void NetworkC_Dispatcher_stop(void)
{
    LOG_NETWORKC();
    pthread_mutex_lock(&dispatcherMutex);
    running = false;
    pthread_mutex_unlock(&dispatcherMutex);
}

void NetworkC_Dispatcher_free(void)
{
    free(buffer);
    LOG_NETWORKC();
}

static void * NetworkC_Dispatcher_run(void * dataSocket)
{
    LOG_NETWORKC();
    int socket = (intptr_t) dataSocket;
    s_message * theMessage = calloc(1, sizeof(s_message));
    while (running && (NetworkC_getConnectionState() ==  E_CONNECTED))
    {
        NetworkC_Postman_read(buffer);
        NetworkC_Coder_decode((s_log *) buffer, theMessage);
        NetworkC_Dispatcher_dispatch(theMessage);
    }
    free(theMessage);
    close(socket);
    return NULL;
}

static void NetworkC_Dispatcher_dispatch(s_message* dataToDispatch)
{
    LOG_NETWORKC();
    switch (dataToDispatch->command)
    {
    case A_PING:
        //Nothing to do
        break;
    case A_ASK4SCAN:
        //Use the id field to send the marker to geographer
        Geographer_ask4Scan(dataToDispatch->carto.id);
        break;
    case A_ACKCARTO:
        Geographer_ackCarto();
        break;
    case A_SETCARTO:
        Geographer_setCarto(&(dataToDispatch->carto));
        break;
    default:
        break;
    }
}