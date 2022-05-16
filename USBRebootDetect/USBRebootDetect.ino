/*

A USB initialise/re-initialise detector... for such things as detecting reboots when using Keyboard.h, and Mouse.h

This demo shows the initialise callback used to send the Bitlocker password through to a warm rebooted Windows PC.

To note though - The warm re-boot directly AFTER the Bitlocker warm boot triggers the password entry timer again which will enter the text on the Windows login prompt, so a nice to have would be to send the password on EVERY-OTHER warm boot. I've not done this to keep the example very simple.


  Structure of USB system:

  Keyboard / Mouse
  	HID
  		PluggableUSB
  			USBAPI
  				USBDesc
  				USBCore

*/

#define _BitLockerPassword "Bitlocker Password Here"
#define _SecondsDelay 20
#define _PinForRebootIndicator 13

#include "Keyboard.h"

int tickTop = _SecondsDelay * 10;
int tick = 0;
bool hasRebooted = false;

void USBInitEndpointCallback() {
  analogWrite(_PinForRebootIndicator, 255);
  hasRebooted = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(_PinForRebootIndicator, OUTPUT);
  analogWrite(_PinForRebootIndicator, 0);
  Keyboard.begin(&USBInitEndpointCallback);
}

void loop() {
  if (hasRebooted) {
    if (++tick >= tickTop) {
      Keyboard.println(_BitLockerPassword);
      tick = 0;
      hasRebooted = false;
      analogWrite(_PinForRebootIndicator, 0);
    }
  }
  delay(100);
}
