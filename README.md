# ESP32 Bluetooth Audio with Volume Control Using Rotary-Encoder
I was messing around with Phil Schatzmann's library and how to use a Rotary Encoder, and then I accidentally created a Bluetooth device using a Rotary Encoder to control the volume. The device's volume will also update when the Rotary Encoder is being rotated.

In addition, when the device is inactive for 1 minute (changeable), it will enter "deep sleep" mode. In order to wake up the module, you need to connect PIN 15 of ESP32 with GND via the pull-down resistor. You can modify the auto shutdown time by changing the value of minutes in the code. 

Updated: It works on Android, IOS, and Samsung Watch (Wear OS, but not sure about Tizen OS). 

The built-in LED of the board will be lit up when your phone is connected to Bluetooth. Also, when you change the volume, the LED on WS2812B will also lit up depending on the volume of the device, and the number of LEDs that will illuminate is 10 (you can change the number of LEDs depending on your project)

# PCM5102A
Here is the information on how to wire the PCM5102A module to the ESP32:
| PCM5102A  | ESP32 |
|------|----------------|
| LCK | GPIO 25 |
| DIN | GPIO 14 |
| BCK | GPIO 26 |
| SCK | GND |
| GND | GND |
| VIN | 3V3 OR 5V (VIN)|

<img src="https://user-images.githubusercontent.com/72125448/213976186-991fbb73-26de-42e9-9aea-8901ce2a2613.jpg" width=45% height=45%>

# Rotary Encoder
Here is the information on how to wire the Rotary Encoder to the ESP32:
| Rotary Encoder  | ESP32 |
| ------ | ----------------|
| CLK | GPIO 33 |
| DT | GPIO 32 |
| GND | GND |
| VIN | 5V (VIN) |

<img src="https://user-images.githubusercontent.com/72125448/213977013-4a5b1336-3c5c-4319-94e6-383daaa219d4.jpg" width=45% height=45%>

# WS2812B Led Strip
Here is the information on how to wire the WS2812B Led Strip to the ESP32:
| WS2812B | ESP32 |
|------|----------------|
| V+ | VIN (5V) or 3.3V |
| Data In | GPIO 18 |
| GND | GND |

| WS2812B  | ESP32 |
| ------ | ----------------|
| Data In | GPIO 18 |
| V+ | VIN (5V) or 3.3V |
| GND | GND |

<img src="https://user-images.githubusercontent.com/72125448/217063951-24d0d14b-80ca-4c57-81b6-0bb9044d79c7.jpg" width=45% height=45%>

# Library Requirements
https://github.com/pschatzmann/ESP32-A2DP <br />
https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation
# LICENSE
MIT LICENSED
