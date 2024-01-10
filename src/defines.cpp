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


//adc defines
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

//io_call struct setup
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
//io_call struct defines  {mask, port, iox#, pin, pin_mode, onboard, allow_interrupt}
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
struct pin f_usbc_15V_sel {0x02, 0, 1, 5, out, false, false};   // all these pin positions are gunna be wrong im just gunna wait till im done with the hrdware desighn to fix them
struct pin f_usbc_20V_sel {0x01, 0, 1, 4, out, false, false};
struct pin adc_alert {0x40, 1, 0, 19, in, false, false};
struct pin ufp_c_attach_0 {0x20, 1, 0, 18, out, false, false};
struct pin hub_vbus_det {0x10, 1, 0, 17, out, false, false};
struct pin dfp_c_attach_1 {0x08, 1, 0, 16, out, false, false};
struct pin disp_irq {0x04, 1, 0, 15, in, false, true};
struct pin unit_btn {0x02, 1, 0, 14, in, false, true};
struct pin src_btn {0x01, 1, 0, 13, in, false, true};
struct pin mode_btn {0x80, 0, 0, 11, in, false, true};
struct pin iox_0_p_0_0 {0X01, 0, 0, 4, in, false, false};
struct pin iox_0_p_0_1 {0X02, 0, 0, 5, in, false, false};

//io_call pin struct names for auto pin init
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
  &mode_btn,
  &iox_0_p_0_0,
  &iox_0_p_0_1,
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
struct leds {
  uint8_t mask;
  led_location location;
};

struct leds amps {0x40, dig_7};
struct leds watts {0x80, dig_7};
struct leds volts {0x20, dig_7};
struct leds usb_c_back {0x10, dig_7};
struct leds usb_c_front {0x08, dig_7};
struct leds usb_a {0x04, dig_7};
struct leds system_power {0x02, dig_7};
struct leds watts_10 {0x80, dig_6};
struct leds watts_20 {0x40, dig_6};
struct leds watts_40 {0x20, dig_6};
struct leds watts_65 {0x10, dig_6};
struct leds watts_100 {0x08, dig_6};


//led on/off enum
enum led_on_off {
  on,
  off
};

