/**
 * @file UI.h
 * @brief  This component display a window with a color related to the current connection state and a quit button to quit the app
 *
 * @author Jean-Théophane Deschard
 * @date 2022-05-11
 * 
 * @version 1
 * 
 * @copyright Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice, 
 *  this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice, 
 *  this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its contributors
 *  may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 *  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef UI_H
#define UI_H

/**
 * @struct UI
 * @brief structure UI
 * 
 */
//typedef struct Ui_t Ui;

/******************************************************** PUBLIC FUNCTIONS **********************************************************/

/* ----------------------- NEW START STOP FREE -----------------------*/

/**
 * @fn void UI_new()
 * @brief UI class constructor
 */
void UI_new();


/**
 * @fn void UI_start()
 * @brief UI class starter
 *
 * Starts the UI and the gtk window object
 */
void UI_start();


/**
 * @fn void UI_stop ()
 * @brief UI singleton stopper
 *
 */

void UI_stop ();

/**
 * @fn void UI_free ()
 * @brief UI singleton destructor
 *
 */

void UI_free ();

#endif //UI_H
