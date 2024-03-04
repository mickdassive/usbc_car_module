//{usbc car module}
//{main.cpp}
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

#ifndef pd_power_cont_cpp
#define pd_power_cont_cpp

#include <Arduino.h>
#include <Wire.h>
#include "io.h"
#include "adc.h"
#include "pd_phy.h"

//disabels given port output
void pd_power_cont_return_to_base_state (enum ufp_dfp ufp_dfp) {

    if (ufp_dfp == ufp) {
        //set adc threshold
        adc_threshold_set(ch4, 0xFFF, 0x0);
        adc_threshold_set(ch5, 0xFFF, 0x0);
        io_call(b_usbc_buck_en, write, low);
        io_call(b_usbc_20V_sel, write, low);
        io_call(b_usbc_15V_sel, write, low);
        io_call(b_usbc_12V_sel, write, low);
        io_call(b_usbc_9V_sel, write, low);
        io_call(b_usbc_5V_sel, write, low);
    } else if (ufp_dfp == dfp) {
        //set adc threshold
        adc_threshold_set(ch6, 0xFFF, 0x0);
        adc_threshold_set(ch7, 0xFFF, 0x0);
        io_call(f_usbc_buck_en, write, low);
        io_call(f_usbc_20V_sel, write, low);
        io_call(f_usbc_15V_sel, write, low);
        io_call(f_usbc_12V_sel, write, low);
        io_call(f_usbc_9V_sel, write, low);
        io_call(f_usbc_5V_sel, write, low); 
    }

    

    return;
}

//sets buck cotroler for a given port to output 5 volts
void pd_power_cont_en_vsafe5v (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        io_call(b_usbc_20V_sel, write, low);
        io_call(b_usbc_15V_sel, write, low);
        io_call(b_usbc_12V_sel, write, low);
        io_call(b_usbc_9V_sel, write, low);
        io_call(b_usbc_5V_sel, write, high);
        io_call(b_usbc_buck_en, write, high);
        //set adc thresholds
        adc_threshold_set(ch4, 600, 500);
        adc_threshold_set(ch5, 600, 500);
    } else if (ufp_dfp == dfp) {
        io_call(f_usbc_20V_sel, write, low);
        io_call(f_usbc_15V_sel, write, low);
        io_call(f_usbc_12V_sel, write, low);
        io_call(f_usbc_9V_sel, write, low);
        io_call(f_usbc_5V_sel, write, high);
        io_call(f_usbc_buck_en, write, high);
        //set adc thresholds
        adc_threshold_set(ch6, 600, 500);
        adc_threshold_set(ch7, 600, 500);
    }

    
}

//pd_power_cont_pgood determines if the current voltage for a given port is within 10% of what it shold be
//ufp_dfp: select port to read voltage from
//voltage: voltage that we are cheking for
//true = voltage good & within range
//false = voltage more than 10% out 
bool pd_power_cont_pgood (enum ufp_dfp ufp_dfp, int voltage) {
    //init local vars 
    int upper_valid_value = 0;
    int lower_valid_value = 0;
    int expected_voltage_after_devider = 0;
    int expected_voltage_in_counts = 0;

    //calculate the devider voltage
    expected_voltage_after_devider = ((voltage * 1000) / (1000 + 10000));

    //calculate expected counts
    expected_voltage_in_counts = (3.3 / expected_voltage_after_devider) * 65535;

    //calulate upper and lower limmits
    upper_valid_value = expected_voltage_in_counts * 1.1;
    lower_valid_value = expected_voltage_in_counts *0.9;

    if (ufp_dfp == ufp) {
        if (adc_read(ch4) > lower_valid_value && adc_read(ch4) < upper_valid_value) {
            return true;
        } else {
            return false;
        }
    } else if (ufp_dfp == dfp) {
        if (adc_read(ch6) > lower_valid_value && adc_read(ch6) < upper_valid_value) {
            return true;
        } else {
            return false;
        }
    }


}


//full voltage range check
//true = passed
//false = failed
bool pd_power_cont_self_check () {
    //init local vars
    int n_tests_passed = 0;

    io_call(f_usbc_5V_sel, write, high);
    io_call(f_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(dfp, 5)) {
        ++n_tests_passed;
    }
    io_call(f_usbc_buck_en, write, low);
    io_call(f_usbc_5V_sel, write, low);
    io_call(f_usbc_9V_sel, write, high);
    io_call(f_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(dfp, 9)) {
        ++n_tests_passed;
    }
    io_call(f_usbc_buck_en, write, low);
    io_call(f_usbc_9V_sel, write, low);
    io_call(f_usbc_12V_sel, write, high);
    io_call(f_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(dfp, 12)) {
        ++n_tests_passed;
    }
    io_call(f_usbc_buck_en, write, low);
    io_call(f_usbc_12V_sel, write, low);
    io_call(f_usbc_15V_sel, write, high);
    io_call(f_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(dfp, 15)) {
        ++n_tests_passed;
    }
    io_call(f_usbc_buck_en, write, low);
    io_call(f_usbc_15V_sel, write, low);
    io_call(f_usbc_20V_sel, write, high);
    io_call(f_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(dfp, 20)) {
        ++n_tests_passed;
    }
    io_call(f_usbc_buck_en, write, low);
    io_call(f_usbc_20V_sel, write, low);
    io_call(b_usbc_5V_sel, write, high);
    io_call(b_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(dfp, 5)) {
        ++n_tests_passed;
    }
    io_call(b_usbc_buck_en, write, low);
    io_call(b_usbc_5V_sel, write, low);
    io_call(b_usbc_9V_sel, write, high);
    io_call(b_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(ufp, 9)) {
        ++n_tests_passed;
    }
    io_call(b_usbc_buck_en, write, low);
    io_call(b_usbc_9V_sel, write, low);
    io_call(b_usbc_12V_sel, write, high);
    io_call(b_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(ufp, 12)) {
        ++n_tests_passed;
    }
    io_call(b_usbc_buck_en, write, low);
    io_call(b_usbc_12V_sel, write, low);
    io_call(b_usbc_15V_sel, write, high);
    io_call(b_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(ufp, 15)) {
        ++n_tests_passed;
    }
    io_call(b_usbc_buck_en, write, low);
    io_call(b_usbc_15V_sel, write, low);
    io_call(b_usbc_20V_sel, write, high);
    io_call(b_usbc_buck_en, write, high);
    delay (100);
    if (pd_power_cont_pgood(ufp, 20)) {
        ++n_tests_passed;
    }
    io_call(b_usbc_buck_en, write, low);
    io_call(b_usbc_20V_sel, write, low);

    pd_power_cont_return_to_base_state(ufp);
    pd_power_cont_return_to_base_state(dfp);

    //return test results
    if (n_tests_passed == 10) {
        return true;
    } else {
        return false;
    }

    
}


#endif // pd_power_cont_cpp