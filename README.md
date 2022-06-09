# Arduino Leonardo: Bitlocker Auto Login
The sketch detects a USB initialise call from the host machine, and sets a countdown before typing and entering a string via the Leonardo acting as a keyboard.

In effect it will wait for the PC to reboot, wait for a minute, and then type in the text supplied in the INO sketch. Such as Windows login details, or the BitLocker password for rebooting a machine remotely. I've seen the question asked on the forums. =) 

This little sketch implements a callback functionality I added into the Leonardo USB library to detect when the Leonardo is being enumerated - such as when the device is first plugged in and with a warm-boot. All the required files are included.

I'm betting there's a unique warm-boot type message sent, which would be better than the current solution, as plugging in the Leonardo starts the countdown to entering the text.
I've kept the sketch very simple - and it shouldn't be too hard to write it so it skips the first USB init received.

Demo on Youtube:            
https://www.youtube.com/watch?v=h_g4F5-BUzY

The forum questions:                 
https://forum.arduino.cc/t/arduino-leonardo-how-to-decipher-the-signals-the-pc-sends-on-a-soft-reboot/678726

https://forum.arduino.cc/t/detect-when-a-pc-reboots/480727/2


Example of an Leonardo on a USB key:             
![image](https://user-images.githubusercontent.com/1586332/172832360-74f80115-60de-4ee8-848b-02f241951935.png)


The normal sized Leonardo is a bit cumbersome for this use-case:                 
![image](https://user-images.githubusercontent.com/1586332/172832862-b2bdcfad-18e5-41fa-975e-ef2a7127d0c6.png)
