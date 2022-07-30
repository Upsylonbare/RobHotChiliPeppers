/**
 * @file  LiDAR.c
 * @brief  This component communicates with the physical LiDAR to get a scan in a txt format and converts it to an 
 * integer array
 * @author Jean-Théophane Deschard, Marin BONSERGENT
 * @date 2022
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

#include <pthread.h>
#include <stdbool.h> 
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "../Config/util.h"
#include "LiDAR.h"

/* ----------------------- MAILBOX DEFINITIONS -----------------------*/


/**
 * @def MQ_MAX_MESSAGES
 *
 * The maximum number of message the queue can handle at one time
 *
 * By default, cannot be higher than 10, unless you change this
 * value into /proc/sys/fs/mqueue/msg_max
 */
#define MQ_MAX_MESSAGES (10)


/*----------------------- TYPE DEFINITIONS -----------------------*/

/**
 * @brief Enumeration of all the states that can be taken by the state machine
 */
typedef enum {
	S_FORGET = 0,   ///< Nothing happens
	
    // TODO : Add here the states corresponding to your state machine. Do not remove S_FORGET, S_DEATH and NB_STATE
    S_IDLE,         ///< Idle state
	S_SCAN,      ///< Running state
	
    S_DEATH,        ///< Transition state for stopping the state machine
	NB_STATE        ///< Number of states
} e_state;


/**
 * @brief Enumaration of all the possible actions called by the state machine
 */
typedef enum {
	A_NOP = 0,              ///< Nothing happens

	// TODO : Add here the actions corresponding to your state machine. Do not remove A_NOP, A_KILL and NB_ACTIONS

    A_STARTSCAN,///< Action called when passing from the running state to the example1 state
	A_ENDSCAN,   ///< Action called when passing from the idle state to the running state
	
	NB_ACTION               ///< Number of actions
} e_action;


/**
 * @brief Enumeration of all the possible events that triggers the state machine
 */
typedef enum {
	E_NOP = 0,  ///< Do nothing

    // TODO : Add here the events corresponding to your state machine. Do not remove E_NOP, E_KILL and NB_EVENT
	E_STARTSCAN, ///< Event example 1
	E_ENDSCAN, ///< Event example 2

	E_KILL,     ///< Kills the state machine
	NB_EVENT    ///< Number of events
} e_event;


/**
 * @brief Transition structure of the state machine
 */
typedef struct {
	e_state destinationState; ///< Next state of the state machine
	e_action action;   ///< Action done before going in the next state
} s_transition;


/**
 * @brief Structure of a message sent in the mailbox
 */
typedef struct 
{
	e_event event; ///< Event sent in the message
} s_mqMessage;


/**
 * @brief Structure of the Example object
 */
typedef struct {
    pthread_t threadId; ///< Pthread identifier for the active function of the class.
	e_state state;        ///< Actual state of the state machine
    int rawData[RAW_DATA_SIZE];
}s_lidar;

static s_lidar *lidar;
static mqd_t mq;
static const char queueName[] = "/lidar"; // name of mailbox

/*----------------------- STATIC FUNCTIONS PROTOTYPES -----------------------*/

static void LiDAR_run();

/*------------- Action functions -------------*/
// TODO : put here all the action functions prototypes
/**
 * @brief Function called when nothing needs to be done
 */
static void LiDAR_actionNop();


/**
 * @brief Function called when there is the event Example 1 and when the state is Idle
 */
static void LiDAR_actionStartScan();


/**
 * @brief Function called when there is the event Example 1 and when the state is Running
 */
static void LiDAR_actionEndScan();


/*------------- Mailbox functions -------------*/

/**
 * @brief Initializes the queue
 */
static void LiDAR_mailboxInit();


/**
 * @brief Destroys the queue
 */
static void LiDAR_mailboxClose();


/**
 * @brief Sends a stop event to the queue
 *
 * @note There is no specific content in the message, so there 
 * is no need to specify any argument.
 */
static void LiDAR_mailboxSendStop();


/**
 * @brief Receives a message from the queue
 *
 * @note This function is blocking if the queue is empty
 */
static s_mqMessage LiDAR_mailboxReceive();

/**
 * @brief Sends a message to the queue
 *
 * @note This function is blocking if the queue is full
 * @param msg message
 */
static void LiDAR_mailboxSendMsg(e_event event);


/*----------------------- STATE MACHINE DECLARATION -----------------------*/

/**
 * @def Function pointer used to call the actions of the state machine.
 */
typedef void (*ActionPtr)(s_lidar*);

/**
 * @brief Function pointer array used to call the actions of the state machine.
 */
static const ActionPtr actionPtr[NB_ACTION] = { 
        &LiDAR_actionNop,
        &LiDAR_actionStartScan,
        &LiDAR_actionEndScan,
    };


/**
 * @brief State machine of the Example class
 */
static s_transition stateMachine[NB_STATE][NB_EVENT] = { // TODO : fill the state machine
	[S_IDLE][E_STARTSCAN]    = {S_SCAN,	A_STARTSCAN},
    [S_SCAN][E_ENDSCAN] = {S_IDLE, A_ENDSCAN},

    [S_IDLE][E_KILL] = {S_DEATH, A_NOP}
};

/* ----------------------- ACTIONS FUNCTIONS ----------------------- */

// TODO : Write all the action functions

static void LiDAR_actionStartScan() 
{
    LOG_LIDAR();
    
    LiDAR_A1M8_launchScan();
}


static void LiDAR_actionEndScan() 
{ 
    LOG_LIDAR();

    Geographer_endScan();    
}


static void LiDAR_actionNop() 
{
}


/*----------------------- EVENT FUNCTIONS -----------------------*/
// TODO : write the events functions

void LiDAR_startScan() 
{
    LOG_LIDAR();

    LiDAR_mailboxSendMsg(E_STARTSCAN);
}

void LiDAR_endScan()
{
    LOG_LIDAR();

    LiDAR_mailboxSendMsg(E_ENDSCAN);
}


/* ----------------------- RUN FUNCTION ----------------------- */

/**
 * @brief Main running function of the Example class
 */
static void LiDAR_run() {
    LOG_LIDAR();

    s_mqMessage mqMsg;
    e_action action;
    e_state nextState;


    while (lidar->state != S_DEATH) 
    {
        mqMsg = LiDAR_mailboxReceive(); ///< Receiving an event from the mailbox
        action = stateMachine[lidar->state][mqMsg.event].action;

        nextState = stateMachine[lidar->state][mqMsg.event].destinationState;
        actionPtr[action](lidar);
        lidar->state = nextState;

    }
}

/* ----------------------- NEW START STOP FREE -----------------------*/
void LiDAR_new() {

    LOG_LIDAR();
   

    // initialize the object with it particularities
	lidar = (s_lidar *) malloc(sizeof(s_lidar));
    lidar->state = S_IDLE; 
    LiDAR_mailboxInit();
}


void LiDAR_start() {
    // TODO : start the object with it particularities
    LOG_LIDAR();
    pthread_create(&(lidar->threadId), NULL, (void *) LiDAR_run, NULL);

}


void LiDAR_stop() {
    // TODO : stop the object with it particularities
    LOG_LIDAR();
	LiDAR_mailboxSendStop();
    pthread_join(lidar->threadId, NULL);

}


void LiDAR_free() {
    // TODO : free the object with it particularities
    LOG_LIDAR();
    LiDAR_mailboxClose();
    
	free(lidar);

}


/* -------------- MAILBOX ------------- */


static void LiDAR_mailboxInit() 
{
    LOG_LIDAR();

	/* INIT BAL */
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = MQ_MAX_MESSAGES;
	attr.mq_msgsize = sizeof(s_mqMessage);
	attr.mq_curmsgs = 0;

	/* Destruct a pre-existing mailbox */
	mq_unlink(queueName);

	/* Create and open the mailbox */
	mq = mq_open(queueName, O_CREAT | O_RDWR, 0600, &attr); // Creation of a new mailbox if any was created before.
	// TODO: Gestion des erreurs


}

static void LiDAR_mailboxClose() 
{
    LOG_LIDAR();

	/* Destruction of the queue */
    mq_close(mq);
	mq_unlink(queueName);

}
static void LiDAR_mailboxSendStop() {
    LOG_LIDAR();

	LiDAR_mailboxSendMsg(E_KILL);
}

static void LiDAR_mailboxSendMsg(e_event event)
{
    LOG_LIDAR();

    s_mqMessage mqMsg;
    mqMsg.event = event;

    mq_send(mq, (const char *)&mqMsg, sizeof(s_mqMessage), 0);
}

static s_mqMessage LiDAR_mailboxReceive() 
{
    LOG_LIDAR();
    s_mqMessage mqMsg;

	mq_receive(mq, (char*)&mqMsg, sizeof(s_mqMessage), 0);
    return mqMsg;

}

void LiDAR_getScan(s_rawData *myRawData)
{
    LOG_LIDAR();
    // open file
    FILE * file;
    file = fopen(RAW_DATA_FILE, "r");

    if(file)
    {
        int i = 0;
        while(!feof(file))
        {
            // Scans file data and stores it in lidar
            fscanf(file, "%d,", &myRawData->rawData_a[i]);
            i++;
        }
        fclose(file);
    }
    else
    {
        printf("ERROR OPEN FILE : File not found.\n");
    }

}