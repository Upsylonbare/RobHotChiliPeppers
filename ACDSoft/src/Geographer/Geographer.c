/**
 * @file Geographer.c
 * @brief This component is the active object of ACDSoft
 * @author Thibault MALARY inspired by Thomas CRAVIC for the MaE
 * @date 2022-05-06
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
#include <pthread.h>
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>

#include "../Config/util.h"
#include "Geographer.h"
#include "../Converter/Converter.h"
#include "../LiDAR/LiDAR.h"
#include "../Folder/Folder.h"
#include "../Merger/Merger.h"

#include "../NetworkC/Proxy/NetworkC_ProxyCartoManager.h"
#include "../NetworkC/Proxy/NetworkC_ProxyGUI.h"

/******************************************************* DEFINE *******************************************************/

/**
 * @def MQ_MAX_MESSAGES
 *
 * The maximum number of message the queue can handle at one time
 *
 * By default, cannot be higher than 10, unless you change this
 * value into /proc/sys/fs/mqueue/msg_max
 */
#define MQ_MAX_MESSAGES (10)

/***************************************************** END DEFINE *****************************************************/

/***************************************************** STRUCTURE ******************************************************/

/**
 * @enum e_geographerState
 * @brief e_geographerState enumeration of state machine states
 */
typedef enum
{
    S_IDLE = 0,	///< IDLE State
    S_SCANNING,	///< Scan State
    S_END_SCAN,	///< End scan Stae
    S_SAVE,		///< Save State
    S_DEATH,	///< Death State
    S_NB_STATE	///< Number of states
} e_geographerState;

/**
 * @enum e_geographerAction
 * @brief e_geographerAction enumeration of the first actions during a state change
 */
typedef enum
{
    A_RESET_RAW_SCAN = 0, ///< Reset Raw Scan Action
    A_END_SCAN,           ///< End Scan Action
    A_ACK_4_SCAN,         ///< Ack for scan action
    A_ACK_CARTO,          ///< Ack carto action
    A_ACK_4_SAVE_CARTO,   ///< Ack for save carto action
    A_EXIT,               ///< Exit action
    A_NB_ACTIONS          /// Number of actions
} e_geographerAction;

/**
 * @enum e_geographerEvent
 * @brief e_geographerEvent enumeration of events changing a state
 */
typedef enum
{
    E_ASK_4_SCAN = 0,   ///< Ask for scan event
    E_END_SCAN,         ///< End scan event
    E_ACK_CARTO,        ///< Ack Carto event
    E_SET_CARTO,        ///< Set Carto event
    E_ACK_SAVE,         ///< Ack Save event
    E_EXIT,             ///< Exit event
    E_NB_EVENT          ///< Number of event
} e_geographerEvent;

/**
 * @struct s_geographerTransition
 * @brief s_geographerTransition structure determine the following state to reach after a specific event occur
 */
typedef struct
{
    e_geographerState destinationState;
    e_geographerAction actionToPerform;
} s_geographerTransition;

/**
 * @struct s_geographerMqMessage
 * @brief s_geographerMqMessage structure dedicated to pass the event between multiples threads
 */
typedef struct
{
    e_geographerEvent event;
    s_carto *myCarto;
    e_marker myMarker;
} s_geographerMqMessage;

/**
 * @struct s_geographer
 * @brief s_geographer structure determine the following state
 */
struct geographer
{
    pthread_t idThreadGeographerRun;
    mqd_t mqId;
    e_geographerState myState;
    s_rawData *myRawData;
    s_rawScan *myRawScan;
    s_rawScan *myRawScanMerged;
    s_carto *myCarto;
    e_marker myMarker;
};

/*************************************************** END STRUCTURE ****************************************************/

/*******************************************  STATIC FUNCTIONS DECLARATIONS *******************************************/

/**
 * @fn static void Geographer_run(void)
 * @brief Function dedicated to ask an action when a message is received in the mailbox
 */
static void *Geographer_run(void);

/**
 * @fn static void Geographer_actionResetRawScan(s_geographer * this)
 * @brief Action to reset raw scan
 */
static void Geographer_actionResetRawScan(s_geographer * this);

/**
 * @fn static void Geographer_actionEndScan(s_geographer * this)
 * @brief Action when a scan end
 */
static void Geographer_actionEndScan(s_geographer * this);

/**
 * @fn static void Geographer_actionAck4Scan(s_geographer * this)
 * @brief Action to ack that a scan is finished
 */
static void Geographer_actionAck4Scan(s_geographer * this);

/**
 * @fn static void Geographer_actionAckCarto(s_geographer * this)
 * @brief Action to ack that a carto has been received
 */
static void Geographer_actionAckCarto(s_geographer * this);

/**
 * @fn static void Geographer_actionAck4SaveCarto(s_geographer * this)
 * @brief Action to ack that we saved the carto
 */
static void Geographer_actionAck4SaveCarto(s_geographer * this);

/**
 * @fn static void Geographer_actionExit(s_geographer * this)
 * @brief Action when exit is ask
 */
static void Geographer_actionExit(s_geographer * this);

/**
 * @fn static mqd_t Geographer_mailboxInit ()
 * @brief Function dedicated to initialize the log queue
 * @return The mailbox id
 *
 */
static mqd_t Geographer_mailboxInit();

/**
 * @fn static void Geographer_mailboxSend(mqd_t mqId, e_geographerEvent event, s_carto *thisCarto, e_marker myMarker)
 * @brief Function dedicated to send a special stop message to the mailbox
 * @param event the event to send through the mailbox
 * @param thisCarto the carto to send through the mailbox
 * @param thisMarker the marker to send through the mailbox
 */
static void Geographer_mailboxSend(mqd_t mqId, e_geographerEvent event, s_carto *thisCarto, e_marker thisMarker);

/**
 * @fn static s_geographerMqMessage Geographer_mailboxReceive(mqd_t mqId)
 * @brief Function dedicated to receive a message from the mailbox
 * @return The message received in the mailbox
 */
static s_geographerMqMessage Geographer_mailboxReceive(mqd_t mqId);

/**
 * @fn static void Geographer_mailboxDone(mqd_t mqId)
 * @brief Function dedicated to destroy the mailbox
 */
static void Geographer_mailboxDone(mqd_t mqId);

/**************************************** END OF STATIC FUNCTIONS DECLARATIONS ****************************************/

/********************************************* STATE MACHINE DECLARATION **********************************************/

/**
 * @def Function pointer used to call the actions of the state machine.
 */
typedef void (*ActionPtr)(s_geographer *);

/**
 * @brief Function pointer array used to call the actions of the state machine.
 */
static const ActionPtr actionPtr[A_NB_ACTIONS] = {
    &Geographer_actionResetRawScan,
    &Geographer_actionEndScan,
    &Geographer_actionAck4Scan,
    &Geographer_actionAckCarto,
    &Geographer_actionAck4SaveCarto,
    &Geographer_actionExit,
};



/**
 * @brief The state machine transition table
 * 
 * \startuml
 * [*] -->S_IDLE
 * S_IDLE --> S_SCANNING : E_ASK_4_SCAN / A_RESET_RAW_SCAN
 * S_SCANNING --> S_END_SCAN : E_END_SCAN / A_END_SCAN
 * S_END_SCAN --> S_IDLE : E_ACK_CARTO / A_ACK_4_SCAN
 * S_IDLE --> S_SAVE : E_SET_CARTO / A_ACK_CARTO
 * S_SAVE --> S_IDLE : E_ACK_SAVE / A_ACK_4_SAVE_CARTO
 * S_IDLE --> S_DEATH : E_EXIT / A_EXIT
 * S_SCANNING --> S_DEATH : E_EXIT / A_EXIT
 * S_END_SCAN --> S_DEATH : E_EXIT / A_EXIT
 * S_SAVE --> S_DEATH : E_EXIT / A_EXIT
 * \enduml
 */
static s_geographerTransition myTransition[S_NB_STATE][E_NB_EVENT] = {
    [S_IDLE][E_ASK_4_SCAN] = {S_SCANNING, A_RESET_RAW_SCAN},
    [S_SCANNING][E_END_SCAN] = {S_END_SCAN, A_END_SCAN},
    [S_END_SCAN][E_ACK_CARTO] = {S_IDLE, A_ACK_4_SCAN},
    [S_IDLE][E_SET_CARTO] = {S_SAVE, A_ACK_CARTO},
    [S_SAVE][E_ACK_SAVE] = {S_IDLE, A_ACK_4_SAVE_CARTO},
    [S_IDLE][E_EXIT] = {S_DEATH, A_EXIT},
    [S_SCANNING][E_EXIT] = {S_DEATH, A_EXIT},
    [S_END_SCAN][E_EXIT] = {S_DEATH, A_EXIT},
    [S_SAVE][E_EXIT] = {S_DEATH, A_EXIT},
};

/**************************************** END OF STATE MACHINE DECLARATION *******************************************/

/*********************************************** VALUE INITIALIZATION *************************************************/

/**
 * @brief The name of mailbox
 */
static const char queueName[] = "/geographerBAL";

/**
 * @brief The mutex of geographer mailbox
 */
static pthread_mutex_t geographerMutex=PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief The pointer of geographer structure
 */
static s_geographer *myGeographer;

/******************************************* END OF VALUE INITIALIZATION **********************************************/

/************************************************** PUBLIC FUNCTIONS **************************************************/

void Geographer_new(void)
{
	LOG_GEOGRAPHER();
    myGeographer = NULL;
	myGeographer = (s_geographer *)calloc(1, sizeof(s_geographer));
    if (myGeographer == NULL)
    {
        LOG_GEOGRAPHER("Geographer : Allocate memory for geographer structure error.\n");
    }
    myGeographer->myRawData = NULL;
	myGeographer->myRawData = (s_rawData *)calloc(1, sizeof(s_rawData));
    if (myGeographer->myRawData == NULL)
    {
        LOG_GEOGRAPHER("Geographer : Allocate memory for rawData structure error.\n");
    }
    myGeographer->myRawScan = NULL;
	myGeographer->myRawScan = (s_rawScan *)calloc(1, sizeof(s_rawScan));
    if (myGeographer->myRawScan == NULL)
    {
        LOG_GEOGRAPHER("Geographer : Allocate memory for rawScan structure error.\n");
    }
    myGeographer->myRawScanMerged = NULL;
	myGeographer->myRawScanMerged = (s_rawScan *)calloc(1, sizeof(s_rawScan));
    if (myGeographer->myRawScanMerged == NULL)
    {
        LOG_GEOGRAPHER("Geographer : Allocate memory for rawScanMerged structure error.\n");
    }
	myGeographer->mqId = Geographer_mailboxInit();
	myGeographer->myState = S_IDLE;
	Converter_resetRawScan(myGeographer->myRawScanMerged);
}

void Geographer_free(void)
{
	LOG_GEOGRAPHER();
	Geographer_mailboxDone(myGeographer->mqId);
	if (myGeographer->myRawScanMerged)
	{
		free(myGeographer->myRawScanMerged);
	}
	if (myGeographer->myRawScan)
	{
		free(myGeographer->myRawScan);
	}
	if (myGeographer->myRawData)
	{
		free(myGeographer->myRawData);
	}
	if (myGeographer)
	{
		free(myGeographer);
	}
}

void Geographer_start(void)
{
    LOG_GEOGRAPHER();
    int pthreadError = 0;
    pthreadError = pthread_create(&myGeographer->idThreadGeographerRun, NULL, (void *)&Geographer_run, NULL);
    if (pthreadError != 0)
    {
        LOG_GEOGRAPHER("Geographer : Create the run thread error.\npthread error : %d\n", pthreadError);
    }
}

void Geographer_stop(void)
{
    LOG_GEOGRAPHER();
    Geographer_mailboxSend(myGeographer->mqId, E_EXIT, NULL, NONE);
    int pthreadError = 0;
    pthread_join(myGeographer->idThreadGeographerRun, NULL);
    if (pthreadError != 0)
    {
        LOG_GEOGRAPHER("Geographer : Join the run thread error.\npthread error : %d\n", pthreadError);
    }
}

void Geographer_ask4Scan(e_marker myMarker)
{
	LOG_GEOGRAPHER();
	Geographer_mailboxSend(myGeographer->mqId, E_ASK_4_SCAN, NULL, myMarker);
}

void Geographer_endScan(void)
{
	LOG_GEOGRAPHER();
	Geographer_mailboxSend(myGeographer->mqId, E_END_SCAN, NULL, NONE);
}

void Geographer_ackCarto(void)
{
	LOG_GEOGRAPHER();
	Geographer_mailboxSend(myGeographer->mqId, E_ACK_CARTO, NULL, NONE);
}

void Geographer_ackSave(void)
{
	LOG_GEOGRAPHER();
	Geographer_mailboxSend(myGeographer->mqId, E_ACK_SAVE, NULL, NONE);
}

void Geographer_setCarto(s_carto *carto)
{
	LOG_GEOGRAPHER();
	Geographer_mailboxSend(myGeographer->mqId, E_SET_CARTO, carto, NONE);
}

/********************************************* END OF PUBLIC FUNCTIONS ************************************************/

/******************************************* MAE PERFORMING ACTION MECANISM *******************************************/

static void *Geographer_run(void)
{
	LOG_GEOGRAPHER();
	s_geographerMqMessage mqMsg;
	e_geographerAction action;
	e_geographerState state;
	while (myGeographer->myState != S_DEATH)
	{
		mqMsg = Geographer_mailboxReceive(myGeographer->mqId);
		// If we received the exit event, we do nothing and we change the state to death.
		if (mqMsg.event == E_EXIT)
		{
			myGeographer->myState = S_DEATH;
		}
		else
		{
			state = myTransition[myGeographer->myState][mqMsg.event].destinationState;
			action = myTransition[myGeographer->myState][mqMsg.event].actionToPerform;
			myGeographer->myState = state;
			if(E_SET_CARTO)
			{
				myGeographer->myCarto = mqMsg.myCarto;
			}
			else if (E_ASK_4_SCAN)
			{
				myGeographer->myMarker = mqMsg.myMarker;
			}
			actionPtr[action](myGeographer);
		}
	}
	return NULL;
}

static void Geographer_actionResetRawScan(s_geographer * this)
{
    LOG_GEOGRAPHER();
    Converter_resetRawScan(myGeographer->myRawScan);
    LiDAR_startScan();
}

static void Geographer_actionEndScan(s_geographer * this)
{
    LOG_GEOGRAPHER();
    LiDAR_getScan(myGeographer->myRawData);
    Converter_convert2RawScan(myGeographer->myRawScan, myGeographer->myRawData);
    Merger_merge(myGeographer->myRawScanMerged, myGeographer->myRawScan, myGeographer->myMarker);
    myGeographer->myCarto = Folder_createNewCarto();
    Folder_convert2Bitmap(myGeographer->myRawScanMerged, myGeographer->myCarto->rawCarto);
    NetworkC_ProxyCartoManager_setCarto(myGeographer->myCarto);
    if(myGeographer->myCarto)
    {
        free(myGeographer->myCarto);
    }
}

static void Geographer_actionAck4Scan(s_geographer * this)
{
    LOG_GEOGRAPHER();
    NetworkC_ProxyGUI_ack4Scan();
}

static void Geographer_actionAckCarto(s_geographer * this)
{
    LOG_GEOGRAPHER();
    NetworkC_ProxyCartoManager_ackCarto();
    Folder_saveTreatedCarto(myGeographer->myCarto);
    if(myGeographer->myCarto)
    {
        free(myGeographer->myCarto);
    }
}

static void Geographer_actionAck4SaveCarto(s_geographer * this)
{
    LOG_GEOGRAPHER();
    Converter_resetRawScan(myGeographer->myRawScanMerged);
    NetworkC_ProxyGUI_ack4SaveCarto();
}

static void Geographer_actionExit(s_geographer * this)
{
    LOG_GEOGRAPHER();
    // Do nothing
}

/*************************************** END OF MAE PERFORMING ACTION MECANISM ****************************************/

/************************************************** MAILBOX FUNCTION **************************************************/

static mqd_t Geographer_mailboxInit()
{
	LOG_GEOGRAPHER();
	/* Init BAL */
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MQ_MAX_MESSAGES;
	attr.mq_msgsize = sizeof(s_geographerMqMessage);
	attr.mq_curmsgs = 0;
	/* Destruct a pre-existing mailbox */
	mq_unlink(queueName);
	/* Create and open the mailbox */
    // Creation of a new mailbox if any was created before.
    errno = 0;
	mqd_t mqId = mq_open(queueName, O_CREAT | O_RDWR, 0600, &attr);
	if (mqId == -1)
    {
        LOG_GEOGRAPHER("Geographer : Mailbox open error.\nerrno error : %d\n", errno);
    }
	return mqId;
}

static void Geographer_mailboxSend(mqd_t mqId, e_geographerEvent event, s_carto *thisCarto, e_marker myMarker)
{
	LOG_GEOGRAPHER();
	/* Send the message */
	/* RACE CONDITION */
    pthread_mutex_lock(&geographerMutex);
	s_geographerMqMessage mqMsg;
	mqMsg.event = event;
	mqMsg.myCarto = thisCarto;
    // Priority 0 to 31 (highest priority first)
	int mqError = 0;
    errno = 0;
	mqError = mq_send(mqId, (const char *)&mqMsg, sizeof(s_geographerMqMessage), 0);
    if (mqError == -1)
    {
        LOG_GEOGRAPHER("Geographer : Mailbox send error.\nerrno error : %d\n", errno);
    }
    /* END RACE CONDITION */
	pthread_mutex_unlock(&geographerMutex);
}

static s_geographerMqMessage Geographer_mailboxReceive(mqd_t mqId)
{
	LOG_GEOGRAPHER();
	/* Reception of a message from the BAL */
	s_geographerMqMessage mqMsg;
    // Null priority => mailbox use as a FIFO
	int mqError = 0;
    errno = 0;
	mqError = mq_receive(mqId, (char *)&mqMsg, sizeof(s_geographerMqMessage), NULL);
    if (mqError == -1)
    {
        LOG_GEOGRAPHER("Geographer : Mailbox receive error.\nerrno error : %d\n", errno);
    }
	return mqMsg;
}

static void Geographer_mailboxDone(mqd_t mqId)
{
	LOG_GEOGRAPHER();
	/* Close the existing mailbox */
	int mqError = 0;
    errno = 0;
	mqError = mq_close(mqId);
    if (mqError == -1)
    {
        LOG_GEOGRAPHER("Geographer : Mailbox close error.\nerrno error : %d\n", errno);
    }
	/* Destruct the existing mailbox */
	mqError = 0;
    errno = 0;
	mqError = mq_unlink(queueName);
    if (mqError == -1)
    {
        LOG_GEOGRAPHER("Geographer : Mailbox unlink error.\nerrno error : %d\n", errno);
    }
}

/********************************************** END OF MAILBOX FUNCTION ***********************************************/