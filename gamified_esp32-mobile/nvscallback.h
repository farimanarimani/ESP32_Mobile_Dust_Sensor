#pragma once
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEDescriptor.h>
#include <Preferences.h>
#include "src/lib/ArduinoJson/ArduinoJson.h"

/*
   Callback functions for storing values in nvs
*/
/*
    nvs callback (nvsCallback)
    manage what happens on read or write
    writes data received over BLE to the non-volatile storage
    received data has to be in JSON format
    functions:
    set_value: sets key-value pair in nvs
    get_value: gets key-value pair in nvs
    onRead: calls get_value() when a "read" operation is done via BLE device
    onWrite: calls set_value() when a "write" operation is done via BLE device


*/

Preferences preferences;



// nvs callback
class nvsCallback: public BLECharacteristicCallbacks {
    const char *key;
    void set_value(const char used_namespace[14], const char key_nvs[14], const String value) {
      // Open Preferences with my-app namespace.
      // RW-mode if second parameter is false
      preferences.begin(used_namespace, false);
      preferences.putString(key_nvs, value);
      // Close the Preferences
      preferences.end();
    }

    String get_value(const char used_namespace[14], const char key_nvs[14]) {
      // Open Preferences with my-app namespace.
      // RW-mode if second parameter is false
      preferences.begin(used_namespace, true);
      // get value of key, assume value is String
      // if key does not exist, return a default value
      String default_value = "unknown_key";
      String tmp = preferences.getString(key_nvs, default_value);
      // Close the Preferences
      preferences.end();
      return tmp;
    }

    void onRead(BLECharacteristic *pCharacteristic) {
      // define namespace of nvs
      const char used_namespace[14] = "sds011";

      // define all possible keys
      String sensor = get_value(used_namespace, "sensor");
      String time = get_value(used_namespace, "time");
      String latitude = get_value(used_namespace, "latitude");
      String longitude = get_value(used_namespace, "longitude");

      // create Json buffer. inside brackets: size of the pool in bytes.
      // Use arduinojson.org/assistant to compute the capacity.
      StaticJsonBuffer<1024> jsonBuffer; //TODO set a good buffer size
      // create json object
      JsonObject& root_create = jsonBuffer.createObject();
      // add all key-value pairs to json object
      root_create["sensor"] = sensor;
      root_create["time"] = time;
      root_create["latitude"] = latitude;
      root_create["longitude"] = longitude;
      char root_create_char[1024]; //TODO set maximum size of char here
      // create a char out of the json object
      root_create.printTo(root_create_char);
      pCharacteristic->setValue(root_create_char);
    }

    void onWrite(BLECharacteristic *pCharacteristic) {
      const char used_namespace[14] = "sds011";
      // get value of user input
      std::string value = pCharacteristic->getValue();
      // convert std::string to char array
      const char *value_char = value.c_str();
      if (value.length() > 0) {
        // create Json buffer. inside brackets: size of the pool in bytes.
        // Use arduinojson.org/assistant to compute the capacity.Jsonbuffer
        StaticJsonBuffer<1024> jsonBuffer; //TODO set a good buffer size
        // parse Json object from user input
        JsonObject& root_parse = jsonBuffer.parseObject(value_char);
        // Test if parsing succeeds.
        if (!root_parse.success()) {
          Serial.println("parseObject() failed, root");
          return;
        }
        const char* sensor = root_parse["sensor"];
        const char* time = root_parse["time"];
        const char* latitude = root_parse["data"][0];
        const char* longitude = root_parse["data"][1];

        set_value(used_namespace, "sensor", sensor);
        set_value(used_namespace, "time", time);
        set_value(used_namespace, "latitude", latitude);
        set_value(used_namespace, "longitude", longitude);


      }
    }

  public:
    //contructor
    nvsCallback(const char *pkey)
    {
      key = pkey;
    }
};
