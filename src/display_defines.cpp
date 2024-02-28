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

#include <Arduino.h>

//display driver drightness var
uint8_t disp_intense_defult = 0xff; //set this number in hex to set 7 segment display brightness

//display driver addres
const uint8_t disp_base_add = 0x00;
const uint8_t disp_add = 0x02;

//display driver config registers
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

//display driver digit write registers
const uint8_t disp_digit_0 = 0x01;
const uint8_t disp_digit_1 = 0x02;
const uint8_t disp_digit_2 = 0x03;
const uint8_t disp_digit_3 = 0x04;
const uint8_t disp_digit_4 = 0x05;
const uint8_t disp_digit_5 = 0x06;
const uint8_t disp_digit_6 = 0x07;
const uint8_t disp_digit_7 = 0x08;

//display driver dig diag registers
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

//display driver shutdown modes
const uint8_t disp_down_rst = 0x00;
const uint8_t disp_down = 0x80;
const uint8_t disp_up_rst = 0x01;
const uint8_t disp_up = 0x81;


//led control defines

enum led_location {
  dig_7,
  dig_6
};

enum led_names {
  amps,
  watts,
  volts,
  usb_c_back,
  usb_c_front,
  usb_a,
  system_power,
  watts_10,
  watts_20,
  watts_40,
  watts_65,
  watts_100
};

struct leds {
  led_names name;
  uint8_t mask;
  led_location location;
};

struct leds amps {amps, 0x40, dig_7};
struct leds watts {watts, 0x80, dig_7};
struct leds volts {volts, 0x20, dig_7};
struct leds usb_c_back {usb_c_back, 0x10, dig_7};
struct leds usb_c_front {usb_c_front, 0x08, dig_7};
struct leds usb_a {usb_a, 0x04, dig_7};
struct leds system_power {system_power, 0x02, dig_7};
struct leds watts_10 {watts_10, 0x80, dig_6};
struct leds watts_20 {watts_20, 0x40, dig_6};
struct leds watts_40 {watts_40, 0x20, dig_6};
struct leds watts_65 {watts_65, 0x10, dig_6};
struct leds watts_100 {watts_100, 0x08, dig_6};


//led on/off enum
enum led_on_off {
  on,
  off
};

