//{usbc car module}
//{pd_phy.cpp}
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

#ifndef dp_phy_cpp
#define dp_phy_cpp

#include <Arduino.h>
#include <Wire.h>
#include "pd_phy.h"
#include "pd_power_cont.h"



//plug orientaion vars
int pd_phy_ufp_plug_orientaion = 0;
int pd_phy_dfp_plug_orientaion = 0;

//port attach status
bool pd_phy_ufp_attached = false;
bool pd_phy_dfp_attached = false;

//recived message vars 
int pd_phy_ufp_last_recived_message_contents[256];
int pd_phy_ufp_last_recived_message_lenght = 0;
int pd_phy_ufp_last_recived_message_id = 0;
enum message_type pd_phy_ufp_last_recived_message_type;
int pd_phy_dfp_last_recived_message_contents[256];
int pd_phy_dfp_last_recived_message_lenght = 0;
int pd_phy_dfp_last_recived_message_id = 0;
enum message_type pd_phy_dfp_last_recived_message_type;


/**
 * Sends a "looking for connection" command to the PD PHY.
 * 
 * @param ufp_dfp The type of device (UFP or DFP) to send the command to.
 */
void pd_phy_send_looking_4_connection (enum ufp_dfp ufp_dfp) {
    //send looking for connection command
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_look_4_connection);
    Wire.endTransmission();

    return;
}

/**
 * @brief Sends a command to enable VBUS detection for the specified UFP/DFP.
 * 
 * This function sends a command to enable VBUS detection for the specified UFP (Upstream Facing Port)
 * or DFP (Downstream Facing Port). It uses the Wire library to communicate with the PD PHY (Physical Layer)
 * device and sends the appropriate command based on the value of the ufp_dfp parameter.
 * 
 * @param ufp_dfp The UFP/DFP for which VBUS detection should be enabled. It can be either ufp or dfp.
 * 
 * @return None.
 */
void pd_phy_send_enable_vbus_detect(enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_enable_vbus_detect);
    Wire.endTransmission();

    return;
}

/**
 * @brief Sends a command to disable VBUS detection for the specified UFP/DFP.
 * 
 * This function sends a command to disable VBUS detection for the specified UFP/DFP.
 * The function uses the Wire library to begin a transmission, write the command and data,
 * and end the transmission.
 * 
 * @param ufp_dfp The UFP/DFP to disable VBUS detection for.
 * 
 * @return None.
 */
void pd_phy_send_disabel_vbus_detect(enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_disabel_vbus_detect);
    Wire.endTransmission();

    return;
}

/**
 * Sends a command to disable the source VBUS for the specified UFP/DFP.
 *
 * @param ufp_dfp The type of UFP/DFP to disable the source VBUS for.
 *                Must be either ufp or dfp.
 */
void pd_phy_send_disabel_source_vbus (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_disabel_source_vbus);
    Wire.endTransmission();

    return;
}

/**
 * Sends a command to set the source VBUS default voltage.
 * 
 * @param ufp_dfp The type of device (UFP or DFP).
 */
void pd_phy_send_source_vbus_dflt (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_source_vbus_defult_voltage);
    Wire.endTransmission();

    return;
}

/**
 * Sends a command to set the source VBUS high voltage.
 * 
 * @param ufp_dfp The type of device (UFP or DFP).
 */
void pd_phy_send_source_vbus_high (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_souce_vbus_high_voltage);
    Wire.endTransmission();

    return;
}

/**
 * Sends an I2C wake command to the specified UFP or DFP device.
 *
 * @param ufp_dfp The device type (UFP or DFP) to send the command to.
 */
void pd_phy_send_i2c_wake (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_wake_i2c);
    Wire.endTransmission();

    return;
}

/**
 * Sends an I2C idle command to the specified UFP or DFP device.
 *
 * @param ufp_dfp The type of device to send the command to (ufp or dfp).
 */
void pd_phy_send_i2c_idle (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_i2c_idle);
    Wire.endTransmission();

    return;
}

/**
 * Sends a command to the PD PHY to receive one more packet.
 * 
 * @param ufp_dfp The type of device (UFP or DFP).
 */
void pd_phy_send_rx_one_more (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_rx_one_more);
    Wire.endTransmission();

    return;
}

/**
 * Sends a Fast Role Swap (FRS) signal to the specified UFP or DFP.
 *
 * @param ufp_dfp The type of device to send the FRS signal to (ufp or dfp).
 */
void pd_phy_send_frs_signal (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_send_frs_swap_signal);
    Wire.endTransmission();

    return;
}

/**
 * @brief Sends a reset transmit buffer command to the PD PHY.
 * 
 * This function sends a command to reset the transmit buffer of the PD PHY.
 * The command is sent to either the UFP or DFP based on the value of the ufp_dfp parameter.
 * 
 * @param ufp_dfp The type of device to send the command to (UFP or DFP).
 */
void pd_phy_send_reset_transmit_buffer (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_reset_transmit_buffer);
    Wire.endTransmission();

    return;
}

/**
 * Sends a hard reset command to the PD PHY.
 * 
 * @param ufp_dfp The type of device (UFP or DFP) to send the hard reset to.
 */
void pd_phy_send_hard_reset (enum ufp_dfp ufp_dfp) {

    pd_phy_send_i2c_wake(ufp_dfp);

    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_transmit);
    Wire.write(0x00);
    Wire.write(0x05);
    Wire.endTransmission();

    pd_phy_send_i2c_idle(ufp_dfp);
}

/**
 * @brief Sends a reset command to the receive buffer of the PD PHY.
 * 
 * This function sends a reset command to the receive buffer of the PD PHY based on the specified UFP/DFP mode.
 * 
 * @param ufp_dfp The UFP/DFP mode to determine the target PD PHY address.
 *                - If `ufp_dfp` is `ufp`, the command is sent to the UFP PD PHY address.
 *                - If `ufp_dfp` is `dfp`, the command is sent to the DFP PD PHY address.
 */
void pd_phy_send_reset_recive_buffer (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_command);
    Wire.write(pd_phy_comm_reset_receive_buffer);
    Wire.endTransmission();

    return;
}

/**
 * @brief Controls the VCONN power for the specified UFP or DFP port.
 *
 * This function wakes up the PHY, reads the power control register, performs bitwise operations
 * to turn on or off the VCONN power, and writes the updated value back to the register.
 * Finally, it puts the PHY back to sleep.
 *
 * @param ufp_dfp The type of port (UFP or DFP) for which to control the VCONN power.
 * @param on_off The desired state of the VCONN power (on or off).
 */
void pd_phy_vconn_cont(enum ufp_dfp ufp_dfp, enum on_off on_off) {
    //init local vars
    uint8_t reg_contents_b0 = 0;
    uint8_t reg_contents_b1 = 0;

    // wake phy 
    pd_phy_send_i2c_wake(ufp_dfp);

    //tell it what port to read from
    if (ufp_dfp = ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_power_control);
    Wire.endTransmission();

    //read register value
    if (ufp_dfp = ufp) {
        Wire.requestFrom(pd_phy_add_ufp, 2);
    } else {
        Wire.requestFrom(pd_phy_add_dfp, 2);
    }

    //read reg contents
    reg_contents_b1 = Wire.read();
    reg_contents_b0 = Wire.read();
    Wire.endTransmission();

    //do bitwise operations to trun on or off 
    if (on_off == on) {
        reg_contents_b0 = reg_contents_b0 | 0x01;
    } else {
        reg_contents_b0 = reg_contents_b0 & 0xFE;
    }

    //write value back to register
    if (ufp_dfp = ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_power_control);
    Wire.write(reg_contents_b1);
    Wire.write(reg_contents_b0);
    Wire.endTransmission();

    //put phy back to sleep

    pd_phy_send_i2c_idle(ufp_dfp);

    return;   

}

/**
 * @brief Clears the alert register of the PD PHY.
 * 
 * This function clears the alert register of the PD PHY based on the specified UFP/DFP mode.
 * 
 * @param ufp_dfp The UFP/DFP mode to clear the alert register for.
 *                - If `ufp_dfp` is `ufp`, the alert register of the UFP mode will be cleared.
 *                - If `ufp_dfp` is `dfp`, the alert register of the DFP mode will be cleared.
 */
void pd_phy_clear_alert (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_alert);
    Wire.write(0x0000);
    Wire.endTransmission();
    return;    
}

/**
 * @brief Clears the extended alert for the specified UFP/DFP.
 * 
 * This function clears the extended alert for the specified UFP (Upstream Facing Port) or DFP (Downstream Facing Port).
 * It uses the Wire library to communicate with the PD PHY (Physical Layer) device and writes the appropriate values
 * to clear the extended alert register.
 * 
 * @param ufp_dfp The UFP/DFP for which the extended alert needs to be cleared.
 *                Possible values are 'ufp' for UFP and 'dfp' for DFP.
 */
void pd_phy_clear_extended_alert (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_alert_extended);
    Wire.write(0x00);
    Wire.endTransmission();
    return;    
}

/**
 * @brief Clears the fault status of the USB Power Delivery (PD) PHY.
 * 
 * This function clears the fault status of the PD PHY for the specified UFP/DFP role.
 * 
 * @param ufp_dfp The role of the USB Function/Device Port (UFP/DFP). 
 *                Must be either `ufp` or `dfp`.
 */
void pd_phy_clear_fault (enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        Wire.beginTransmission(pd_phy_add_ufp);
    } else if (ufp_dfp == dfp) {
        Wire.beginTransmission(pd_phy_add_dfp);
    }
    Wire.write(pd_phy_reg_fault_status);
    Wire.write(0x00);
    Wire.endTransmission();
    return;    
}

/**
 * @brief Initializes the PD PHY module.
 * 
 * This function initializes the PD PHY module by performing the following steps:
 * 1. Sends I2C wake signal to the upstream facing port (ufp) and downstream facing port (dfp).
 * 2. Clears all faults on the ufp.
 * 3. Writes default values to various registers using the Wire library.
 * 4. Clears all faults on both ufp and dfp.
 * 5. Sends I2C idle signal to both ufp and dfp.
 * 
 * @return None.
 */
void pd_phy_init() {
    //wake i2c interface on the phys
    pd_phy_send_i2c_wake(ufp);
    pd_phy_send_i2c_wake(dfp);

    //clear all faults
    pd_phy_clear_alert(ufp);
    pd_phy_clear_extended_alert(ufp);
    pd_phy_clear_fault(ufp);

    //write tptc control
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_tcpc_control);
    Wire.write(pd_phy_dflt_tptc_control);
    Wire.endTransmission();

    //write fault control
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_fault_control);
    Wire.write(pd_phy_dflt_fault_control);
    Wire.endTransmission();

    //write power control
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_power_control);
    Wire.write(pd_phy_dflt_power_control);
    Wire.endTransmission();

    //write headder info
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_message_headder_info);
    Wire.write(pd_phy_ufp_dflt_message_header_info);
    Wire.endTransmission();

    //write recive detect
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_recive_detect);
    Wire.write(pd_phy_dflt_recive_detect);
    Wire.endTransmission();

    //write ext gpio config
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_ext_gpio_config);
    Wire.write(pd_phy_dflt_ext_gpio_config);
    Wire.endTransmission();

    //write ext gpio control
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_ext_gpio_control);
    Wire.write(pd_phy_dflt_ext_gpio_control);
    Wire.endTransmission();

    //write ext gpio alert config
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_ext_gpio_alert_config);
    Wire.write(pd_phy_dflt_ext_gpio_alert_config);
    Wire.endTransmission();

    //write vconn config
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_vconn_config);
    Wire.write(pd_phy_dflt_vconn_config);
    Wire.endTransmission();

    //write vconn fault attemps
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_vconn_fault_attempts);
    Wire.write(pd_phy_dflt_vconn_fault_attemps);
    Wire.endTransmission();

    //write role control
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_role_control);
    Wire.write(pd_phy_ufp_dflt_role_control);
    Wire.endTransmission();

    //write device capabilities
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_device_capabilities_1);
    Wire.write(pd_phy_dflt_device_capabilities_1);
    Wire.endTransmission();
    Wire.beginTransmission(pd_phy_add_ufp);
    Wire.write(pd_phy_reg_device_capabilities_2);
    Wire.write(pd_phy_dflt_device_capabilities_2);
    Wire.endTransmission();

    //write tptc control
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_tcpc_control);
    Wire.write(pd_phy_dflt_tptc_control);
    Wire.endTransmission();

    //write fault control
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_fault_control);
    Wire.write(pd_phy_dflt_fault_control);
    Wire.endTransmission();

    //write power control
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_power_control);
    Wire.write(pd_phy_dflt_power_control);
    Wire.endTransmission();

    //write headder info
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_message_headder_info);
    Wire.write(pd_phy_dfp_dflt_message_header_info);
    Wire.endTransmission();

    //write recive detect
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_recive_detect);
    Wire.write(pd_phy_dflt_recive_detect);
    Wire.endTransmission();

    //write ext gpio config
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_ext_gpio_config);
    Wire.write(pd_phy_dflt_ext_gpio_config);
    Wire.endTransmission();

    //write ext gpio control
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_ext_gpio_control);
    Wire.write(pd_phy_dflt_ext_gpio_control);
    Wire.endTransmission();

    //write ext gpio alert config
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_ext_gpio_alert_config);
    Wire.write(pd_phy_dflt_ext_gpio_alert_config);
    Wire.endTransmission();

    //write vconn config
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_vconn_config);
    Wire.write(pd_phy_dflt_vconn_config);
    Wire.endTransmission();

    //write vconn fault attemps
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_vconn_fault_attempts);
    Wire.write(pd_phy_dflt_vconn_fault_attemps);
    Wire.endTransmission();

    //write role control
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_role_control);
    Wire.write(pd_phy_dfp_dflt_role_control);
    Wire.endTransmission();

    //write device capabilities
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_device_capabilities_1);
    Wire.write(pd_phy_dflt_device_capabilities_1);
    Wire.endTransmission();
    Wire.beginTransmission(pd_phy_add_dfp);
    Wire.write(pd_phy_reg_device_capabilities_2);
    Wire.write(pd_phy_dflt_device_capabilities_2);
    Wire.endTransmission();

    //clear all faults
    pd_phy_clear_alert(ufp);
    pd_phy_clear_extended_alert(ufp);
    pd_phy_clear_fault(ufp);
    pd_phy_clear_alert(dfp);
    pd_phy_clear_extended_alert(dfp);
    pd_phy_clear_fault(dfp);

    //put i2c interface back to sleep
    pd_phy_send_i2c_idle(ufp);
    pd_phy_send_i2c_idle(dfp);

    return;

}

/**
 * @brief Determines the alert type based on the current alert register status.
 * 
 * This function reads the current alert register status of the specified PHY and determines the type of alert that has occurred.
 * The function first sets the current PHY address based on the UFP/DFP parameter. Then, it wakes up the I2C interface on the given PHY.
 * Next, it reads the current alert register status and checks each bit to identify the type of alert. If a specific bit is set, the function
 * sends an I2C idle command and returns the corresponding alert type.
 * 
 * @param ufp_dfp The UFP/DFP parameter indicating the type of PHY (UFP or DFP).
 * @return The enum value representing the determined alert type.
 */
enum pd_phy_alert_type pd_phy_determine_alert_type (enum ufp_dfp ufp_dfp) {
    //init local vars
    uint8_t current_phy_addres = 0;
    uint16_t current_alert_reg_value = 0;
    uint8_t current_alert_extended_reg_value = 0;
    uint8_t current_fault_reg_value = 0;

    //set current phy
    if (ufp_dfp == ufp) {
        current_phy_addres = pd_phy_add_ufp;
    } else if (ufp_dfp == dfp) {
        current_phy_addres = pd_phy_add_ufp;
    }

    //wake i2c interface on given phy
    pd_phy_send_i2c_wake(ufp_dfp);

    //read current alert regfister status
    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_alert);
    Wire.endTransmission();
    Wire.requestFrom(current_phy_addres, 2);
    current_alert_reg_value = Wire.read();
    Wire.endTransmission();
    
    //determine and return intrupt type 
    if ((current_alert_reg_value & 0x8000) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return vendor_defined_extended;
    } else if ((current_alert_reg_value & 0x4000) != 0) {
        //read extended alert register
        Wire.beginTransmission(current_phy_addres);
        Wire.write(pd_phy_reg_alert_extended);
        Wire.endTransmission();
        Wire.requestFrom(current_phy_addres, 1);
        current_alert_extended_reg_value = Wire.read();
        Wire.endTransmission();

        //return extended alert type
        if ((current_alert_extended_reg_value & 0x0004) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return extended_timer_expired;
        } else if ((current_alert_extended_reg_value & 0x0002) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return extended_souce_frs;
        } else if ((current_alert_extended_reg_value & 0x0001) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return extended_sink_frs;
        }

        
    } else if ((current_alert_reg_value & 0x2000) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return extended_status_cahnged;
    } else if ((current_alert_reg_value & 0x1000) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return beginning_sop_message_status;
    } else if ((current_alert_reg_value & 0x0800) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return vbus_sink_disconnect_detected;
    } else if ((current_alert_reg_value & 0x0400) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return rx_buffer_overflow;
    } else if ((current_alert_reg_value & 0x0200) != 0) {
        //read fault register
        Wire.beginTransmission(current_phy_addres);
        Wire.write(pd_phy_reg_fault_status);
        Wire.endTransmission();
        Wire.requestFrom(current_phy_addres, 1);
        current_alert_reg_value = Wire.read();
        Wire.endTransmission();

        //return fault type
        if ((current_fault_reg_value & 0x40) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return force_off_vbus_status;
        } else if ((current_fault_reg_value & 0x20) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return auto_discahrge_failed;
        } else if ((current_fault_reg_value & 0x10) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return force_discharge_failled;
        } else if ((current_fault_reg_value & 0x08) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return internal_or_external_vbus_over_current_protection_fault;
        } else if ((current_fault_reg_value & 0x04) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return internal_or_external_vbus_over_voltage_protection_fault;
        } else if ((current_fault_reg_value & 0x02) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return vconn_over_current_fault;
        } else if ((current_fault_reg_value & 0x01) != 0) {
            pd_phy_send_i2c_idle(ufp_dfp);
            return i2c_error;
        }
    } else if ((current_alert_reg_value & 0x0100) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return vbus_voltage_low;
    } else if ((current_alert_reg_value & 0x0080) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return vbus_voltage_high;
    } else if ((current_alert_reg_value & 0x0040) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return transmit_sop_message_succsessful;
    } else if ((current_alert_reg_value & 0x0020) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return transmit_sop_message_discarded;
    } else if ((current_alert_reg_value & 0x0010) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return transmit_sop_message_failed;
    } else if ((current_alert_reg_value & 0x0008) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return recived_hard_reset;
    } else if ((current_alert_reg_value & 0x0004) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return recvied_sop_message_status;
    } else if ((current_alert_reg_value & 0x0002) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return port_power_status_changed;
    } else if ((current_alert_reg_value & 0x0001) != 0) {
        pd_phy_send_i2c_idle(ufp_dfp);
        return cc_status_alert;
    }
    return alert_empty;
}

/**
 * @brief Completes the attachment process for the PD PHY.
 * 
 * This function initializes the local variables, sets the current PHY address based on the UFP/DFP type,
 * wakes up the PD PHY I2C interface, reads the current CC status register value, determines if looking4connection is 1,
 * reads the plug orientation, sets the orientation variables, reads the current power control register status,
 * sets auto discharge to false, enables VCONN, writes to the power control register, enables VSAFE5V,
 * checks if the voltage is within range, sends the source VBUS command, clears the alert, sends the I2C sleep command,
 * and sets the port attached variable to true.
 * 
 * @param ufp_dfp The UFP/DFP type (enum ufp_dfp).
 * 
 * @return None.
 */
void pd_phy_complite_attach (enum ufp_dfp ufp_dfp) {
    //init local vars 
    uint8_t current_phy_addres = 0;
    uint8_t current_cc_status_reg_value = 0;
    uint8_t current_tcpc_control_reg_value = 0;
    uint8_t current_power_control_reg_value = 0;

    //set current phy address
    if (ufp_dfp == ufp) {
        current_phy_addres = pd_phy_add_ufp;
    } else if (ufp_dfp == dfp) {
        current_phy_addres = pd_phy_add_dfp;
    }

    //wake pd phy i2c interface
    pd_phy_send_i2c_wake(ufp_dfp);

    //read current cc status register value
    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_cc_status);
    Wire.endTransmission();
    Wire.requestFrom(current_phy_addres, 1);
    current_cc_status_reg_value = Wire.read();
    Wire.endTransmission();

    //determine if looking4connection = 1
    if ((current_cc_status_reg_value & 0x20) != 0) {
        //read plug orentation
        Wire.beginTransmission(current_phy_addres);
        Wire.write(pd_phy_reg_tcpc_control);
        Wire.endTransmission();
        Wire.requestFrom(current_phy_addres, 1);
        current_tcpc_control_reg_value = Wire.read();
        Wire.endTransmission();

        //set orentation vars
        if ((current_tcpc_control_reg_value & 0x01) == 0){
            if (ufp_dfp == ufp) {
                pd_phy_ufp_plug_orientaion = 0;
            } else if (ufp_dfp == dfp) {
                pd_phy_dfp_plug_orientaion = 0;
            }
        } else if ((current_tcpc_control_reg_value & 0x01) != 0) {
            if (ufp_dfp == ufp) {
                pd_phy_ufp_plug_orientaion = 1;
            } else if (ufp_dfp == dfp) {
                pd_phy_dfp_plug_orientaion = 1;
            }
        }

        //read current power control reg status 
        Wire.beginTransmission(current_phy_addres);
        Wire.write(pd_phy_reg_power_control);
        Wire.endTransmission();
        Wire.requestFrom(current_phy_addres, 1);
        current_power_control_reg_value = Wire.read();
        Wire.endTransmission();

        //set atuto discarge to false
        current_power_control_reg_value = current_power_control_reg_value & 0xEF;

        //enabel vconn
        current_power_control_reg_value = current_power_control_reg_value | 0x01;

        //write to power control reg
        Wire.beginTransmission(current_phy_addres);
        Wire.write(pd_phy_reg_power_control);
        Wire.write(current_power_control_reg_value);
        Wire.endTransmission();

        pd_power_cont_en_vsafe5v(ufp_dfp);

        //chek if voltage if within range
        while (pd_power_cont_pgood (ufp_dfp, 5) != true) {
            delay(100);
        }
        
        //send souce vbus command
        pd_phy_send_source_vbus_dflt(ufp_dfp);

        pd_phy_clear_alert(ufp_dfp);

        //send i2c sleep command
        pd_phy_send_i2c_idle(ufp_dfp);

        //set port attched var to true
        if (ufp_dfp == ufp) {
            pd_phy_ufp_attached = true;
        } else if (ufp_dfp == dfp) {
            pd_phy_dfp_attached = true;
        }

        return;

    } else {
        return;
    }
    
}

/**
 * @brief Completes the detach process for the PD PHY.
 * 
 * This function performs the necessary steps to complete the detach process for the PD PHY.
 * It initializes local variables, sets the current PHY address based on the UFP/DFP type,
 * wakes up the PD PHY from I2C sleep, clears alerts, reads the current CC status register value,
 * determines if a detach actually happened, turns off power to the given port, clears alerts,
 * reads the current power status register value, disables VCONN, voltage alarms, and VBUS voltage monitor,
 * sends the new power control value to the PHY, sends disable source VBUS command, disables SOP* and resets,
 * sends disable VBUS detect command, sets up for the next attach, sends looking for connection command,
 * sends sleep command, and updates the attachment status.
 * 
 * @param ufp_dfp The UFP/DFP type (enum ufp_dfp) indicating whether it is UFP or DFP.
 */
void pd_phy_complite_detatch (enum ufp_dfp ufp_dfp) {
    //init local vars 
    uint8_t current_phy_addres = 0;
    uint8_t current_cc_status_reg_value = 0;
    uint8_t current_power_status_reg_value = 0;
    uint8_t current_power_control_reg_value = 0;

    //set current phy address
    if (ufp_dfp == ufp) {
        current_phy_addres = pd_phy_add_ufp;
    } else if (ufp_dfp == dfp) {
        current_phy_addres = pd_phy_add_dfp;
    }

    //wake pd phy from i2c sleep
    pd_phy_send_i2c_wake(ufp_dfp);

    pd_phy_clear_alert(ufp_dfp);

    //reac current cc state
    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_cc_status);
    Wire.endTransmission();
    Wire.requestFrom(current_phy_addres, 1);
    current_cc_status_reg_value = Wire.read();
    Wire.endTransmission();

    

    //detrmine if a detatch actuly happend
    if ((current_cc_status_reg_value & 0x0F) == 0) {
        //turn off power to given port
        pd_power_cont_return_to_base_state(ufp_dfp);

        if (pd_phy_alert_type(ufp_dfp) == port_power_status_changed) {
            //clear alert
            pd_phy_clear_alert(ufp_dfp);
            //read current power status reg status 
            Wire.beginTransmission(current_phy_addres);
            Wire.write(pd_phy_reg_power_status);
            Wire.endTransmission();
            Wire.requestFrom(current_phy_addres, 1);
            current_power_status_reg_value = Wire.read();
            Wire.endTransmission();

            if ((current_power_status_reg_value & 0x04) == 0) {
                pd_phy_clear_alert(ufp_dfp);

                //read current power status reg status 
                Wire.beginTransmission(current_phy_addres);
                Wire.write(pd_phy_reg_power_control);
                Wire.endTransmission();
                Wire.requestFrom(current_phy_addres, 1);
                current_power_control_reg_value = Wire.read();
                Wire.endTransmission();
                
                //disabel vconn
                current_power_control_reg_value = current_power_control_reg_value ^ 0x01;

                //disabel voltage alarms
                current_power_control_reg_value = current_power_control_reg_value ^ 0x20;

                //disabel vbus voltage monitor
                current_power_control_reg_value = current_power_control_reg_value ^ 0x40;

                //send new power control value to phy
                Wire.beginTransmission(current_phy_addres);
                Wire.write(pd_phy_reg_power_control);
                Wire.write(current_power_control_reg_value);
                Wire.endTransmission();

                //send disabel source vbus command
                pd_phy_send_disabel_source_vbus(ufp_dfp);

                //disabel sop* and resets 
                Wire.beginTransmission(current_phy_addres);
                Wire.write(pd_phy_reg_recive_detect);
                Wire.write(0x00);
                Wire.endTransmission();

                //send disabel vbus detect command
                pd_phy_send_disabel_vbus_detect(ufp_dfp);


                //setup for next attach 
                Wire.beginTransmission(current_phy_addres);
                Wire.write(pd_phy_reg_role_control);
                if (ufp_dfp == ufp) {
                    Wire.write(pd_phy_ufp_dflt_role_control);
                } else if (ufp_dfp == dfp) {
                    Wire.write(pd_phy_dfp_dflt_role_control);
                }

                //send looking 4 connection command
                pd_phy_send_looking_4_connection(ufp_dfp);

                //send sleep command
                pd_phy_send_i2c_idle(ufp_dfp);

                if (ufp_dfp == ufp) {
                  pd_phy_ufp_attached = false;
                } else if (ufp_dfp == dfp) {
                  pd_phy_dfp_attached = false;
                }

                return;                
            }
        }
    }

    return;
 }

/**
 * @brief Transmits a hard reset command to the PD PHY.
 *
 * This function transmits a hard reset command to the PD PHY. It performs the following steps:
 * 1. Initializes local variables.
 * 2. Wakes up the I2C interface.
 * 3. Resets the transmit buffer.
 * 4. Sets the current PHY address based on the UFP/DFP mode.
 * 5. Begins the I2C transmission to the current PHY address.
 * 6. Writes the transmit register address and the hard reset command.
 * 7. Ends the I2C transmission.
 * 8. Puts the I2C interface to sleep.
 *
 * @param ufp_dfp The mode of the PD PHY (UFP or DFP).
 */
void pd_phy_transmit_hard_reset (enum ufp_dfp ufp_dfp) {
    //inti local vars
    uint8_t current_phy_addres = 0;

    //wake i2c interface
    pd_phy_send_i2c_wake(ufp_dfp);

    //reset transmit buffer
    pd_phy_send_reset_transmit_buffer(ufp_dfp);

    //set current phy address
    if (ufp_dfp == ufp) {
        current_phy_addres = pd_phy_add_ufp;
    } else if (ufp_dfp == dfp) {
        current_phy_addres = pd_phy_add_dfp;
    }

    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_transmit);
    Wire.write(0x35);
    Wire.endTransmission();

    //put i2c iterface to sleep
    pd_phy_send_i2c_idle(ufp_dfp);

    return;
}

/**
 * @brief Transmits a cable reset command to the PD PHY.
 *
 * This function transmits a cable reset command to the PD PHY. It wakes up the I2C interface,
 * resets the transmit buffer, sets the current PHY address based on the UFP/DFP mode, writes
 * the cable reset command to the transmit register of the PHY, and puts the I2C interface to sleep.
 *
 * @param ufp_dfp The mode of operation (UFP or DFP).
 */
void pd_phy_transmit_cable_reset (enum ufp_dfp ufp_dfp) {
    //inti local vars
    uint8_t current_phy_addres = 0;

    //wake i2c interface
    pd_phy_send_i2c_wake(ufp_dfp);

    //reset transmit buffer
    pd_phy_send_reset_transmit_buffer(ufp_dfp);

    //set current phy address
    if (ufp_dfp == ufp) {
        current_phy_addres = pd_phy_add_ufp;
    } else if (ufp_dfp == dfp) {
        current_phy_addres = pd_phy_add_dfp;
    }

    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_transmit);
    Wire.write(0x36);
    Wire.endTransmission();
    //put i2c iterface to sleep
    pd_phy_send_i2c_idle(ufp_dfp);

    return;
}

/**
 * @brief Transmits data over the PD PHY interface.
 *
 * This function transmits the provided data over the PD PHY interface. It takes the type of the device (UFP or DFP),
 * the data to transmit, and the length of the transmission as input parameters. It returns a boolean value indicating
 * whether the transmission was successful or not.
 *
 * @param ufp_dfp The type of the device (UFP or DFP).
 * @param to_transmit The data to transmit.
 * @param length_of_transmission The length of the transmission.
 * @return True if the transmission was successful, false otherwise.
 */
bool pd_phy_transmit (enum ufp_dfp ufp_dfp, uint8_t to_transmit[], int lenght_of_transmission) {
    //inti local vars
    uint8_t current_phy_addres = 0;
    uint8_t lenght_of_message = lenght_of_transmission;
    
    //set current phy address
    if (ufp_dfp == ufp) {
        current_phy_addres = pd_phy_add_ufp;
    } else if (ufp_dfp == dfp) {
        current_phy_addres = pd_phy_add_dfp;
    }

    //wake i2c interface on phy
    pd_phy_send_i2c_wake(ufp_dfp);

    //reset the transmit buffer
    pd_phy_send_reset_transmit_buffer(ufp_dfp);

    //begin transmitting data to buffer
    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_i2c_write_byte_count);
    Wire.write(lenght_of_message);
    for (int i; i < lenght_of_message; ++i) {
        Wire.write(to_transmit[i]);
    }
    Wire.endTransmission();

    //send command for phy to transmit the data
    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_transmit);
    Wire.write(0x30);
    Wire.endTransmission();

    //wait for messgae to be sent
    delay(pd_phy_transmit_wait_time);

    if (pd_phy_alert_type(ufp_dfp) == transmit_sop_message_succsessful) {
        pd_phy_clear_alert(ufp_dfp);
        pd_phy_send_i2c_idle(ufp_dfp);
        return true;
    } else {
        pd_phy_clear_alert(ufp_dfp);
        pd_phy_send_i2c_idle(ufp_dfp);
        return false;
    }


}

/**
 * @brief Receives a message from the PD PHY.
 * 
 * This function receives a message from the PD PHY and performs the necessary operations
 * to extract and store the message details. It wakes up the I2C interface, checks if a
 * SOP message has been received, reads the message length and type, reads the actual
 * message contents, resets the receive buffer, determines the message ID, determines
 * the message type, and stores the values in the respective variables.
 * 
 * @param ufp_dfp The enum value indicating whether the message is from UFP or DFP.
 */
void pd_phy_recive_message (enum ufp_dfp ufp_dfp) {
    //init local vars
    uint8_t current_phy_addres = 0;
    uint16_t current_alert_reg_value = 0;
    uint8_t current_message_type_reg_value = 0;
    uint8_t current_message_length = 0;
    int current_message_contents[current_message_length];
    enum message_type current_message_type;
    
    //set current phy address
    if (ufp_dfp == ufp) {
        current_phy_addres = pd_phy_add_ufp;
    } else if (ufp_dfp == dfp) {
        current_phy_addres = pd_phy_add_dfp;
    }

    //wake i2c interface
    pd_phy_send_i2c_wake(ufp_dfp);

    //check if sop message recived bit is true 
    Wire.beginTransmission(current_phy_addres);
    Wire.write(pd_phy_reg_alert);
    Wire.endTransmission();
    Wire.requestFrom(current_phy_addres, 2);
    current_alert_reg_value = Wire.read();
    Wire.endTransmission();

    if ((current_alert_reg_value & 0x0004) != 0){
        //clear alert register
        pd_phy_clear_alert(ufp_dfp);

        //read recived message lenght in bytes & message type
        Wire.beginTransmission(current_phy_addres);
        Wire.write(pd_phy_reg_readael_byte_count);
        Wire.endTransmission();
        Wire.requestFrom(current_phy_addres, 2);
        current_message_length = Wire.read();
        current_message_type_reg_value = Wire.read();
        Wire.endTransmission();

        //read actual message and laod it in to array
        Wire.beginTransmission(current_phy_addres);
        Wire.write(pd_phy_reg_readael_byte_count);
        Wire.endTransmission();
        Wire.requestFrom(current_phy_addres, current_message_length);
        for (int i; i < current_message_length; ++i) {
            if (i <= 2) {
                //do nothing for first 2 bytes
            } else {
                current_message_contents[i] = Wire.read();
            }
        }
        Wire.endTransmission();

        //reset recive buffer
        pd_phy_send_reset_recive_buffer(ufp_dfp);

        //clear alerts
        pd_phy_clear_alert(ufp_dfp);

        //determine message id
        if (ufp_dfp == ufp) {
            pd_phy_ufp_last_recived_message_id = (current_message_contents[0] & 0x0D) >> 1;
        } else {
            pd_phy_dfp_last_recived_message_id = (current_message_contents[0] & 0x0D) >> 1;
        }

        //determine message type and store it 
        if ((current_message_type_reg_value | 0x00) == 0) {
            current_message_type = sop;
        } else if ((current_message_type_reg_value & 0x01) != 0) {
            current_message_type = sop_col;
        } else if ((current_message_type_reg_value & 0x02) != 0) {
            current_message_type = sop_col_col;
        } else if ((current_message_type_reg_value & 0x03) != 0) {
            current_message_type = sop_dbg_col;
        } else if ((current_message_type_reg_value & 0x04) != 0) {
            current_message_type = sop_dbg_col_col;
        } else if ((current_message_type_reg_value & 0x06) != 0) {
            current_message_type = cable_reset;
        }

        //load values in to port respective vars
        if (ufp_dfp == ufp) {
            pd_phy_ufp_last_recived_message_type = current_message_type;
            pd_phy_ufp_last_recived_message_lenght = (current_message_length - 2);
            for (int i; i < (current_message_length - 2); ++i) {
                pd_phy_ufp_last_recived_message_contents[i] = current_message_contents[i];
            }
        } else if (ufp_dfp == dfp) {
            pd_phy_dfp_last_recived_message_type = current_message_type;
            pd_phy_dfp_last_recived_message_lenght = (current_message_length - 2);
            for (int i; i < (current_message_length - 2); ++i) {
                pd_phy_dfp_last_recived_message_contents[i] = current_message_contents[i];
            }
        }
    }

    //send i2c sleep command
    pd_phy_send_i2c_idle(ufp_dfp);

    return;

}




#endif // dp_phy_cpp