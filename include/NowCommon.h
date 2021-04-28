#ifndef _Gsdc_NowCommon_h_
#define _Gsdc_NowCommon_h_

#include <NonVolatileMemory.h>
#include <SPIFFS.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <WiFi.h>

#include "NowStructs.h"


/**
 * The DataMarkers are used to identify which 'slots' need to be read 
 * from the external EEPROM, for the specific data.
 */
const DataMarkers SSID_MARKER = DataMarkers::DLE;
const DataMarkers REMOTE_SSID_MARKER = DataMarkers::ENQ;
const DataMarkers PASSWORD_MARKER = DataMarkers::ETX;
const DataMarkers REMOTE_PASSWORD_MARKER = DataMarkers::FF;
const DataMarkers SERVER_MAC_ADDRESS_MARKER = DataMarkers::SI;
const DataMarkers REMOTE_SERVER_MAC_ADDRESS_MARKER = DataMarkers::SO;

const uint8_t local_broadcastAddress[]  = { 0x7C, 0x9E, 0xBD, 0xF9, 0xB5, 0xFC }; // Local AP
const uint8_t remote_broadcastAddress[] = { 0xab, 0xbc, 0xcd, 0xdc, 0xcb, 0xba };

inline int32_t getWiFiChannel(const char *ssid) 
{ 
  if (int32_t n = WiFi.scanNetworks()) 
  { 
      for (uint8_t i=0; i<n; i++) 
      {
        if (!strcmp(ssid, WiFi.SSID(i).c_str())) { return WiFi.channel(i); } 
      }
  } 
  return 0; 
}

#define DEFAULT_NVM() \
  NonVolatileMemory _nonValatileMemory(0x50);

#define NVM(i2c_address) \
  NonVolatileMemory _nonValatileMemory(i2c_address);

#define READ_CREDENTIALS_FROM_EEPROM_AND_CONNECT_TO_WIFI_AS_A_STATION() \
  _nonValatileMemory.readEEPROM(); \
  delay(5); \
  CALL_AND_WAIT_100_MILLIS(_display.flashHeading("STARTUP")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(MIDDLE, "Reading NVM")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "5")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "4")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "3")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "2")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "1")); \
  while(!WiFi.mode(WIFI_STA)) \
  { \
      CALL_AND_WAIT_100_MILLIS(_display.important("Wifi Mode fail")); \
  } \
  CALL_AND_WAIT_100_MILLIS(_display.important("Configured")); \
  _display.scrubLine(MIDDLE); 

#define READ_CREDENTIALS_FROM_EEPROM_AND_CONNECT_TO_WIFI_AS_ACCESSPOINT() \
  _nonValatileMemory.readEEPROM(); \
  delay(5); \
  CALL_AND_WAIT_100_MILLIS(_display.flashHeading("STARTUP")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(MIDDLE, "Reading NVM")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "5")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "4")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "3")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "2")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "1")); \
  CALL_AND_WAIT_100_MILLIS(_display.important("Network Config")); \
  _display.scrubLine(MIDDLE); \
  String ssid = _nonValatileMemory.read(SSID_MARKER); \
  String password = _nonValatileMemory.read(PASSWORD_MARKER); \
  CALL_AND_WAIT_100_MILLIS(_display.center(MIDDLE, "Starting Wifi")); \
  while(!WiFi.mode(WIFI_AP)) \
  { \
      CALL_AND_WAIT_100_MILLIS(_display.flashCenter(MIDDLE,"Wifi Mode fail")); \
  } \
  while(!WiFi.softAP(ssid.c_str(), password.c_str())) \
  { \
    CALL_AND_WAIT_100_MILLIS(_display.flashCenter(MIDDLE,"Access Point fail")); \
  } \
  CALL_AND_WAIT_100_MILLIS(_display.important("Configured")); \
  _display.scrubLine(MIDDLE); 

#define READ_CREDENTIALS_FROM_EEPROM_AND_CONNECT_TO_WIFI_AS_ACCESSPOINT_AND_REMOTE_STATION() \
  _nonValatileMemory.readEEPROM(); \
  delay(5); \
  CALL_AND_WAIT_100_MILLIS(_display.flashHeading("STARTUP")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(MIDDLE, "Reading NVM")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "5")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "4")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "3")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "2")); \
  CALL_AND_WAIT_100_MILLIS(_display.center(BOTTOM, "1")); \
  CALL_AND_WAIT_100_MILLIS(_display.important("Network Config")); \
  _display.scrubLine(MIDDLE); \
  String ssid = _nonValatileMemory.read(SSID_MARKER); \
  String password = _nonValatileMemory.read(PASSWORD_MARKER); \
  CALL_AND_WAIT_100_MILLIS(_display.center(MIDDLE, "Starting Wifi")); \
  while(!WiFi.mode(WIFI_AP_STA)) \
  { \
      CALL_AND_WAIT_100_MILLIS(_display.flashCenter(MIDDLE,"Wifi Mode fail")); \
  } \
  while(!WiFi.softAP(ssid.c_str(), password.c_str())) \
  { \
    CALL_AND_WAIT_100_MILLIS(_display.flashCenter(MIDDLE,"Access Point fail")); \
  } \
  String remote_ssid = _nonValatileMemory.read(REMOTE_SSID_MARKER); \
  String remote_password = _nonValatileMemory.read(REMOTE_PASSWORD_MARKER); \
  int32_t channel = getWiFiChannel(ssid.c_str()); \
  esp_wifi_set_promiscuous(true); \
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE); \
  esp_wifi_set_promiscuous(false); \
  CALL_AND_WAIT_100_MILLIS(_display.important("Configured")); \
  _display.scrubLine(MIDDLE); 

#define READ_VALUE_FROM_EEPROM(data_marker) \
  _nonValatileMemory.read(data_marker);

#define SERVER_MAC_ADDRESS_STRING() \
  READ_VALUE_FROM_EEPROM(SERVER_MAC_ADDRESS_MARKER);

#define INITIALIZE_THE_LOCAL_FILE_SYSTEM() \
  Serial.println("Preparing the file system.."); \
  if(!SPIFFS.begin(true)){ \
    Serial.println("An Error has occurred while mounting SPIFFS"); \
    return; \
  } 

#define INITIALIZE_ESP_NOW() \
    Serial.println("Initializing ESP_NOW communications.."); \
    if (esp_now_init() != ESP_OK) { \
        Serial.println("Error initializing ESP-NOW"); \
        return; \
    } 

#define REGISTER_SEND_HANDLER(handler) \
    esp_now_register_send_cb(handler);

#define INITIALIZE_ESP_NOW_AND_REGISTER_SEND_HANDLER(handler) \
    INITIALIZE_ESP_NOW() \
    REGISTER_SEND_HANDLER(handler);

#define INITIALIZE_ESP_NOW_AND_REGISTER_RECEIVED_HANDLER(handler) \
    INITIALIZE_ESP_NOW() \
    esp_now_register_recv_cb(handler);

#define REGISTER_ROUTE(route, verb, spiffs_file, content_type) \
  server.on(route, verb, [](AsyncWebServerRequest *request){ \
    request->send(SPIFFS, spiffs_file, content_type, false); \
  });

#define CREATE_WEB_SERVER_AND_REGISTER_EVENT_SOURCE(port, event_source_name) \
  AsyncWebServer server(port); \
  AsyncEventSource events(event_source_name);

#define REGISTER_ESP_NOW_PEER(broadcast_address) \
  esp_now_peer_info_t peerInfo; \
  memcpy(peerInfo.peer_addr, broadcast_address, 6); \
  peerInfo.encrypt = false; \
  if (esp_now_add_peer(&peerInfo) != ESP_OK){ \
    Serial.println("Failed to add peer "); \
    return; \
  } 

#define SEND_MESSAGE_USING_ESP_NOW(address, message) \
    Serial.printf("SENDING TO %s\n\r", _serverMacAddress.c_str()); \
    esp_err_t result = esp_now_send(address, (uint8_t *) &message, sizeof(message)); \
    if (result == ESP_OK) \
    { \
      Serial.println("Sent"); \
    } \
    else if(result == ESP_ERR_ESPNOW_ARG) \
    { \
      Serial.println("Damn mac address  didn't work"); \
    } \
    else if(result == ESP_ERR_ESPNOW_NOT_FOUND) \
    { \
      Serial.println("Peer not found"); \
    } \
    else \
    { \
        Serial.println("failed"); \
    }

#define PREPARE_DATAGRAM(transmitted_data_type, board_identifier) \
  _datagram.header.transmitted_data = transmitted_data_type; \
  memcpy(&_datagram.header.sender, board_identifier, SENDER_STRING_LENGTH);
    
#endif