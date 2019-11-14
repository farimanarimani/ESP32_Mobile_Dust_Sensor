#pragma once
#include "src/lib/SDS011/SDS011.h"
#include "src/lib/Adafruit_Sensor/Adafruit_Sensor.h"
#include "src/lib/Adafruit_BME280_Library/Adafruit_BME280.h"



/* 
 *  Nova SDS011
 */

HardwareSerial SDS_SERIAL(2); // SDS011: use Serial 2: ESP-RX pin:12 (connect to SDS TX), ESP-TX pin:17 (connect to SDS RX) 

SDS011 sds; // sensor object
float pm10, pm25; // sensor results

// read sensor and store results into global variables pm10, pm25
int sdsRead() {
  int error = sds.read(&pm25, &pm10);
  //Log.verbose("!SDS011! read-out success: %d\n", error);
  return error;
}


/*
 * BME280
 */

Adafruit_BME280 bme; // Adafruit_BME280 bme; // BME280 (I2C): ESP-SCL pin:22 (connect to BME-SCK); ESP-SDA pin:21 (connect to BME-SDI).
