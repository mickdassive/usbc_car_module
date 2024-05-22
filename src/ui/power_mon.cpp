//{usbc car module}
//{power_mon.cpp}
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

#ifndef power_mon_cpp
#define power_mon_cpp

#include <Arduino.h>
#include "power_mon.h"
#include "pd/pd_power_cont.h"
#include "adc.h"
#include "display.h"

/**
 * Calculates and displays the power values for a given zone and output type.
 *
 * @param zone The power monitoring zone to calculate and display the power values for.
 * @param v_a_w The type of power values to display (volts, amps, or watts).
 */
void power_mon_calc_and_display(power_mon_zones zone, power_mon_v_a_w v_a_w) {
    //init local vars
    uint16_t csp_adc_value = 0;
    float csp_volts = 0;
    uint16_t csn_adc_value = 0;
    float csn_volts = 0;
    float delta_volts = 0;
    float output_to_disp = 0;

    //turn on v/a/w leds
    if (v_a_w == volts) {
        disp_led_write(volts_led, on);
        disp_led_write(amps_led, off);
        disp_led_write(watts_led, off);
    } else if (v_a_w == amps) {
        disp_led_write(volts_led, off);
        disp_led_write(amps_led, on);
        disp_led_write(watts_led, off);
    } else if (v_a_w == watts) {
        disp_led_write(volts_led, off);
        disp_led_write(amps_led, off);
        disp_led_write(watts_led, on);
    }
    
    //zone select 
    if (zone == system_total) {
        //set zone leds
        disp_led_write(total_system_power_led, on);
        disp_led_write(front_usb_c_power_led, off);
        disp_led_write(back_usb_c_power_led, off);
        disp_led_write(usb_a_power_led, off);

        //read value of csp & csn
        csp_adc_value = adc_read(ch0);
        csn_adc_value = adc_read(ch1);

        //calculate voltage for each channel
        csp_volts = ((0.00005035 * csp_adc_value) * (power_mon_21v_r1 + power_mon_21v_r2)) / power_mon_21v_r2;
        csn_volts = ((0.00005035 * csn_adc_value) * (power_mon_21v_r1 + power_mon_21v_r2)) / power_mon_21v_r2;

        //calulate delta volts
        delta_volts = csp_volts - csn_volts;

        //selct calculation for given output type
        if (v_a_w == volts) {
            disp_write(csp_volts);
        } else if (v_a_w == amps) {
            output_to_disp = delta_volts / power_mon_21v_rs;
            disp_write(output_to_disp);
        } else if (v_a_w == watts) {
            output_to_disp = (delta_volts / power_mon_21v_rs) *  csp_volts;
            disp_write(output_to_disp);
        }

    } else if (zone == usb_a) {
        //set zone leds
        disp_led_write(total_system_power_led, off);
        disp_led_write(front_usb_c_power_led, off);
        disp_led_write(back_usb_c_power_led, off);
        disp_led_write(usb_a_power_led, on);

        //read value of csp & csn
        csp_adc_value = adc_read(ch2);
        csn_adc_value = adc_read(ch3);

        //calculate voltage for each channel
        csp_volts = ((0.00005035 * csp_adc_value) * (power_mon_5v_r1 + power_mon_5v_r2)) / power_mon_5v_r2;
        csn_volts = ((0.00005035 * csn_adc_value) * (power_mon_5v_r1 + power_mon_5v_r2)) / power_mon_5v_r2;

        //calulate delta volts
        delta_volts = csp_volts - csn_volts;

        //selct calculation for given output type
        if (v_a_w == volts) {
            disp_write(csp_volts);
        } else if (v_a_w == amps) {
            output_to_disp = delta_volts / power_mon_5v_rs;
            disp_write(output_to_disp);
        } else if (v_a_w == watts) {
            output_to_disp = (delta_volts / power_mon_5v_rs) * csp_volts;
            disp_write(output_to_disp);
        }

    } else if (zone == back_c) {
        //set zone leds
        disp_led_write(total_system_power_led, off);
        disp_led_write(front_usb_c_power_led, off);
        disp_led_write(back_usb_c_power_led, on);
        disp_led_write(usb_a_power_led, off);

        //read value of csp & csn
        csp_adc_value = adc_read(ch4);
        csn_adc_value = adc_read(ch5);

        //calculate voltage for each channel
        csp_volts = ((0.00005035 * csp_adc_value) * (power_mon_f_c_r1 + power_mon_f_c_r2)) / power_mon_f_c_r2;
        csn_volts = ((0.00005035 * csn_adc_value) * (power_mon_f_c_r1 + power_mon_f_c_r2)) / power_mon_f_c_r2;

        //calulate delta volts
        delta_volts = csp_volts - csn_volts;

        //selct calculation for given output type
        if (v_a_w == volts) {
            disp_write(csp_volts);
        } else if (v_a_w == amps) {
            output_to_disp = delta_volts / power_mon_f_c_rs;
            disp_write(output_to_disp);
        } else if (v_a_w == watts) {
            output_to_disp = (delta_volts / power_mon_f_c_rs) * csp_volts;
            disp_write(output_to_disp);
        }

    } else if (zone == front_c) {
        //set zone leds
        disp_led_write(total_system_power_led, off);
        disp_led_write(front_usb_c_power_led, on);
        disp_led_write(back_usb_c_power_led, off);
        disp_led_write(usb_a_power_led, off);

        //read value of csp & csn
        csp_adc_value = adc_read(ch6);
        csn_adc_value = adc_read(ch7);

        //calculate voltage for each channel
        csp_volts = ((0.00005035 * csp_adc_value) * (power_mon_b_c_r1 + power_mon_b_c_r2)) / power_mon_b_c_r2;
        csn_volts = ((0.00005035 * csn_adc_value) * (power_mon_b_c_r1 + power_mon_b_c_r2)) / power_mon_b_c_r2;

        //calulate delta volts
        delta_volts = csp_volts - csn_volts;

        //selct calculation for given output type
        if (v_a_w == volts) {
            disp_write(csp_volts);
        } else if (v_a_w == amps) {
            output_to_disp = delta_volts / power_mon_b_c_rs;
            disp_write(output_to_disp);
        } else if (v_a_w == watts) {
            output_to_disp = (delta_volts / power_mon_b_c_rs) * csp_volts;
            disp_write(output_to_disp);
        }

    }

    return;

}


#endif // power_mon_cpp