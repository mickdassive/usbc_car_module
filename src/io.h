//{usbc car module}
//{io.h}
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

#ifndef io_h
#define io_h

#include <Arduino.h>

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
  intr,     //used for software interupts only works with onboard pins
  empty_pin //empty for empty pin object
};

struct pin {
  char pin_ident;        //name of pin uneque identifyer for eatch pin only used in itrupt handeler
  uint8_t mask;          //mask for iox
  int port;              //port on iox (can be 0 or 1 only)
  int iox_number;        //iox number
  int pin_number;        //pin number, for ESP-12F: GPIO#, for iox: phisical pin#
  in_out pin_mode;       //defines pinmode see enum above for deatails
  bool onboard;          //If true, IO is on ESP8266; if false, IO is on IO expander
  bool allow_interrupt;  //allow a given input pin to assert an interrupt only relivent for offboard pins 
  
};

//BE SHURE TO ADD PINS TO BOTH THE "pin" STRUCT AND THE "pin_names" ARRAY THEY MUST MATCH
//io_call struct defines  {pin_ident, mask, port, iox#, pin, pin_mode, onboard, allow_interrupt}
static struct pin sda {'a', 0x00, 0, 0, 4, bi_dir, true, false};
static struct pin scl {'b', 0x00, 0, 0, 5, bi_dir, true, false};
static struct pin onboard_led {'c', 0x00, 0, 0, 2, out, true, false};
static struct pin can_rx {'d', 0x00, 0, 0, 12, in, true, false};
static struct pin can_tx {'e', 0x00, 0, 0, 13, out, true, false};
static struct pin can_silent {'f', 0x02, 0, 0, 5, out, false, false};
static struct pin iox_0_int {'g', 0x00, 0, 1, 14, intr, true, true};
static struct pin iox_1_int {'h', 0x01, 0, 0, 4, in, false, true};
static struct pin dfp_cc_orient {'i', 0x80, 0, 0, 8, out, false, false};
static struct pin b_usbc_pgood {'j', 0x20, 0, 1, 9, in, false, true};
static struct pin b_usbc_buck_en {'k', 0x01, 1, 1, 13, out, false, false};
static struct pin b_usbc_5V_sel {'l', 0x02, 1, 1, 14, out, false, false};
static struct pin b_usbc_9V_sel {'m', 0x04, 1, 1, 15, out, false, false};
static struct pin b_usbc_12V_sel {'n', 0x08, 1, 1, 16, out, false, false};
static struct pin b_usbc_15V_sel {'o', 0x10, 1, 1, 17, out, false, false};
static struct pin b_usbc_20V_sel {'p', 0x20, 1, 1, 18, out, false, false};
static struct pin f_usbc_pgood {'q', 0x40, 0, 1, 10, in, false, true};
static struct pin f_usbc_buck_en {'r', 0x80, 0, 1, 11, out, false, false};
static struct pin f_usbc_5V_sel {'s', 0x01, 0, 1, 4, out, false, false};
static struct pin f_usbc_9V_sel {'t', 0x02, 0, 1, 5, out, false, false};
static struct pin f_usbc_12V_sel {'u', 0x04, 0, 1, 6, out, false, false};
static struct pin f_usbc_15V_sel {'v', 0x08, 0, 1, 7, out, false, false};
static struct pin f_usbc_20V_sel {'w', 0x10, 0, 1, 8, out, false, false};
static struct pin adc_alert {'x', 0x80, 1, 1, 20, in, false, true};
static struct pin ufp_c_attach_0 {'y', 0x80, 0, 0, 11, out, false, false};
static struct pin hub_vbus_det {'z', 0x40, 0, 0, 10, out, false, false};
static struct pin dfp_c_attach_1 {'1', 0x20, 0, 0, 9, out, false, false};
static struct pin disp_irq {'2', 0x10, 1, 0, 17, in, false, true};
static struct pin unit_btn {'3', 0x40, 1, 0, 19, in, false, true};
static struct pin src_btn {'4', 0x80, 1, 0, 20, in, false, true};
static struct pin mode_btn {'5', 0x20, 0, 0, 18, in, false, true};
static struct pin iox_0_p_0_0 {'6', 0X08, 0, 0, 7, in, false, false};
static struct pin iox_0_p_0_1 {'7', 0X04, 0, 0, 6, in, false, false};
static struct pin ufp_dbgacc {'8', 0x04, 1, 0, 15, in, false, false};
static struct pin dfp_dbgacc {'9', 0x80, 1, 1, 19, in, false, false};
static struct pin ufp_alert_n {'0', 0x02, 1, 0, 14, in, false, true};
static struct pin dfp_alert_n {'?', 0x01, 1, 0, 13, in, false, true};
static struct pin ufp_cc_orient {'~', 0x10, 0, 0, 8, out, false, false};
static struct pin empty_struct_pin {'!', 0x0, 0, 0, 0, empty_pin, false, false};


//io_call pin struct names for auto pin init
static struct pin* pin_names[] = {
  &sda,
  &scl,
  &onboard_led,
  &can_rx,
  &can_tx,
  &can_silent,
  &iox_0_int,
  &iox_1_int,
  &dfp_cc_orient,
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
  &ufp_dbgacc,
  &dfp_dbgacc,
  &ufp_alert_n,
  &dfp_alert_n,
  &ufp_cc_orient,
  &empty_struct_pin

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

//iox intrupt register values
extern uint8_t iox_0_port_0_interrupt;
extern uint8_t iox_0_port_1_interrupt;
extern uint8_t iox_1_port_0_interrupt;
extern uint8_t iox_1_port_1_interrupt;
extern bool io_interupt_flag;

//buttion info defines
extern bool io_unit_btn_pressed;
extern unsigned long io_unit_btn_pressed_time;
extern bool io_mode_btn_pressed;
extern unsigned long io_mode_btn_pressed_time;
extern bool io_src_btn_pressed;
extern unsigned long io_src_btn_pressed_time;
 
//fuction defines
uint8_t io_read_current_io_state(int port, int iox_num);
int io_call(struct pin pin_needed, enum read_write read_write, enum high_low high_low);
void io_gpio_init();
struct pin io_determine_intrupt_source();
void io_pin_intrupt_flagger ();
void io_intrupt_handeler ();



#endif // io_h
