//{usbc car module}
//{hub.cpp}
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

#ifndef hub_cpp
#define hub_cpp

#include <Arduino.h>
#include <Wire.h>
#include "hub.h"


/**
 * Writes a 16-bit value to the hub register.
 * 
 * @param input The value to be written to the hub register.
 */
void hub_reg_write (uint16_t input) {
    //init local vars
    uint8_t hub_reg_msb = 0;
    uint8_t hub_reg_lsb = 0;

    hub_reg_lsb = input & 0x00FF;
    hub_reg_msb = (input >> 8) & 0x00FF;

    Wire.write(hub_reg_msb);
    Wire.write(hub_reg_lsb);
    return;
}

/**
 * Sends a reboot command to the hub.
 */
void hub_send_reboot() {
    Wire.beginTransmission(hub_addr);
    hub_reg_write(0x9936);
    Wire.write(0x00);
    Wire.endTransmission();
    return;
}

/**
 * Sends a USB attach signal to the hub.
 */
void hub_send_usb_attach() {
    Wire.beginTransmission(hub_addr);
    hub_reg_write(0xAA55);
    Wire.write(0x00);
    Wire.endTransmission();
    return;
}

/**
 * Sends a USB attach command with SMBus active to the hub.
 */
void hub_send_usb_attach_with_smbus_active() {
    Wire.beginTransmission(hub_addr);
    hub_reg_write(0xAA56);
    Wire.write(0x00);
    Wire.endTransmission();
    return;
}

/**
 * Sends a command to register access command to the hub.
 */
void hub_send_command_register_accsess_command() {
    Wire.beginTransmission(hub_addr);
    hub_reg_write(0x9937);
    Wire.write(0x00);
    Wire.endTransmission();
    return;
}

/**
 * Sends a write command to the hub to perform OTP (One-Time Programmable) write operation.
 */
void hub_send_otp_write() {
    Wire.beginTransmission(hub_addr);
    hub_reg_write(0x9933);
    Wire.write(0x00);
    Wire.endTransmission();
    return;
}

/**
 * Sends a command to the hub to read the OTP (One-Time Programmable) memory.
 */
void hub_send_otp_read() {
    Wire.beginTransmission(hub_addr);
    hub_reg_write(0x9934);
    Wire.write(0x00);
    Wire.endTransmission();
    return;
}

/**
 * Initializes the hub by sending commands to configure various registers.
 * This function sets the default values for different hub registers.
 * 
 */
void hub_init() {

    hub_send_command_register_accsess_command();

    //begin writeing defult vlaues to hub 
    //clock_ctl register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_clock_ctl);
    Wire.write(1);
    //prog guide page 15
    //(xtal_susp_dis, resv, resv, pll125_en, pll125_stable, rosc_en, pll60_en, resv)
    Wire.write(0b1000000);
    Wire.write(0x00);
    Wire.endTransmission();

    //util_config1 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_util_config1);
    Wire.write(1);
    //prog guide page 16
    //(resv, dev_reset, resv, resv, resv, spi_master_dis, resv, hub_resume_inhibit)
    Wire.write(0b0);
    Wire.write(0x00);
    Wire.endTransmission();

    //pf6_ctl register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_pf6_ctl);
    Wire.write(1);
    //prog guide page 26
    //(resv, resv, resv, resv, resv, b2, b1, b0)
    Wire.write(0b00000011);
    Wire.write(0x00);
    Wire.endTransmission();

    //pf8_ctl register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_pf8_ctl);
    Wire.write(1);
    //prog guide page 27
    //(resv, resv, resv, resv, resv, b2, b1, b0)
    Wire.write(0b00000010);
    Wire.write(0x00);
    Wire.endTransmission();

    //hub_cfg_1 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_hub_cfg_1);
    Wire.write(1);
    //prog guide page 30
    //(self_bus_power, vsm_disabel, hs_disabel, mtt_enabel, eop_disabel, current_sns_b1, current_sns_b0, port_pwr)
    Wire.write(0b11110011);
    Wire.write(0x00);
    Wire.endTransmission();

    //hub_cfg_2 register 
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_hub_cfg_2);
    Wire.write(1);
    //prog guide page 31
    //(resv, resv, oc_timer_b1, oc_timer_b0, compound, resv, resv, resv)
    Wire.write(0b00111000);
    Wire.write(0x00);
    Wire.endTransmission();

    //hub_cfg_3 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_hub_cfg_3);
    Wire.write(1);
    //prog guide page 32
    //(resv, resv, resv, resv, prtmap_en, bos_disable, resv, string_en)
    Wire.write(0b00000001);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb2_nrd register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb2_nrd);
    Wire.write(1);
    //prog guide page 33
    //(prt7, prt6, prt5, prt4, prt3, prt2, prt1, resv)
    Wire.write(0b01000000);
    Wire.write(0x00);
    Wire.endTransmission();

    //bc_en register 
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_bc_en);
    Wire.write(1);
    //prog guide page 35
    //(prt7, prt6, prt5, prt4, prt3, prt2, prt1, resv)
    Wire.write(0b11111110);
    Wire.write(0x00);
    Wire.endTransmission();

    //start_lockout_timer_reg register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_start_lockout_timer_reg);
    Wire.write(1);
    //prog guide page 35
    //time in ms to allow overcurrent events when a device is connected 
    Wire.write(hub_over_current_lockout_bypas_time);
    Wire.write(0x00);
    Wire.endTransmission();

    //prt_swap register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_prt_swap);
    Wire.write(1);
    //prog guide page 36
    //ports with swaped usb2.0 pairs
    //(prt7, prt6, prt5, prt4, prt3, prt2, prt1, prt0)
    Wire.write(0b01011100);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb2_prt_remap_12 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb2_prt_remap_12);
    Wire.write(1);
    //prog guide page 36
    Wire.write(0x21);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb2_prt_remap_34 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb2_prt_remap_34);
    Wire.write(1);
    //prog guide page 37
    Wire.write(0x43);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb2_prt_remap_56 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb2_prt_remap_56);
    Wire.write(1);
    //prog guide page 38
    Wire.write(0x65);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb2_prt_remap_7 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb2_prt_remap_7);
    Wire.write(1);
    //prog guide page 38
    Wire.write(0x07);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_hub_ctl register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_hub_ctl);
    Wire.write(1);
    //prog guide page 46
    //(resv, resv, scramble_en, gang_ovr_current, bus_powerd, resv, resv, resv)
    Wire.write(0b00100000);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_hub_ctl2 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_hub_ctl2);
    Wire.write(1);
    //prog guide page 46
    //(hub_ds_prop_rst_ctl, hub_u3_rmt_wkup_en, hub_u1_u2_exit_failed, hub_ping_to_500ms, hub_stall_ep0_halt, hub_ux_exit_ctrl, resv, usb3_hub_enable)
    Wire.write(0b11111100);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_hub_ctl3 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_hub_ctl3);
    Wire.write(1);
    //prog guide page 47
    //(hub_7port_2bytes, force_u1_u2_ff, hub_scaledown_b1, hub_scaledown_b0, disable_u1_u2, disable_p3, usb3_bias_on, usb3_xtal_on)
    Wire.write(0b00001101);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_hub_ctl4 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_hub_ctl4);
    Wire.write(1);
    //prog guide page 48
    //(resv, resv, usb3_sc_timer_b1, usb3_sc_timer_b0, usb3_gang_pwr_en, hub_dis_dsport_ecr, hub_dis_vbus_off_ecr, hub_ds_power_sw_en)
    Wire.write(0b00110001);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_hub_ctl5 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_hub_ctl5);
    Wire.write(1);
    //prog guide page 49
    //(resv, disable_hp_pending_fix, us_set_ftr_fc_en_b1, us_set_ftr_fc_en_b0, resv, link_ulor2_ul_timeout_wkp_en, ds_link_config_fail_ctrl, us_linkconfig_fail_ctrl)
    Wire.write(0b00000000);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_prt_remap register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_prt_remap_en);
    Wire.write(1);
    //prog guide page 52
    Wire.write(0x01);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_prt_remap_p1_p2 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_prt_remap_p1_p2);
    Wire.write(1);
    //prog guide page 53
    Wire.write(0x21);      
    Wire.write(0x00);                        
    Wire.endTransmission();

    //usb3_prt_remap_p3_p4 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_prt_remap_p3_p4);
    Wire.write(1);
    //prog guide page 53
    Wire.write(0x43);       
    Wire.write(0x00);                       
    Wire.endTransmission();

    //usb3_prt_remap_p5_p6 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_prt_remap_p5_p6);
    Wire.write(1);
    //prog guide page 53
    Wire.write(0x65);         
    Wire.write(0x00);                     
    Wire.endTransmission();

    //usb3_prt_remap_p7 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_prt_remap_p7);
    Wire.write(1);
    //prog guide page 54
    Wire.write(0x07);          
    Wire.write(0x00);                    
    Wire.endTransmission();

    //usb3_port_split_en register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_port_split_en);
    Wire.write(1);
    //prog guide page 63
    //(prt7, prt6, prt5, prt4, prt3, prt2, prt1, resv)
    Wire.write(0b01000000);
    Wire.write(0x00);
    Wire.endTransmission();

    //flex_cfg1 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_flex_cfg1);
    Wire.write(1);
    //prog guide page 63
    //(chng_pin_funct, flexconnect, dis_p5, dis_p4, dis_p3, dis_p2, dis_p1, resv)
    Wire.write(0b10000000);
    Wire.write(0x00);
    Wire.endTransmission();

    //flex_cfg2 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_flex_cfg2);
    Wire.write(1);
    //prog guide page 63
    //(resv, dcp_en, resv, resv, resv, hd_timer_b2, hd_timer_b1, hd_timer_b0)
    //wait 1 second for flexconnect if not return to base state
    Wire.write(0b11000100);
    Wire.write(0x00);
    Wire.endTransmission();

    //hfc_enable register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_hfc_en);
    Wire.write(1);
    //prog guide page 66
    Wire.write(0x01);
    Wire.write(0x00);
    Wire.endTransmission();

    //prtpwr6_usb3_split
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_prtpwr6_usb3_split);
    Wire.write(1);
    //prog guide page 71
    Wire.write(0x44);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_port_split_timeout
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_port_split_timeout);
    Wire.write(1);
    //prog guide page 72
    Wire.write(0x06);
    Wire.write(0x00);
    Wire.endTransmission();

    //bc_cfg_p1 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_bc_cfg_p1);
    Wire.write(1);
    //prog guide page 73
    //(bcdcp_dis_prts_en, resv, bc12_cdcp, china, resv, se1_mode_b1, se1_mode_b0, bc_en)
    Wire.write(0b11100101);
    Wire.write(0x00);
    Wire.endTransmission();

    //bc_cfg_p2 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_bc_cfg_p2);
    Wire.write(1);
    //prog guide page 73
    //(bcdcp_dis_prts_en, resv, bc12_cdcp, china, resv, se1_mode_b1, se1_mode_b0, bc_en)
    Wire.write(0b11100101);
    Wire.write(0x00);
    Wire.endTransmission();

    //bc_cfg_p3 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_bc_cfg_p3);
    Wire.write(1);
    //prog guide page 74
    //(bcdcp_dis_prts_en, resv, bc12_cdcp, china, resv, se1_mode_b1, se1_mode_b0, bc_en)
    Wire.write(0b11100101);
    Wire.write(0x00);
    Wire.endTransmission();

    //bc_cfg_p4 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_bc_cfg_p4);
    Wire.write(1);
    //prog guide page 75
    //(bcdcp_dis_prts_en, resv, bc12_cdcp, china, resv, se1_mode_b1, se1_mode_b0, bc_en)
    Wire.write(0b11100101);
    Wire.write(0x00);
    Wire.endTransmission();

    //bc_cfg_p5 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_bc_cfg_p5);
    Wire.write(1);
    //prog guide page 75
    //(bcdcp_dis_prts_en, resv, bc12_cdcp, china, resv, se1_mode_b1, se1_mode_b0, bc_en)
    Wire.write(0b11100101);
    Wire.write(0x00);
    Wire.endTransmission();

    //bc_cfg_p6 register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_bc_cfg_p6);
    Wire.write(1);
    //prog guide page 76
    //(bcdcp_dis_prts_en, resv, bc12_cdcp, china, resv, se1_mode_b1, se1_mode_b0, bc_en)
    Wire.write(0b11100101);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_nbr_prts register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_nbr_prts);
    Wire.write(1);
    //prog guide page 80
    Wire.write(0x07);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_nrd register
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_nrd);
    Wire.write(1);
    //prog guide page 80
    //(prt7, prt6, prt5, prt4, prt3, prt2, prt1, resv)
    Wire.write(0b11000000);
    Wire.write(0x00);
    Wire.endTransmission();

    //hub_cmd_stat register
    //this write moves the hub from config mode to run mode
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_hub_cmd_stat);
    Wire.write(1);
    //prog guide page 39
    Wire.write(0x01);
    Wire.write(0x00);
    Wire.endTransmission();

    //usb3_hub_ctl2 register
    //starts usb3 hub fugtionality
    Wire.beginTransmission(hub_addr);
    hub_reg_write(hub_reg_usb3_hub_ctl2);
    Wire.write(1);
    //prog guide page 46
    //(hub_ds_prop_rst_ctl, hub_u3_rmt_wkup_en, hub_u1_u2_exit_failed, hub_ping_to_500ms, hub_stall_ep0_halt, hub_ux_exit_ctrl, resv, usb3_hub_enable)
    Wire.write(0b11111101);
    Wire.write(0x00);
    Wire.endTransmission();

    //send config register access command
    hub_send_command_register_accsess_command();

    //allow i2c to stay active in runtime
    hub_send_usb_attach_with_smbus_active();



    return;
}


#endif // hub_cpp