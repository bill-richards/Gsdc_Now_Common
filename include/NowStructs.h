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
 * This struct is used to send data from the ESP32
 * slaves to the Master.
 * 
 * ESP_NOW only permits messages of 256k so keep that in mind
 */
typedef struct esp_now_network_client_sensor_datagram { 
  NowTransmittedDataTypes containedData = GPS;  // Identifies the type of data contained in the datagram
  char sender[16] = { };                        // Identifies the sender of the datagram
  double lattitude;                             // For GPS data transfer
  double longitude;                             // For GPS data transfer
  double altitude;                              // For GPS data transfer
} esp_datagram;


#endif