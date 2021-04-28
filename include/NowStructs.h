#ifndef _NowStructs_h_
#define _NowStructs_h_

#include "NowTransmittedDataTypes.h"

/**
 * The structure of the transmitted messages
 */
typedef struct inter_network_datagram {
  char sender[16] = { };
  char message[64] = { };
  int readingId;
} inter_gram;


/**
 * This struct is used to send GPS data from the ESP32 slave to the Master.
 */
struct esp_now_network_client_gps_sensor_datagram { 
  char sender[32] = { };                          // Identifies the sender of the datagram
  double lattitude;                               // For GPS data transfer
  double longitude;                               // For GPS data transfer
  double altitude;                                // For GPS data transfer
};

/**
 * This struct is used to send IMU data from the ESP32 slave to the Master.
 */
struct esp_now_network_client_imu_sensor_datagram { 
  char sender[32] = { };                          // Identifies the sender of the datagram
  float pitch;                                    // For IMU data transfer
  float yaw;                                      // For IMU data transfer
};

/**
 * ESP_NOW only permits messages of 256k so keeping that in mind
 * the esp_datagram struct is a union of the various possible data
 */
union esp_datagram
{
  NowTransmittedDataTypes transmitted_data = NONE;// Identifies the type of data contained in the datagram
  esp_now_network_client_gps_sensor_datagram gps;
  esp_now_network_client_imu_sensor_datagram imu;
};


#endif