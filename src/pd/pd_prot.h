//{usbc car module}
//{pd_prot.h}
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



#ifndef pd_prot_h
#define pd_prot_h

#include <Arduino.h>
#include "pd_phy.h"

//pd control messages
//usb-if docs page 131
const uint16_t pd_prot_cont_msg_goodcrc = 0x0001;
const uint16_t pd_prot_cont_msg_gotomin = 0x0002;
const uint16_t pd_prot_cont_msg_accept = 0x0003;
const uint16_t pd_prot_cont_msg_reject = 0x0004;
const uint16_t pd_prot_cont_msg_ping = 0x0005;
const uint16_t pd_prot_cont_msg_ps_rdy = 0x0006;
const uint16_t pd_prot_cont_msg_get_source_cap = 0x0007;
const uint16_t pd_prot_cont_msg_get_sink_cap = 0x0008;
const uint16_t pd_prot_cont_msg_dr_swap = 0x0009;
const uint16_t pd_prot_cont_msg_pr_swap = 0x000A;
const uint16_t pd_prot_cont_msg_vconn_swap = 0x000B;
const uint16_t pd_prot_cont_msg_wait = 0x000C;
const uint16_t pd_prot_cont_msg_soft_reset = 0x000D;
const uint16_t pd_prot_cont_msg_data_reset = 0x000E;
const uint16_t pd_prot_cont_msg_data_reset_complete = 0x000F;
const uint16_t pd_prot_cont_msg_not_supported = 0x0010;
const uint16_t pd_prot_cont_msg_get_status = 0x0011;
const uint16_t pd_prot_cont_msg_fr_swap = 0x0012;
const uint16_t pd_prot_cont_msg_get_pps_status = 0x0013;
const uint16_t pd_prot_cont_msg_get_country_codes = 0x0014;
const uint16_t pd_prot_cont_msg_get_sink_cap_extended = 0x0015;
const uint16_t pd_prot_cont_msg_get_souce_info = 0x0016;
const uint16_t pd_prot_cont_msg_get_revision = 0x0017;

//pd control message enum
enum pd_prot_cont_msg_enum {
    gotomin,
    accept,
    reject,
    ping,
    ps_rdy,
    get_source_cap,
    get_sink_cap,
    dr_swap,
    pr_swap,
    vconn_swap,
    wait,
    soft_reset_msg,
    data_reset_msg,
    data_reset_complete,
    not_supported,
    get_status,
    fr_swap,
    get_pps_status,
    get_country_codes,
    get_sink_cap_extended,
    get_source_info,
    get_revision
};

//pd data messgaes
//usb-if docs page 142
const uint16_t pd_prot_data_msg_source_capabilities = 0x0101;
const uint16_t pd_prot_data_msg_request = 0x0102;
const uint16_t pd_prot_data_msg_bist = 0x0103;
const uint16_t pd_prot_data_msg_sink_capabilities = 0x0104;
const uint16_t pd_prot_data_msg_battery_status = 0x0105;
const uint16_t pd_prot_data_msg_alert = 0x0106;
const uint16_t pd_prot_data_msg_get_country_info = 0x0107;
const uint16_t pd_prot_data_msg_enter_usb = 0x0108;
const uint16_t pd_prot_data_msg_epr_request = 0x0109;
const uint16_t pd_prot_data_msg_per_mode = 0x010A;
const uint16_t pd_prot_data_msg_source_info = 0x010B;
const uint16_t pd_prot_data_msg_vendor_defined =0x010F;

//pd data message enum
enum pd_prot_data_msg_enum {
    sounce_capabilitiys,
    request,
    bist,
    sink_capabilitiys,
    battery_status,
    alert,
    get_country_info,
    enter_usb_msg,
    epr_request,
    per_mode,
    source_info,
    vendor_defined,
    void_msg
};

//pd extended control messages
//usb-if docs page 232
const uint32_t pd_prot_ext_msg_source_capabilities_extended = 0x81010000;
const uint32_t pd_prot_ext_msg_status = 0x81020000;
const uint32_t pd_prot_ext_msg_get_battery_cap = 0x81030000;
const uint32_t pd_prot_ext_msg_get_battery_status = 0x81040000;
const uint32_t pd_prot_ext_msg_battery_capbilities = 0x81050000;
const uint32_t pd_prot_ext_msg_get_manufacturer_info = 0x81060000;
const uint32_t pd_prot_ext_msg_manufacturer_info = 0x81070000;
const uint32_t pd_prot_ext_msg_security_request = 0x81080000;
const uint32_t pd_prot_ext_msg_security_response = 0x81090000;
const uint32_t pd_prot_ext_msg_firmware_update_request = 0x810A0000;
const uint32_t pd_prot_ext_msg_firmware_update_response = 0x810B0000;
const uint32_t pd_prot_ext_msg_pps_status = 0x810C0000;
const uint32_t pd_prot_ext_msg_country_info = 0x810D0000;
const uint32_t pd_prot_ext_msg_country_codes = 0x810E0000;
const uint32_t pd_prot_ext_msg_sink_capabilities_extended = 0x810F0000;
const uint32_t pd_prot_ext_msg_extended_controll = 0x81800000;
const uint32_t pd_prot_ext_msg_epr_source_capabilites = 0x81810000;
const uint32_t pd_prot_ext_msg_epr_sink_capbilites = 0x81820000;
const uint32_t pd_prot_ext_msg_vendor_defined_extended = 0x818E0000;

//pd message header vars & const's
//usb-if docs page 119
extern int pd_prot_head_ufp_message_id;
extern int pd_prot_head_dfp_message_id;
const uint16_t pd_prot_head_ufp_data_role = 0x0000;
const uint16_t pd_prot_head_dfp_data_role = 0x0020;
const uint16_t pd_prot_head_spec_ver_1 = 0x0000;
const uint16_t pd_prot_head_spec_ver_2 = 0x0040;
const uint16_t pd_prot_head_spec_ver_3 = 0x0080;

//pd power data objects 
//usb-if docs page 144
const uint32_t pd_prot_pdo_vsafe_5v = 0x0C119024;
const uint32_t pd_prot_pdo_vsafe_5v_at_10 = 0x0C1190C8;
const uint32_t pd_prot_pdo_vsafe_5v_at_20 = 0x0C119190;
const uint32_t pd_prot_pdo_9v = 0x0012D024;
const uint32_t pd_prot_pdo_12v = 0x0013C024;
const uint32_t pd_prot_pdo_12v_at_40 = 0x0013C14D; //3.333 amps
const uint32_t pd_prot_pdo_15v = 0x0014B024;
const uint32_t pd_prot_pdo_15v_at_65 = 0x0014B1B1; //4.333 amps
const uint32_t pd_prot_pdo_20v = 0x001C8024;


//pd timer threshold vals
//time in ms
//usb-if docs page 271
const int pd_prot_timer_th_ac_temp_update = 500;
const int pd_prot_timer_th_bist_cont_mode = 60;
const int pd_prot_timer_th_shared_test_mode = 1000;
const int pd_prot_timer_th_cable_message = 1;
const int pd_prot_timer_th_chunking_not_supported = 50;
const int pd_prot_timer_th_chunk_receiver_request = 15;
const int pd_prot_timer_th_chunk_receiver_response = 15;
const int pd_prot_timer_th_chunk_sender_request = 30;
const int pd_prot_timer_th_chunk_sender_response = 30;
const int pd_prot_timer_th_data_reset = 250;
const int pd_prot_timer_th_data_reset_fail = 400;
const int pd_prot_timer_th_data_reset_fail_ufp = 550;
const int pd_prot_timer_th_discover_identity = 50;
const int pd_prot_timer_th_dr_swap_hard_reset = 15;
const int pd_prot_timer_th_dr_swap_wait = 100;
const int pd_prot_timer_th_enter_usb = 500;
const int pd_prot_timer_th_enter_usb_wait = 100;
const int pd_prot_timer_th_enter_epr = 550;
const int pd_prot_timer_th_epr_source_cable_discovery = 2000;
const int pd_prot_timer_th_first_source_cap = 250;
const int pd_prot_timer_th_fr_swap_5v = 15;
const int pd_prot_timer_th_fr_swap_complete = 15;
const int pd_prot_timer_th_fr_swap_init = 15;
const int pd_prot_timer_th_hard_reset = 5;
const int pd_prot_timer_th_hard_reset_complete = 5;
const int pd_prot_timer_th_source_epr_keep_alive = 1000;
const int pd_prot_timer_th_sink_epr_keep_alive = 500;
const int pd_prot_timer_th_no_response = 5500;
const int pd_prot_timer_th_pps_request = 10000;
const int pd_prot_timer_th_pps_timeout = 15000;
const int pd_prot_timer_th_prot_err_hard_reset = 15;
const int pd_prot_timer_th_prot_err_soft_reset = 15;
const int pd_prot_timer_th_pr_swap_wait = 100;
const int pd_prot_timer_th_ps_hard_reset = 35;
const int pd_prot_timer_th_spr_ps_source_off = 920;
const int pd_prot_timer_th_epr_ps_source_off = 1400;
const int pd_prot_timer_th_ps_source_on = 480;
const int pd_prot_timer_th_spr_ps_transition = 550;
const int pd_prot_timer_th_epr_ps_transition = 1020;
const int pd_prot_timer_th_receive = 1;
const int pd_prot_timer_th_receive_response = 15;
const int pd_prot_timer_th_retry = 195;
const int pd_prot_timer_th_sender_response = 33;
const int pd_prot_timer_th_sink_delay = 5;
const int pd_prot_timer_th_sink_tx = 20;
const int pd_prot_timer_th_soft_reset = 15;
const int pd_prot_timer_th_scr_holds_bus = 50;
const int pd_prot_timer_th_swap_sink_ready = 15;
const int pd_prot_timer_th_swap_source_start = 20;
const int pd_prot_timer_th_transmit = 195;
const int pd_prot_timer_th_type_c_send_source_cap = 200;
const int pd_prot_timer_th_type_c_sink_wait_cap = 620;
const int pd_prot_timer_th_vconn_source_discharge = 240;
const int pd_prot_timer_th_vconn_source_off = 25;
const int pd_prot_timer_th_vconn_source_on = 50;
const int pd_prot_timer_th_vconn_source_timeout = 200;
const int pd_prot_timer_th_vconn_swap_wait = 100;
const int pd_prot_timer_th_vdm_busy = 50;
const int pd_prot_timer_th_vdm_enter_mode = 25;
const int pd_prot_timer_th_vdm_exit_mode = 25;
const int pd_prot_timer_th_vdm_receiver_response = 15;
const int pd_prot_timer_th_vdm_sender_response = 30;
const int pd_prot_timer_th_vdm_wait_mode_entry = 50;
const int pd_prot_timer_th_vdm_wait_mode_exit = 50;
const int pd_prot_timer_th_source_pps_comm = 15000;

//pd timer start times for ufp
//usb-if docs page 271
extern unsigned long pd_prot_ufp_timer_start_time_ac_temp_update;
extern unsigned long pd_prot_ufp_timer_start_time_bist_cont_mode;
extern unsigned long pd_prot_ufp_timer_start_time_shared_test_mode;
extern unsigned long pd_prot_ufp_timer_start_time_cable_message;
extern unsigned long pd_prot_ufp_timer_start_time_chunking_not_supported;
extern unsigned long pd_prot_ufp_timer_start_time_chunk_receiver_request;
extern unsigned long pd_prot_ufp_timer_start_time_chunk_receiver_response;
extern unsigned long pd_prot_ufp_timer_start_time_chunk_sender_request;
extern unsigned long pd_prot_ufp_timer_start_time_chunk_sender_response;
extern unsigned long pd_prot_ufp_timer_start_time_data_reset;
extern unsigned long pd_prot_ufp_timer_start_time_data_reset_fail;
extern unsigned long pd_prot_ufp_timer_start_time_data_reset_fail_ufp;
extern unsigned long pd_prot_ufp_timer_start_time_discover_identity;
extern unsigned long pd_prot_ufp_timer_start_time_dr_swap_hard_reset;
extern unsigned long pd_prot_ufp_timer_start_time_dr_swap_wait;
extern unsigned long pd_prot_ufp_timer_start_time_enter_usb;
extern unsigned long pd_prot_ufp_timer_start_time_enter_usb_wait;
extern unsigned long pd_prot_ufp_timer_start_time_enter_epr;
extern unsigned long pd_prot_ufp_timer_start_time_epr_source_cable_discovery;
extern unsigned long pd_prot_ufp_timer_start_time_first_source_cap;
extern unsigned long pd_prot_ufp_timer_start_time_fr_swap_5v;
extern unsigned long pd_prot_ufp_timer_start_time_fr_swap_complete;
extern unsigned long pd_prot_ufp_timer_start_time_fr_swap_init;
extern unsigned long pd_prot_ufp_timer_start_time_hard_reset;
extern unsigned long pd_prot_ufp_timer_start_time_hard_reset_complete;
extern unsigned long pd_prot_ufp_timer_start_time_source_epr_keep_alive;
extern unsigned long pd_prot_ufp_timer_start_time_sink_epr_keep_alive;
extern unsigned long pd_prot_ufp_timer_start_time_no_response;
extern unsigned long pd_prot_ufp_timer_start_time_pps_request;
extern unsigned long pd_prot_ufp_timer_start_time_pps_timeout;
extern unsigned long pd_prot_ufp_timer_start_time_prot_err_hard_reset;
extern unsigned long pd_prot_ufp_timer_start_time_prot_err_soft_reset;
extern unsigned long pd_prot_ufp_timer_start_time_pr_swap_wait;
extern unsigned long pd_prot_ufp_timer_start_time_ps_hard_reset;
extern unsigned long pd_prot_ufp_timer_start_time_spr_ps_source_off;
extern unsigned long pd_prot_ufp_timer_start_time_epr_ps_source_off;
extern unsigned long pd_prot_ufp_timer_start_time_ps_source_on;
extern unsigned long pd_prot_ufp_timer_start_time_spr_ps_transition;
extern unsigned long pd_prot_ufp_timer_start_time_epr_ps_transition;
extern unsigned long pd_prot_ufp_timer_start_time_receive;
extern unsigned long pd_prot_ufp_timer_start_time_receive_response;
extern unsigned long pd_prot_ufp_timer_start_time_retry;
extern unsigned long pd_prot_ufp_timer_start_time_sender_response;
extern unsigned long pd_prot_ufp_timer_start_time_sink_delay;
extern unsigned long pd_prot_ufp_timer_start_time_sink_tx;
extern unsigned long pd_prot_ufp_timer_start_time_soft_reset;
extern unsigned long pd_prot_ufp_timer_start_time_scr_holds_bus;
extern unsigned long pd_prot_ufp_timer_start_time_swap_sink_ready;
extern unsigned long pd_prot_ufp_timer_start_time_swap_source_start;
extern unsigned long pd_prot_ufp_timer_start_time_transmit;
extern unsigned long pd_prot_ufp_timer_start_time_type_c_send_source_cap;
extern unsigned long pd_prot_ufp_timer_start_time_type_c_sink_wait_cap;
extern unsigned long pd_prot_ufp_timer_start_time_vconn_source_discharge;
extern unsigned long pd_prot_ufp_timer_start_time_vconn_source_off;
extern unsigned long pd_prot_ufp_timer_start_time_vconn_source_on;
extern unsigned long pd_prot_ufp_timer_start_time_vconn_source_timeout;
extern unsigned long pd_prot_ufp_timer_start_time_vconn_swap_wait;
extern unsigned long pd_prot_ufp_timer_start_time_vdm_busy;
extern unsigned long pd_prot_ufp_timer_start_time_vdm_enter_mode;
extern unsigned long pd_prot_ufp_timer_start_time_vdm_exit_mode;
extern unsigned long pd_prot_ufp_timer_start_time_vdm_receiver_response;
extern unsigned long pd_prot_ufp_timer_start_time_vdm_sender_response;
extern unsigned long pd_prot_ufp_timer_start_time_vdm_wait_mode_entry;
extern unsigned long pd_prot_ufp_timer_start_time_vdm_wait_mode_exit;
extern unsigned long pd_prot_ufp_timer_start_time_source_pps_comm;

//pd timer start times for dfp
//usb-if docs page 271
extern unsigned long pd_prot_dfp_timer_start_time_ac_temp_update;
extern unsigned long pd_prot_dfp_timer_start_time_bist_cont_mode;
extern unsigned long pd_prot_dfp_timer_start_time_shared_test_mode;
extern unsigned long pd_prot_dfp_timer_start_time_cable_message;
extern unsigned long pd_prot_dfp_timer_start_time_chunking_not_supported;
extern unsigned long pd_prot_dfp_timer_start_time_chunk_receiver_request;
extern unsigned long pd_prot_dfp_timer_start_time_chunk_receiver_response;
extern unsigned long pd_prot_dfp_timer_start_time_chunk_sender_request;
extern unsigned long pd_prot_dfp_timer_start_time_chunk_sender_response;
extern unsigned long pd_prot_dfp_timer_start_time_data_reset;
extern unsigned long pd_prot_dfp_timer_start_time_data_reset_fail;
extern unsigned long pd_prot_dfp_timer_start_time_data_reset_fail_ufp;
extern unsigned long pd_prot_dfp_timer_start_time_discover_identity;
extern unsigned long pd_prot_dfp_timer_start_time_dr_swap_hard_reset;
extern unsigned long pd_prot_dfp_timer_start_time_dr_swap_wait;
extern unsigned long pd_prot_dfp_timer_start_time_enter_usb;
extern unsigned long pd_prot_dfp_timer_start_time_enter_usb_wait;
extern unsigned long pd_prot_dfp_timer_start_time_enter_epr;
extern unsigned long pd_prot_dfp_timer_start_time_epr_source_cable_discovery;
extern unsigned long pd_prot_dfp_timer_start_time_first_source_cap;
extern unsigned long pd_prot_dfp_timer_start_time_fr_swap_5v;
extern unsigned long pd_prot_dfp_timer_start_time_fr_swap_complete;
extern unsigned long pd_prot_dfp_timer_start_time_fr_swap_init;
extern unsigned long pd_prot_dfp_timer_start_time_hard_reset;
extern unsigned long pd_prot_dfp_timer_start_time_hard_reset_complete;
extern unsigned long pd_prot_dfp_timer_start_time_source_epr_keep_alive;
extern unsigned long pd_prot_dfp_timer_start_time_sink_epr_keep_alive;
extern unsigned long pd_prot_dfp_timer_start_time_no_response;
extern unsigned long pd_prot_dfp_timer_start_time_pps_request;
extern unsigned long pd_prot_dfp_timer_start_time_pps_timeout;
extern unsigned long pd_prot_dfp_timer_start_time_prot_err_hard_reset;
extern unsigned long pd_prot_dfp_timer_start_time_prot_err_soft_reset;
extern unsigned long pd_prot_dfp_timer_start_time_pr_swap_wait;
extern unsigned long pd_prot_dfp_timer_start_time_ps_hard_reset;
extern unsigned long pd_prot_dfp_timer_start_time_spr_ps_source_off;
extern unsigned long pd_prot_dfp_timer_start_time_epr_ps_source_off;
extern unsigned long pd_prot_dfp_timer_start_time_ps_source_on;
extern unsigned long pd_prot_dfp_timer_start_time_spr_ps_transition;
extern unsigned long pd_prot_dfp_timer_start_time_epr_ps_transition;
extern unsigned long pd_prot_dfp_timer_start_time_receive;
extern unsigned long pd_prot_dfp_timer_start_time_receive_responce;
extern unsigned long pd_prot_dfp_timer_start_time_retry;
extern unsigned long pd_prot_dfp_timer_start_time_sender_responce;
extern unsigned long pd_prot_dfp_timer_start_time_sink_delay;
extern unsigned long pd_prot_dfp_timer_start_time_sink_tx;
extern unsigned long pd_prot_dfp_timer_start_time_soft_reset;
extern unsigned long pd_prot_dfp_timer_start_time_scr_holds_bus;
extern unsigned long pd_prot_dfp_timer_start_time_swap_sink_ready;
extern unsigned long pd_prot_dfp_timer_start_time_swap_source_start;
extern unsigned long pd_prot_dfp_timer_start_time_transmit;
extern unsigned long pd_prot_dfp_timer_start_time_type_c_send_source_cap;
extern unsigned long pd_prot_dfp_timer_start_time_type_c_sink_wait_cap;
extern unsigned long pd_prot_dfp_timer_start_time_vconn_source_discharge;
extern unsigned long pd_prot_dfp_timer_start_time_vconn_source_off;
extern unsigned long pd_prot_dfp_timer_start_time_vconn_source_on;
extern unsigned long pd_prot_dfp_timer_start_time_vconn_source_timeout;
extern unsigned long pd_prot_dfp_timer_start_time_vconn_swap_wait;
extern unsigned long pd_prot_dfp_timer_start_time_vdm_busy;
extern unsigned long pd_prot_dfp_timer_start_time_vdm_enter_mode;
extern unsigned long pd_prot_dfp_timer_start_time_vdm_exit_mode;
extern unsigned long pd_prot_dfp_timer_start_time_vdm_receiver_responce;
extern unsigned long pd_prot_dfp_timer_start_time_vdm_sender_responce;
extern unsigned long pd_prot_dfp_timer_start_time_vdm_wait_mode_entry;
extern unsigned long pd_prot_dfp_timer_start_time_vdm_wait_mode_exit;
extern unsigned long pd_prot_dfp_timer_start_time_source_pps_comm;

//pd timer names enum
enum pd_prot_timer_names {
ac_temp_update,
bist_cont_mode,
shared_test_mode,
cable_message,
chunking_not_supported,
chunk_recevier_request,
chunk_recevier_response,
chunk_sender_request,
chunk_sender_response,
data_reset,
data_reset_fail,
data_reset_fail_ufp,
discover_identity,
dr_swap_hard_reset,
dr_swap_wait,
enter_usb,
enter_usb_wait,
enter_epr,
epr_soruce_cable_discovvery,
fisrt_source_cap,
fr_swap_5v,
fr_swap_complete,
fr_swap_init,
hard_reset,
hard_reset_complete,
source_epr_keep_alive,
sink_epr_keep_alive,
no_responce,
pps_request,
pps_timeout,
prot_err_hard_reset,
prot_err_soft_reset,
pr_swap_wait,
ps_hard_reset,
spr_ps_source_off,
epr_ps_source_off,
ps_source_on,
spr_ps_transition,
epr_ps_transition,
receive,
receive_response,
retry,
sender_response,
sink_delay,
sink_tx,
soft_reset,
scr_holds_bus,
swap_sink_ready,
swap_source_start,
transmit,
type_c_send_source_cap,
type_c_sink_wait_cap,
vconn_source_discharge,
vconn_source_off,
vconn_source_on,
vconn_source_timeout,
vconn_swap_wait,
vdm_busy,
vdm_enter_mode,
vdm_exit_mode,
vdm_receiver_responce,
vdm_sender_responce,
vdm_wait_mode_entry,
vdm_wait_mode_exit,
source_pps_comm
};

//enum for start/stop of timers
enum pd_prot_timer_start_stop {start, stop};

//pd counter treshhold values 
//usb-if docs page 289
const int pd_prot_counter_th_busy = 5;
const int pd_prot_counter_th_caps = 50;
const int pd_prot_counter_th_discover_identity = 20;
const int pd_prot_counter_th_hard_reset = 2;
const int pd_prot_counter_th_message_id = 7;
const int pd_prot_counter_th_retry = 2;

//pd counter vars for ufp
//usb-if docs page 289
extern int pd_prot_ufp_counter_busy;
extern int pd_prot_ufp_counter_caps;
extern int pd_prot_ufp_counter_discover_identity;
extern int pd_prot_ufp_counter_hard_reset;
extern int pd_prot_ufp_counter_message_id;
extern int pd_prot_ufp_counter_retry;

//pd counter vars for dfp
//usb-if docs page 289
extern int pd_prot_dfp_counter_busy;
extern int pd_prot_dfp_counter_caps;
extern int pd_prot_dfp_counter_discover_identity;
extern int pd_prot_dfp_counter_hard_reset;
extern int pd_prot_dfp_counter_message_id;
extern int pd_prot_dfp_counter_retry;

//retransmit vars
extern bool pd_prot_ufp_retransit_failled;
extern bool pd_prot_dfp_retransit_failled;
extern uint8_t pd_prot_ufp_last_message [255];
extern int pd_prot_ufp_last_message_length;
extern uint8_t pd_prot_dfp_last_message [255];
extern int pd_prot_dfp_last_message_length;

//enum for power cap 
enum pd_prot_power_cap_enum {
    watts_100,
    watts_65,
    watts_40,
    watts_20,
    watts_10
};

//enum for current policy engine state
enum pd_port_policy_engine_state_enum {
    pe_src_hard_reset_recived,
    pe_src_transition_to_dflt,
    pe_src_hard_reset,
    pe_src_startup,
    pe_src_discovery,
    pe_src_send_capabilitiys,
    pe_src_disabled,
    pe_src_negotiate_capabilitiys,
    pe_src_transition_supply,
    pe_src_ready,
    pe_src_epr_keep_alive,
    pe_src_get_sink_cap,
    pe_src_give_souce_cap,
    pe_src_capabilitiy_response,
    pe_src_wait_new_capabilitiys,
    error_recovery
};

//previous policy engine state vars
extern enum pd_port_policy_engine_state_enum pd_prot_ufp_pe_prev_state;
extern enum pd_port_policy_engine_state_enum pd_prot_dfp_pe_prev_state;

//selcted port power (in watts)
extern enum pd_prot_power_cap_enum pd_prot_ufp_current_power_cap;
extern enum pd_prot_power_cap_enum pd_prot_dfp_current_power_cap;

//vars for sink necgotiation
extern int pd_prot_ufp_negotiated_sink_voltage;
extern bool pd_prot_ufp_negotiated_sink_met; //true if we can souce the negotiated voltage
extern int pd_prot_dfp_negotiated_sink_voltage;
extern bool pd_prot_dfp_negotiated_sink_met; //true if we can souce the negotiated voltage

//enum for port power role
enum pd_prot_port_power_role {src, sink};

//enumm for headder type 
enum pd_prot_message_type_enum {normal, extended};

//abort flags
extern bool pd_prot_ufp_abbort_flag;
extern bool pd_prot_dfp_abbort_flag;

//flags for the policy engine
extern bool pd_prot_ufp_last_good_crc;
extern bool pd_prot_dfp_last_good_crc;
extern enum ufp_dfp pd_prot_ufp_pe_port_data_role;
extern enum ufp_dfp pd_prot_dfp_pe_port_data_role;
extern enum pd_port_policy_engine_state_enum pd_prot_ufp_pe_current_state;
extern enum pd_port_policy_engine_state_enum pd_prot_dfp_pe_current_state;

//function defines
void pd_prot_hard_reset_handeler (enum ufp_dfp ufp_dfp, bool from_policy_engine);








#endif // pd_prot_h