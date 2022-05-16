# Arduino Leonardo: Bitlocker Auto Login
The sketch detects a USB initialise call from the host machine, and sets a countdown before typing and entering a string via the Leonardo acting as a keyboard.

In effect it will wait for the PC to reboot, wait for a minute, and then type in the text supplied in the INO sketch. Such as Windows login details, or the BitLocker password for rebooting a machine remotely. I've seen the question asked on the forums. =) 

This little sketch implements a callback functionality I added into the Leonardo USB library to detect when the Leonardo is being enumerated - such as when the device is first plugged in and with a warm-boot. All the required files are included.

I'm betting there's a unique warm-boot type message sent, which would be better than the current solution, as plugging in the Leonardo starts the countdown to entering the text.
I've kept the sketch very simple - and it shouldn't be too hard to write it so it skips the first USB init received.

https://forum.arduino.cc/t/arduino-leonardo-how-to-decipher-the-signals-the-pc-sends-on-a-soft-reboot/678726

https://forum.arduino.cc/t/detect-when-a-pc-reboots/480727/2

