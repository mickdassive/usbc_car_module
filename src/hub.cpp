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
void hub_send_reset() {
    Wire.beginTransmission(hub_addr);
    hub_reg_write(0x9936);
    Wire.write(0x00);
    Wire.endTransmission();
    return;
}

/**
 * Sends a USB attach signal to the hub.
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
void hub_send_command_register_access_command() {
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

    hub_send_command_register_access_command();

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
    //(self_bus_power, vsm_disable, hs_disable, mtt_enable, eop_disable, current_sns_b1, current_sns_b0, port_pwr)
    Wire.write(0b11110011);
    Wire.write(0x00);
    Wire.endTransmission();
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
    hub_send_command_register_access_command();

    //allow i2c to stay active in runtime
    hub_send_usb_attach_with_smbus_active();



    return;
}


#endif // hub_cpp