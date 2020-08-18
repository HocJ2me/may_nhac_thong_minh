
#include <Arduino.h>
#include <ArduinoJson.h>
#include <string.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <ESP8266HTTPClient.h>
#include <FS.h>
#include <LittleFS.h>
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"
#include "config.h"
#include "wifi_config.h"
#include "play_mp3.h"
#include "time_config.h"


void setup() {
   pinMode(  output, OUTPUT);  // # pin bật âm thanh
   pinMode(  A0, INPUT);  // # pin thu cảm biến thanh
   Serial.begin(115200); //Khởi tạo baud 115200
   Serial.println();   
    if (!SPIFFS.begin()) {
      Serial.println("SPIFFS mount failed");
      return;
  }
  
   smart_config();
}

void loop() {
  
   server.handleClient();

   if (WiFi.status() == WL_CONNECTED)
   {
       if (connect_time == 0)
       {
           setClock();
           update_json();
           update_mp3();
           connect_time = 1;
           last_time = millis();
       }
        if (millis() - last_time > 15*1000)
        {
            update_json();
        }
          if (millis() - last_time > 15*1000)
          {
            update_time();      
            last_time = millis();
         }
          if (millis() - last_update > 60*60*1000)
          {
            update_mp3();      
            last_update = millis();
         }
         int sensor = analogRead(A0);
           if ((sensor>30)&&(sensor<1000))
                if(!playing_audio)
                {
                  play_audio();
                }
         if (playing_audio) audio_running();
   }
}
