#ifndef _NowStructs_h_
#define _NowStructs_h_

#include "NowTransmittedDataTypes.h"

#define SENDER_STRING_LENGTH 32

/**
 * The structure of the transmitted messages
 */
typedef struct inter_network_datagram {
  char sender[SENDER_STRING_LENGTH] = { };
  char message[64] = { };
  int readingId;
} inter_gram;

/**
 * This struct is used to send data from the ESP32 slave to the Master.
 */
typedef struct esp_now_network_client_sensor_datagram_ 
{ 
  struct
  {
    NowTransmittedDataTypes transmitted_data = NONE;
    char sender[SENDER_STRING_LENGTH] = { };
  } header;           // Describes the type of data contained and the sender

  union
  {
    struct            // For IMU data transfer
    {
      float pitch;
      float roll;
    } imu;

    struct            // For GPS data transfer
    {
      double longitude;                               
      double latitude;                                 
      double altitude;                                
    } gps;
  };
  
} esp_datagram;

#endif