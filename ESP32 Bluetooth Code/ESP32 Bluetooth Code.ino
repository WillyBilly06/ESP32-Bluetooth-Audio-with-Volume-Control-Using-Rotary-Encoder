/*
MIT License

Copyright (c) 2023 BillyDaKidz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;
#define I2S_PORT I2S_NUM_0

#define CLK 13
#define DT 12
#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // pin number is specific to your esp32 board
#endif

int counter = 0;
int currentStateCLK;
int lastStateCLK;

esp_a2d_connection_state_t last_state;
uint16_t minutes = 5; //countdown time
unsigned long shutdown_ms = millis() + 1000 * 60 * minutes;

// for esp_a2d_audio_state_t see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_a2dp.html#_CPPv421esp_a2d_audio_state_t
void audio_state_changed(esp_a2d_audio_state_t state, void *ptr){
  Serial.println(a2dp_sink.to_str(state));
}



 int volume = 0;
 void volumeChanged(int newVolume) {
    Serial.println(newVolume);
    volume = newVolume;
}

void on_data() {
  shutdown_ms = millis() + 1000 * 60 * minutes; 
}


void setup() {
  Serial.begin(115200);

  i2s_install(); // install i2s profile
  i2s_pin(); // set i2s output pin
  i2s_start(I2S_PORT); //initialize i2s
  
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,0); //1 = High, 0 = Low (Deep sleep wake up pin)

  a2dp_sink.set_on_data_received(on_data);
  a2dp_sink.set_on_volumechange(volumeChanged);
  a2dp_sink.set_on_audio_state_changed(audio_state_changed);
  a2dp_sink.start("BDK Speaker"); // name of the device
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  lastStateCLK = digitalRead(CLK);
}




void i2s_install()
{
      static i2s_config_t i2s_config = {
      .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = 44100, // updated automatically by A2DP
      .bits_per_sample = (i2s_bits_per_sample_t)32,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = (i2s_comm_format_t) (I2S_COMM_FORMAT_STAND_I2S),
      .intr_alloc_flags = 0, // default interrupt priority
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = true,
      .tx_desc_auto_clear = true // avoiding noise in case of data unavailability
      };
        i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

}

void i2s_pin()
{
  i2s_pin_config_t my_pin_config = {
        .bck_io_num = 26,
        .ws_io_num = 25,
        .data_out_num = 14,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
  i2s_set_pin(I2S_PORT, &my_pin_config);
}

void loop() {

  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);
  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter -=13;
      if (counter<0)
        counter=0;
    } else {
      // Encoder is rotating CW so increment
      counter +=13;
      if (counter>127)
        counter=127;
    }
a2dp_sink.set_volume(counter);  } // 127 for max volume, 0 to mute
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
  
  // check timeout
  if (millis()>shutdown_ms){
    // stop the processor
    Serial.println("Shutting down");
    esp_deep_sleep_start();
  }
  // check state
  esp_a2d_connection_state_t state = a2dp_sink.get_connection_state();
  if (last_state != state){
    bool is_connected = state == ESP_A2D_CONNECTION_STATE_CONNECTED; // reading connection state of the device
    Serial.println(is_connected ? "Connected" : "Not connected");    
    digitalWrite(LED_BUILTIN, is_connected);
    last_state = state;
  }
  delay(1000);

}
