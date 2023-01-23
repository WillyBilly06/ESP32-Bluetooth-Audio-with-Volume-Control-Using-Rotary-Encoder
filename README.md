# ESP32-Bluetooth-Audio-with-Volume-Control-Using-Rotary-Encoder
So I was just messing around with Phil Schatzmann's library and using Rotary Encoder which I accidently create a bluetooth device using Rotary Encoder to control the volume. The device's volume will also update when we rotate the Rotary Encoder.

Also when the device is inactive for 5 minutes, it will go to deep sleep mode and to wake up the module, we need to pulldown PIN 15 of ESP32 to GND.
| PCM5102A  | ESP32 |
| ------ |         ----------------|
| LCK | GPIO 25  |
| DIN | GPIO 26 |
| BCK | GPIO 27  |
| GND | GND|
| VIN | 3V3|
