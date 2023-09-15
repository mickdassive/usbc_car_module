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
// usbc car module
// v0.1
// 15/09/2023
// Tokyo Andreana


#include <Arduino.h>
#include <Wire.h>
#include <iostream>


//iox defines
const uint8_t iox_0_add = 0x00;
const uint8_t iox_1_add = 0x20;
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
  in,
  out
};

struct pin {
  uint8_t mask;    //mask for iox
  int port;        //port on iox (can be 0 or 1 only)
  int iox_number;  //iox number
  int pin_number;  //pin number 
  in_out pin_mode;  //defines weather a given pin is an out put or an input
  bool onboard;    //If true, IO is on ESP8266; if false, IO is on IO expander
  
};

//struct defines  {mask, port, iox#, pin, pin_mode, onboard}
struct pin io_int = {0b0, 0, 0, 14, true};
struct pin sda = {0b0, 0, 0, 4, true};
struct pin scl = {0b0, 0, 0, 2, true};
struct pin htr_1 = {0b0, 0, 0, 13, true};
struct pin htr_2 = {0b0, 0, 0, 12, true};
struct pin fan = {0b0, 0, 0, 5, true};
struct pin ovlight = {0b10000000, 1, 20, false};
struct pin wifi_led_g = {0b00001000, 1, 16, false};
struct pin wifi_led_or = {0b00000100, 1, 15, false};
struct pin wifi_led_r = {0b00000010, 1, 14, false};
struct pin status_led_g = {0b00000001, 1, 13, false};
struct pin status_led_r = {0b10000000, 0, 11, false};
struct pin up_btn = {0b01000000, 1, 19, false};
struct pin dwn_btn = {0b00100000, 1, 18, false};
struct pin ent_btn = {0b00010000, 1, 17, false};
struct pin io_00 = {0b00000001, 0, 4, false};
struct pin io_01 = {0b00000010, 0, 5, false};
struct pin io_02 = {0b00000100, 0, 6, false};
struct pin io_03 = {0b00001000, 0, 7, false};
struct pin io_04 = {0b00010000, 0, 8, false};
struct pin io_05 = {0b00100000, 0, 9, false};
struct pin io_06 = {0b01000000, 0, 10, false};

// read write enum define for io_call function
enum read_write {
  read,
  write
};

// io_call high low input enum
enum high_low {
  high,
  low,
  read_mode
};

// reads current pin state of the io expander outputs
// port: port of iox to read
// iox_num: number of iox to read from

// reads current pin state of the io expander outputs
// port: port of iox to read
// iox_num: number of iox to read from
uint8_t read_current_io_state(int port, int iox_num) {
  uint8_t iox_address = (iox_num == 0) ? iox_0_add : iox_1_add;
  uint8_t iox_output_register = (port == 0) ? iox_output_port_0 : iox_output_port_1;

  Wire.beginTransmission(iox_address);
  Wire.write(iox_output_register);
  Wire.endTransmission();

  Wire.requestFrom(iox_address, 1);
  return Wire.read();
}

// io_call function
// This function is used to read or write digital values to onboard or offboard IOs.
// pin_needed: a pin struct that defines the pin being read/written to
// read_write: a read_write enum value that specifies if the function should read or write
// high_low: a high_low enum value that specifies if the function should write a high or low value
int io_call(struct pin pin_needed, enum read_write read_write, enum high_low high_low) {

  

  // Check if the pin is onboard or offboard
  if (pin_needed.onboard == true) {
    // If the pin is onboard, check if we need to read or write
    if (read_write == write) {
      // If we need to write, check if we need to write high or low
      if (high_low == high) { // onborad digital write
        digitalWrite(pin_needed.pin_number, HIGH);
        
      } else if (high_low == low) { // onborad digital write low
        digitalWrite (pin_needed.pin_number, LOW);
        
      } else {
         // If high_low is not high or low, do something here (error handling?)
      }
    } else if (read_write == read) { //onboard digital read
      int read_value = digitalRead(pin_needed.pin_number);
      return(read_value);
    } else {
       // If read_write is not read or write, do something here (error handling?)
    }

  } else if (pin_needed.onboard == false){ //digital write to io expander
    
    if (read_write == write) {  // chek to see if we are writeing the the ioxepander

      // int local varibels
      uint8_t current = read_current_io_state(pin_needed.port, pin_needed.iox_number); // read and store the current state of the output register of the the given pin
      uint8_t output = 0b00000000;
      uint8_t mask_not = ~pin_needed.mask;

      // bitwise logic to ether set high or low a given pin
      if (high_low == high) {
        output = current | pin_needed.mask;
      } else if (high_low == low){
        output = current & mask_not;
      }

      // begin write to iox
      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);
      } else {
        Wire.beginTransmission(iox_1_add);
      }
        
      // write to slected port
      if (pin_needed.port = 0) {
        Wire.write(iox_output_port_0);
      } else {
        Wire.write(iox_output_port_1);
      }
      
      Wire.write(output);

      Wire.endTransmission();

    } else if (read_write == read) {  // check to see if we are reading from the io expanders input
      
      // init local varibles
      uint8_t readval = 0b00000000;
      uint8_t output_byte = 0b00000000;
      
      // select witch iox to red from
      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);
      } else {
        Wire.beginTransmission(iox_1_add);
      }
      
      // selcect port based on given pin
      if (pin_needed.port == 0) {
        Wire.write(iox_input_port_0);
      } else if (pin_needed.port == 1) {
        Wire.write(iox_input_port_1);
      }

      Wire.endTransmission();

      // begin reading from selcted iox
      if (pin_needed.iox_number == 0) {
        Wire.requestFrom(iox_0_add, 1);
      } else {
        Wire.requestFrom(iox_1_add, 1);
      }
      
      //read the given value from the i2c bus
      readval = Wire.read();

      // isolate the indivdual bit of the given pin bsed on its mask
      output_byte = readval & pin_needed.mask;

      // return high or low based on wether or not the byte is more than 0
      if (output_byte == 0) {
        return (LOW);
      } else {
        return (HIGH);
      }
      
    }

  } else { // return if input bad
    return 0;
  }
  return 0;

}


void setup() {
  
}

void loop() {
}

