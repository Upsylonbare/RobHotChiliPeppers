#include <cstddef>
#include "../../libs/lidar-x86_64/sdk/include/rplidar.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <math.h>

#define RAW_DATA_FILE "lidar_output/position_gtk.txt"

/*
FonctionsCpp.h
*/
 
/* Définition de la macro EXTERN_C pour C ou C++ */
#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif
 
/* Ces fonctions sont accessibles en C et en C++, car:
 Le linker C croira que ce sont des fonctions C et il aura presque raison,
 Le linker C++ saura que leurs définitions sont en extern "C" */

/* Ces fonctions ne seront pas accessibles en C, 
   car le linker croira, à tort, que ce sont des fonctions C. */

using namespace rp::standalone::rplidar;
using namespace std;

bool checkRPLIDARHealth(RPlidarDriver * drv);
void delay(_word_size_t ms);
u_result displayValue(RPlidarDriver * drv);
void fichier_close(void);
void fichier_open(void);
 
/* Ces fonctions ne doivent être accessibles qu'en C++,
   car elles seraient inutilisables en C et leur déclaration seule 
   causerait une erreur de compilation */
#ifdef __cplusplus


#endif
