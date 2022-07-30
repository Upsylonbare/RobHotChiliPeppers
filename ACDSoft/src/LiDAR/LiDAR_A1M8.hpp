
/* Définition de la macro EXTERN_C pour C ou C++ */
#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

#define RAW_DATA_FILE "lidar_output/position_gtk.txt"

EXTERN_C void LiDAR_A1M8_launchScan(void);

#ifdef __cplusplus
 
#endif