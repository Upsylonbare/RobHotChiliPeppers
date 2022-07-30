/**
 * @file NetworkC_Postman.c
 * @author Clément Le Goffic inspired by Thomas CRAVIC for the mq
 * @brief NetworkC Postman is the interface of the socket
 * @version 1
 * @date 2022-05-07
 *
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

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <mqueue.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../../Config/util.h"
#include "../../Config/config.h"

#include "NetworkC_Postman.h"
#include "../Dispatcher/NetworkC_Dispatcher.h"

#include "../NetworkC.h"

/**
 * @def MQ_MAX_MESSAGES
 * The maximum number of message the queue can handle at one time
 * By default, cannot be higher than 10, unless you change this
 * value into /proc/sys/fs/mqueue/msg_max
 */
#define MQ_MAX_MESSAGES (10)

/**
 * @brief Msg for the queue
 */
typedef struct
{
    uint8_t * data; ///< Pointer for the datas to be send
    uint32_t size; ///< size of the datas to be send
    uint8_t isStop;
}s_args;

/**
 * @brief Positive Option byte to set opion on the socket
 */
static int opt = 1;

/**
 * @brief checker for the return error and error handling
 */
static int myChecker;

/**
 * @brief Struct that contains the socket parameters
 */
static struct addrinfo myServerInfo;

/**
 * @brief Struct that contains the current socket parameters when running
 */
static struct addrinfo * currentInfo;

/**
 * @brief hostsocket
 */
static int mySocket;

/**
 * @brief data socket
 */
static int myDataSocket;

/**
 * @brief Postman thread
 */
static pthread_t runThread;

/**
 * @brief Name of the queue
 */
static const char QueueName[] = "/MailBox";

/**
 * @brief Mutex that protect the running flag of Postman thread
 */
static pthread_mutex_t postmanMutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief Boolean flag for constantly sending datas
 */
static bool sending;

/**
 * @brief Boolean flag that autorize the running thread to keep accept after a disconection
 */
static bool running;

static mqd_t mq;

/**
 * @brief Postman class runner
 * Firstly wait on the accept and then constantly wait a message to be send and send it
 * @return void* 
 */
static void * NetworkC_Postman_run(void * unused);

/**
 * @brief Initialize the Queue
 */
static void mailboxInit(void);

/**
 * @brief Destruct the Queue
 */
static void mailboxClose(void);

/**
 * @brief Send a msg to the Queue
 * @note this function is blocking if the queue is full
 * @param msg Msg send to the Queue
 */
static void mailboxSendMsg(s_args * msg);

/**
 * @brief Received a message from the queue
 * @note this function is blocking if the queue is full
 * @param msg 
 */
static void mailboxReceive(s_args * msg);


void NetworkC_Postman_new(void)
{
    LOG_NETWORKC();
    myChecker = 0;
    NetworkC_setConnectionState(E_WAITING);
    memset(&myServerInfo, 0, sizeof(myServerInfo));
    myServerInfo.ai_family = AF_INET;
    myServerInfo.ai_socktype = SOCK_STREAM;
    myServerInfo.ai_flags = AI_PASSIVE;
    myChecker = 0;
    myChecker = getaddrinfo(NULL, SERVER_PORT, &myServerInfo, &currentInfo);
    if (myChecker != 0)
    {
        LOG_NETWORKC("Getaddrinfo error code : %d", myChecker);
        myChecker = 0;
    }
    running = true;
    mailboxInit();
}

void NetworkC_Postman_start(void)
{
    LOG_NETWORKC();
    errno = 0;
    mySocket = socket(currentInfo->ai_family, currentInfo->ai_socktype, currentInfo->ai_protocol);
    if (mySocket == -1)
    {
        LOG_NETWORKC("Socket error errno :%d", errno);
    }
    errno = 0;
    myChecker = setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (myChecker != 0)
    {
        LOG_NETWORKC("Setsockopt error errno : %d", errno);
        myChecker = 0;
    }
    myChecker = bind(mySocket, currentInfo->ai_addr, currentInfo->ai_addrlen);
    if (myChecker != 0)
    {
        LOG_NETWORKC("Bind error errno : %d", errno);
        myChecker = 0;
    }
    myChecker = listen(mySocket, MAX_PENDING_CONNECTIONS);
    if (myChecker != 0)
    {
        LOG_NETWORKC("Listen error errno : %d", errno);
        myChecker = 0;
    }
    myChecker = pthread_create(&runThread, NULL, &NetworkC_Postman_run, NULL);
    if (myChecker != 0)
    {
        LOG_NETWORKC("Pthread create Postman run error");
        myChecker = 0;
    }
}

void NetworkC_Postman_stop(void)
{
    LOG_NETWORKC();
    pthread_mutex_lock(&postmanMutex);
    sending = false;
    running = false;
    pthread_mutex_unlock(&postmanMutex);
    s_args stopArgs;
    stopArgs.isStop = 1;
    mailboxSendMsg(&stopArgs);
    mailboxClose();
}

void NetworkC_Postman_free(void)
{
    LOG_NETWORKC();
}

void NetworkC_Postman_read(uint8_t* myBuffer)
{
    LOG_NETWORKC();
    uint32_t size;
    errno = 0;
    int quantity = recv(myDataSocket, &size, sizeof(uint32_t), 0);
    if (quantity < 0)
    {
        LOG_NETWORKC("Recv error %d", errno);
        NetworkC_setConnectionState(E_WAITING);
    }
    else if (quantity == 0)
    {
        LOG_NETWORKC("Client disconnected");
        NetworkC_setConnectionState(E_ERROR);
    }
    else
    {
        *((uint32_t *)myBuffer) = size;
        myBuffer += sizeof(uint32_t);
        uint32_t quantityToRead = ntohl(size);
        uint32_t quantityReaden = 0;

        while(quantityToRead != 0)
        {
            quantityReaden = recv(myDataSocket, myBuffer, quantityToRead, 0);
            quantityToRead -= quantityReaden;
            myBuffer += quantityReaden;
            if (quantityReaden < 0)
            {
                LOG_NETWORKC("Recv error %d", errno);
                NetworkC_setConnectionState(E_WAITING);
            }
            else if (quantityReaden == 0)
            {
                LOG_NETWORKC("Client disconnected");
                NetworkC_setConnectionState(E_WAITING);
            }
        }
    }
}

void NetworkC_Postman_askSend(uint8_t* datas, uint32_t size)
{
    LOG_NETWORKC();
    s_args args;
    args.data = datas;
    args.size = size;
    args.isStop = 0;
    mailboxSendMsg(&args);
}

static void *NetworkC_Postman_run(void * unused)
{
    LOG_NETWORKC();
    while (running)
    {
        myDataSocket = accept(mySocket, NULL, 0);
        if (myDataSocket < 0)
        {
            NetworkC_setConnectionState(E_ERROR);
            LOG_NETWORKC("Connection error errno=%d", errno);
            continue;
        }
        else
        {
            NetworkC_setConnectionState(E_CONNECTED);
            LOG_NETWORKC("Connection is ok");
            sending = true;
        }
        NetworkC_Dispatcher_start(myDataSocket);
        while (sending)
        {
            s_args messageToSend = {0};
            mailboxReceive(&messageToSend);
            if(messageToSend.isStop)
            {
                break;
            }
            uint32_t quantityToSend = messageToSend.size;
            uint32_t quantitySent = 0;
            uint8_t* bufferCpy = messageToSend.data;
            while (quantitySent < quantityToSend)
            {
                quantitySent = send(myDataSocket, bufferCpy, quantityToSend, 0);
                if (quantitySent == -1)
                {
                    LOG_NETWORKC("Error while sending");
                    NetworkC_setConnectionState(E_WAITING);
                    break;
                }
                else if (quantitySent == 0)
                {
                    LOG_NETWORKC("Client disconnected");
                    NetworkC_setConnectionState(E_WAITING);
                    sending = false;
                    break;
                }
                quantityToSend -= quantitySent;
                bufferCpy +=  quantitySent;
            }
            free(messageToSend.data);
        }
    }
    return NULL;
}

static void mailboxInit(void)
{
    errno = 0;
    myChecker = mq_unlink(QueueName);
    if(myChecker < 0 && errno != ENOENT)
    {
        LOG_NETWORKC("Mq Unlink error errno : %d", errno);
        myChecker = 0;
    }
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MQ_MAX_MESSAGES;
	attr.mq_msgsize = sizeof(s_args);
	attr.mq_curmsgs = 0;

	mq = mq_open(QueueName, O_CREAT | O_RDWR, 0600, &attr);
    if(mq == -1)
    {
        LOG_NETWORKC("Error opening the mailbox %s", QueueName);
    }
}

static void mailboxClose(void)
{
    LOG_NETWORKC();
    myChecker = mq_unlink(QueueName);
    LOG_NETWORKC("Error unlinking the mq %s", QueueName);
}

static void mailboxReceive(s_args * msg)
{
    LOG_NETWORKC();
    myChecker = mq_receive(mq, (char *) msg, sizeof(s_args), 0);
    if(myChecker == -1)
    {
        LOG_NETWORKC("Error sending a message");
        myChecker = 0;
    }
}

static void mailboxSendMsg(s_args* msg)
{
    LOG_NETWORKC();
    myChecker = mq_send(mq, (char *) msg, sizeof(s_args), 0 );
    if(myChecker == -1)
    {
        LOG_NETWORKC("Error receiving a message");
        myChecker = 0;
    }
}