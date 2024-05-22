//{usbc car module}
//{pd_power_cont.cpp}
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

//port info vars 
int pd_power_cont_ufp_current_voltage = 0;
int pd_power_cont_dfp_current_voltage = 0;
bool pd_power_cont_ufp_allow_output = false;
bool pd_power_cont_dfp_allow_output = false;


/**
 * @brief Resets the power control state to the base state for the specified UFP/DFP.
 *
 * This function resets the power control state to the base state for the specified UFP/DFP.
 * It sets the current voltage to 0, clears the ADC thresholds, and writes low values to various IO pins.
 *
 * @param ufp_dfp The UFP/DFP type (ufp or dfp).
 */
void pd_power_cont_return_to_base_state (enum ufp_dfp ufp_dfp) {

    if (ufp_dfp == ufp) {
        //set current voltage
        pd_power_cont_ufp_current_voltage = 0;
        //clear adc threshold
        adc_threshold_set(ch4, 0xFFF, 0x0);
        adc_threshold_set(ch5, 0xFFF, 0x0);
        io_call(b_usbc_buck_en, write, low);
        io_call(b_usbc_20V_sel, write, low);
        io_call(b_usbc_15V_sel, write, low);
        io_call(b_usbc_12V_sel, write, low);
        io_call(b_usbc_9V_sel, write, low);
        io_call(b_usbc_5V_sel, write, low);
    } else if (ufp_dfp == dfp) {
        //set current voltage
        pd_power_cont_dfp_current_voltage = 0;
        //clear adc threshold
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

/**
 * Enables the VSafe5V power control for the specified UFP/DFP mode.
 *
 * @param ufp_dfp The UFP/DFP mode to enable VSafe5V power control for.
 */
void pd_power_cont_en_vsafe5v (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        if (pd_power_cont_ufp_allow_output != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(ufp);
        } else {
            //set current voltage
            pd_power_cont_ufp_current_voltage = 5;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch4, 0xFFF, 0x0);
            adc_threshold_set(ch5, 0xFFF, 0x0);
            io_call(b_usbc_buck_en, write, low);
            io_call(b_usbc_20V_sel, write, low);
            io_call(b_usbc_15V_sel, write, low);
            io_call(b_usbc_12V_sel, write, low);
            io_call(b_usbc_9V_sel, write, low);
            io_call(b_usbc_5V_sel, write, high);
            io_call(b_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch4, 600, 500);
            adc_threshold_set(ch5, 600, 500);
        }
        
    } else if (ufp_dfp == dfp) {
        if (pd_power_cont_ufp_allow_output != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(dfp);
        } else {
            //set current voltage
            pd_power_cont_dfp_current_voltage = 5;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch6, 0xFFF, 0x0);
            adc_threshold_set(ch7, 0xFFF, 0x0);
            io_call(f_usbc_buck_en, write, low);
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
    return;    
}

/**
 * Enables the power control for 9V voltage level based on the specified UFP/DFP mode.
 *
 * @param ufp_dfp The UFP/DFP mode (ufp or dfp).
 */
void pd_power_cont_en_9v (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        if (pd_power_cont_ufp_allow_output != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(ufp);
        } else {
            //set current voltage
            pd_power_cont_ufp_current_voltage = 9;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch4, 0xFFF, 0x0);
            adc_threshold_set(ch5, 0xFFF, 0x0);
            io_call(b_usbc_buck_en, write, low);
            io_call(b_usbc_20V_sel, write, low);
            io_call(b_usbc_15V_sel, write, low);
            io_call(b_usbc_12V_sel, write, low);
            io_call(b_usbc_5V_sel, write, low);
            io_call(b_usbc_9V_sel, write, high);
            io_call(b_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch4, 1100, 950);
            adc_threshold_set(ch5, 1100, 950);
        }
    } else if (ufp_dfp == dfp) {
        if (pd_power_cont_ufp_allow_output != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(dfp);
        } else {
            //set current voltage
            pd_power_cont_dfp_current_voltage = 9;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch6, 0xFFF, 0x0);
            adc_threshold_set(ch7, 0xFFF, 0x0);
            io_call(f_usbc_buck_en, write, low);
            io_call(f_usbc_20V_sel, write, low);
            io_call(f_usbc_15V_sel, write, low);
            io_call(f_usbc_12V_sel, write, low);
            io_call(f_usbc_5V_sel, write, low);
            io_call(f_usbc_9V_sel, write, high);
            io_call(f_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch6, 1100, 950);
            adc_threshold_set(ch7, 1100, 950);
        }
    }
    return;    
}

/**
 * Enables the 12V power control for the specified UFP/DFP.
 *
 * @param ufp_dfp The UFP/DFP type (ufp or dfp).
 */
void pd_power_cont_en_12v (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        if (pd_power_cont_ufp_allow_output  != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(ufp);
        } else {
            //set current voltage
            pd_power_cont_ufp_current_voltage = 12;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch4, 0xFFF, 0x0);
            adc_threshold_set(ch5, 0xFFF, 0x0);
            io_call(b_usbc_buck_en, write, low);
            io_call(b_usbc_20V_sel, write, low);
            io_call(b_usbc_15V_sel, write, low);
            io_call(b_usbc_9V_sel, write, low);
            io_call(b_usbc_5V_sel, write, low);
            io_call(b_usbc_12V_sel, write, high);
            io_call(b_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch4, 1450, 1250);
            adc_threshold_set(ch5, 1450, 1250);
        }
    } else if (ufp_dfp == dfp) {
        if (pd_power_cont_ufp_allow_output  != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(dfp);
        } else {
            //set current voltage
            pd_power_cont_dfp_current_voltage = 12;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch6, 0xFFF, 0x0);
            adc_threshold_set(ch7, 0xFFF, 0x0);
            io_call(f_usbc_buck_en, write, low);
            io_call(f_usbc_20V_sel, write, low);
            io_call(f_usbc_15V_sel, write, low);
            io_call(f_usbc_9V_sel, write, low);
            io_call(f_usbc_5V_sel, write, low);
            io_call(f_usbc_12V_sel, write, high);
            io_call(f_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch6, 1450, 1250);
            adc_threshold_set(ch7, 1450, 1250);
        }
    }
    return;    
}

/**
 * @brief Enables the power control for 15V on the USB Type-C port.
 * 
 * This function sets the current voltage to 15V and configures the necessary
 * I/O calls and ADC thresholds based on the type of USB port (UFP or DFP).
 * If the output is not allowed, it returns to the base state where the output
 * is disabled.
 * 
 * @param ufp_dfp The type of USB port (UFP or DFP).
 */
void pd_power_cont_en_15v (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        if (pd_power_cont_ufp_allow_output  != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(ufp);
        } else {
            //set current voltage
            pd_power_cont_ufp_current_voltage = 15;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch4, 0xFFF, 0x0);
            adc_threshold_set(ch5, 0xFFF, 0x0);
            io_call(b_usbc_buck_en, write, low);
            io_call(b_usbc_20V_sel, write, low);
            io_call(b_usbc_12V_sel, write, low);
            io_call(b_usbc_9V_sel, write, low);
            io_call(b_usbc_5V_sel, write, low);
            io_call(b_usbc_15V_sel, write, high);
            io_call(b_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch4, 1700, 1500);
            adc_threshold_set(ch5, 1700, 1500);
        }
    } else if (ufp_dfp == dfp) {
        if (pd_power_cont_ufp_allow_output  != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(dfp);
        } else {
            //set current voltage
            pd_power_cont_dfp_current_voltage = 15;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch6, 0xFFF, 0x0);
            adc_threshold_set(ch7, 0xFFF, 0x0);
            io_call(f_usbc_buck_en, write, low);
            io_call(f_usbc_20V_sel, write, low);
            io_call(f_usbc_12V_sel, write, low);
            io_call(f_usbc_9V_sel, write, low);
            io_call(f_usbc_5V_sel, write, low);
            io_call(f_usbc_15V_sel, write, high);
            io_call(f_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch6, 1700, 1500);
            adc_threshold_set(ch7, 1700, 1500);
        }
    }
    return;    
}

/**
 * @brief Enables the power control for 20V on the USB Type-C port.
 * 
 * This function sets the current voltage to 20V and configures the necessary
 * I/O calls and ADC thresholds based on the type of port (UFP or DFP).
 * If the output is not allowed for the specified port, it returns to the base state
 * where the output is not allowed.
 * 
 * @param ufp_dfp The type of port (UFP or DFP).
 */
void pd_power_cont_en_20v (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        if (pd_power_cont_ufp_allow_output  != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(ufp);
        } else {
            //set current voltage
            pd_power_cont_ufp_current_voltage = 20;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch4, 0xFFF, 0x0);
            adc_threshold_set(ch5, 0xFFF, 0x0);
            io_call(b_usbc_buck_en, write, low);
            io_call(b_usbc_20V_sel, write, low);
            io_call(b_usbc_12V_sel, write, low);
            io_call(b_usbc_9V_sel, write, low);
            io_call(b_usbc_5V_sel, write, low);
            io_call(b_usbc_15V_sel, write, high);
            io_call(b_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch4, 2350, 2150);
            adc_threshold_set(ch5, 2350, 2150);
        }
    } else if (ufp_dfp == dfp) {
        if (pd_power_cont_ufp_allow_output != true) {
            // return to base state of output not allowed
            pd_power_cont_return_to_base_state(dfp);
        } else {
            //set current voltage
            pd_power_cont_dfp_current_voltage = 20;
            //clear adc thresholds as to not alarm when changing voltages
            adc_threshold_set(ch6, 0xFFF, 0x0);
            adc_threshold_set(ch7, 0xFFF, 0x0);
            io_call(f_usbc_buck_en, write, low);
            io_call(f_usbc_20V_sel, write, low);
            io_call(f_usbc_12V_sel, write, low);
            io_call(f_usbc_9V_sel, write, low);
            io_call(f_usbc_5V_sel, write, low);
            io_call(f_usbc_15V_sel, write, high);
            io_call(f_usbc_buck_en, write, high);
            //set adc thresholds
            adc_threshold_set(ch6, 2350, 2150);
            adc_threshold_set(ch7, 2350, 2150);
        }
    }
    return;    
}

/**
 * @brief Checks if the power controller's output voltage is within a valid range.
 * 
 * This function calculates the expected voltage after the voltage divider and
 * then converts it to counts based on the ADC's reference voltage. It then checks
 * if the ADC reading for the corresponding channel is within the valid range.
 * 
 * @param ufp_dfp The type of power controller (UFP or DFP).
 * @param voltage The input voltage to the power controller.
 * @return True if the power controller's output voltage is within the valid range (10%), false otherwise.
 */
bool pd_power_cont_pgood (enum ufp_dfp ufp_dfp, int voltage) {
    //init local vars 
    float upper_valid_value = 0;
    float lower_valid_value = 0;
    float expected_voltage_after_devider = 0;
    int expected_voltage_in_counts = 0;

    //calculate the devider voltage
    expected_voltage_after_devider = ((voltage * 1000) / (1000 + 10000));

    //calculate expected counts
    expected_voltage_in_counts = (3.3 / expected_voltage_after_devider) * 65535;

    //calulate upper and lower limmits
    upper_valid_value = expected_voltage_in_counts * 1.1;
    lower_valid_value = expected_voltage_in_counts * 0.9;

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

    return false;
}

/**
 * @brief Performs a self-check of the power control module.
 * 
 * This function tests the power control module by sequentially enabling and disabling different voltage levels
 * and checking if the power good signal is received for each voltage level. The function returns true if all tests pass,
 * otherwise it returns false.
 * 
 * @return true if all tests pass, false otherwise.
 */
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