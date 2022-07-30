/**
 * @file  UI.c
 * @brief  This component displays a window with a color related to the current connection state and a quit button to 
 * quit the app
 * @author Jean-Théophane Deschard
 * @date 2022-05-11
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

/****************************************************** INCLUDE *******************************************************/

#include <pthread.h>
#include <mqueue.h>
#include <gtk/gtk.h> 
#include "UI.h"
#include "../Config/util.h"
#include "../NetworkC/NetworkC.h"

/******************************************************* DEFINE *******************************************************/

/**
 * @def MQ_MAX_MESSAGES
 * @brief The max number of message in the mail box
 * 
 */
#define MQ_MAX_MESSAGES (10)

/*------------------------------------------ TYPE DEFINITIONS -------------------------------------------*/

/**
 * @enum State
 * @brief Enumeration of all the states that can be taken by the state machine
 */
typedef enum {
    S_WAITING,      ///< The state machine is waiting for a connection
    S_CONNECTED,    ///< Connection is established
    S_ERROR,        ///< Error State
    S_DEATH,        ///< Transition state for stopping the state machine
    NB_STATE        ///< Number of states
} e_state;

/**
 * @enum Action
 * @brief Enumeration of all the possible actions called by the state machine
 */
typedef enum {

    A_ERROR,        ///< Action called when passing to error state
    A_CONNECTED,    ///< Action called when passing to the connected state
    A_WAITING,      ///< Action called when passing to the waiting state
    A_KILL,         ///< Kills the state machine
    NB_ACTION       ///< Number of actions
} e_action;


/***************************************************** STRUCTURE ******************************************************/

/**
 * @struct Transistion
 * @brief Transition structure of the state machine
 */
typedef struct {
    e_state nextState; ///< Next state of the state machine
    e_action action;   ///< Action done before going in the next state
} s_transition;

/**
 * @fn UI
 * @brief Structure of the UI object
 */
typedef struct {
    pthread_t threadId; ///< Pthread identifier for the active function of the class.
    e_state state;      ///< Actual state of the state machine
}s_ui;

/**
 * @fn s_mqMessage
 * @brief Structure of the message object
 */
typedef struct
{
    e_connectionState event; ///< Event of the message
} s_mqMessage;

/*********************************************** VALUE INITIALIZATION *************************************************/

/**
 * @brief Ui object 
 */
static s_ui* ui;

/**
 * @brief GTK pointer to the window
 */
static GtkWidget *pWindow;

/**
 * @brief GTK pointer to the connection state boutton
 */
static GtkWidget *pConnectionStateBtn;

/**
 * @brief GTK pointer to the container
 */
static GtkWidget *pContainer;

/**
 * @brief GTK pointer to the quit button
 */
static GtkWidget *pQuitBtn;

/**
 * @brief GTK pointer to the quit button
 */
static GtkWidget *pQuitPopUp;

/**
 * @brief Name of the mail box 
 */
static const char queueName[] = "/ui";

/**
 * @brief Message queue of UI
 */
static mqd_t mq;

/**
 * @brief GTK color red
 */
static GdkRGBA colorRed;

/**
 * @brief GTK color orange
 */
static GdkRGBA colorOrange;

/**
 * @brief GTK color green
 */
static GdkRGBA colorGreen;

/*********************************************** STATIC FUNCTIONS *************************************************/

/*------------- Action functions -------------*/

/**
 * @fn static void UI_run();
 * @brief While loop which run the state machine 
 */
static void UI_run();

/**
 * @fn static void UI_actionError()
 * @brief Set the color to red 
 */
static void UI_actionError();

/**
 * @fn static void UI_actionConnected()
 * @brief Set the color to green 
 */
static void UI_actionConnected();

/**
 * @fn static void UI_actionWaiting()
 * @brief Set the color to orange 
 */
static void UI_actionWaiting();

/**
 * @fn static void UI_actionKill()
 * @brief Changes the state of the state machine to S_DEATH
 */
static void UI_actionKill();

/*----------------------- GTK functions -----------------------*/

/**
 * @fn static void UI_showPopUp (GtkWindow *parent, gpointer window))
 * @brief function to show the qUIt PopUp
 * 
 * @param parent Gtkwindow
 * @param window point the window
 */
static void UI_showPopUp(GtkWindow *parent, gpointer window);

/**
 * @fn static void UI_yes ()
 * @brief function to perform an action when ok is selected on the quit PopUp
 * 
 */
static void UI_yes();

/**
 * @fn static void UI_no ()
 * @brief function to perform an action when no is selected on the quit PopUp
 * 
 */
static void UI_no();

/**
 * @fn static void UI_quit ()
 * @brief function wich call UI_stop when yes is selected on the quit PopUp
 */
static void UI_quit();

/**
 * @fn static void UI_setColor (Color)
 * @brief function wich change the color of the button according to the color passed into parameters
 * 
 */
static void UI_setColor(GdkRGBA *color);

/* -------------- Mailbox ------------- */

/**
 * @fn static void UI_mailboxInit ()
 * @brief function dedicated to initialize the log queue
 *
 */
static void UI_mailboxInit();

/**
 * @fn static void UI_mailboxClose ()
 * @brief function dedicated to close the log queue
 *
 */
static void UI_mailboxClose();

/**
 * @fn static void UI_mailboxSendMsg (e_connectionState event)
 * @brief function dedicated to send a message
 *
 * @param e_event the event to send threw the mail box
 */
static void UI_mailboxSendMsg(e_connectionState event);

/**
 * @fn static void UI_mailboxReceive ()
 * @brief function dedicated to receive a message
 * 
 * @return s_mqMessage 
 */
static s_mqMessage UI_mailboxReceive();

/**
 * @fn static void UI_mailboxSendStop ()
 * @brief function dedicated to stop the run function
 * 
 */
static void UI_mailboxSendStop();

/*------------------------------------------- STATE MACHINE DECLARATION -------------------------------------------*/

/**
 * @def Function pointer used to call the actions of the state machine.
 */
typedef void (*ActionPtr)(s_ui*);

static const ActionPtr actionPtr[NB_ACTION] = { 
        &UI_actionError,
        &UI_actionConnected,
        &UI_actionWaiting,
        &UI_actionKill
    };

/**
 * @brief State machine of the UI class
 * 
 * \startuml
 * [*] --> S_WAITING
 * S_WAITING --> S_CONNECTED : E_CONNECTED / A_CONNECTED
 * S_WAITING --> S_ERROR : E_ERROR / A_ERROR
 * S_CONNECTED --> S_ERROR : E_ERROR / A_ERROR
 * S_ERROR --> S_CONNECTED : E_CONNECTED / A_CONNECTED
 * S_WAITING --> S_WAITING : E_WAITING / A_WAITING
 * S_ERROR --> S_ERROR : E_ERROR / A_ERROR
 * S_CONNECTED --> S_CONNECTED : E_CONNECTED / A_CONNECTED
 * S_CONNECTED --> S_DEATH : E_KILL / A_KILL
 * S_WAITING --> S_DEATH : E_KILL / A_KILL
 * S_ERROR --> S_DEATH : E_KILL / A_KILL
 * \enduml
 */
static s_transition stateMachine[NB_STATE][NB_EVENT] = { 
    [S_WAITING][E_CONNECTED] = {S_CONNECTED, A_CONNECTED},
    [S_WAITING][E_ERROR] = {S_ERROR, A_ERROR},
    [S_CONNECTED][E_ERROR] = {S_ERROR, A_ERROR},
    [S_ERROR][E_CONNECTED] = {S_CONNECTED, A_CONNECTED},
    [S_WAITING][E_WAITING] = {S_WAITING, A_WAITING},
    [S_ERROR][E_ERROR] = {S_ERROR, A_ERROR},
    [S_CONNECTED][E_CONNECTED] = {S_CONNECTED, A_CONNECTED},
    [S_CONNECTED][E_KILL] = {S_DEATH, A_KILL},
    [S_WAITING][E_KILL] = {S_DEATH, A_KILL},
    [S_ERROR][E_KILL] = {S_DEATH, A_KILL},
};

/* ------------------------------------------- ACTIONS FUNCTION ------------------------------------------- */
static void UI_actionError()
{
    LOG_UI();
    /* Display a red button corresponding to error state */
    colorRed.red = 1;
    colorRed.green = 0;
    colorRed.blue = 0;
    colorRed.alpha = 1;
    UI_setColor(&colorRed);
}

static void UI_actionConnected()
{
    LOG_UI();
    /* Display a green button corresponding to connected state */
    colorGreen.red = 0;
    colorGreen.green = 1;
    colorGreen.blue = 0;
    colorGreen.alpha = 1;
    UI_setColor(&colorGreen);
}

static void UI_actionWaiting()
{
    LOG_UI();
    /* Display an orange button corresponding to waiting state*/
    colorOrange.red = 1;
    colorOrange.green = 0.5;
    colorOrange.blue = 0;
    colorOrange.alpha = 1; 
    UI_setColor(&colorOrange);
}
static void UI_actionKill()
{
    LOG_UI();
}


/* ----------------------- RUN FUNCTION ----------------------- */

/**
 * @fn static void UI_run ()
 * @brief Main running function of the UI class
 */

static void UI_run() 
{

    LOG_UI();
    e_action action;
    e_state state;
    s_mqMessage mqMsg;
    int tConnection = 10;
    e_connectionState myConnectionState;
    while (ui->state != S_DEATH) 
    {
        mqMsg = UI_mailboxReceive();
        myConnectionState = NetworkC_getConnectionState();
            if(mqMsg.event == E_KILL)
            {
               break;
            }
            else
            {
                action = stateMachine[ui->state][myConnectionState].action;
                state = stateMachine[ui->state][myConnectionState].nextState;

                actionPtr[action](ui);
                ui->state=state;
            }
        sleep(tConnection);
    }
}

/* -------------- GTK functions ------------- */

static void UI_showPopUp(GtkWindow *parent, gpointer window)
{
    LOG_UI();
    pQuitPopUp = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "Voulez-vous quitter ?");  
    switch(gtk_dialog_run(GTK_DIALOG(pQuitPopUp)))  
    {  
        /*GTK_RESPONSE_YES is the value return of the yes button */
        case GTK_RESPONSE_YES://   
            UI_yes();  
            break;  
        /* GTK_RESPONSE_NO is the value return of the no button */    
        case GTK_RESPONSE_NO: 
            UI_no();
            break;  
    }  
}

static void UI_yes()
{
    LOG_UI();
    /* Call quit function which quit the app */
    UI_quit();
}

static void UI_no()
{
    LOG_UI();
    /* Only destroy pQuitPopUp widget */
    gtk_widget_destroy(pQuitPopUp);  
}

static void UI_quit()
{
    UI_stop();
}

static void UI_setColor(GdkRGBA *color)
{
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(pConnectionStateBtn), color);
}

/* ----------------------- NEW START STOP FREE -----------------------*/
void UI_new() 
{
    LOG_UI();
    UI_mailboxInit();
    // initialize the object with it particularities
	ui = (s_ui *) malloc(sizeof(s_ui));
    ui->state = S_WAITING;
}


void UI_start() 
{
    LOG_UI();
    /* init threads */
    gtk_init(NULL,NULL);
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 480 ,800); 
    gtk_window_fullscreen(GTK_WINDOW(pWindow));
    /* Creat a container to display "Quit" button */
    pContainer = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(pWindow), pContainer);
    /* Creat button */
    pQuitBtn = gtk_button_new_with_label("QUITTER");
    gtk_fixed_put (GTK_FIXED (pContainer), pQuitBtn,50,400);
    gtk_widget_set_size_request(pQuitBtn, 380, 100);
    pConnectionStateBtn = gtk_color_button_new();
    //gtk_widget_set_sensitive (GTK_WIDGET (pConnectionStateBtn), FALSE); 
    gtk_fixed_put (GTK_FIXED (pContainer), pConnectionStateBtn,140,200);
    gtk_widget_set_size_request(pConnectionStateBtn, 200, 70);
    /*Connect "clicked" signal of pQuitBtn */
    g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(UI_showPopUp), (gpointer) pWindow);
    /* Connect "destroy" signal */
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(UI_stop), NULL);
    gtk_widget_show_all(pWindow);
    pthread_create(&(ui->threadId), NULL, (void *)&UI_run, NULL);
    gtk_main();
}


void UI_stop() 
{
    LOG_UI();
    // stop the object with it particularities
    UI_mailboxSendStop();
    //pthread_join(ui->threadId, NULL);
    gtk_main_quit();
}


void UI_free() 
{

    LOG_UI();
    UI_mailboxClose();
    // free the object with it particularities
    free(ui);
}

/* -------------- Mailbox ------------- */

static void UI_mailboxInit() 
{
    LOG_UI();
	/* Destroying the mailbox if it already exists */
	mq_unlink(queueName);
	/* Initializes the queue attributes */
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MQ_MAX_MESSAGES;		// Size of the queue
	attr.mq_msgsize = sizeof(s_mqMessage);		// Max size of a message
	attr.mq_curmsgs = 0;
    // Creating the queue
	mq = mq_open(queueName, O_CREAT | O_RDWR | O_NONBLOCK, 0644, &attr);
}

static void UI_mailboxClose() 
{
    LOG_UI();
	/* Destruction of the queue */
    mq_close(mq);
	mq_unlink(queueName);
}

static void UI_mailboxSendStop() 
{
    LOG_UI();
	UI_mailboxSendMsg(E_KILL);
}

static void UI_mailboxSendMsg(e_connectionState event) 
{
    LOG_UI();
    s_mqMessage mqMsg;
    mqMsg.event = event;	
    mq_send(mq, (const char *)&mqMsg, sizeof(s_mqMessage), 0);
}

static s_mqMessage UI_mailboxReceive() 
{
    LOG_UI();
    s_mqMessage mqMsg;
	mq_receive(mq, (char*)&mqMsg, sizeof(s_mqMessage), NULL);
    return mqMsg;
}
