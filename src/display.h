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

#ifndef display_defines_h
#define display_defines_h

#include <Arduino.h>

//display driver drightness var
const uint8_t disp_intense_defult = 0xFF; //set this number in hex to set 7 segment display brightness

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

//display digits 
const uint8_t disp_num_0 = 0b01111110;
const uint8_t disp_num_1 = 0b00110000;
const uint8_t disp_num_2 = 0b01101101;
const uint8_t disp_num_3 = 0b01111001;
const uint8_t disp_num_4 = 0b00110011;
const uint8_t disp_num_5 = 0b01011011;
const uint8_t disp_num_6 = 0b01011111;
const uint8_t disp_num_7 = 0b01110000;
const uint8_t disp_num_8 = 0b01111111;
const uint8_t disp_num_9 = 0b01111011;
const uint8_t disp_num_dp = 0b10000000;


//led control defines

enum led_on_off {
  on,
  off
};

struct leds {
  uint8_t mask;
  int digit;
};

static struct leds watts {0x40, 7};
static struct leds amps {0x20, 7};
static struct leds volts {0x10, 7};
static struct leds back_usb_c_power {0x08, 7};
static struct leds front_usb_c_power {0x04, 7};
static struct leds usb_a_power {0x02};
static struct leds total_system_power {0x01, 7};
static struct leds watts_10 {0x40, 6};
static struct leds watts_20 {0x20, 6};
static struct leds watts_40 {0x10, 6};
static struct leds watts_65 {0x08, 6};
static struct leds watts_100 {0x04, 6};

//function defines 
void disp_init();
void disp_blank();
void disp_bright(uint8_t desired_brightness);
void disp_write(float input);
void led_write (struct leds leds, enum led_on_off led_on_off);




#endif // display_defines_h