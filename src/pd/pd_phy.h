//{usbc car module}
//{pd_phy.h}
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

#ifndef pd_phy_defines_h
#define pd_phy_defines_h

#include <Arduino.h>

//phy address and register defines
const uint8_t pd_phy_add_ufp = 0x52;
const uint8_t pd_phy_add_dfp = 0x50;
const uint8_t pd_phy_reg_vendor_id = 0x00;
const uint8_t pd_phy_reg_product_id = 0x02;
const uint8_t pd_phy_reg_device_id = 0x04;
const uint8_t pd_phy_reg_usbtypec_rev = 0x06;
const uint8_t pd_phy_reg_usbpd_rev_ver = 0x08;
const uint8_t pd_phy_reg_pd_interface_rev = 0x0A;
const uint8_t pd_phy_reg_alert = 0x10;
const uint8_t pd_phy_reg_alert_mask = 0x12;
const uint8_t pd_phy_reg_power_status_mask = 0x14;
const uint8_t pd_phy_reg_fault_status_mask = 0x15;
const uint8_t pd_phy_reg_extended_status_mask = 0x16;
const uint8_t pd_phy_reg_alert_extened_mask = 0x17;
const uint8_t pd_phy_reg_configure_standard_output = 0x18;
const uint8_t pd_phy_reg_tcpc_control = 0x19;
const uint8_t pd_phy_reg_role_control = 0x1A;
const uint8_t pd_phy_reg_fault_control = 0x1B;
const uint8_t pd_phy_reg_power_control = 0x1C;
const uint8_t pd_phy_reg_cc_status = 0x1D;
const uint8_t pd_phy_reg_power_status = 0x1E;
const uint8_t pd_phy_reg_fault_status = 0x1F;
const uint8_t pd_phy_reg_extended_status = 0x20;
const uint8_t pd_phy_reg_alert_extended = 0x21;
const uint8_t pd_phy_reg_command = 0x23;
const uint8_t pd_phy_reg_device_capabilities_1 = 0x24;
const uint8_t pd_phy_reg_device_capabilities_2 = 0x26;
const uint8_t pd_phy_reg_standard_input_capabilities = 0x28;
const uint8_t pd_phy_reg_standard_output_capabilities = 0x29;
const uint8_t pd_phy_reg_configure_extended_1 = 0x2A;
const uint8_t pd_phy_reg_generic_timers = 0x2C;
const uint8_t pd_phy_reg_message_header_info = 0x2E;
const uint8_t pd_phy_reg_receive_detect = 0x2F;
const uint8_t pd_phy_reg_readael_byte_count = 0x30;
const uint8_t pd_phy_reg_transmit = 0x50;
const uint8_t pd_phy_reg_i2c_write_byte_count = 0x51;
const uint8_t pd_phy_reg_vbus_voltage = 0x70;
const uint8_t pd_phy_reg_vbus_sink_disconnect_threshold = 0x72;
const uint8_t pd_phy_reg_vbus_stop_discharge_disconnect_threshold = 0x74;
const uint8_t pd_phy_reg_vbus_voltage_alarm_hi_cfg = 0x76;
const uint8_t pd_phy_reg_vbus_voltage_alarm_lo_cfg = 0x78;
const uint8_t pd_phy_reg_vbus_hv_target = 0x7A;
const uint8_t pd_phy_reg_ext_cfg_target = 0x80;
const uint8_t pd_phy_reg_ext_alert = 0x82;
const uint8_t pd_phy_reg_ext_alert_mask = 0x84;
const uint8_t pd_phy_reg_ext_fault_config = 0x88;
const uint8_t pd_phy_reg_ext_control = 0x8E;
const uint8_t pd_phy_reg_ext_status = 0x90;
const uint8_t pd_phy_reg_ext_gpio_config = 0x92;
const uint8_t pd_phy_reg_ext_gpio_control = 0x93;
const uint8_t pd_phy_reg_ext_gpio_alert_config = 0x94;
const uint8_t pd_phy_reg_ext_gpio_status = 0x96;
const uint8_t pd_phy_reg_source_high_voltage_mb4b_time = 0x97;
const uint8_t pd_phy_reg_adc_filter_control_1 = 0x9A;
const uint8_t pd_phy_reg_adc_filter_control_2 = 0x9B;
const uint8_t pd_phy_reg_vconn_config = 0x9C;
const uint8_t pd_phy_reg_vconn_fault_debounce = 0x9D;
const uint8_t pd_phy_reg_vconn_fault_recovery = 0x9E;
const uint8_t pd_phy_reg_vconn_fault_attempts = 0x9F;

//default pd phy values
const uint16_t pd_phy_default_vendor_id = 8137;
const uint16_t pd_phy_default_product_id = 0;
const uint16_t pd_phy_default_device_id = 0;
const uint16_t pd_phy_default_usbtypec_rev = 0x0012;
const uint16_t pd_phy_default_pd_interface_rev = 0x2012;
const uint16_t pd_phy_default_tptc_control = 0x007C;
const uint16_t pd_phy_default_fault_control = 0x000F;
const uint16_t pd_phy_default_power_control = 0x0019;
const uint16_t pd_phy_ufp_default_message_header_info = 0x000B;
const uint16_t pd_phy_dfp_default_message_header_info = 0x000C;
const uint16_t pd_phy_default_receive_detect = 0xFF;
const uint16_t pd_phy_default_ext_gpio_config = 0x0002;
const uint16_t pd_phy_default_ext_gpio_control = 0x0080;
const uint16_t pd_phy_default_ext_gpio_alert_config = 0x0060;
const uint16_t pd_phy_default_vconn_config = 0x00FB;
const uint16_t pd_phy_default_vconn_fault_attempts = 0x0033;
const uint16_t pd_phy_default_alert = 0x0000;
const uint16_t pd_phy_ufp_default_role_control = 0x002D;
const uint16_t pd_phy_dfp_default_role_control = 0x002A;
const uint16_t pd_phy_default_device_capabilities_1 = 0xFE3F;
const uint16_t pd_phy_default_device_capabilities_2 = 0x31DD;

//phy commands
const uint8_t pd_phy_comm_wake_i2c = 0x11;
const uint8_t pd_phy_comm_disable_vbus_detect = 0x22;
const uint8_t pd_phy_comm_enable_vbus_detect = 0x33;
const uint8_t pd_phy_comm_disable_sink_vbus = 0x44;
const uint8_t pd_phy_comm_sink_vbus = 0x55;
const uint8_t pd_phy_comm_disable_source_vbus = 0x66;
const uint8_t pd_phy_comm_source_vbus_default_voltage = 0x77;
const uint8_t pd_phy_comm_source_vbus_high_voltage = 0x88;
const uint8_t pd_phy_comm_look_4_connection = 0x99;
const uint8_t pd_phy_comm_rx_one_more = 0xAA;
const uint8_t pd_phy_comm_send_frs_swap_signal = 0xBB;
const uint8_t pd_phy_comm_reset_transmit_buffer = 0xCC;
const uint8_t pd_phy_comm_reset_receive_buffer = 0xDD;
const uint8_t pd_phy_comm_i2c_idle = 0xEE;

//message transmit wait time in ms
const int pd_phy_transmit_wait_time = 10;

//ufp/dfp enum
enum ufp_dfp {
    dfp,
    ufp
};

//on/off enum 
enum on_off {
    on,
    off
};

//alert type enum
enum pd_phy_alert_type {
    vendor_defined_extended,
    extended_status_changed,
    beginning_sop_message_status,
    vbus_sink_disconnect_detected,
    rx_buffer_overflow,
    vbus_voltage_low,
    vbus_voltage_high,
    transmit_sop_message_successful,
    transmit_sop_message_discarded,
    transmit_sop_message_failed,
    received_hard_reset,
    received_sop_message_status,
    port_power_status_changed,
    cc_status_alert,
    extended_timer_expired,
    extended_source_frs,
    extended_sink_frs,
    force_off_vbus_status,
    auto_discharge_failed,
    force_discharge_failed,
    internal_or_external_vbus_over_current_protection_fault,
    internal_or_external_vbus_over_voltage_protection_fault,
    vconn_over_current_fault,
    i2c_error,
    alert_empty
};

//plug orientation vars
extern int pd_phy_ufp_plug_orientation;
extern int pd_phy_dfp_plug_orientation;

//port attach status
extern bool pd_phy_ufp_attached;
extern bool pd_phy_dfp_attached;

enum message_type {sop, sop_col, sop_col_col, sop_dbg_col, sop_dbg_col_col, cable_reset};

//received message vars
extern int pd_phy_ufp_last_received_message_contents[256];
extern int pd_phy_ufp_last_received_message_length;
extern int pd_phy_ufp_last_received_message_id;
extern enum message_type pd_phy_ufp_last_received_message_type;
extern int pd_phy_dfp_last_received_message_contents[256];
extern int pd_phy_dfp_last_received_message_length;
extern int pd_phy_dfp_last_received_message_id;
extern enum message_type pd_phy_dfp_last_received_message_type;

//function defines
void pd_phy_init();
void pd_phy_send_look_4_connection(enum ufp_dfp ufp_dfp);
void pd_phy_send_enable_vbus_detect(enum ufp_dfp ufp_dfp);
void pd_phy_send_disable_vbus_detect(enum ufp_dfp ufp_dfp);
void pd_phy_send_disable_source_vbus(enum ufp_dfp ufp_dfp);
void pd_phy_send_source_vbus_default(enum ufp_dfp ufp_dfp);
void pd_phy_send_source_vbus_high(enum ufp_dfp ufp_dfp);
void pd_phy_send_i2c_wake(enum ufp_dfp ufp_dfp);
void pd_phy_send_i2c_idle(enum ufp_dfp ufp_dfp);
void pd_phy_send_rx_one_more(enum ufp_dfp ufp_dfp);
void pd_phy_send_frs_signal(enum ufp_dfp ufp_dfp);
void pd_phy_send_reset_transmit_buffer(enum ufp_dfp ufp_dfp);
void pd_phy_send_reset_receive_buffer(enum ufp_dfp ufp_dfp);
void pd_phy_vconn_cont(enum ufp_dfp ufp_dfp, enum on_off on_off);
void pd_phy_send_hard_reset(enum ufp_dfp ufp_dfp);
void pd_phy_clear_alert(enum ufp_dfp ufp_dfp);
void pd_phy_clear_extended_alert(enum ufp_dfp ufp_dfp);
void pd_phy_clear_fault(enum ufp_dfp ufp_dfp);
enum pd_phy_alert_type pd_phy_determine_alert_type(enum ufp_dfp ufp_dfp);
void pd_phy_complete_attach(enum ufp_dfp ufp_dfp);
void pd_phy_complete_detach(enum ufp_dfp ufp_dfp);
bool pd_phy_transmit(enum ufp_dfp ufp_dfp, uint8_t to_transmit[], int length_of_transmission);
void pd_phy_receive_message(enum ufp_dfp ufp_dfp);

#endif // pd_phy_defines_h