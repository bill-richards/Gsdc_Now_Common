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


struct esp_now_network_client_sensor_datagram 
{ 
  NowTransmittedDataTypes transmitted_data = NONE;// Identifies the type of data contained in the datagram
  char sender[SENDER_STRING_LENGTH] = { };        // Identifies the sender of the datagram
};

/**
 * This struct is used to send IMU data from the ESP32 slave to the Master.
 */
struct esp_now_network_client_imu_sensor_datagram // For IMU data transfer
{ 
  NowTransmittedDataTypes transmitted_data = NONE;
  char sender[SENDER_STRING_LENGTH] = { };                          
  float pitch;                                    
  float yaw;                                      
};

/**
 * This struct is used to send GPS data from the ESP32 slave to the Master.
 */
struct esp_now_network_client_gps_sensor_datagram // For GPS data transfer
{ 
  NowTransmittedDataTypes transmitted_data = NONE;
  char sender[SENDER_STRING_LENGTH] = { };                          
  double lattitude;                                 
  double longitude;                               
  double altitude;                                
};

/**
 * ESP_NOW only permits messages of 256k so keeping that in mind
 * the esp_datagram struct is a union of the various possible data
 */
union esp_datagram
{
  esp_now_network_client_sensor_datagram descriptor;  // Access this struct to set sender and data type
  esp_now_network_client_imu_sensor_datagram imu;
  esp_now_network_client_gps_sensor_datagram gps;
};


#endif