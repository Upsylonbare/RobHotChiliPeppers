/**
 * @file util.h
 * @brief Macros to color the terminal in debug mode and do assert
 * @author Jerome Delatour adapted by Clément Le Goffic
 * @date 2021
 * @warning Only work with gcc compiler for TRACE
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

#ifndef UTIL_H 
#define UTIL_H 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

//Foreground color
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define DEFAUT  "\033[39m"

//Background color
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"
#define BG_DEFAUT  "\033[49m"


#ifndef NDEBUG
#define TRACE(frColor, bgColor ,fmt, ...) do {fprintf(stderr, frColor bgColor "Line: %d:%s(): " fmt BG_DEFAUT DEFAUT "\n", __LINE__, __func__, ##__VA_ARGS__); fflush (stderr); } while(0);     
#define ASSERT_PRINTERROR(assertion) do {if (!(assertion)) {perror("Erreur"); assert(assertion);} } while(0);    
#define STOP_ON_ERROR(error_condition) do {     \
	if(error_condition) { \
		fprintf (stderr, "*** Error (%s) at \
		%s:%d\nExiting\n", \
		#error_condition, __FILE__, __LINE__); \
		perror (""); \
		_exit (1); } \
    } while (0); 

//Clement's MACRO
#define LOG_CARTO(fmt, ...) do{TRACE(YELLOW,BG_BLACK,fmt,##__VA_ARGS__);}while(0);
#define LOG_CONVERTER(fmt, ...) do{TRACE(CYAN,BG_BLACK,fmt,##__VA_ARGS__);}while(0);
#define LOG_FOLDER(fmt, ...) do{TRACE(BLUE,BG_BLACK,fmt,##__VA_ARGS__);}while(0);
#define LOG_GEOGRAPHER(fmt, ...) do{TRACE(GREEN,BG_BLACK,fmt,##__VA_ARGS__);}while(0);
#define LOG_LIDAR(fmt, ...) do{TRACE(MAGENTA,BG_BLACK,fmt,##__VA_ARGS__);}while(0);
#define LOG_NETWORKC(fmt, ...) do{TRACE(WHITE,BG_GREEN,fmt,##__VA_ARGS__);}while(0);
#define LOG_UI(fmt, ...) do{TRACE(WHITE,BG_BLACK,fmt,##__VA_ARGS__);}while(0);
#define LOG_MERGER(fmt, ...) do{TRACE(BLACK,BG_YELLOW,fmt,##__VA_ARGS__);}while(0);
#define LOG_ACDSOFT(fmt, ...) do{TRACE(RED,BG_BLACK,fmt,##__VA_ARGS__);}while(0);



#else
#define TRACE(fmt, ...) 
//must keep assert loggs for prod due to 
#define ASSERT_PRINTERROR(assertion) do {if (!(assertion)) {perror("Erreur"); assert(assertion);} } while(0);
#define TRACE_PUML(fmt, ...)
#define TRACE_PUML_START 
#define TRACE_PUML_END

#define LOG_CARTO(fmt, ...)
#define LOG_CONVERTER(fmt, ...)
#define LOG_FOLDER(fmt, ...)
#define LOG_GEOGRAPHER(fmt, ...)
#define LOG_LIDAR(fmt, ...)
#define LOG_NETWORKC(fmt, ...)
#define LOG_UI(fmt, ...)
#define LOG_ACDSOFT(fmt, ...)
#define STOP_ON_ERROR(error_condition)

#endif 

#endif /* UTIL_H */


