#pragma once
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEDescriptor.h>


/*
   BLE

*/
// use uuidgenerator:  www.uuidgenerator.net/
// service UUID
#define DUST_SERVICE_UUID "6e57fcf9-8064-4995-a3a8-e5ca44552192"
#define METADATA_SERVICE_UUID "aec37142-b2a4-4f05-a8b3-bf4602267641"

// define characterstic uuids, generator was used (UUIDv4)
#define METADATA_CHARACTERISTIC_UUID "0933fb51-155f-4f17-98c6-3a9663f51a3c"
#define DATA_CHARACTERISTIC_UUID "3525d870-6549-490a-bcc8-576cd6afde8a"
#define DATADESCRIPTION_CHARACTERISTIC_UUID "aa1c2b71-e510-41bb-96b2-7129cf59f260"
#define NOTIFY_CHARACTERISTIC_UUID "7a812f99-06fa-4d89-819d-98e9aafbd4ef"
#define BUTTINNOTIFY_CHARACTERISTIC_UUID "2b2d5a29-eec8-4155-8261-2d75774aab49" 
#define SENSORPM_UNIT "ug/m3"
#define DEVICE_NAME "TECO-PM-Duster_1"

// inital definitons
BLEServer *pServer = nullptr;
BLEService *pDustService = nullptr;
BLEService *pMetadataService = nullptr;
BLECharacteristic *pMetadataCharacteristic = nullptr;
BLECharacteristic *pDataCharacteristic = nullptr;
BLECharacteristic *pButtonCharacteristic = nullptr;
BLECharacteristic *pDataDescriptionCharacteristic = nullptr;
BLECharacteristic *pNotifyCharacteristic = nullptr;
BLEDescriptor *pDataDescriptor = nullptr;
BLE2902 *pNotifyDescriptor2902 = nullptr;
BLEAdvertising *pAdvertising = nullptr;
