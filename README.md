 # Setup
 This is the ESP8266/IR-Receiver/Actuator setup part of the smart-blind project. Make sur you also have setup the RaspberryPi part.
#### HW part
* Wire the circuit as follows:

#### SW part
* Install the required libraries: `ESP8266 libraries, IRremoteESP8266, PubSubClient`.
* Open the __espSmartBlinds.ino__ file with the arduino IDE.
* Change the MQTT broker's IP address in __mqtt.cpp__ to a free address that match your network (the same as the RPi's one).
* Setup the correct compilation and flashing parameters.
* Compile the project and flash the ESP8266.


# Requirements:
The system time shall be up to date.
The system must be connected to the same network as the ESP8266. 


# Misc
#### To compile and upload code without opening the Arduino IDE use the following:
* To compile and upload code on MacOS:
```shell
/Applications/Arduino.app/Contents/MacOS/Arduino --upload /Users/Than/smart-blinds/esp8266/espSmartBlinds.ino
```
* To compile only on Windows:
```shell
C:\Users\Than\arduino-1.8.2-windows\arduino-1.8.2\arduino_debug.exe --verify C:\Users\Than\smart-blinds\esp8266\espSmartBlinds.ino
```

#### To see what's happening on serial use ino and picocom
(Ctrl + A then Ctrl + X to exit picocom)
```shell
ino serial -p /dev/cu.SLAB_USBtoUART -b 9600
```