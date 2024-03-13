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
int pd_phy_ufp_last_recived_message_id = 0;
enum message_type pd_phy_dfp_last_recived_message_type;


//pd_phy_send_looking_4_connection
//sends looking 4 connection command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_enable_vbus_detect
//sends enable vbus detect command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_disabel_vbus_detect
//sends disabel vbus detect command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_disabel_source_vbus
//sends disabel souce vbus command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_source_vbus_dflt
//sends enabel souce vbus command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_source_vbus_high
//sends enabel souce vbus high voltage command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_i2c_wake
//sends i2c wake command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_i2c_idle
//sends i2c sleep command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_rx_one_more
//sends rx one more command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_frs_signal
//sends rx one more command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_reset_transmit_buffer
//sends reset transmit buffer command to port controler 
//ufp_dfp: select port to sent command to
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

//pd_phy_send_hard_reset
//sends hard reset from the given port
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

//pd_phy_send_reset_recive_buffer
//sends reset recive buffer command to port controler 
//ufp_dfp: select port to sent command to
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

//clears the alert register
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

//clears the extended alert register
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

//clears the fault register
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

//init the pd phys
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

//reads allert type from a given port controler
//ufp_dfp: select port to read allert registter from
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

//once a plug attach event is detected complete the conection
//ufp_dfp: select port to complete the attach seqwice
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

//once a plug detatch event is detected complete the disconnect
//ufp_dfp: select port to complete the attach seqwice
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

//pd_phy_transmit_hard_reset
//transmits a hard reset message with 3 retrys 
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

//pd_phy_transmit_cable_reset
//transmits a hard reset message with 3 retrys 
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

//pd_phy_transmit
//function to transmit a given message over the pd bus
//ufp_dfp: given port to tramit the message from
//to_transmit: messgae to transmit in array seperated by individual bytes
//true = transmit sucsessful
//false = trasmit failled/discarded
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

//pd_phy_recive_message
//function reads recive buffer and loads necicary info in to the respective ports last_message_lenght, last_message_contents[], and last_messgae_type vars
//ufp_dfp: given port to recive the message from
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