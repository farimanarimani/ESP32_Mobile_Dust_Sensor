#pragma once


/*
   watchdog callback:
   resets the hardware timer if a "read" action over ble is done
*/
// watchdog switch. true for enable, false for disable
bool enable_wd = false;

const int wdtTimeout = 120000;  //time in ms to trigger the watchdog



hw_timer_t *timer = NULL; // initialise hardware timer

// reboot esp
void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}



// manage what happens on read of watchdog charactericstic
// reset hardware timer on read of watchdog characteristic
class watchdogCallback: public BLECharacteristicCallbacks {


    void onRead(BLECharacteristic *pCharacteristic) {
      if (enable_wd==true){
        timerWrite(timer, 0);

      }
    }
};
