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

#ifndef pd_phy_defines_h
#define pd_phy_defines_h

#include <Arduino.h>

//phy address and register defines
const uint8_t pd_phy_add_ufp = 0xE4;
const uint8_t pd_phy_add_dfp = 0xE0;
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
const uint8_t pd_phy_reg_standard_input_capailities = 0x28;
const uint8_t pd_phy_reg_standard_output_capailities = 0x29;
const uint8_t pd_phy_reg_configure_extended_1 = 0x2A;
const uint8_t pd_phy_reg_genreic_timers = 0x2C;
const uint8_t pd_phy_reg_message_headder_info = 0x2E;
const uint8_t pd_phy_reg_recive_detect = 0x2F;
const uint8_t pd_phy_reg_readael_byte_count = 0x30;
const uint8_t pd_phy_reg_transmit = 0x50;
const uint8_t pd_phy_reg_i2c_write_byte_count = 0x51;
const uint8_t pd_phy_reg_vbus_voltage = 0x70;
const uint8_t pd_phy_reg_vbus_sink_disconnect_threshold = 0x72;
const uint8_t pd_phy_reg_vbus_stop_discharge_disconnect_threshold = 0x74;
const uint8_t pd_phy_reg_vbus_voltage_alarm_hi_cfg = 0x76;
const uint8_t pd_phy_reg_vbus_voltage_alarm_lo_cfg = 0x78;
const uint8_t pd_phy_reg_vbus_hv_traget = 0x7A;
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

//defult pd phy values
const uint16_t pd_phy_dflt_vendor_id = 8137;
const uint16_t pd_phy_dflt_product_id = 0;
const uint16_t pd_phy_dflt_device_id = 0;
const uint16_t pd_phy_dflt_usbtypec_rev = 0x0012;
const uint16_t pd_phy_dflt_pd_interface_rev = 0x2012;
const uint16_t pd_phy_dflt_tptc_control = 0x007C;
const uint16_t pd_phy_dflt_fault_control = 0x000F;
const uint16_t pd_phy_dflt_power_control = 0x0019;
const uint16_t pd_phy_ufp_dflt_message_header_info = 0x000B;
const uint16_t pd_phy_dfp_dflt_message_header_info = 0x000C;
const uint16_t pd_phy_dflt_recive_detect = 0xFF;
const uint16_t pd_phy_dflt_ext_gpio_config = 0x0002;
const uint16_t pd_phy_dflt_ext_gpio_control = 0x0080;
const uint16_t pd_phy_dflt_ext_gpio_alert_config = 0x0060;
const uint16_t pd_phy_dflt_vconn_config = 0x00FB;
const uint16_t pd_phy_dflt_vconn_fault_attemps = 0x0033;
const uint16_t pd_phy_dflt_alert = 0x0000;
const uint16_t pd_phy_ufp_dflt_role_control = 0x002D;
const uint16_t pd_phy_dfp_dflt_role_control = 0x002A;
const uint16_t pd_phy_dflt_device_capabilities_1 = 0xFE3F;
const uint16_t pd_phy_dflt_device_capabilities_2 = 0x31DD;

//phy commands
const uint8_t pd_phy_comm_wake_i2c = 0x11;
const uint8_t pd_phy_comm_disabel_vbus_detect = 0x22;
const uint8_t pd_phy_comm_enable_vbus_detect = 0x33;
const uint8_t pd_phy_comm_disable_sink_vbus = 0x44;
const uint8_t pd_phy_comm_sink_vbus = 0x55;
const uint8_t pd_phy_comm_disabel_source_vbus = 0x66;
const uint8_t pd_phy_comm_source_vbus_defult_voltage = 0x77;
const uint8_t pd_phy_comm_souce_vbus_high_voltage = 0x88;
const uint8_t pd_phy_comm_look_4_connection = 0x99;
const uint8_t pd_phy_comm_rx_one_more = 0xAA;
const uint8_t pd_phy_comm_send_frs_swap_signal = 0xBB;
const uint8_t pd_phy_comm_reset_transmit_buffer = 0xCC;
const uint8_t pd_phy_comm_reset_receive_buffer = 0xDD;
const uint8_t pd_phy_comm_i2c_idle = 0xEE;

//pd control messages
//usb-if docs page 131
const uint16_t pd_phy_cont_msg_goodcrc = 0x0101;
const uint16_t pd_phy_cont_msg_gotomin = 0x0102;
const uint16_t pd_phy_cont_msg_accept = 0x0103;
const uint16_t pd_phy_cont_msg_reject = 0x0104;
const uint16_t pd_phy_cont_msg_ping = 0x0105;
const uint16_t pd_phy_cont_msg_ps_rdy = 0x0106;
const uint16_t pd_phy_cont_msg_get_source_cap = 0x0107;
const uint16_t pd_phy_cont_msg_get_sink_cap = 0x0108;
const uint16_t pd_phy_cont_msg_dr_swap = 0x0109;
const uint16_t pd_phy_cont_msg_pr_swap = 0x010A;
const uint16_t pd_phy_cont_msg_vconn_swap = 0x010B;
const uint16_t pd_phy_cont_msg_wait = 0x010C;
const uint16_t pd_phy_cont_msg_soft_reset = 0x010D;
const uint16_t pd_phy_cont_msg_data_reset = 0x010E;
const uint16_t pd_phy_cont_msg_data_reset_complete = 0x010F;
const uint16_t pd_phy_cont_msg_not_supported = 0x0180;
const uint16_t pd_phy_cont_msg_get_status = 0x0181;
const uint16_t pd_phy_cont_msg_fr_swap = 0x0182;
const uint16_t pd_phy_cont_msg_get_pps_status = 0x0183;
const uint16_t pd_phy_cont_msg_get_county_codes = 0x0184;
const uint16_t pd_phy_cont_msg_get_sink_cap_extended = 0x0185;
const uint16_t pd_phy_cont_msg_get_souce_info = 0x0186;
const uint16_t pd_phy_cont_msg_get_revision = 0x0187;

//pd data messgaes
//usb-if docs page 142
const uint16_t pd_phy_data_msg_source_capabilities = 0x0101;
const uint16_t pd_phy_data_msg_request = 0x0102;
const uint16_t pd_phy_data_msg_bist = 0x0103;
const uint16_t pd_phy_data_msg_sink_capabilities = 0x0104;
const uint16_t pd_phy_data_msg_battery_status = 0x0105;
const uint16_t pd_phy_data_msg_alert = 0x0106;
const uint16_t pd_phy_data_msg_get_country_info = 0x0107;
const uint16_t pd_phy_data_msg_enter_usb = 0x0108;
const uint16_t pd_phy_data_msg_epr_request = 0x0109;
const uint16_t pd_phy_data_msg_per_mode = 0x010A;
const uint16_t pd_phy_data_msg_source_info = 0x010B;
const uint16_t pd_phy_data_msg_vendor_defined =0x010F;

//pd extended control messages
//usb-if docs page 232
const uint32_t pd_phy_ext_msg_source_capabilities_extended = 0x81010000;
const uint32_t pd_phy_ext_msg_status = 0x81020000;
const uint32_t pd_phy_ext_msg_get_battery_cap = 0x81030000;
const uint32_t pd_phy_ext_msg_get_battery_status = 0x81040000;
const uint32_t pd_phy_ext_msg_battery_capbilities = 0x81050000;
const uint32_t pd_phy_ext_msg_get_manufacturer_info = 0x81060000;
const uint32_t pd_phy_ext_msg_manufacturer_info = 0x81070000;
const uint32_t pd_phy_ext_msg_security_request = 0x81080000;
const uint32_t pd_phy_ext_msg_security_response = 0x81090000;
const uint32_t pd_phy_ext_msg_firmware_update_request = 0x810A0000;
const uint32_t pd_phy_ext_msg_firmware_update_response = 0x810B0000;
const uint32_t pd_phy_ext_msg_pps_status = 0x810C0000;
const uint32_t pd_phy_ext_msg_country_info = 0x810D0000;
const uint32_t pd_phy_ext_msg_country_codes = 0x810E0000;
const uint32_t pd_phy_ext_msg_sink_capabilities_extended = 0x810F0000;
const uint32_t pd_phy_ext_msg_extended_controll = 0x81800000;
const uint32_t pd_phy_ext_msg_epr_source_capabilites = 0x81810000;
const uint32_t pd_phy_ext_msg_epr_sink_capbilites = 0x81820000;
const uint32_t pd_phy_ext_msg_vendor_defined_extended = 0x818E0000;

//pd message header vars & const's
//usb-if docs page 119
extern int pd_phy_head_ufp_message_id;
extern int pd_phy_head_dfp_message_id;
const uint16_t pd_phy_head_ufp_data_role = 0x0000;
const uint16_t pd_phy_head_dfp_data_role = 0x0020;
const uint16_t pd_phy_head_spec_ver_1 = 0x0000;
const uint16_t pd_phy_head_spec_ver_2 = 0x0040;
const uint16_t pd_phy_head_spec_ver_3 = 0x0080;

//pd power data objects 
//usb-if docs page 144
const uint32_t pd_phy_pdo_vsafe_5v = 0x0C119024;
const uint32_t pd_phy_pdo_9v = 0x0012D024;
const uint32_t pd_phy_pdo_12v = 0x0013C024;
const uint32_t pd_phy_pdo_15v = 0x0014B024;
const uint32_t pd_phy_pdo_20v = 0x001C8024;


//pd timer threshold vals
//time in ms
//usb-if docs page 271
const int pd_phy_timer_th_ac_temp_update = 500;
const int pd_phy_timer_th_bist_cont_mode = 60;
const int pd_phy_timer_th_shared_test_mode = 1000;
const int pd_phy_timer_th_cable_message = 1;
const int pd_phy_timer_th_chunking_not_supported = 50;
const int pd_phy_timer_th_chunk_recevier_request = 15;
const int pd_phy_timer_th_chunk_recevier_response = 15;
const int pd_phy_timer_th_chunk_sender_request = 30;
const int pd_phy_timer_th_chunk_sender_response = 30;
const int pd_phy_timer_th_data_reset = 250;
const int pd_phy_timer_th_data_reset_fail = 400;
const int pd_phy_timer_th_data_reset_fail_ufp = 550;
const int pd_phy_timer_th_discover_identity = 50;
const int pd_phy_timer_th_dr_swap_hard_reset = 15;
const int pd_phy_timer_th_dr_swap_wait = 100;
const int pd_phy_timer_th_enter_usb = 500;
const int pd_phy_timer_th_enter_usb_wait = 100;
const int pd_phy_timer_th_enter_epr = 550;
const int pd_phy_timer_th_epr_soruce_cable_discovvery = 2000;
const int pd_phy_timer_th_fisrt_source_cap = 250;
const int pd_phy_timer_th_fr_swap_5v = 15;
const int pd_phy_timer_th_fr_swap_complete = 15;
const int pd_phy_timer_th_fr_swap_init = 15;
const int pd_phy_timer_th_hard_reset = 5;
const int pd_phy_timer_th_hard_reset_complete = 5;
const int pd_phy_timer_th_source_epr_keep_alive = 1000;
const int pd_phy_timer_th_sink_epr_keep_alive = 500;
const int pd_phy_timer_th_no_responce = 5500;
const int pd_phy_timer_th_pps_request = 10000;
const int pd_phy_timer_th_pps_timeout = 15000;
const int pd_phy_timer_th_prot_err_hard_reset = 15;
const int pd_phy_timer_th_prot_err_soft_reset = 15;
const int pd_phy_timer_th_pr_swap_wait = 100;
const int pd_phy_timer_th_ps_hard_reset = 35;
const int pd_phy_timer_th_spr_ps_source_off = 920;
const int pd_phy_timer_th_epr_ps_source_off = 1400;
const int pd_phy_timer_th_ps_source_on = 480;
const int pd_phy_timer_th_spr_ps_transition = 550;
const int pd_phy_timer_th_epr_ps_transition = 1020;
const int pd_phy_timer_th_receive = 1;
const int pd_phy_timer_th_receive_responce = 15;
const int pd_phy_timer_th_retry = 195;
const int pd_phy_timer_th_sender_responce = 33;
const int pd_phy_timer_th_sink_delay = 5;
const int pd_phy_timer_th_sink_tx = 20;
const int pd_phy_timer_th_soft_reset = 15;
const int pd_phy_timer_th_scr_holds_bus = 50;
const int pd_phy_timer_th_swap_sink_ready = 15;
const int pd_phy_timer_th_swap_source_start = 20;
const int pd_phy_timer_th_transmit = 195;
const int pd_phy_timer_th_type_c_send_source_cap = 200;
const int pd_phy_timer_th_type_c_sink_wait_cap = 620;
const int pd_phy_timer_th_vconn_source_discharge = 240;
const int pd_phy_timer_th_vconn_source_off = 25;
const int pd_phy_timer_th_vconn_source_on = 50;
const int pd_phy_timer_th_vconn_source_timeout = 200;
const int pd_phy_timer_th_vconn_swap_wait = 100;
const int pd_phy_timer_th_vdm_busy = 50;
const int pd_phy_timer_th_vdm_enter_mode = 25;
const int pd_phy_timer_th_vdm_exit_mode = 25;
const int pd_phy_timer_th_vdm_receiver_responce = 15;
const int pd_phy_timer_th_vdm_sender_responce = 30;
const int pd_phy_timer_th_vdm_wait_mode_entry = 50;
const int pd_phy_timer_th_vdm_wait_mode_exit = 50;

//pd timer start times for ufp
//usb-if docs page 271
extern unsigned long pd_phy_ufp_timer_start_time_ac_temp_update;
extern unsigned long pd_phy_ufp_timer_start_time_bist_cont_mode;
extern unsigned long pd_phy_ufp_timer_start_time_shared_test_mode;
extern unsigned long pd_phy_ufp_timer_start_time_cable_message;
extern unsigned long pd_phy_ufp_timer_start_time_chunking_not_supported;
extern unsigned long pd_phy_ufp_timer_start_time_chunk_recevier_request;
extern unsigned long pd_phy_ufp_timer_start_time_chunk_recevier_response;
extern unsigned long pd_phy_ufp_timer_start_time_chunk_sender_request;
extern unsigned long pd_phy_ufp_timer_start_time_chunk_sender_response;
extern unsigned long pd_phy_ufp_timer_start_time_data_reset;
extern unsigned long pd_phy_ufp_timer_start_time_data_reset_fail;
extern unsigned long pd_phy_ufp_timer_start_time_data_reset_fail_ufp;
extern unsigned long pd_phy_ufp_timer_start_time_discover_identity;
extern unsigned long pd_phy_ufp_timer_start_time_dr_swap_hard_reset;
extern unsigned long pd_phy_ufp_timer_start_time_dr_swap_wait;
extern unsigned long pd_phy_ufp_timer_start_time_enter_usb;
extern unsigned long pd_phy_ufp_timer_start_time_enter_usb_wait;
extern unsigned long pd_phy_ufp_timer_start_time_enter_epr;
extern unsigned long pd_phy_ufp_timer_start_time_epr_soruce_cable_discovvery;
extern unsigned long pd_phy_ufp_timer_start_time_fisrt_source_cap;
extern unsigned long pd_phy_ufp_timer_start_time_fr_swap_5v;
extern unsigned long pd_phy_ufp_timer_start_time_fr_swap_complete;
extern unsigned long pd_phy_ufp_timer_start_time_fr_swap_init;
extern unsigned long pd_phy_ufp_timer_start_time_hard_reset;
extern unsigned long pd_phy_ufp_timer_start_time_hard_reset_complete;
extern unsigned long pd_phy_ufp_timer_start_time_source_epr_keep_alive;
extern unsigned long pd_phy_ufp_timer_start_time_sink_epr_keep_alive;
extern unsigned long pd_phy_ufp_timer_start_time_no_responce;
extern unsigned long pd_phy_ufp_timer_start_time_pps_request;
extern unsigned long pd_phy_ufp_timer_start_time_pps_timeout;
extern unsigned long pd_phy_ufp_timer_start_time_prot_err_hard_reset;
extern unsigned long pd_phy_ufp_timer_start_time_prot_err_soft_reset;
extern unsigned long pd_phy_ufp_timer_start_time_pr_swap_wait;
extern unsigned long pd_phy_ufp_timer_start_time_ps_hard_reset;
extern unsigned long pd_phy_ufp_timer_start_time_spr_ps_source_off;
extern unsigned long pd_phy_ufp_timer_start_time_epr_ps_source_off;
extern unsigned long pd_phy_ufp_timer_start_time_ps_source_on;
extern unsigned long pd_phy_ufp_timer_start_time_spr_ps_transition;
extern unsigned long pd_phy_ufp_timer_start_time_epr_ps_transition;
extern unsigned long pd_phy_ufp_timer_start_time_receive;
extern unsigned long pd_phy_ufp_timer_start_time_receive_responce;
extern unsigned long pd_phy_ufp_timer_start_time_retry;
extern unsigned long pd_phy_ufp_timer_start_time_sender_responce;
extern unsigned long pd_phy_ufp_timer_start_time_sink_delay;
extern unsigned long pd_phy_ufp_timer_start_time_sink_tx;
extern unsigned long pd_phy_ufp_timer_start_time_soft_reset;
extern unsigned long pd_phy_ufp_timer_start_time_scr_holds_bus;
extern unsigned long pd_phy_ufp_timer_start_time_swap_sink_ready;
extern unsigned long pd_phy_ufp_timer_start_time_swap_source_start;
extern unsigned long pd_phy_ufp_timer_start_time_transmit;
extern unsigned long pd_phy_ufp_timer_start_time_type_c_send_source_cap;
extern unsigned long pd_phy_ufp_timer_start_time_type_c_sink_wait_cap;
extern unsigned long pd_phy_ufp_timer_start_time_vconn_source_discharge;
extern unsigned long pd_phy_ufp_timer_start_time_vconn_source_off;
extern unsigned long pd_phy_ufp_timer_start_time_vconn_source_on;
extern unsigned long pd_phy_ufp_timer_start_time_vconn_source_timeout;
extern unsigned long pd_phy_ufp_timer_start_time_vconn_swap_wait;
extern unsigned long pd_phy_ufp_timer_start_time_vdm_busy;
extern unsigned long pd_phy_ufp_timer_start_time_vdm_enter_mode;
extern unsigned long pd_phy_ufp_timer_start_time_vdm_exit_mode;
extern unsigned long pd_phy_ufp_timer_start_time_vdm_receiver_responce;
extern unsigned long pd_phy_ufp_timer_start_time_vdm_sender_responce;
extern unsigned long pd_phy_ufp_timer_start_time_vdm_wait_mode_entry;
extern unsigned long pd_phy_ufp_timer_start_time_vdm_wait_mode_exit;

//pd timer start times for dfp
//usb-if docs page 271
extern unsigned long pd_phy_dfp_timer_start_time_ac_temp_update;
extern unsigned long pd_phy_dfp_timer_start_time_bist_cont_mode;
extern unsigned long pd_phy_dfp_timer_start_time_shared_test_mode;
extern unsigned long pd_phy_dfp_timer_start_time_cable_message;
extern unsigned long pd_phy_dfp_timer_start_time_chunking_not_supported;
extern unsigned long pd_phy_dfp_timer_start_time_chunk_recevier_request;
extern unsigned long pd_phy_dfp_timer_start_time_chunk_recevier_response;
extern unsigned long pd_phy_dfp_timer_start_time_chunk_sender_request;
extern unsigned long pd_phy_dfp_timer_start_time_chunk_sender_response;
extern unsigned long pd_phy_dfp_timer_start_time_data_reset;
extern unsigned long pd_phy_dfp_timer_start_time_data_reset_fail;
extern unsigned long pd_phy_dfp_timer_start_time_data_reset_fail_ufp;
extern unsigned long pd_phy_dfp_timer_start_time_discover_identity;
extern unsigned long pd_phy_dfp_timer_start_time_dr_swap_hard_reset;
extern unsigned long pd_phy_dfp_timer_start_time_dr_swap_wait;
extern unsigned long pd_phy_dfp_timer_start_time_enter_usb;
extern unsigned long pd_phy_dfp_timer_start_time_enter_usb_wait;
extern unsigned long pd_phy_dfp_timer_start_time_enter_epr;
extern unsigned long pd_phy_dfp_timer_start_time_epr_soruce_cable_discovvery;
extern unsigned long pd_phy_dfp_timer_start_time_fisrt_source_cap;
extern unsigned long pd_phy_dfp_timer_start_time_fr_swap_5v;
extern unsigned long pd_phy_dfp_timer_start_time_fr_swap_complete;
extern unsigned long pd_phy_dfp_timer_start_time_fr_swap_init;
extern unsigned long pd_phy_dfp_timer_start_time_hard_reset;
extern unsigned long pd_phy_dfp_timer_start_time_hard_reset_complete;
extern unsigned long pd_phy_dfp_timer_start_time_source_epr_keep_alive;
extern unsigned long pd_phy_dfp_timer_start_time_sink_epr_keep_alive;
extern unsigned long pd_phy_dfp_timer_start_time_no_responce;
extern unsigned long pd_phy_dfp_timer_start_time_pps_request;
extern unsigned long pd_phy_dfp_timer_start_time_pps_timeout;
extern unsigned long pd_phy_dfp_timer_start_time_prot_err_hard_reset;
extern unsigned long pd_phy_dfp_timer_start_time_prot_err_soft_reset;
extern unsigned long pd_phy_dfp_timer_start_time_pr_swap_wait;
extern unsigned long pd_phy_dfp_timer_start_time_ps_hard_reset;
extern unsigned long pd_phy_dfp_timer_start_time_spr_ps_source_off;
extern unsigned long pd_phy_dfp_timer_start_time_epr_ps_source_off;
extern unsigned long pd_phy_dfp_timer_start_time_ps_source_on;
extern unsigned long pd_phy_dfp_timer_start_time_spr_ps_transition;
extern unsigned long pd_phy_dfp_timer_start_time_epr_ps_transition;
extern unsigned long pd_phy_dfp_timer_start_time_receive;
extern unsigned long pd_phy_dfp_timer_start_time_receive_responce;
extern unsigned long pd_phy_dfp_timer_start_time_retry;
extern unsigned long pd_phy_dfp_timer_start_time_sender_responce;
extern unsigned long pd_phy_dfp_timer_start_time_sink_delay;
extern unsigned long pd_phy_dfp_timer_start_time_sink_tx;
extern unsigned long pd_phy_dfp_timer_start_time_soft_reset;
extern unsigned long pd_phy_dfp_timer_start_time_scr_holds_bus;
extern unsigned long pd_phy_dfp_timer_start_time_swap_sink_ready;
extern unsigned long pd_phy_dfp_timer_start_time_swap_source_start;
extern unsigned long pd_phy_dfp_timer_start_time_transmit;
extern unsigned long pd_phy_dfp_timer_start_time_type_c_send_source_cap;
extern unsigned long pd_phy_dfp_timer_start_time_type_c_sink_wait_cap;
extern unsigned long pd_phy_dfp_timer_start_time_vconn_source_discharge;
extern unsigned long pd_phy_dfp_timer_start_time_vconn_source_off;
extern unsigned long pd_phy_dfp_timer_start_time_vconn_source_on;
extern unsigned long pd_phy_dfp_timer_start_time_vconn_source_timeout;
extern unsigned long pd_phy_dfp_timer_start_time_vconn_swap_wait;
extern unsigned long pd_phy_dfp_timer_start_time_vdm_busy;
extern unsigned long pd_phy_dfp_timer_start_time_vdm_enter_mode;
extern unsigned long pd_phy_dfp_timer_start_time_vdm_exit_mode;
extern unsigned long pd_phy_dfp_timer_start_time_vdm_receiver_responce;
extern unsigned long pd_phy_dfp_timer_start_time_vdm_sender_responce;
extern unsigned long pd_phy_dfp_timer_start_time_vdm_wait_mode_entry;
extern unsigned long pd_phy_dfp_timer_start_time_vdm_wait_mode_exit;


//pd counter treshhold values 
//usb-if docs page 289
const int pd_phy_counter_th_busy = 5;
const int pd_phy_counter_th_caps = 50;
const int pd_phy_counter_th_discover_identity = 20;
const int pd_phy_counter_th_hard_reset = 2;
const int pd_phy_counter_th_message_id = 7;
const int pd_phy_counter_th_retry = 2;

//pd counter vars for ufp
//usb-if docs page 289
extern int pd_phy_ufp_counter_busy;
extern int pd_phy_ufp_counter_caps;
extern int pd_phy_ufp_counter_discover_identity;
extern int pd_phy_ufp_counter_hard_reset;
extern int pd_phy_ufp_counter_message_id;
extern int pd_phy_ufp_counter_retry;

//pd counter vars for dfp
//usb-if docs page 289
extern int pd_phy_dfp_counter_busy;
extern int pd_phy_dfp_counter_caps;
extern int pd_phy_dfp_counter_discover_identity;
extern int pd_phy_dfp_counter_hard_reset;
extern int pd_phy_dfp_counter_message_id;
extern int pd_phy_dfp_counter_retry;

//ufp/dfp enum
enum ufp_dfp {
    dfp,
    ufp
};

//fuction defines
void pd_phy_init ();
void pd_send_looking_4_connection (enum ufp_dfp ufp_dfp);



#endif // pd_phy_defines_h