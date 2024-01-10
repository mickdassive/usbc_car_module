//{usbc car module}
//{main.cpp}
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


extern "C" {
  #include "user_interface.h"
}

#include <Arduino.h>
#include <Wire.h>
#include <iostream>
#include "defines.cpp"

//firmware version
const char* firmware_version = "V 0.1";

//io intrupt rutine
void IRAM_ATTR ioISR() {

}


//reads current pin state of the io expander outputs
//port: port of iox to read
//iox_num: number of iox to read from
uint8_t read_current_io_state(int port, int iox_num) {
  uint8_t iox_address = (iox_num == 0) ? iox_0_add : iox_1_add;
  uint8_t iox_output_register = (port == 0) ? iox_output_port_0 : iox_output_port_1;

  Wire.beginTransmission(iox_address);
  Wire.write(iox_output_register);
  Wire.endTransmission();

  Wire.requestFrom(iox_address, 1);
  return Wire.read();
}

//io_call function
//This function is used to read or write digital values to onboard or offboard IOs.
//pin_needed: a pin struct that defines the pin being read/written to
//read_write: a read_write enum value that specifies if the function should read or write
//high_low: a high_low enum value that specifies if the function should write a high or low value
int io_call(struct pin pin_needed, enum read_write read_write, enum high_low high_low) {

  //Check if the pin is onboard or offboard
  if (pin_needed.onboard == true) {
    //If the pin is onboard, check if we need to read or write
    if (read_write == write) {
      //If we need to write, check if we need to write high or low
      if (high_low == high) { //onborad digital write
        digitalWrite(pin_needed.pin_number, HIGH);
        
      } else if (high_low == low) { //onborad digital write low
        digitalWrite (pin_needed.pin_number, LOW);
        
      } else {
         //If high_low is not high or low, do something here (error handling?)
      }
    } else if (read_write == read) { //onboard digital read
      int read_value = digitalRead(pin_needed.pin_number);
      return(read_value);
    } else {
       //If read_write is not read or write, do something here (error handling?)
    }

  } else if (pin_needed.onboard == false){ //digital write to io expander
    
    if (read_write == write) {  //chek to see if we are writeing the the ioxepander

      //int local varibels
      uint8_t current = read_current_io_state(pin_needed.port, pin_needed.iox_number); //read and store the current state of the output register of the the given pin
      uint8_t output = 0b00000000;
      uint8_t mask_not = ~pin_needed.mask;

      //bitwise logic to ether set high or low a given pin
      if (high_low == high) {
        output = current | pin_needed.mask;
      } else if (high_low == low){
        output = current & mask_not;
      }

      //begin write to iox
      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);
      } else {
        Wire.beginTransmission(iox_1_add);
      }
        
      //write to selcted port
      if (pin_needed.port == 0) {
        Wire.write(iox_output_port_0);
      } else {
        Wire.write(iox_output_port_1);
      }
      
      Wire.write(output);

      Wire.endTransmission();

    } else if (read_write == read) {  //check to see if we are reading from the io expanders input
      
      //init local varibles
      uint8_t readval = 0b00000000;
      uint8_t output_byte = 0b00000000;
      
      //select witch iox to red from
      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);
      } else {
        Wire.beginTransmission(iox_1_add);
      }
      
      //selcect port based on given pin
      if (pin_needed.port == 0) {
        Wire.write(iox_input_port_0);
      } else if (pin_needed.port == 1) {
        Wire.write(iox_input_port_1);
      }

      Wire.endTransmission();

      //begin reading from selcted iox
      if (pin_needed.iox_number == 0) {
        Wire.requestFrom(iox_0_add, 1);
      } else {
        Wire.requestFrom(iox_1_add, 1);
      }
      
      //read the given value from the i2c bus
      readval = Wire.read();

      //isolate the indivdual bit of the given pin bsed on its mask
      output_byte = readval & pin_needed.mask;

      //return high or low based on wether or not the byte is more than 0
      if (output_byte == 0) {
        return (LOW);
      } else {
        return (HIGH);
      }
      
    }

  } else { //return if input bad
    return 0;
  }
  return 0;

}

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
void adc_init(bool fast_mode) {
  //init local vars
  uint8_t ch0_hysteresis = 0b0;
  uint8_t ch0_high_threshold = 0b0;
  uint8_t ch0_event_count = 0b0;
  uint8_t ch0_low_threshold =0b0;
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

//reads from the i2c ADC returns value in 16bit ADC counts
//adc_channel: select the desired channel to read from
int adc_read(enum adc_channel adc_channel){
  //init local vars
  uint8_t read_byte_0 = 0b0;
  uint8_t read_byte_1 = 0b0;
  uint16_t output = 0b0;

  Wire.beginTransmission(adc_add);
  Wire.write(adc_op_single_write);

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

//display init function
void disp_init() {
  //wake up display controler
  Wire.beginTransmission(disp_base_add);
  Wire.write(disp_shutdown);
  Wire.write(disp_up_rst);
  Wire.endTransmission();

  //tell display controler to self address
  Wire.beginTransmission(disp_base_add);
  Wire.write(disp_self_add);
  Wire.write(0x01);
  Wire.endTransmission();

  //wake display from shutdown after self addressing
  Wire.beginTransmission(disp_add);
  Wire.write(disp_shutdown);
  Wire.write(disp_up);
  Wire.endTransmission();

  //set disp controler decode mode to raw
  Wire.beginTransmission(disp_add);
  Wire.write(disp_decode_mode);
  Wire.write(0x00); //decode mode raw
  Wire.endTransmission();

  //set display scan limit
  Wire.beginTransmission(disp_add);
  Wire.write(disp_scan_limit);
  Wire.write(0x07); //scan all digits
  Wire.endTransmission();

  //set display intensity
  Wire.beginTransmission(disp_add);
  Wire.write(disp_global_intensity);
  Wire.write(disp_intense_defult);
  Wire.endTransmission();

  return;
}

//display balnk function just writes 0s to the first 4 digit registers but keeps the status leds
void disp_blank() {
  Wire.beginTransmission(disp_add);
  Wire.write(disp_digit_0);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  return;
}

//set disply brightness
//desired_brightness: brightness of display from 0-255
void disp_bright(uint8_t desired_brightness) {
  Wire.beginTransmission(disp_add);
  Wire.write(disp_global_intensity);
  Wire.write(desired_brightness);
  Wire.endTransmission();

  return;
}

//display write function
//will only work with flaots and ints
void disp_write(float input) {
  
}

//read current led state
uint8_t read_current_led_state (enum led_names){
  
}


//led control
//led_names: name of led to control
//led_on_off: set desired led state
void led_control(enum led_names,enum led_on_off){

  if (led_on_off = on) {
    switch (led_names) {
      case (watts):

      break;
      case (amps):

      break;
      case (volts):

      break;
      case (usb_c_back):

      break;
      case (usb_c_front):

      break;
      case (usb_a):

      break;
      case (system_power):

      break;
      case (watts_10):

      break;
      case (watts_20):

      break;
      case (watts_40):

      break;
      case (watts_65):

      break;
      case (watts_100):

      break;
    }
  } else if (led_on_off = off) {

  }
  return 0;
}



//GPIO pin auto init for both iox and onborad pins
void gpio_init() {

  //init vars
  uint8_t iox_0_port_0_pinmode = 0x00;
  uint8_t iox_0_port_1_pinmode = 0x00;
  uint8_t iox_1_port_0_pinmode = 0x00;
  uint8_t iox_1_port_1_pinmode = 0x00;

  uint8_t iox_0_port_0_interrupt = 0xFF;
  uint8_t iox_0_port_1_interrupt = 0xFF;
  uint8_t iox_1_port_0_interrupt = 0xFF;
  uint8_t iox_1_port_1_interrupt = 0xFF;

  //begin iterationg thru pins
  for (uint i = 1; i < sizeof(pin_names[0]); i++) {

    //init local loop vars
    //struct pin* curent_pin = pin_names[i];

    switch (pin_names[i]->pin_mode)
    {
    case in:
      if (pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, INPUT);
      } else {
        if (pin_names[i]->iox_number == 0) {
          if (pin_names[i]->port == 0){
            iox_0_port_0_pinmode = pin_names[i]->mask | iox_0_port_0_pinmode;
          } else {
            iox_0_port_1_pinmode = pin_names[i]->mask | iox_0_port_1_pinmode;
          }
        } else {
          if (pin_names[i]->port == 0) {
            iox_1_port_0_pinmode = pin_names[i]->mask | iox_1_port_0_pinmode;
          } else {
            iox_1_port_1_pinmode = pin_names[i]->mask | iox_1_port_1_pinmode;
          }
        }
      }
      break;
    
    case out:
      if (pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, OUTPUT);
      }
      //no need to do anything to the iox all pins defult to output
      break;

    case bi_dir:
      //do nothing only used for i2c coms witch are defined else-ware 
      break;
    
    case intr: //setup iterups for cheking when io state is changed
      if(pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, INPUT);
        attachInterrupt(digitalPinToInterrupt(pin_names[i]->pin_number), ioISR, FALLING);
      }      
      break;
    }  

    // setup the interrupt masks for the io expanders
    if (pin_names[i]->allow_interrupt && !pin_names[i]->onboard) {
      if (pin_names[i]->iox_number == 0) {
        if (pin_names[i]->port == 0) {
          iox_0_port_0_interrupt = iox_0_port_0_interrupt ^ pin_names[i]->mask;
        } else {
          iox_0_port_1_interrupt = iox_0_port_1_interrupt ^ pin_names[i]->mask;
        }
      } else {
        if (pin_names[i]->port == 0) {
          iox_1_port_0_interrupt = iox_1_port_0_interrupt ^ pin_names[i]->mask;
        } else {
          iox_1_port_1_interrupt = iox_1_port_1_interrupt ^ pin_names[i]->mask;
        }
      }
    }

  }

  //set all outputs of ioxs low
  //write to output at iox 0 port 0
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_output_port_0);
  Wire.write(0x00);
  Wire.endTransmission();

  //write to output at iox 0 port 1
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_output_port_1);
  Wire.write(0x00);
  Wire.endTransmission();

  //write to output at iox 1 port 0
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_output_port_0);
  Wire.write(0x00);
  Wire.endTransmission();

  //write to output at iox 1 port 1
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_output_port_1);
  Wire.write(0x00);
  Wire.endTransmission();


  //begin writeing pinmodes to ioxs 
  //write pinmode to iox 0 port 0 
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_config_port_0);
  Wire.write(iox_0_port_0_pinmode);
  Wire.endTransmission();

  //write pinmode to iox 0 port 1 
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_config_port_1);
  Wire.write(iox_0_port_1_pinmode);
  Wire.endTransmission();

  //write pinmode to iox 1 port 0 
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_config_port_0);
  Wire.write(iox_1_port_0_pinmode);
  Wire.endTransmission();

  //write pinmode to iox 1 port 1 
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_config_port_1);
  Wire.write(iox_1_port_1_pinmode);
  Wire.endTransmission();


  //write to ioxs interup mask registers
  //write mask to iox 0 port 0
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(iox_0_port_0_interrupt);
  Wire.endTransmission();

  //write mask to iox 0 port 1
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_mask_register_1);
  Wire.write(iox_0_port_1_interrupt);
  Wire.endTransmission();

  //write mask to iox 1 port 0
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(iox_1_port_0_interrupt);
  Wire.endTransmission();

  //write mask to iox 1 port 1
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_int_mask_register_1);
  Wire.write(iox_1_port_1_interrupt);
  Wire.endTransmission();


  return;
};

void setup() {

  //begin serial
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Serial started");
  Serial.print("Firmware version: ");
  Serial.print(firmware_version);
  Serial.println(" ");

  //begin i2c
  Wire.begin(sda.pin_number, scl.pin_number);
  Wire.setClock(400000);
  Serial.println("I2c strated");

  //begin GPIO inits for on and offboard 
  gpio_init();
  Serial.println("GPIO init complete");

  //bgegin init for ADC
  //adc_init(false);
  Serial.println("ADC init and self cal complete");

  //begin init for display
  disp_init();
  Serial.println("Front display init complete");

  //begin USB hub chip init

  Serial.println("USB-hub init complete");

  //begin init for USB-PD PHYs

  Serial.println("USB-PD PHY UFP&DFP init complete");

  //begin USB-PD power supply check 

  Serial.println("UFP&DFP voltage outputs within safe range");

  
}

void loop() {
  io_call(onboard_led, write, high);
  delay(rand() % (1000-1+1)+1);
  io_call(onboard_led, write, low);
  delay(rand() % (1000-1+1)+1);
}


