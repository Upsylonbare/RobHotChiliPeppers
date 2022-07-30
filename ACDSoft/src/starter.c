/**
 * @file starter.c
 * @author Malary Thibault, Jean-Théophane Deschard
 * @brief Starter of ACDSoft
 * @version 1
 * @date 2022-05-01
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

#include "UI/UI.h"
#include "Geographer/Geographer.h"
#include "NetworkC/Postman/NetworkC_Postman.h"
#include "NetworkC/Dispatcher/NetworkC_Dispatcher.h"
#include "LiDAR/LiDAR.h"

int main(int argc, char *argv[])
{
    NetworkC_Postman_new();
    NetworkC_Dispatcher_new();
    Geographer_new();
    LiDAR_new();
    UI_new();
    NetworkC_Postman_start();
    Geographer_start();
    LiDAR_start();
    UI_start();
    LiDAR_stop();
    Geographer_stop();
    NetworkC_Dispatcher_stop();
    NetworkC_Postman_stop();
    UI_free();
    LiDAR_free();
    Geographer_free();
    NetworkC_Dispatcher_free();
    NetworkC_Postman_free();
    return 0;
}