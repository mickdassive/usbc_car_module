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

#ifndef adc_defines_h
#define adc_defines_h

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

//adc defult window coparitor config values
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

#endif // adc_defines_h