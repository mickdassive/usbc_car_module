//{usbc car module}
//{adc.cpp}
//Copyright (C) {2023}  {mickmake}
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//usbc car module
//15/09/2023
//Tokyo Andreana

#ifndef adc_cpp
#define adc_cpp

#include <Arduino.h>
#include <Wire.h>
#include "adc.h"


/**
 * @brief Performs self calibration for the ADC module.
 * 
 * This function starts a self calibration process for the ADC module. It reads the current configuration state
 * of the ADC, sets the self calibration bit, and writes the updated configuration back to the ADC. Then, it continuously
 * checks the self calibration bit until it is cleared, indicating that the calibration process is complete.
 * 
 */
void adc_self_cal () {
  // Local variables
  bool cal_complete = false;
  uint8_t self_cal_mask = 0b0000010;
  uint8_t current_gen_config_state = 0b0;

  // Read current config register state
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);
  Wire.write(adc_gen_config);
  Wire.endTransmission();

  // Begin read
  Wire.requestFrom(adc_add, 1);
  current_gen_config_state = Wire.read();
  Wire.endTransmission();

  // Bitwise OR current state with self cal mask
  current_gen_config_state |= self_cal_mask;

  // Write to gen config register to start a self cal
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_gen_config);
  Wire.write(current_gen_config_state);
  Wire.endTransmission();

  // Set current state to 0 so it can be reused later
  current_gen_config_state = 0b0;

  // Begin checking if the self cal is complete
  while (!cal_complete) {
    // Read current self cal bit state
    Wire.beginTransmission(adc_add);
    Wire.write(adc_op_single_read);
    Wire.write(adc_gen_config);
    Wire.endTransmission();

    // Begin read
    Wire.requestFrom(adc_add, 1);
    current_gen_config_state = Wire.read();
    Wire.endTransmission();

    // Bitwise AND the current self cal bit with the self cal mask
    current_gen_config_state &= self_cal_mask;

    if (current_gen_config_state == 0) {
      cal_complete = true;
    }
  }
  return;
}

/**
 * @brief Initializes the ADC module with the specified configuration.
 * 
 * This function initializes the ADC module by configuring various parameters such as
 * hysteresis, thresholds, event counts, and pin modes. It also performs self-calibration
 * and sets up oversampling, mode, clock, sequence, and alert channel configurations.
 * 
 * @param fast_mode Flag indicating whether to enable fast mode or not.
 *                  If set to true, the ADC will operate in i2c fast mode with a higher clock speed for sending config information.
 *                  If set to false, the ADC will operate in i2c normal mode with a lower clock speed for sending config information.
 * 
 */
void adc_init(bool fast_mode) {
  // Initialize local variables
  uint8_t ch0_hysteresis = 0b0;
  uint8_t ch0_high_threshold = 0b0;
  uint8_t ch0_event_count = 0b0;
  uint8_t ch0_low_threshold = 0b0;
  uint8_t ch1_hysteresis = 0b0;
  uint8_t ch1_high_threshold = 0b0;
  uint8_t ch1_event_count = 0b0;
  uint8_t ch1_low_threshold = 0b0;
  uint8_t ch2_hysteresis = 0b0;
  uint8_t ch2_high_threshold = 0b0;
  uint8_t ch2_event_count = 0b0;
  uint8_t ch2_low_threshold = 0b0;
  uint8_t ch3_hysteresis = 0b0;
  uint8_t ch3_high_threshold = 0b0;
  uint8_t ch3_event_count = 0b0;
  uint8_t ch3_low_threshold = 0b0;
  uint8_t ch4_hysteresis = 0b0;
  uint8_t ch4_high_threshold = 0b0;
  uint8_t ch4_event_count = 0b0;
  uint8_t ch4_low_threshold = 0b0;
  uint8_t ch5_hysteresis = 0b0;
  uint8_t ch5_high_threshold = 0b0;
  uint8_t ch5_event_count = 0b0;
  uint8_t ch5_low_threshold = 0b0;
  uint8_t ch6_hysteresis = 0b0;
  uint8_t ch6_high_threshold = 0b0;
  uint8_t ch6_event_count = 0b0;
  uint8_t ch6_low_threshold = 0b0;
  uint8_t ch7_hysteresis = 0b0;
  uint8_t ch7_high_threshold = 0b0;
  uint8_t ch7_event_count = 0b0;
  uint8_t ch7_low_threshold = 0b0;

  // Broadcast on I2C bus for ADC self-addressing
  Wire.beginTransmission(0x00);
  Wire.write(0x04);
  Wire.endTransmission();

  // Begin general config
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_gen_config);
  // ADC datasheet page 34
  // rms_en, crc_en, stats_en, dwc_en, cnvst, ch_rst, cal, rst
  Wire.write(0b00011100);
  Wire.endTransmission();

  // Self-calibrate the ADC
  adc_self_cal();

  // Begin data config init
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_data_config);
  // ADC datasheet page 35
  // fix_pat, resv, appendstat_b1, append_stat_b0, resv, resv, resv, resv
  Wire.write(0b00100000);
  Wire.endTransmission();

  // Begin oversample setup
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_osr_config);
  // ADC datasheet page 35
  // resv, resv, resv, res, resv, osr_b2, osr_b1, osr_b0
  Wire.write(0b00000111); // 128 oversamples
  Wire.endTransmission();

  // Begin mode and clock setup
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_opmode_config);
  // ADC datasheet pages 35&36
  // conv_on_err, conv_mode_b1, conv_mode_b0, osc_sel, clk_div_b3, clk_div_b2, clk_div_b1, clk_div_b0
  Wire.write(0b00000000);
  Wire.endTransmission();

  // Set pin modes all to analog input
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_pin_config);
  // ADC datasheet pages 36
  // gpio_cfg_7, gpio_cfg_, gpio_cfg_5, gpio_cfg_4, gpio_cfg_3, gpio_cfg_2, gpio_cfg_1, gpio_cfg_0
  Wire.write(0b00000000); // all pins as analog inputs
  Wire.endTransmission();

  // Sequence setup
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_sequence_config);
  // ADC datasheet page 38
  // resv, resv, resv, seq_start, resv, resv, seq_mode_b1, seq_mode_b0
  Wire.write(0b00000000); // no sequencing of any kind
  Wire.endTransmission();

  // Remove all analog inputs from the auto sequencer
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_auto_sequence_channel_sel);
  // ADC datasheet page 39
  // ain_7, ain_6, ain_5, ain_4, ain_3, ain_2, ain_1, ain_0
  Wire.write(0b00000000);
  Wire.endTransmission();

  // Setup which channels will be allowed to assert the alert pin
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_alert_channel_sel);
  // ADC datasheet page 39
  // ch7, ch6, ch5, ch4, ch3, ch2, ch1, ch0
  Wire.write(0b11111111); // all channels can assert
  Wire.endTransmission();

  // Begin configuring bytes to be sent for channel config
  // Ch0 bitwise operations
  ch0_hysteresis = (adc_ch0_hysteresis << 4) | (adc_ch0_high_threshold & 0x000F);
  ch0_high_threshold = (adc_ch0_high_threshold >> 4);
  ch0_event_count = ((adc_ch0_low_threshold & 0x00F0) >> 4) | (adc_ch0_event_count << 4);
  ch0_low_threshold = (adc_ch0_low_threshold >> 4);

  // Ch1 bitwise operations
  ch1_hysteresis = (adc_ch1_hysteresis << 4) | (adc_ch1_high_threshold & 0x000F);
  ch1_high_threshold = (adc_ch1_high_threshold >> 4);
  ch1_event_count = ((adc_ch1_low_threshold & 0x00F0) >> 4) | (adc_ch1_event_count << 4);
  ch1_low_threshold = (adc_ch1_low_threshold >> 4);

  // Ch2 bitwise operations
  ch2_hysteresis = (adc_ch2_hysteresis << 4) | (adc_ch2_high_threshold & 0x000F);
  ch2_high_threshold = (adc_ch2_high_threshold >> 4);
  ch2_event_count = ((adc_ch2_low_threshold & 0x00F0) >> 4) | (adc_ch2_event_count << 4);
  ch2_low_threshold = (adc_ch2_low_threshold >> 4);

  // Ch3 bitwise operations
  ch3_hysteresis = (adc_ch3_hysteresis << 4) | (adc_ch3_high_threshold & 0x000F);
  ch3_high_threshold = (adc_ch3_high_threshold >> 4);
  ch3_event_count = ((adc_ch3_low_threshold & 0x00F0) >> 4) | (adc_ch3_event_count << 4);
  ch3_low_threshold = (adc_ch3_low_threshold >> 4);

  // Ch4 bitwise operations
  ch4_hysteresis = (adc_ch4_hysteresis << 4) | (adc_ch4_high_threshold & 0x000F);
  ch4_high_threshold = (adc_ch4_high_threshold >> 4);
  ch4_event_count = ((adc_ch4_low_threshold & 0x00F0) >> 4) | (adc_ch4_event_count << 4);
  ch4_low_threshold = (adc_ch4_low_threshold >> 4);

  // Ch5 bitwise operations
  ch5_hysteresis = (adc_ch5_hysteresis << 4) | (adc_ch5_high_threshold & 0x000F);
  ch5_high_threshold = (adc_ch5_high_threshold >> 4);
  ch5_event_count = ((adc_ch5_low_threshold & 0x00F0) >> 4) | (adc_ch5_event_count << 4);
  ch5_low_threshold = (adc_ch5_low_threshold >> 4);

  // Ch6 bitwise operations
  ch6_hysteresis = (adc_ch6_hysteresis << 4) | (adc_ch6_high_threshold & 0x000F);
  ch6_high_threshold = (adc_ch6_high_threshold >> 4);
  ch6_event_count = ((adc_ch6_low_threshold & 0x00F0) >> 4) | (adc_ch6_event_count << 4);
  ch6_low_threshold = (adc_ch6_low_threshold >> 4);

  // Ch7 bitwise operations
  ch7_hysteresis = (adc_ch7_hysteresis << 4) | (adc_ch7_high_threshold & 0x000F);
  ch7_high_threshold = (adc_ch7_high_threshold >> 4);
  ch7_event_count = ((adc_ch7_low_threshold & 0x00F0) >> 4) | (adc_ch7_event_count << 4);
  ch7_low_threshold = (adc_ch7_low_threshold >> 4);

  // Begin sending all the config data to the ADC
  Wire.beginTransmission(adc_add);
  if (fast_mode) { // Jump to fast mode if enabled
    Wire.write(0xB0);
    Wire.setClock(3400000);
  }
  Wire.write(adc_op_continuous_write);
  Wire.write(adc_hysteresis_ch0);
  Wire.write(ch0_hysteresis);
  Wire.write(ch0_high_threshold);
  Wire.write(ch0_event_count);
  Wire.write(ch0_low_threshold);
  Wire.write(ch1_hysteresis);
  Wire.write(ch1_high_threshold);
  Wire.write(ch1_event_count);
  Wire.write(ch1_low_threshold);
  Wire.write(ch2_hysteresis);
  Wire.write(ch2_high_threshold);
  Wire.write(ch2_event_count);
  Wire.write(ch2_low_threshold);
  Wire.write(ch3_hysteresis);
  Wire.write(ch3_high_threshold);
  Wire.write(ch3_event_count);
  Wire.write(ch3_low_threshold);
  Wire.write(ch4_hysteresis);
  Wire.write(ch4_high_threshold);
  Wire.write(ch4_event_count);
  Wire.write(ch4_low_threshold);
  Wire.write(ch5_hysteresis);
  Wire.write(ch5_high_threshold);
  Wire.write(ch5_event_count);
  Wire.write(ch5_low_threshold);
  Wire.write(ch6_hysteresis);
  Wire.write(ch6_high_threshold);
  Wire.write(ch6_event_count);
  Wire.write(ch6_low_threshold);
  Wire.write(ch7_hysteresis);
  Wire.write(ch7_high_threshold);
  Wire.write(ch7_event_count);
  Wire.write(ch7_low_threshold);
  Wire.endTransmission();
  if (fast_mode) {
    Wire.setClock(400000);
  }
  return;
}

/**
 * @brief Sets the threshold values for the specified ADC channel.
 * 
 * This function sets the high and low threshold values for the specified ADC channel.
 * It reads the current hysteresis and event count values for the channel, converts the
 * threshold values to the format accepted by the ADC, and writes the new values to the ADC.
 * 
 * @param adc_channel The ADC channel for which to set the threshold values.
 * @param high_th The high threshold value to set (12 bits max).
 * @param low_th The low threshold value to set (12 bits max).
 */
void adc_threshold_set(enum adc_channel adc_channel, uint16_t high_th, uint16_t low_th) {
  //init local vars
  uint8_t chx_hysteresis = 0b0;
  uint8_t chx_high_th = 0b0;
  uint8_t chx_event_count = 0b0;
  uint8_t chx_low_th = 0b0;
  uint8_t current_hysteresis_val = 0b0;
  uint8_t current_event_count = 0b0;

  //read current hysteresis & event count values
  //begin hysteresis read
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);

  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_hysteresis);
    break;
  case ch1:
    Wire.write(adc_ch1_hysteresis);
    break;
  case ch2:
    Wire.write(adc_ch2_hysteresis);
    break;
  case ch3:
    Wire.write(adc_ch3_hysteresis);
    break;
  case ch4:
    Wire.write(adc_ch4_hysteresis);
    break;
  case ch5:
    Wire.write(adc_ch5_hysteresis);
    break;
  case ch6:
    Wire.write(adc_ch6_hysteresis);
    break;
  case ch7:
    Wire.write(adc_ch7_hysteresis);
    break;
  }

  Wire.endTransmission();

  Wire.requestFrom(adc_add, 1);
  current_hysteresis_val = (Wire.read() & 0x0F);
  Wire.endTransmission();
  
  //begin event count read
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);

  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_event_count);
    break;
  case ch1:
    Wire.write(adc_ch1_event_count);
    break;
  case ch2:
    Wire.write(adc_ch2_event_count);
    break;
  case ch3:
    Wire.write(adc_ch3_event_count);
    break;
  case ch4:
    Wire.write(adc_ch4_event_count);
    break;
  case ch5:
    Wire.write(adc_ch5_event_count);
    break;
  case ch6:
    Wire.write(adc_ch6_event_count);
    break;
  case ch7:
    Wire.write(adc_ch7_event_count);
    break;
  }

  Wire.endTransmission();

  Wire.requestFrom(adc_add, 1);
  current_event_count = (Wire.read() & 0x0F);
  Wire.endTransmission();

  //convert values to format the adc accepts 
  chx_hysteresis = (((high_th & 0x000F) << 4) | current_hysteresis_val);
  chx_high_th = (high_th >> 4);
  chx_event_count = (((low_th & 0x000F) << 4) | current_event_count);
  chx_low_th = (low_th >> 4);

  // begin writeing to adc
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_continuous_write);

  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_hysteresis);
    break;
  case ch1:
    Wire.write(adc_ch1_hysteresis);
    break;
  case ch2:
    Wire.write(adc_ch2_hysteresis);
    break;
  case ch3:
    Wire.write(adc_ch3_hysteresis);
    break;
  case ch4:
    Wire.write(adc_ch4_hysteresis);
    break;
  case ch5:
    Wire.write(adc_ch5_hysteresis);
    break;
  case ch6:
    Wire.write(adc_ch6_hysteresis);
    break;
  case ch7:
    Wire.write(adc_ch7_hysteresis);
    break;
  }
  
  Wire.write(chx_hysteresis);
  Wire.write(chx_high_th);
  Wire.write(chx_event_count);
  Wire.write(chx_low_th);
  Wire.endTransmission();

  return;

}

/**
 * @brief Sets the hysteresis value for a specific ADC channel.
 *
 * This function sets the hysteresis value for the specified ADC channel. The hysteresis value determines the
 * difference in input voltage required to trigger a change in the ADC reading. The function reads the current
 * hysteresis register value, calculates the new value to write, and writes it to the hysteresis register.
 *
 * @param adc_channel The ADC channel for which to set the hysteresis value.
 * @param hysteresis_set The hysteresis value to set for the ADC channel (4 bits max).
 */
void adc_hysteresis_set(enum adc_channel adc_channel, uint8_t hysteresis_set) {
  //init local vars
  uint8_t current_hysteresis_reg_val = 0x00;
  uint8_t chx_hysteresis = 0x00;

  //read current hysteresis register value
  //begin hysteresis read
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);

  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_hysteresis);
    break;
  case ch1:
    Wire.write(adc_ch1_hysteresis);
    break;
  case ch2:
    Wire.write(adc_ch2_hysteresis);
    break;
  case ch3:
    Wire.write(adc_ch3_hysteresis);
    break;
  case ch4:
    Wire.write(adc_ch4_hysteresis);
    break;
  case ch5:
    Wire.write(adc_ch5_hysteresis);
    break;
  case ch6:
    Wire.write(adc_ch6_hysteresis);
    break;
  case ch7:
    Wire.write(adc_ch7_hysteresis);
    break;
  }

  Wire.endTransmission();

  Wire.requestFrom(adc_add, 1);
  current_hysteresis_reg_val = (Wire.read() & 0x0F);
  Wire.endTransmission();
  
  //convert values to format the adc accepts 
  chx_hysteresis = (((hysteresis_set & 0x000F) << 4) | current_hysteresis_reg_val);

  // begin writeing to adc
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_continuous_write);

  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_hysteresis);
    break;
  case ch1:
    Wire.write(adc_ch1_hysteresis);
    break;
  case ch2:
    Wire.write(adc_ch2_hysteresis);
    break;
  case ch3:
    Wire.write(adc_ch3_hysteresis);
    break;
  case ch4:
    Wire.write(adc_ch4_hysteresis);
    break;
  case ch5:
    Wire.write(adc_ch5_hysteresis);
    break;
  case ch6:
    Wire.write(adc_ch6_hysteresis);
    break;
  case ch7:
    Wire.write(adc_ch7_hysteresis);
    break;
  }
  
  Wire.write(chx_hysteresis);
  Wire.endTransmission();

  return;

}

/**
 * @brief Reads the event count for a specific ADC channel.
 * 
 * This function reads the event count for the specified ADC channel using the I2C communication protocol.
 * 
 * @param adc_channel The ADC channel for which to read the event count.
 * @return The current event count for the specified ADC channel.
 */
int adc_event_count_read(enum adc_channel adc_channel) {
  //init local vars 
  uint8_t chx_current_event_count = 0x00;

  //begin event count read
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);
  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_event_count);
    break;
  case ch1:
    Wire.write(adc_ch1_event_count);
    break;
  case ch2:
    Wire.write(adc_ch2_event_count);
    break;
  case ch3:
    Wire.write(adc_ch3_event_count);
    break;
  case ch4:
    Wire.write(adc_ch4_event_count);
    break;
  case ch5:
    Wire.write(adc_ch5_event_count);
    break;
  case ch6:
    Wire.write(adc_ch6_event_count);
    break;
  case ch7:
    Wire.write(adc_ch7_event_count);
    break;
  }
  Wire.endTransmission();

  Wire.requestFrom(adc_add, 1);
  chx_current_event_count = (Wire.read() & 0x0F);
  return chx_current_event_count;
}

/**
 * @brief Clears the event count for the specified ADC channel.
 * 
 * This function clears the event count register for the specified ADC channel.
 * It first reads the current event count value, then writes 0 to the event count register.
 * 
 * @param adc_channel The ADC channel to clear the event count for.
 * 
 */
void adc_event_clear(enum adc_channel adc_channel) {
  //init local vars
  uint8_t event_count_value = 0x00;

  //begin read
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);
  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_event_count);
    break;
  case ch1:
    Wire.write(adc_ch1_event_count);
    break;
  case ch2:
    Wire.write(adc_ch2_event_count);
    break;
  case ch3:
    Wire.write(adc_ch3_event_count);
    break;
  case ch4:
    Wire.write(adc_ch4_event_count);
    break;
  case ch5:
    Wire.write(adc_ch5_event_count);
    break;
  case ch6:
    Wire.write(adc_ch6_event_count);
    break;
  case ch7:
    Wire.write(adc_ch7_event_count);
    break;
  }
  Wire.endTransmission();

  Wire.requestFrom(adc_add, 1);
  event_count_value = (Wire.read() & 0xF0);

  //write 0 to event count register
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  switch (adc_channel){
  case ch0:
    Wire.write(adc_ch0_event_count);
    break;
  case ch1:
    Wire.write(adc_ch1_event_count);
    break;
  case ch2:
    Wire.write(adc_ch2_event_count);
    break;
  case ch3:
    Wire.write(adc_ch3_event_count);
    break;
  case ch4:
    Wire.write(adc_ch4_event_count);
    break;
  case ch5:
    Wire.write(adc_ch5_event_count);
    break;
  case ch6:
    Wire.write(adc_ch6_event_count);
    break;
  case ch7:
    Wire.write(adc_ch7_event_count);
    break;
  }
  Wire.write(event_count_value);
  Wire.endTransmission();
  
  return;

}

//adc_alert_read
//reads and returns 
//enum adc_alert_read() {

//}

/**
 * @brief Reads the analog value from the specified ADC channel.
 * 
 * @param adc_channel The ADC channel to read from.
 * @return The 16-bit analog value read from the ADC.
 */
int adc_read(enum adc_channel adc_channel) {
  //init local vars
  uint16_t read_word = 0x0000;

  //begin read
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_continuous_read);

  switch (adc_channel){
  case ch0:
    Wire.write(adc_recent_ch0_lsb);
    break;
  case ch1:
    Wire.write(adc_recent_ch1_lsb);
    break;
  case ch2:
    Wire.write(adc_recent_ch2_lsb);
    break;
  case ch3:
    Wire.write(adc_recent_ch3_lsb);
    break;
  case ch4:
    Wire.write(adc_recent_ch4_lsb);
    break;
  case ch5:
    Wire.write(adc_recent_ch5_lsb);
    break;
  case ch6:
    Wire.write(adc_recent_ch6_lsb);
    break;
  case ch7:
    Wire.write(adc_recent_ch7_lsb);
    break;
  }
  
  Wire.endTransmission();

  Wire.requestFrom(adc_add, 2);
  read_word = Wire.read();
  Wire.endTransmission();

  return read_word;

}

/**
 * Clears the event flags for the ADC module.
 */
void adc_clear_event_flags() {
  Wire.write(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_event_flag);
  Wire.write(0x0);
  Wire.endTransmission();
}

/**
 * @brief Determines the alert source based on the current event flag register value.
 * 
 * @return The ADC channel corresponding to the alert source, or `empty` if no alert is detected.
 */
enum adc_channel adc_determine_alert_source() {
  //init local vars 
  uint8_t current_event_flag_register_value = 0;

  //read alert flag register
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);
  Wire.write(adc_event_flag);
  Wire.endTransmission();
  Wire.requestFrom(adc_add, 1);
  current_event_flag_register_value = Wire.read();
  Wire.endTransmission();

  if ((current_event_flag_register_value & 0x01) != 0) {
    return ch0;
  } else if ((current_event_flag_register_value & 0x02) != 0) {
    return ch1;
  } else if ((current_event_flag_register_value & 0x04) != 0) {
    return ch2;
  } else if ((current_event_flag_register_value & 0x08) != 0) {
    return ch3;
  } else if ((current_event_flag_register_value & 0x10) != 0) {
    return ch4;
  } else if ((current_event_flag_register_value & 0x20) != 0) {
    return ch5;
  } else if ((current_event_flag_register_value & 0x40) != 0) {
    return ch6;
  } else if ((current_event_flag_register_value & 0x80) != 0) {
    return ch7;
  }

  return empty;

}

#endif // adc_cpp