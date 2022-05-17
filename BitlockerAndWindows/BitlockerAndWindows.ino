/*

  A USB initialise/re-initialise detector... for such things as detecting reboots when using Keyboard.h, and Mouse.h

  This demo shows the initialise callback used to send the Bitlocker password through to a warm rebooted Windows PC, followed a short time later by the Windows login.
  
  When triggered, the onboard LED will light up until after the Bitlocker and Windows psasword has been enetered. Then it will go dark until a warm reboot is sensed.
  
  A new feature has been added - Reset the trigger.
  Touching pin 9 (it normally works just floating, without connecting up a proper switch and resistor) will flicker the onboard LED for a couple of seconds and reset the reboot trigger. It's useful for plugging the device into a booted PC, as that also triggers the boot password entry sequence!

  Structure of USB system:

  Keyboard / Mouse
  	HID
  		PluggableUSB
  			USBAPI
  				USBDesc
  				USBCore

*/

#define _PasswordBitLocker "BTLOCKER PASSWORD HERE"
#define _PasswordWindows "WINDOWS PASSWORD HERE"
#define _SecondsDelayToBitlocker 10
#define _SecondsDelayToWindowsLogin 14

#define _PinForRebootIndicator 13
#define _PinForResetRebootTrigger 9

#include "Keyboard.h"

int tickTrigger1 = _SecondsDelayToBitlocker * 10;
int tickTrigger2 = tickTrigger1 + (_SecondsDelayToWindowsLogin * 15);
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
  pinMode(_PinForResetRebootTrigger, INPUT);
  Keyboard.begin(&USBInitEndpointCallback);
}

void resetRebootCountdown() {
  tick = 0;
  hasRebooted = false;
}

void flickerLED() {
  for (int i = 0; i < 30; i++) {
    analogWrite(_PinForRebootIndicator, 255);
    delay(25);
    analogWrite(_PinForRebootIndicator, 0);
    delay(25);
  }
}

void loop() {
  if (digitalRead(_PinForResetRebootTrigger)) {
    flickerLED();
    resetRebootCountdown();
    return;
  }

  if (hasRebooted) {
    tick++;
    // Bitlocker password
    if (tick == tickTrigger1) {
      Keyboard.println(_PasswordBitLocker);
    }

    // Windows password
    if (tick == tickTrigger2) {
      Keyboard.println("");
      delay(200);
      Keyboard.println("");
      delay(500);
      
      Keyboard.println(_PasswordWindows);
      analogWrite(_PinForRebootIndicator, 0);
      tick = 0;
      hasRebooted = false;
    }
  }

  delay(100);
}