//{usbc car module}
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





//firmware version
const char* firmware_version = "V 0.1";


//i2c adc defines
const uint8_t adc_add = 0x17;//check this 
const uint8_t adc_sys_stat = 0x00;
const uint8_t adc_gen_config = 0x01;
const uint8_t adc_data_config = 0x02;
const uint8_t adc_osr_config = 0x03;
const uint8_t adc_opmode_config = 0x04;
const uint8_t adc_pin_config = 0x05;
const uint8_t adc_gpio_config = 0x07;
const uint8_t adc_gpo_drive_config = 0x09;
const uint8_t adc_gpo_value = 0x0B;
const uint8_t adc_pgi_value = 0x0D;
const uint8_t adc_zcd_blank_config = 0x0F;
const uint8_t adc_sequence_config = 0x10;
const uint8_t adc_channel_sel = 0x11;
const uint8_t adc_auto_sequence_channel_sel = 0x12;
const uint8_t adc_alert_channel_sel = 0x14;
const uint8_t adc_alert_map = 0x16;
const uint8_t adc_alert_pin_config = 0x17;
const uint8_t adc_event_flag = 0x18;
const uint8_t adc_event_high_flag = 0x1A;
const uint8_t adc_event_low_flag = 0x1C;
const uint8_t adc_event_rgn = 0x1E;
const uint8_t adc_hysteresis_ch0 = 0x20;
const uint8_t adc_high_th_ch0 = 0x21;
const uint8_t adc_event_count_ch0 = 0x22;
const uint8_t adc_low_th_ch0 = 0x23;
const uint8_t adc_hysteresis_ch1 = 0x24;
const uint8_t adc_high_th_ch1 = 0x25;
const uint8_t adc_event_count_ch1 = 0x26;
const uint8_t adc_low_th_ch1 = 0x27;
const uint8_t adc_hysteresis_ch2 = 0x28;
const uint8_t adc_high_th_ch2 = 0x29;
const uint8_t adc_event_count_ch2 = 0x2A;
const uint8_t adc_low_th_ch2 = 0x2B;
const uint8_t adc_hysteresis_ch3 = 0x2C;
const uint8_t adc_high_th_ch3 = 0x2D;
const uint8_t adc_event_count_ch3 = 0x2E;
const uint8_t adc_low_th_ch3 = 0x2F;
const uint8_t adc_hysteresis_ch4 = 0x30;
const uint8_t adc_high_th_ch4 = 0x31;
const uint8_t adc_event_count_ch4 = 0x32;
const uint8_t adc_low_th_ch4 = 0x33;
const uint8_t adc_hysteresis_ch5 = 0x34;
const uint8_t adc_high_th_ch5 = 0x35;
const uint8_t adc_event_count_ch5 = 0x36;
const uint8_t adc_low_th_ch5 = 0x37;
const uint8_t adc_hysteresis_ch6 = 0x38;
const uint8_t adc_high_th_ch6 = 0x39;
const uint8_t adc_event_count_ch6 = 0x3A;
const uint8_t adc_low_th_ch6 = 0x3B;
const uint8_t adc_hysteresis_ch7 = 0x3C;
const uint8_t adc_high_th_ch7 = 0x3D;
const uint8_t adc_event_count_ch7 = 0x3E;
const uint8_t adc_low_th_ch7 = 0x3F;
const uint8_t adc_max_ch0_lsb = 0x60;
const uint8_t adc_max_ch0_msb = 0x61;
const uint8_t adc_max_ch1_lsb = 0x62;
const uint8_t adc_max_ch1_msb = 0x63;
const uint8_t adc_max_ch2_lsb = 0x64;
const uint8_t adc_max_ch2_msb = 0x65;
const uint8_t adc_max_ch3_lsb = 0x66;
const uint8_t adc_max_ch3_msb = 0x67;
const uint8_t adc_max_ch4_lsb = 0x68;
const uint8_t adc_max_ch4_msb = 0x69;
const uint8_t adc_max_ch5_lsb = 0x6A;
const uint8_t adc_max_ch5_msb = 0x6B;
const uint8_t adc_max_ch6_lsb = 0x6C;
const uint8_t adc_max_ch6_msb = 0x6D;
const uint8_t adc_max_ch7_lsb = 0x6E;
const uint8_t adc_max_ch7_msb = 0x6F;
const uint8_t adc_min_ch0_lsb = 0x80;
const uint8_t adc_min_ch0_msb = 0x81;
const uint8_t adc_min_ch1_lsb = 0x82;
const uint8_t adc_min_ch1_msb = 0x83;
const uint8_t adc_min_ch2_lsb = 0x84;
const uint8_t adc_min_ch2_msb = 0x85;
const uint8_t adc_min_ch3_lsb = 0x86;
const uint8_t adc_min_ch3_msb = 0x87;
const uint8_t adc_min_ch4_lsb = 0x88;
const uint8_t adc_min_ch4_msb = 0x89;
const uint8_t adc_min_ch5_lsb = 0x8A;
const uint8_t adc_min_ch5_msb = 0x8B;
const uint8_t adc_min_ch6_lsb = 0x8C;
const uint8_t adc_min_ch6_msb = 0x8D;
const uint8_t adc_min_ch7_lsb = 0x8E;
const uint8_t adc_min_ch7_msb = 0x8F;
const uint8_t adc_recent_ch0_lsb = 0xA0;
const uint8_t adc_recent_ch0_msb = 0xA1;
const uint8_t adc_recent_ch1_lsb = 0xA2;
const uint8_t adc_recent_ch1_msb = 0xA3;
const uint8_t adc_recent_ch2_lsb = 0xA4;
const uint8_t adc_recent_ch2_msb = 0xA5;
const uint8_t adc_recent_ch3_lsb = 0xA6;
const uint8_t adc_recent_ch3_msb = 0xA7;
const uint8_t adc_recent_ch4_lsb = 0xA8;
const uint8_t adc_recent_ch4_msb = 0xA9;
const uint8_t adc_recent_ch5_lsb = 0xAA;
const uint8_t adc_recent_ch5_msb = 0xAB;
const uint8_t adc_recent_ch6_lsb = 0xAC;
const uint8_t adc_recent_ch6_msb = 0xAD;
const uint8_t adc_recent_ch7_lsb = 0xAE;
const uint8_t adc_recent_ch7_msb = 0xAF;
const uint8_t adc_rms_config = 0xC0;
const uint8_t adc_rms_lsb = 0xC1;
const uint8_t adc_rms_msb = 0xC2;
const uint8_t adc_gpo0_trig_event_sel = 0xC3;
const uint8_t adc_gpo1_trig_event_sel = 0xC5;
const uint8_t adc_gpo2_trig_event_sel = 0xC7;
const uint8_t adc_gpo3_trig_event_sel = 0xC9;
const uint8_t adc_gpo4_trig_event_sel = 0xCB;
const uint8_t adc_gpo5_trig_event_sel = 0xCD;
const uint8_t adc_gpo6_trig_event_sel = 0xCF;
const uint8_t adc_gpo7_trig_event_sel = 0xD1;
const uint8_t adc_gpo_value_zcd_config_ch0_ch3 = 0xE3;
const uint8_t adc_gpo_value_zcd_config_ch4_ch7 = 0xE4;
const uint8_t adc_gpo_zcd_update_en = 0xE7;
const uint8_t adc_gpo_trigger_config = 0xE9;
const uint8_t adc_gpo_value_trig = 0xEB;

//adc i2c opcodes
const uint8_t adc_op_single_read = 0x10;
const uint8_t adc_op_single_write = 0x00;
const uint8_t adc_op_set_bit = 0x18;
const uint8_t adc_op_clr_bit = 0x20;
const uint8_t adc_op_continuous_read = 0x30;
const uint8_t adc_op_continuous_write = 0x28;

//adc ch config values
//adc_chX_high_treshold 12bits max defult 16383
//adc_chX_low_treshold 12bits max defult 0
//adc_chX_event_count 4bits max defult 0 number of events that pass the threshold values before the event flag is rased
//adc_chX_hysteresis 4bits max defult 0
const uint16_t adc_ch0_high_threshold = 0b111111111111;
const uint16_t adc_ch0_low_threshold = 0b0;
const uint8_t adc_ch0_event_count = 0b0;
const uint8_t adc_ch0_hysteresis = 0b0;
const uint16_t adc_ch1_high_threshold = 0b111111111111;
const uint16_t adc_ch1_low_threshold = 0b0;
const uint8_t adc_ch1_event_count = 0b0;
const uint8_t adc_ch1_hysteresis = 0b0;
const uint16_t adc_ch2_high_threshold = 0b111111111111;
const uint16_t adc_ch2_low_threshold = 0b0;
const uint8_t adc_ch2_event_count = 0b0;
const uint8_t adc_ch2_hysteresis = 0b0;
const uint16_t adc_ch3_high_threshold = 0b111111111111;
const uint16_t adc_ch3_low_threshold = 0b0;
const uint8_t adc_ch3_event_count = 0b0;
const uint8_t adc_ch3_hysteresis = 0b0;
const uint16_t adc_ch4_high_threshold = 0b111111111111;
const uint16_t adc_ch4_low_threshold = 0b0;
const uint8_t adc_ch4_event_count = 0b0;
const uint8_t adc_ch4_hysteresis = 0b0;
const uint16_t adc_ch5_high_threshold = 0b111111111111;
const uint16_t adc_ch5_low_threshold = 0b0;
const uint8_t adc_ch5_event_count = 0b0;
const uint8_t adc_ch5_hysteresis = 0b0;
const uint16_t adc_ch6_high_threshold = 0b111111111111;
const uint16_t adc_ch6_low_threshold = 0b0;
const uint8_t adc_ch6_event_count = 0b0;
const uint8_t adc_ch6_hysteresis = 0b0;
const uint16_t adc_ch7_high_threshold = 0b111111111111;
const uint16_t adc_ch7_low_threshold = 0b0;
const uint8_t adc_ch7_event_count = 0b0;
const uint8_t adc_ch7_hysteresis = 0b0;

enum adc_channel {
  ch0,
  ch1,
  ch2,
  ch3,
  ch4,
  ch5,
  ch6,
  ch7
};

//iox defines
const uint8_t iox_0_add = 0x20; //???? notshire about the addresess not shure they make sence
const uint8_t iox_1_add = 0x21;
const uint8_t iox_input_port_0 = 0x00;
const uint8_t iox_input_port_1 = 0x01;
const uint8_t iox_output_port_0 = 0x02;
const uint8_t iox_output_port_1 = 0x03;
const uint8_t iox_pol_inv_port_0 = 0x04;
const uint8_t iox_pol_inv_port_1 = 0x05;
const uint8_t iox_config_port_0 = 0x06;
const uint8_t iox_config_port_1 = 0x07;
const uint8_t iox_drive_strength_register_00 = 0x40;
const uint8_t iox_drive_strenght_register_01 = 0x41;
const uint8_t iox_drive_strenght_register_10 = 0x42;
const uint8_t iox_drive_strenght_register_11 = 0x43;
const uint8_t iox_in_latch_register_0 = 0x44;
const uint8_t iox_in_ltach_register_1 =0x45;
const uint8_t iox_pull_up_down_en_register_0 = 0x46;
const uint8_t iox_pull_up_down_en_register_1 = 0x47;
const uint8_t iox_pull_up_down_sel_register_0 = 0x48;
const uint8_t iox_pull_up_down_sel_register_1 = 0x49;
const uint8_t iox_int_mask_register_0 = 0x4a;
const uint8_t iox_int_mask_register_1 = 0x4b;
const uint8_t iox_int_stat_register_0 = 0x4c;
const uint8_t iox_int_stat_register_1 = 0x4d;
const uint8_t iox_out_port_config_register = 0x4f;

//struct setup for pin cals
enum in_out {
  in,       //input
  out,      //output
  bi_dir,   //bi-directional pin only used for i2c comms
  intr      //used for software interupts only works with onboard pins
};

struct pin {
  uint8_t mask;          //mask for iox
  int port;              //port on iox (can be 0 or 1 only)
  int iox_number;        //iox number
  int pin_number;        //pin number, for ESP-12F: GPIO#, for iox: phisical pin#
  in_out pin_mode;       //defines pinmode see enum above for deatails
  bool onboard;          //If true, IO is on ESP8266; if false, IO is on IO expander
  bool allow_interrupt;  //allow a given input pin to assert an interrupt only relivent for offboard pins 
  
};

//BE SHURE TO ADD PINS TO BOTH THE "pin" STRUCT AND THE "pin_names" ARRAY THEY MUST MATCH
//struct defines  {mask, port, iox#, pin, pin_mode, onboard, allow_interrupt}
struct pin sda {0x00, 0, 0, 4, bi_dir, true, false};
struct pin scl {0x00, 0, 0, 5, bi_dir, true, false};
struct pin onboard_led {0x00, 0, 0, 2, out, true, false};
struct pin can_rx {0x00, 0, 0, 12, in, true, false};
struct pin can_tx {0x00, 0, 0, 13, out, true, false};
struct pin can_silent {0x80, 1, 1, 20, out, false, false};
struct pin iox_0_int {0x00, 0, 1, 14, intr, true, true};
struct pin iox_1_int {0x80, 1, 0, 20, in, false, true};
struct pin pgood_21V {0x40, 1, 1, 19, in, false, false};
struct pin b_usbc_pgood {0x20, 1, 1, 18, in, false, true};
struct pin b_usbc_buck_en {0x08, 1, 1, 16, out, false, false};
struct pin b_usbc_5V_sel {0x02, 1, 1, 14, out, false, false};
struct pin b_usbc_9V_sel {0x01, 1, 1, 13, out, false, false};
struct pin b_usbc_12V_sel {0x80, 0, 1, 11, out, false, false};
struct pin b_usbc_15V_sel {0x40, 0, 1, 10, out, false, false};
struct pin b_usbc_20V_sel {0x20, 0, 1, 9, out, false, false};
struct pin f_usbc_pgood {0x10, 1, 1, 17, in, false, true};
struct pin f_usbc_buck_en {0x04, 1, 1, 15, out, false, false};
struct pin f_usbc_5V_sel {0x10, 0, 1, 8, out, false, false};
struct pin f_usbc_9V_sel {0x08, 0, 1, 7, out, false, false};
struct pin f_usbc_12V_sel {0x04, 0, 1, 6, out, false, false};
struct pin f_usbc_15V_sel {0x02, 0, 1, 5, out, false, false};
struct pin f_usbc_20V_sel {0x01, 0, 1, 4, out, false, false};
struct pin adc_alert {0x40, 1, 0, 19, in, false, false};
struct pin ufp_c_attach_0 {0x20, 1, 0, 18, out, false, false};
struct pin hub_vbus_det {0x10, 1, 0, 17, out, false, false};
struct pin dfp_c_attach_1 {0x08, 1, 0, 16, out, false, false};
struct pin disp_irq {0x04, 1, 0, 15, in, false, true};
struct pin unit_btn {0x02, 1, 0, 14, in, false, true};
struct pin src_btn {0x01, 1, 0, 13, in, false, true};

//pin struct names for auto pin init
struct pin* pin_names[] = {
  &sda,
  &scl,
  &onboard_led,
  &can_rx,
  &can_tx,
  &can_silent,
  &iox_0_int,
  &iox_1_int,
  &pgood_21V,
  &b_usbc_pgood,
  &b_usbc_buck_en,
  &b_usbc_5V_sel,
  &b_usbc_9V_sel,
  &b_usbc_12V_sel,
  &b_usbc_15V_sel,
  &b_usbc_20V_sel,
  &f_usbc_pgood,
  &f_usbc_buck_en,
  &f_usbc_5V_sel,
  &f_usbc_9V_sel,
  &f_usbc_12V_sel,
  &f_usbc_15V_sel,
  &f_usbc_20V_sel,
  &adc_alert,
  &ufp_c_attach_0,
  &hub_vbus_det,
  &dfp_c_attach_1,
  &disp_irq,
  &unit_btn,
  &src_btn,
} ;


//read write enum define for io_call function
enum read_write {
  read,
  write
};

//io_call high low input enum
enum high_low {
  high,
  low,
  read_mode
};

//7 seg front diplay defines
uint8_t disp_intense_defult = 0xff; //set this number in hex to set 7 segment display brightness

//disp addresses
const uint8_t disp_base_add = 0x00;
const uint8_t disp_add = 0x02;

//config registers
const uint8_t disp_decode_mode = 0x09;
const uint8_t disp_global_intensity = 0x0A;
const uint8_t disp_scan_limit = 0x0B;
const uint8_t disp_shutdown = 0x0C;
const uint8_t disp_self_add = 0x2D; 
const uint8_t disp_feature = 0x0E;
const uint8_t disp_test = 0x0F;
const uint8_t disp_dig01_int = 0x10;
const uint8_t disp_dig23_int = 0x11;
const uint8_t disp_dig45_int = 0x12;
const uint8_t disp_dig67_int = 0x13;

//digit write registers
const uint8_t disp_digit_0 = 0x01;
const uint8_t disp_digit_1 = 0x02;
const uint8_t disp_digit_2 = 0x03;
const uint8_t disp_digit_3 = 0x04;
const uint8_t disp_digit_4 = 0x05;
const uint8_t disp_digit_5 = 0x06;
const uint8_t disp_digit_6 = 0x07;
const uint8_t disp_digit_7 = 0x08;

//dig diag registers
const uint8_t disp_dig0_diag = 0x14;
const uint8_t disp_dig1_diag = 0x15;
const uint8_t disp_dig2_diag = 0x16;
const uint8_t disp_dig3_diag = 0x17;
const uint8_t disp_dig4_diag = 0x18;
const uint8_t disp_dig5_diag = 0x19;
const uint8_t disp_dig6_diag = 0x1A;
const uint8_t disp_dig7_diag = 0x1B;
const uint8_t disp_keya = 0x1C;
const uint8_t disp_keyb = 0x1D;

//shurtdown modes
const uint8_t disp_down_rst = 0x00;
const uint8_t disp_down = 0x80;
const uint8_t disp_up_rst = 0x01;
const uint8_t disp_up = 0x81;









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

//reads from the i2c ADC returns value in raw 16bit ADC counts
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

//display write command
//will only work with flaots and ints
void disp_write(float input) {
  
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


