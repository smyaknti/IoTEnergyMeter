

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "YOUR HOST URL"
#define FIREBASE_AUTH "YOUR DATABASE SECRET"
#define WIFI_SSID "YOUR SSID"
#define WIFI_PASSWORD "YOUR PASSWORD"

float V , A ;  


void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
     
  }

void loop() {

  
 
  Serial.print("pushed: /power");
  if(Serial.available())
    V = Serial.parseFloat();
     delay(1600);
  if(Serial.available())
    A = Serial.parseFloat();
     delay(400);
 firebasePush();
     delay(10000);
    }  
  
 
 void firebasePush()
 {
  // append a new value to /logs
 Firebase.pushFloat("/Power/Amps" , A);
 Firebase.setFloat("/Power/Amp",A);
 Firebase.pushFloat("/Power/Volts" , V);
   Firebase.setFloat("/Power/Volt",V);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /power failed:");
      Serial.println(Firebase.error());  
      return;
  }
  } 




