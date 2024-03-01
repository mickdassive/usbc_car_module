//{usbc car module}
//{defines.cpp}
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

//initiates the self cal rutine on the adc and waits till its compltete and returns
void adc_self_cal () {
  //local vars
  bool cal_complete = false;
  uint8_t self_cal_mask = 0b0000010;
  uint8_t current_gen_config_state = 0b0;

  //read current config register state
  //check if i can actuly do this when i have the hardware
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_read);
  Wire.write(adc_gen_config);
  Wire.endTransmission();

  //begin read
  Wire.requestFrom(adc_add, 1);
  current_gen_config_state = Wire.read();
  Wire.endTransmission();

  //bitwise or current state with self cal mask
  current_gen_config_state = current_gen_config_state | self_cal_mask;

  //write to gen config register to start a self cal
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_gen_config);
  Wire.write(current_gen_config_state);
  Wire.endTransmission();

  //set current state to 0 so it can be reused later
  current_gen_config_state = 0b0;

  //begin checking if the self cal is complete
  while(!cal_complete) {
    //read current self cal bit state
    //check if i can actuly do this when i have the hardware
    Wire.beginTransmission(adc_add);
    Wire.write(adc_op_single_read);
    Wire.write(adc_gen_config);
    Wire.endTransmission();

    //begin read
    Wire.requestFrom(adc_add, 1);
    current_gen_config_state = Wire.read();
    Wire.endTransmission();

    //bitwise and the current self cal bit with the self cal mask'
    current_gen_config_state = current_gen_config_state & self_cal_mask;

    if(current_gen_config_state == 0) {
      cal_complete = true;
    }

  }

  return; 
}

//adc bootup init
//fast_mode: when set to true the i2c bus will be jump up to fast mode speed when sending channel config data to the adc
void adc_init (bool fast_mode) {
  //init local vars
  uint8_t ch0_hysteresis = 0b0;
  uint8_t ch0_high_threshold = 0b0;
  uint8_t ch0_event_count = 0b0;
  uint8_t ch0_low_threshold = 0b0;
  uint8_t ch1_hysteresis = 0b0;
  uint8_t ch1_high_threshold = 0b0;
  uint8_t ch1_event_count = 0b0;
  uint8_t ch1_low_threshold =0b0;
  uint8_t ch2_hysteresis = 0b0;
  uint8_t ch2_high_threshold = 0b0;
  uint8_t ch2_event_count = 0b0;
  uint8_t ch2_low_threshold =0b0;
  uint8_t ch3_hysteresis = 0b0;
  uint8_t ch3_high_threshold = 0b0;
  uint8_t ch3_event_count = 0b0;
  uint8_t ch3_low_threshold =0b0;
  uint8_t ch4_hysteresis = 0b0;
  uint8_t ch4_high_threshold = 0b0;
  uint8_t ch4_event_count = 0b0;
  uint8_t ch4_low_threshold =0b0;
  uint8_t ch5_hysteresis = 0b0;
  uint8_t ch5_high_threshold = 0b0;
  uint8_t ch5_event_count = 0b0;
  uint8_t ch5_low_threshold =0b0;
  uint8_t ch6_hysteresis = 0b0;
  uint8_t ch6_high_threshold = 0b0;
  uint8_t ch6_event_count = 0b0;
  uint8_t ch6_low_threshold =0b0;
  uint8_t ch7_hysteresis = 0b0;
  uint8_t ch7_high_threshold = 0b0;
  uint8_t ch7_event_count = 0b0;
  uint8_t ch7_low_threshold =0b0;

  //bordcast on i2c bus for adc self addresing
  Wire.beginTransmission(0x00);
  Wire.write(0x04);
  Wire.endTransmission();

  //begin geniral config 
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_gen_config);
  //adc datasheet page 34
  //rms_en, crc_en, stats_en, dwc_en, cnvst, ch_rst, cal, rst
  Wire.write(0b00011100);
  Wire.endTransmission();

  //self cal the adc
  adc_self_cal();

  //begin data config init
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_data_config);
  //adc datasheet page 35
  //fix_pat, resv, append_stat_b1, append_stat_b0, resv, resv, resv, resv
  Wire.write(0b00100000);
  Wire.endTransmission();

  //begin over sampel setup
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_osr_config);
  //adc datasheet page 35
  //resv, resv, resv, resv, resv, osr_b2, osr_b1, osr_b0
  Wire.write(0b00000111);//128 oversampels
  Wire.endTransmission();

  //begin mode and clock setup
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_opmode_config);
  //adc data sheet pages 35&36
  //conv_on_err, conv_mode_b1, conv_mode_b0, osc_sel, clk_div_b3, clk_div_b2, clk_div_b1, clk_div_b0
  Wire.write(0b00000000);
  Wire.endTransmission();

  //set pinmodes all to analogue input
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_pin_config);
  //adc datasheet pages 36
  //gpio_cfg_7, gpio_cfg_6, gpio_cfg_5, gpio_cfg_4, gpio_cfg_3, gpio_cfg_2, gpio_cfg_1, gpio_cfg_0
  Wire.write(0b00000000);//all pins as anlouge inputs
  Wire.endTransmission();

  //seqwincer setup 
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_sequence_config);
  //adc datasheet page 38
  //resv, resv, resv, seq_start, resv, resv, seq_mode_b1, seq_mode_b0
  Wire.write(0b00000000);//no seqwinceing of anykind
  Wire.endTransmission();

  //remove all analouge inputs form the auto seqwincer
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_auto_sequence_channel_sel);
  //adc datasheet page 39
  //ain_7, ain_6, ain_5, ain_4, ain_3, ain_2, ain_1, ain_0
  Wire.write(0b00000000);
  Wire.endTransmission();

  //setup witch channels will be allowed to asert the alert pin
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_alert_channel_sel);
  //adc datasheet page 39
  //ch7, ch6, ch5, ch4, ch3, ch2, ch1, ch0
  Wire.write(0b11111111);//all channels can asert
  Wire.endTransmission();

  //setup other alert assert conditions 
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_alert_map);
  //adc datasheet page 40
  //resv, resv, resv, resv, resv, resv, alert_rms, alert_crc
  Wire.write(0b00000000);
  Wire.endTransmission();

  //setup alert pin config
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_alert_pin_config);
  //adc datasheet page 40
  //resv, resv, resv, resv, resv, alert_drive, alert_logic_b1, alert_logic_b0
  Wire.write(0b00000101);
  Wire.endTransmission();

  //set digital window comparitor to alert on vlaues within the upper and lower limits
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
  Wire.write(adc_event_rgn);
  //adc datasheet page 42
  //ch7, ch6, ch5, ch4, ch3, ch2, ch1, ch0
  Wire.write(0b11111111);
  Wire.endTransmission();

  //begin configureing bytes to be sent for channel config
  //ch0 bitwise opertations
  ch0_hysteresis = (adc_ch0_hysteresis << 4) | (adc_ch0_high_threshold & 0x000F);
  ch0_high_threshold = (adc_ch0_high_threshold >> 4);
  ch0_event_count = ((adc_ch0_low_threshold & 0x00F0) >> 4) | (adc_ch0_event_count << 4);
  ch0_low_threshold = (adc_ch0_low_threshold >> 4);

  //ch1 bitwise operations
  ch1_hysteresis = (adc_ch1_hysteresis << 4) | (adc_ch1_high_threshold & 0x000F);
  ch1_high_threshold = (adc_ch1_high_threshold >> 4);
  ch1_event_count = ((adc_ch1_low_threshold & 0x00F0) >> 4) | (adc_ch1_event_count << 4);
  ch1_low_threshold = (adc_ch1_low_threshold >> 4);

  //ch2 bitwise opertations
  ch2_hysteresis = (adc_ch2_hysteresis << 4) | (adc_ch2_high_threshold & 0x000F);
  ch2_high_threshold = (adc_ch2_high_threshold >> 4);
  ch2_event_count = ((adc_ch2_low_threshold & 0x00F0) >> 4) | (adc_ch2_event_count << 4);
  ch2_low_threshold = (adc_ch2_low_threshold >> 4);

  //ch3 bitwise opertations
  ch3_hysteresis = (adc_ch3_hysteresis << 4) | (adc_ch3_high_threshold & 0x000F);
  ch3_high_threshold = (adc_ch3_high_threshold >> 4);
  ch3_event_count = ((adc_ch3_low_threshold & 0x00F0) >> 4) | (adc_ch3_event_count << 4);
  ch3_low_threshold = (adc_ch3_low_threshold >> 4);

  //ch4 bitwise opertations
  ch4_hysteresis = (adc_ch4_hysteresis << 4) | (adc_ch4_high_threshold & 0x000F);
  ch4_high_threshold = (adc_ch4_high_threshold >> 4);
  ch4_event_count = ((adc_ch4_low_threshold & 0x00F0) >> 4) | (adc_ch4_event_count << 4);
  ch4_low_threshold = (adc_ch4_low_threshold >> 4);

  //ch5 bitwise opertations
  ch5_hysteresis = (adc_ch5_hysteresis << 4) | (adc_ch5_high_threshold & 0x000F);
  ch5_high_threshold = (adc_ch5_high_threshold >> 4);
  ch5_event_count = ((adc_ch5_low_threshold & 0x00F0) >> 4) | (adc_ch5_event_count << 4);
  ch5_low_threshold = (adc_ch5_low_threshold >> 4);

  //ch6 bitwise opertations
  ch6_hysteresis = (adc_ch6_hysteresis << 4) | (adc_ch6_high_threshold & 0x000F);
  ch6_high_threshold = (adc_ch6_high_threshold >> 4);
  ch6_event_count = ((adc_ch6_low_threshold & 0x00F0) >> 4) | (adc_ch6_event_count << 4);
  ch6_low_threshold = (adc_ch6_low_threshold >> 4);

  //ch7 bitwise opertations
  ch7_hysteresis = (adc_ch7_hysteresis << 4) | (adc_ch7_high_threshold & 0x000F);
  ch7_high_threshold = (adc_ch7_high_threshold >> 4);
  ch7_event_count = ((adc_ch7_low_threshold & 0x00F0) >> 4) | (adc_ch7_event_count << 4);
  ch7_low_threshold = (adc_ch7_low_threshold >> 4);

  //begin sending all the config data to the adc
  Wire.beginTransmission(adc_add);
  if (fast_mode) { //jump to fast mode if enabeld
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

//adc_threshold set
//set the treshold vlaues for a given channel
//adc_channel: disired channel on adc to change threshold values
//high_th: upper threshold vale to set (max 12 bit number)
//low_th: lower threshold vale to set (max 12 bit number) 
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

//adc_hysteresis_set
//sets adc channel hysteresis value
//adc_channel: disired channel on adc to set hysteresis value 
//hysteresis_set: value to set hysteresis for a given cnannel (4 bit number max)
void adc_hysteresis_set(enum adc_channel adc_channel, uint8_t hysteresis_set) {
  //init local vars
  uint8_t curent_hysteresis_reg_val = 0x00;
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
  curent_hysteresis_reg_val = (Wire.read() & 0xF0);
  Wire.endTransmission();

  //calculate value to write to the hysteresis register
  chx_hysteresis = curent_hysteresis_reg_val | (hysteresis_set & 0x0F);

  //begin write to hysteresis register
  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);
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

//adc_event_count_read
//read current event count for a given channel
//adc_channel: disired channel on adc to read event count from
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

//adc_event clear
//resets event count for given channel 
//adc_channel: disired channel on adc to reset event count on
void adc_event_clear(enum adc_channel adc_channel) {
  //init local vars
  uint8_t event_count_val = 0x00;

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
  event_count_val = (Wire.read() & 0xF0);

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
  Wire.write(event_count_val);
  Wire.endTransmission();
  
  return;

}

//adc_alert_read
//reads and returns 
//enum adc_alert_read() {

//}

//reads from the ADC returns value in 16bit ADC counts
//adc_channel: select the desired channel to read from
int adc_read(enum adc_channel adc_channel) {
  //init local vars
  uint8_t read_byte_0 = 0b0;
  uint8_t read_byte_1 = 0b0;
  uint16_t output = 0b0;

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
    Wire.write(adc_recent_ch6_lsb);
    break;
  }
  
  Wire.endTransmission();

  Wire.requestFrom(adc_add, 2);
  read_byte_0 = Wire.read();
  read_byte_1 = Wire.read();
  Wire.endTransmission();

  output = (int16_t)((read_byte_0 << 8) | read_byte_1);

  return output;

}

#endif // adc_cpp