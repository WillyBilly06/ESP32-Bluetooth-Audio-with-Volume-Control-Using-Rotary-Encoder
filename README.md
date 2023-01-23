# ESP32-Bluetooth-Audio-with-Volume-Control-Using-Rotary-Encoder
So I was just messing around with Phil Schatzmann's library and using Rotary Encoder which I accidently create a bluetooth device using Rotary Encoder to control the volume. The device's volume will also update when we rotate the Rotary Encoder.

Also when the device is inactive for 5 minutes, it will go to deep sleep mode and to wake up the module, we need to pulldown PIN 15 of ESP32 to GND. You can change the auto shutdown time by changing the value of minutes in the code. 

The built-in led of the board will be lit up when your phone is connected to the bluetooth.

# PCM5102A
Here is the information of how to wire the PCM5102A module to the ESP32
| PCM5102A  | ESP32 |
|------|----------------|
| LCK | GPIO 25 |
| DIN | GPIO 14 |
| BCK | GPIO 26 |
| SCK | GND |
| GND | GND |
| VIN | 3V3 OR 5V (VIN)|

<img src="https://user-images.githubusercontent.com/72125448/213976186-991fbb73-26de-42e9-9aea-8901ce2a2613.jpg" width=50% height=50%>

# Rotary Encoder
Here is the information of how to wire the Rotary Encoder to the ESP32
| Rotary Encoder  | ESP32 |
| ------ | ----------------|
| CLK | GPIO 13 |
| DT | GPIO 12 |
| GND | GND |
| VIN | 5V (VIN) |

<img src="https://user-images.githubusercontent.com/72125448/213977013-4a5b1336-3c5c-4319-94e6-383daaa219d4.jpg" width=45% height=45%>

# Library Requirement
https://github.com/pschatzmann/ESP32-A2DP
# LICENSE
MIT LICENSED
