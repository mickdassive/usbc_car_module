//{usbc car module}
//{pd_prot.cpp}
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

#ifndef pd_prot_cpp
#define pd_prot_cpp

#include <Arduino.h>
#include <Wire.h>
#include "pd_prot.h"
#include "pd_phy.h"


//pd counters
int pd_prot_head_ufp_message_id = 0;
int pd_prot_head_dfp_message_id = 0;

//pd counter vars for ufp
//usb-if docs page 289
int pd_prot_ufp_counter_busy = 0;
int pd_prot_ufp_counter_caps = 0;
int pd_prot_ufp_counter_discover_identity = 0;
int pd_prot_ufp_counter_hard_reset = 0;
int pd_prot_ufp_counter_message_id = 0;
int pd_prot_ufp_counter_retry = 0;

//pd counter vars for dfp
//usb-if docs page 289
int pd_prot_dfp_counter_busy = 0;
int pd_prot_dfp_counter_caps = 0;
int pd_prot_dfp_counter_discover_identity = 0;
int pd_prot_dfp_counter_hard_reset = 0;
int pd_prot_dfp_counter_message_id = 0;
int pd_prot_dfp_counter_retry = 0;


//pd timer start times for ufp
//usb-if docs page 271
unsigned long pd_prot_ufp_timer_start_time_ac_temp_update = 0;
unsigned long pd_prot_ufp_timer_start_time_bist_cont_mode = 0;
unsigned long pd_prot_ufp_timer_start_time_shared_test_mode = 0;
unsigned long pd_prot_ufp_timer_start_time_cable_message = 0;
unsigned long pd_prot_ufp_timer_start_time_chunking_not_supported = 0;
unsigned long pd_prot_ufp_timer_start_time_chunk_recevier_request = 0;
unsigned long pd_prot_ufp_timer_start_time_chunk_recevier_response = 0;
unsigned long pd_prot_ufp_timer_start_time_chunk_sender_request = 0;
unsigned long pd_prot_ufp_timer_start_time_chunk_sender_response = 0;
unsigned long pd_prot_ufp_timer_start_time_data_reset = 0;
unsigned long pd_prot_ufp_timer_start_time_data_reset_fail = 0;
unsigned long pd_prot_ufp_timer_start_time_data_reset_fail_ufp = 0;
unsigned long pd_prot_ufp_timer_start_time_discover_identity = 0;
unsigned long pd_prot_ufp_timer_start_time_dr_swap_hard_reset = 0;
unsigned long pd_prot_ufp_timer_start_time_dr_swap_wait = 0;
unsigned long pd_prot_ufp_timer_start_time_enter_usb = 0;
unsigned long pd_prot_ufp_timer_start_time_enter_usb_wait = 0;
unsigned long pd_prot_ufp_timer_start_time_enter_epr = 0;
unsigned long pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery = 0;
unsigned long pd_prot_ufp_timer_start_time_fisrt_source_cap = 0;
unsigned long pd_prot_ufp_timer_start_time_fr_swap_5v = 0;
unsigned long pd_prot_ufp_timer_start_time_fr_swap_complete = 0;
unsigned long pd_prot_ufp_timer_start_time_fr_swap_init = 0;
unsigned long pd_prot_ufp_timer_start_time_hard_reset = 0;
unsigned long pd_prot_ufp_timer_start_time_hard_reset_complete = 0;
unsigned long pd_prot_ufp_timer_start_time_source_epr_keep_alive = 0;
unsigned long pd_prot_ufp_timer_start_time_sink_epr_keep_alive = 0;
unsigned long pd_prot_ufp_timer_start_time_no_responce = 0;
unsigned long pd_prot_ufp_timer_start_time_pps_request = 0;
unsigned long pd_prot_ufp_timer_start_time_pps_timeout = 0;
unsigned long pd_prot_ufp_timer_start_time_prot_err_hard_reset = 0;
unsigned long pd_prot_ufp_timer_start_time_prot_err_soft_reset = 0;
unsigned long pd_prot_ufp_timer_start_time_pr_swap_wait = 0;
unsigned long pd_prot_ufp_timer_start_time_ps_hard_reset = 0;
unsigned long pd_prot_ufp_timer_start_time_spr_ps_source_off = 0;
unsigned long pd_prot_ufp_timer_start_time_epr_ps_source_off = 0;
unsigned long pd_prot_ufp_timer_start_time_ps_source_on = 0;
unsigned long pd_prot_ufp_timer_start_time_spr_ps_transition = 0;
unsigned long pd_prot_ufp_timer_start_time_epr_ps_transition = 0;
unsigned long pd_prot_ufp_timer_start_time_receive = 0;
unsigned long pd_prot_ufp_timer_start_time_receive_responce = 0;
unsigned long pd_prot_ufp_timer_start_time_retry = 0;
unsigned long pd_prot_ufp_timer_start_time_sender_responce = 0;
unsigned long pd_prot_ufp_timer_start_time_sink_delay = 0;
unsigned long pd_prot_ufp_timer_start_time_sink_tx = 0;
unsigned long pd_prot_ufp_timer_start_time_soft_reset = 0;
unsigned long pd_prot_ufp_timer_start_time_scr_holds_bus = 0;
unsigned long pd_prot_ufp_timer_start_time_swap_sink_ready = 0;
unsigned long pd_prot_ufp_timer_start_time_swap_source_start = 0;
unsigned long pd_prot_ufp_timer_start_time_transmit = 0;
unsigned long pd_prot_ufp_timer_start_time_type_c_send_source_cap = 0;
unsigned long pd_prot_ufp_timer_start_time_type_c_sink_wait_cap = 0;
unsigned long pd_prot_ufp_timer_start_time_vconn_source_discharge = 0;
unsigned long pd_prot_ufp_timer_start_time_vconn_source_off = 0;
unsigned long pd_prot_ufp_timer_start_time_vconn_source_on = 0;
unsigned long pd_prot_ufp_timer_start_time_vconn_source_timeout = 0;
unsigned long pd_prot_ufp_timer_start_time_vconn_swap_wait = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_busy = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_enter_mode = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_exit_mode = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_receiver_responce = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_sender_responce = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_wait_mode_entry = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_wait_mode_exit = 0;

//pd timer start times for dfp
//usb-if docs page 271
unsigned long pd_prot_dfp_timer_start_time_ac_temp_update = 0;
unsigned long pd_prot_dfp_timer_start_time_bist_cont_mode = 0;
unsigned long pd_prot_dfp_timer_start_time_shared_test_mode = 0;
unsigned long pd_prot_dfp_timer_start_time_cable_message = 0;
unsigned long pd_prot_dfp_timer_start_time_chunking_not_supported = 0;
unsigned long pd_prot_dfp_timer_start_time_chunk_recevier_request = 0;
unsigned long pd_prot_dfp_timer_start_time_chunk_recevier_response = 0;
unsigned long pd_prot_dfp_timer_start_time_chunk_sender_request = 0;
unsigned long pd_prot_dfp_timer_start_time_chunk_sender_response = 0;
unsigned long pd_prot_dfp_timer_start_time_data_reset = 0;
unsigned long pd_prot_dfp_timer_start_time_data_reset_fail = 0;
unsigned long pd_prot_dfp_timer_start_time_data_reset_fail_ufp = 0;
unsigned long pd_prot_dfp_timer_start_time_discover_identity = 0;
unsigned long pd_prot_dfp_timer_start_time_dr_swap_hard_reset = 0;
unsigned long pd_prot_dfp_timer_start_time_dr_swap_wait = 0;
unsigned long pd_prot_dfp_timer_start_time_enter_usb = 0;
unsigned long pd_prot_dfp_timer_start_time_enter_usb_wait = 0;
unsigned long pd_prot_dfp_timer_start_time_enter_epr = 0;
unsigned long pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery = 0;
unsigned long pd_prot_dfp_timer_start_time_fisrt_source_cap = 0;
unsigned long pd_prot_dfp_timer_start_time_fr_swap_5v = 0;
unsigned long pd_prot_dfp_timer_start_time_fr_swap_complete = 0;
unsigned long pd_prot_dfp_timer_start_time_fr_swap_init = 0;
unsigned long pd_prot_dfp_timer_start_time_hard_reset = 0;
unsigned long pd_prot_dfp_timer_start_time_hard_reset_complete = 0;
unsigned long pd_prot_dfp_timer_start_time_source_epr_keep_alive = 0;
unsigned long pd_prot_dfp_timer_start_time_sink_epr_keep_alive = 0;
unsigned long pd_prot_dfp_timer_start_time_no_responce = 0;
unsigned long pd_prot_dfp_timer_start_time_pps_request = 0;
unsigned long pd_prot_dfp_timer_start_time_pps_timeout = 0;
unsigned long pd_prot_dfp_timer_start_time_prot_err_hard_reset = 0;
unsigned long pd_prot_dfp_timer_start_time_prot_err_soft_reset = 0;
unsigned long pd_prot_dfp_timer_start_time_pr_swap_wait = 0;
unsigned long pd_prot_dfp_timer_start_time_ps_hard_reset = 0;
unsigned long pd_prot_dfp_timer_start_time_spr_ps_source_off = 0;
unsigned long pd_prot_dfp_timer_start_time_epr_ps_source_off = 0;
unsigned long pd_prot_dfp_timer_start_time_ps_source_on = 0;
unsigned long pd_prot_dfp_timer_start_time_spr_ps_transition = 0;
unsigned long pd_prot_dfp_timer_start_time_epr_ps_transition = 0;
unsigned long pd_prot_dfp_timer_start_time_receive = 0;
unsigned long pd_prot_dfp_timer_start_time_receive_responce = 0;
unsigned long pd_prot_dfp_timer_start_time_retry = 0;
unsigned long pd_prot_dfp_timer_start_time_sender_responce = 0;
unsigned long pd_prot_dfp_timer_start_time_sink_delay = 0;
unsigned long pd_prot_dfp_timer_start_time_sink_tx = 0;
unsigned long pd_prot_dfp_timer_start_time_soft_reset = 0;
unsigned long pd_prot_dfp_timer_start_time_scr_holds_bus = 0;
unsigned long pd_prot_dfp_timer_start_time_swap_sink_ready = 0;
unsigned long pd_prot_dfp_timer_start_time_swap_source_start = 0;
unsigned long pd_prot_dfp_timer_start_time_transmit = 0;
unsigned long pd_prot_dfp_timer_start_time_type_c_send_source_cap = 0;
unsigned long pd_prot_dfp_timer_start_time_type_c_sink_wait_cap = 0;
unsigned long pd_prot_dfp_timer_start_time_vconn_source_discharge = 0;
unsigned long pd_prot_dfp_timer_start_time_vconn_source_off = 0;
unsigned long pd_prot_dfp_timer_start_time_vconn_source_on = 0;
unsigned long pd_prot_dfp_timer_start_time_vconn_source_timeout = 0;
unsigned long pd_prot_dfp_timer_start_time_vconn_swap_wait = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_busy = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_enter_mode = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_exit_mode = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_receiver_responce = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_sender_responce = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_wait_mode_entry = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_wait_mode_exit = 0;

//retransmit vars
bool pd_prot_ufp_retransit_failled = false;
bool pd_prot_dfp_retransit_failled = false;
uint8_t pd_prot_ufp_last_message[256];
int pd_prot_ufp_last_message_length = 0;
uint8_t pd_prot_dfp_last_message[256];
int pd_prot_dfp_last_message_length = 0;

//selcted port power (in watts)
extern enum pd_prot_power_cap_enum pd_prot_ufp_current_power_cap = watts_100;
extern enum pd_prot_power_cap_enum pd_prot_dfp_current_power_cap = watts_100;

//abort flags
bool pd_prot_ufp_abbort_flag = false;
bool pd_prot_dfp_abbort_flag = false;


void pd_prot_timer_handeler() {
    //init time var
    unsigned long current_time = millis();


    if (((current_time - pd_prot_ufp_timer_start_time_ac_temp_update) > pd_prot_timer_th_ac_temp_update) && pd_prot_ufp_timer_start_time_ac_temp_update != 0) {
        //ac_temp_update
    }   
    else if (((current_time - pd_prot_dfp_timer_start_time_ac_temp_update) > pd_prot_timer_th_ac_temp_update) && pd_prot_dfp_timer_start_time_ac_temp_update != 0) {
        //ac_temp_update
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_bist_cont_mode) > pd_prot_timer_th_bist_cont_mode) && pd_prot_ufp_timer_start_time_bist_cont_mode != 0) {
        //bist_cont_mode
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_bist_cont_mode) > pd_prot_timer_th_bist_cont_mode) && pd_prot_dfp_timer_start_time_bist_cont_mode != 0) {
        //bist_cont_mode
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_shared_test_mode) > pd_prot_timer_th_shared_test_mode) && pd_prot_ufp_timer_start_time_shared_test_mode != 0) {
        //shared_test_mode
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_shared_test_mode) > pd_prot_timer_th_shared_test_mode) && pd_prot_dfp_timer_start_time_shared_test_mode != 0) {
        //shared_test_mode
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_cable_message) > pd_prot_timer_th_cable_message) && pd_prot_ufp_timer_start_time_cable_message != 0) {
        //cable_message
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_cable_message) > pd_prot_timer_th_cable_message) && pd_prot_dfp_timer_start_time_cable_message != 0) {
        //cable_message
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_chunking_not_supported) > pd_prot_timer_th_chunking_not_supported) && pd_prot_ufp_timer_start_time_chunking_not_supported != 0) {
        //chunking_not_supported
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_chunking_not_supported) > pd_prot_timer_th_chunking_not_supported) && pd_prot_dfp_timer_start_time_chunking_not_supported != 0) {
        //chunking_not_supported
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_chunk_recevier_request) > pd_prot_timer_th_chunk_recevier_request) && pd_prot_ufp_timer_start_time_chunk_recevier_request != 0) {
        //chunk_recevier_request
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_chunk_recevier_request) > pd_prot_timer_th_chunk_recevier_request) && pd_prot_dfp_timer_start_time_chunk_recevier_request != 0) {
        //chunk_recevier_request
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_chunk_recevier_response) > pd_prot_timer_th_chunk_recevier_response) && pd_prot_ufp_timer_start_time_chunk_recevier_response != 0) {
        //chunk_recevier_response
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_chunk_recevier_response) > pd_prot_timer_th_chunk_recevier_response) && pd_prot_dfp_timer_start_time_chunk_recevier_response != 0) {
        //chunk_recevier_response
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_chunk_sender_request) > pd_prot_timer_th_chunk_sender_request) && pd_prot_ufp_timer_start_time_chunk_sender_request != 0) {
        //chunk_sender_request
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_chunk_sender_request) > pd_prot_timer_th_chunk_sender_request) && pd_prot_dfp_timer_start_time_chunk_sender_request != 0) {
        //chunk_sender_request
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_chunk_sender_response) > pd_prot_timer_th_chunk_sender_response) && pd_prot_ufp_timer_start_time_chunk_sender_response != 0) {
        //chunk_sender_response
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_chunk_sender_response) > pd_prot_timer_th_chunk_sender_response) && pd_prot_dfp_timer_start_time_chunk_sender_response != 0) {
        //chunk_sender_response
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_data_reset) > pd_prot_timer_th_data_reset) && pd_prot_ufp_timer_start_time_data_reset != 0) {
        //data_reset
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_data_reset) > pd_prot_timer_th_data_reset) && pd_prot_dfp_timer_start_time_data_reset != 0) {
        //data_reset
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_data_reset_fail) > pd_prot_timer_th_data_reset_fail) && pd_prot_ufp_timer_start_time_data_reset_fail != 0) {
        //data_reset_fail
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_data_reset_fail) > pd_prot_timer_th_data_reset_fail) && pd_prot_dfp_timer_start_time_data_reset_fail != 0) {
        //data_reset_fail
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_data_reset_fail_ufp) > pd_prot_timer_th_data_reset_fail_ufp) && pd_prot_ufp_timer_start_time_data_reset_fail_ufp != 0) {
        //data_reset_fail_ufp
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_data_reset_fail_ufp) > pd_prot_timer_th_data_reset_fail_ufp) && pd_prot_dfp_timer_start_time_data_reset_fail_ufp != 0) {
        //data_reset_fail_ufp
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_discover_identity) > pd_prot_timer_th_discover_identity) && pd_prot_ufp_timer_start_time_discover_identity != 0) {
        //discover_identity
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_discover_identity) > pd_prot_timer_th_discover_identity) && pd_prot_dfp_timer_start_time_discover_identity != 0) {
        //discover_identity
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_dr_swap_hard_reset) > pd_prot_timer_th_dr_swap_hard_reset) && pd_prot_ufp_timer_start_time_dr_swap_hard_reset != 0) {
        //dr_swap_hard_reset
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_dr_swap_hard_reset) > pd_prot_timer_th_dr_swap_hard_reset) && pd_prot_dfp_timer_start_time_dr_swap_hard_reset != 0) {
        //dr_swap_hard_reset
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_dr_swap_wait) > pd_prot_timer_th_dr_swap_wait) && pd_prot_ufp_timer_start_time_dr_swap_wait != 0) {
        //dr_swap_wait
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_dr_swap_wait) > pd_prot_timer_th_dr_swap_wait) && pd_prot_dfp_timer_start_time_dr_swap_wait != 0) {
        //dr_swap_wait
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_enter_usb) > pd_prot_timer_th_enter_usb) && pd_prot_ufp_timer_start_time_enter_usb != 0) {
        //enter_usb
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_enter_usb) > pd_prot_timer_th_enter_usb) && pd_prot_dfp_timer_start_time_enter_usb != 0) {
        //enter_usb
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_enter_usb_wait) > pd_prot_timer_th_enter_usb_wait) && pd_prot_ufp_timer_start_time_enter_usb_wait != 0) {
        //enter_usb_wait
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_enter_usb_wait) > pd_prot_timer_th_enter_usb_wait) && pd_prot_dfp_timer_start_time_enter_usb_wait != 0) {
        //enter_usb_wait
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_enter_epr) > pd_prot_timer_th_enter_epr) && pd_prot_ufp_timer_start_time_enter_epr != 0) {
        //enter_epr
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_enter_epr) > pd_prot_timer_th_enter_epr) && pd_prot_dfp_timer_start_time_enter_epr != 0) {
        //enter_epr
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery) > pd_prot_timer_th_epr_soruce_cable_discovvery) && pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery != 0) {
        //epr_soruce_cable_discovvery
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery) > pd_prot_timer_th_epr_soruce_cable_discovvery) && pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery != 0) {
        //epr_soruce_cable_discovvery
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_fisrt_source_cap) > pd_prot_timer_th_fisrt_source_cap) && pd_prot_ufp_timer_start_time_fisrt_source_cap != 0) {
        //fisrt_source_cap
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_fisrt_source_cap) > pd_prot_timer_th_fisrt_source_cap) && pd_prot_dfp_timer_start_time_fisrt_source_cap != 0) {
        //fisrt_source_cap
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_fr_swap_5v) > pd_prot_timer_th_fr_swap_5v) && pd_prot_ufp_timer_start_time_fr_swap_5v != 0) {
        //fr_swap_5v
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_fr_swap_5v) > pd_prot_timer_th_fr_swap_5v) && pd_prot_dfp_timer_start_time_fr_swap_5v != 0) {
        //fr_swap_5v
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_fr_swap_complete) > pd_prot_timer_th_fr_swap_complete) && pd_prot_ufp_timer_start_time_fr_swap_complete != 0) {
        //fr_swap_complete
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_fr_swap_complete) > pd_prot_timer_th_fr_swap_complete) && pd_prot_dfp_timer_start_time_fr_swap_complete != 0) {
        //fr_swap_complete
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_fr_swap_init) > pd_prot_timer_th_fr_swap_init) && pd_prot_ufp_timer_start_time_fr_swap_init != 0) {
        //fr_swap_init
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_fr_swap_init) > pd_prot_timer_th_fr_swap_init) && pd_prot_dfp_timer_start_time_fr_swap_init != 0) {
        //fr_swap_init
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_hard_reset) > pd_prot_timer_th_hard_reset) && pd_prot_ufp_timer_start_time_hard_reset != 0) {
        //hard_reset
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_hard_reset) > pd_prot_timer_th_hard_reset) && pd_prot_dfp_timer_start_time_hard_reset != 0) {
        //hard_reset
    }   
    else if (((current_time - pd_prot_ufp_timer_start_time_hard_reset_complete) > pd_prot_timer_th_hard_reset_complete) && pd_prot_ufp_timer_start_time_hard_reset_complete != 0) {
        //hard_reset_complete
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_hard_reset_complete) > pd_prot_timer_th_hard_reset_complete) && pd_prot_dfp_timer_start_time_hard_reset_complete != 0) {
        //hard_reset_complete
    }   
    else if (((current_time - pd_prot_ufp_timer_start_time_source_epr_keep_alive) > pd_prot_timer_th_source_epr_keep_alive) && pd_prot_ufp_timer_start_time_source_epr_keep_alive != 0) {
        //source_epr_keep_alive
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_source_epr_keep_alive) > pd_prot_timer_th_source_epr_keep_alive) && pd_prot_dfp_timer_start_time_source_epr_keep_alive != 0) {
        //source_epr_keep_alive
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_sink_epr_keep_alive) > pd_prot_timer_th_sink_epr_keep_alive) && pd_prot_ufp_timer_start_time_sink_epr_keep_alive != 0) {
        //sink_epr_keep_alive
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_sink_epr_keep_alive) > pd_prot_timer_th_sink_epr_keep_alive) && pd_prot_dfp_timer_start_time_sink_epr_keep_alive != 0) {
        //sink_epr_keep_alive
    }   
    else if (((current_time - pd_prot_ufp_timer_start_time_no_responce) > pd_prot_timer_th_no_responce) && pd_prot_ufp_timer_start_time_no_responce != 0) {
        //no_responce
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_no_responce) > pd_prot_timer_th_no_responce) && pd_prot_dfp_timer_start_time_no_responce != 0) {
        //no_responce
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_pps_request) > pd_prot_timer_th_pps_request) && pd_prot_ufp_timer_start_time_pps_request != 0) {
        //pps_request
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_pps_request) > pd_prot_timer_th_pps_request) && pd_prot_dfp_timer_start_time_pps_request != 0) {
        //pps_request
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_pps_timeout) > pd_prot_timer_th_pps_timeout) && pd_prot_ufp_timer_start_time_pps_timeout != 0) {
        //pps_timeout
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_pps_timeout) > pd_prot_timer_th_pps_timeout) && pd_prot_dfp_timer_start_time_pps_timeout != 0) {
        //pps_timeout
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_prot_err_hard_reset) > pd_prot_timer_th_prot_err_hard_reset) && pd_prot_ufp_timer_start_time_prot_err_hard_reset != 0) {
        //prot_err_hard_reset
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_prot_err_hard_reset) > pd_prot_timer_th_prot_err_hard_reset) && pd_prot_dfp_timer_start_time_prot_err_hard_reset != 0) {
        //prot_err_hard_reset
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_prot_err_soft_reset) > pd_prot_timer_th_prot_err_soft_reset) && pd_prot_ufp_timer_start_time_prot_err_soft_reset != 0) {
        //prot_err_soft_reset
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_prot_err_soft_reset) > pd_prot_timer_th_prot_err_soft_reset) && pd_prot_dfp_timer_start_time_prot_err_soft_reset != 0) {
        //prot_err_soft_reset
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_pr_swap_wait) > pd_prot_timer_th_pr_swap_wait) && pd_prot_ufp_timer_start_time_pr_swap_wait != 0) {
        //pr_swap_wait
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_pr_swap_wait) > pd_prot_timer_th_pr_swap_wait) && pd_prot_dfp_timer_start_time_pr_swap_wait != 0) {
        //pr_swap_wait
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_ps_hard_reset) > pd_prot_timer_th_ps_hard_reset) && pd_prot_ufp_timer_start_time_ps_hard_reset != 0) {
        //ps_hard_reset
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_ps_hard_reset) > pd_prot_timer_th_ps_hard_reset) && pd_prot_dfp_timer_start_time_ps_hard_reset != 0) {
        //ps_hard_reset
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_spr_ps_source_off) > pd_prot_timer_th_spr_ps_source_off) && pd_prot_ufp_timer_start_time_spr_ps_source_off != 0) {
        //spr_ps_source_off
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_spr_ps_source_off) > pd_prot_timer_th_spr_ps_source_off) && pd_prot_dfp_timer_start_time_spr_ps_source_off != 0) {
        //spr_ps_source_off
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_epr_ps_source_off) > pd_prot_timer_th_epr_ps_source_off) && pd_prot_ufp_timer_start_time_epr_ps_source_off != 0) {
        //epr_ps_source_off
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_epr_ps_source_off) > pd_prot_timer_th_epr_ps_source_off) && pd_prot_dfp_timer_start_time_epr_ps_source_off != 0) {
        //epr_ps_source_off
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_ps_source_on) > pd_prot_timer_th_ps_source_on) && pd_prot_ufp_timer_start_time_ps_source_on != 0) {
        //ps_source_on
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_ps_source_on) > pd_prot_timer_th_ps_source_on) && pd_prot_dfp_timer_start_time_ps_source_on != 0) {
        //ps_source_on
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_spr_ps_transition) > pd_prot_timer_th_spr_ps_transition) && pd_prot_ufp_timer_start_time_spr_ps_transition != 0) {
        //spr_ps_transition
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_spr_ps_transition) > pd_prot_timer_th_spr_ps_transition) && pd_prot_dfp_timer_start_time_spr_ps_transition != 0) {
        //spr_ps_transition
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_epr_ps_transition) > pd_prot_timer_th_epr_ps_transition) && pd_prot_ufp_timer_start_time_epr_ps_transition != 0) {
        //epr_ps_transition
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_epr_ps_transition) > pd_prot_timer_th_epr_ps_transition) && pd_prot_dfp_timer_start_time_epr_ps_transition != 0) {
        //epr_ps_transition
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_receive) > pd_prot_timer_th_receive) && pd_prot_ufp_timer_start_time_receive != 0) {
        //receive
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_receive) > pd_prot_timer_th_receive) && pd_prot_dfp_timer_start_time_receive != 0) {
        //receive
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_receive_responce) > pd_prot_timer_th_receive_responce) && pd_prot_ufp_timer_start_time_receive_responce != 0) {
        //receive_responce
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_receive_responce) > pd_prot_timer_th_receive_responce) && pd_prot_dfp_timer_start_time_receive_responce != 0) {
        //receive_responce
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_retry) > pd_prot_timer_th_retry) && pd_prot_ufp_timer_start_time_retry != 0) {
        //retry
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_retry) > pd_prot_timer_th_retry) && pd_prot_dfp_timer_start_time_retry != 0) {
        //retry
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_sender_responce) > pd_prot_timer_th_sender_responce) && pd_prot_ufp_timer_start_time_sender_responce != 0) {
        //sender_responce
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_sender_responce) > pd_prot_timer_th_sender_responce) && pd_prot_dfp_timer_start_time_sender_responce != 0) {
        //sender_responce
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_sink_delay) > pd_prot_timer_th_sink_delay) && pd_prot_ufp_timer_start_time_sink_delay != 0) {
        //sink_delay
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_sink_delay) > pd_prot_timer_th_sink_delay) && pd_prot_dfp_timer_start_time_sink_delay != 0) {
        //sink_delay
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_sink_tx) > pd_prot_timer_th_sink_tx) && pd_prot_ufp_timer_start_time_sink_tx != 0) {
        //sink_tx
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_sink_tx) > pd_prot_timer_th_sink_tx) && pd_prot_dfp_timer_start_time_sink_tx != 0) {
        //sink_tx
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_soft_reset) > pd_prot_timer_th_soft_reset) && pd_prot_ufp_timer_start_time_soft_reset != 0) {
        //soft_reset
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_soft_reset) > pd_prot_timer_th_soft_reset) && pd_prot_dfp_timer_start_time_soft_reset != 0) {
        //soft_reset
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_scr_holds_bus) > pd_prot_timer_th_scr_holds_bus) && pd_prot_ufp_timer_start_time_scr_holds_bus != 0) {
        //scr_holds_bus
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_scr_holds_bus) > pd_prot_timer_th_scr_holds_bus) && pd_prot_dfp_timer_start_time_scr_holds_bus != 0) {
        //scr_holds_bus
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_swap_sink_ready) > pd_prot_timer_th_swap_sink_ready) && pd_prot_ufp_timer_start_time_swap_sink_ready != 0) {
        //swap_sink_ready
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_swap_sink_ready) > pd_prot_timer_th_swap_sink_ready) && pd_prot_dfp_timer_start_time_swap_sink_ready != 0) {
        //swap_sink_ready
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_swap_source_start) > pd_prot_timer_th_swap_source_start) && pd_prot_ufp_timer_start_time_swap_source_start != 0) {
        //swap_source_start
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_swap_source_start) > pd_prot_timer_th_swap_source_start) && pd_prot_dfp_timer_start_time_swap_source_start != 0) {
        //swap_source_start
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_transmit) > pd_prot_timer_th_transmit) && pd_prot_ufp_timer_start_time_transmit != 0) {
        //transmit
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_transmit) > pd_prot_timer_th_transmit) && pd_prot_dfp_timer_start_time_transmit != 0) {
        //transmit
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_type_c_send_source_cap) > pd_prot_timer_th_type_c_send_source_cap) && pd_prot_ufp_timer_start_time_type_c_send_source_cap != 0) {
        //type_c_send_source_cap
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_type_c_send_source_cap) > pd_prot_timer_th_type_c_send_source_cap) && pd_prot_dfp_timer_start_time_type_c_send_source_cap != 0) {
        //type_c_send_source_cap
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_type_c_sink_wait_cap) > pd_prot_timer_th_type_c_sink_wait_cap) && pd_prot_ufp_timer_start_time_type_c_sink_wait_cap != 0) {
        //type_c_sink_wait_cap
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_type_c_sink_wait_cap) > pd_prot_timer_th_type_c_sink_wait_cap) && pd_prot_dfp_timer_start_time_type_c_sink_wait_cap != 0) {
        //type_c_sink_wait_cap
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vconn_source_discharge) > pd_prot_timer_th_vconn_source_discharge) && pd_prot_ufp_timer_start_time_vconn_source_discharge != 0) {
        //vconn_source_discharge
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vconn_source_discharge) > pd_prot_timer_th_vconn_source_discharge) && pd_prot_dfp_timer_start_time_vconn_source_discharge != 0) {
        //vconn_source_discharge
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vconn_source_off) > pd_prot_timer_th_vconn_source_off) && pd_prot_ufp_timer_start_time_vconn_source_off != 0) {
        //vconn_source_off
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vconn_source_off) > pd_prot_timer_th_vconn_source_off) && pd_prot_dfp_timer_start_time_vconn_source_off != 0) {
        //vconn_source_off
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vconn_source_on) > pd_prot_timer_th_vconn_source_on) && pd_prot_ufp_timer_start_time_vconn_source_on != 0) {
        //vconn_source_on
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vconn_source_on) > pd_prot_timer_th_vconn_source_on) && pd_prot_dfp_timer_start_time_vconn_source_on != 0) {
        //vconn_source_on
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vconn_source_timeout) > pd_prot_timer_th_vconn_source_timeout) && pd_prot_ufp_timer_start_time_vconn_source_timeout != 0) {
        //vconn_source_timeout
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vconn_source_timeout) > pd_prot_timer_th_vconn_source_timeout) && pd_prot_dfp_timer_start_time_vconn_source_timeout != 0) {
        //vconn_source_timeout
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vconn_swap_wait) > pd_prot_timer_th_vconn_swap_wait) && pd_prot_ufp_timer_start_time_vconn_swap_wait != 0) {
        //vconn_swap_wait
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vconn_swap_wait) > pd_prot_timer_th_vconn_swap_wait) && pd_prot_dfp_timer_start_time_vconn_swap_wait != 0) {
        //vconn_swap_wait
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_busy) > pd_prot_timer_th_vdm_busy) && pd_prot_ufp_timer_start_time_vdm_busy != 0) {
        //vdm_busy
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_busy) > pd_prot_timer_th_vdm_busy) && pd_prot_dfp_timer_start_time_vdm_busy != 0) {
        //vdm_busy
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_enter_mode) > pd_prot_timer_th_vdm_enter_mode) && pd_prot_ufp_timer_start_time_vdm_enter_mode != 0) {
        //vdm_enter_mode
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_enter_mode) > pd_prot_timer_th_vdm_enter_mode) && pd_prot_dfp_timer_start_time_vdm_enter_mode != 0) {
        //vdm_enter_mode
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_exit_mode) > pd_prot_timer_th_vdm_exit_mode) && pd_prot_ufp_timer_start_time_vdm_exit_mode != 0) {
        //vdm_exit_mode
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_exit_mode) > pd_prot_timer_th_vdm_exit_mode) && pd_prot_dfp_timer_start_time_vdm_exit_mode != 0) {
        //vdm_exit_mode
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_receiver_responce) > pd_prot_timer_th_vdm_receiver_responce) && pd_prot_ufp_timer_start_time_vdm_receiver_responce != 0) {
        //vdm_receiver_responce
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_receiver_responce) > pd_prot_timer_th_vdm_receiver_responce) && pd_prot_dfp_timer_start_time_vdm_receiver_responce != 0) {
        //vdm_receiver_responce
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_sender_responce) > pd_prot_timer_th_vdm_sender_responce) && pd_prot_ufp_timer_start_time_vdm_sender_responce != 0) {
        //vdm_sender_responce
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_sender_responce) > pd_prot_timer_th_vdm_sender_responce) && pd_prot_dfp_timer_start_time_vdm_sender_responce != 0) {
        //vdm_sender_responce
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_wait_mode_entry) > pd_prot_timer_th_vdm_wait_mode_entry) && pd_prot_ufp_timer_start_time_vdm_wait_mode_entry != 0) {
        //vdm_wait_mode_entry
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_wait_mode_entry) > pd_prot_timer_th_vdm_wait_mode_entry) && pd_prot_dfp_timer_start_time_vdm_wait_mode_entry != 0) {
        //vdm_wait_mode_entry
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_wait_mode_exit) > pd_prot_timer_th_vdm_wait_mode_exit) && pd_prot_ufp_timer_start_time_vdm_wait_mode_exit != 0) {
        //vdm_wait_mode_exit
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_wait_mode_exit) > pd_prot_timer_th_vdm_wait_mode_exit) && pd_prot_dfp_timer_start_time_vdm_wait_mode_exit != 0) {
        //vdm_wait_mode_exit
    }

}

//pd_prot_timer_controler
//starts or stops timers for the pd prot 
//ufp_dfp: select witch port to control the times for
//name: nameof timer to control
//start_stop: start or stop the selcted timer
void pd_prot_timer_controler (enum ufp_dfp ufp_dfp, enum pd_prot_timer_names name, enum pd_prot_timer_start_stop start_stop) {
    //slect witch timer to start or stop 
    switch (name) {
    case ac_temp_update:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_ac_temp_update = millis();
            } else {
                pd_prot_dfp_timer_start_time_ac_temp_update = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_ac_temp_update = 0;
            } else {
                pd_prot_dfp_timer_start_time_ac_temp_update = 0;
            }
        }
        break;
    case bist_cont_mode:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_bist_cont_mode = millis();
            } else {
                pd_prot_dfp_timer_start_time_bist_cont_mode = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_bist_cont_mode = 0;
            } else {
                pd_prot_dfp_timer_start_time_bist_cont_mode = 0;
            }
        }
        break;
    case shared_test_mode:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_shared_test_mode = millis();
            } else {
                pd_prot_dfp_timer_start_time_shared_test_mode = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_shared_test_mode = 0;
            } else {
                pd_prot_dfp_timer_start_time_shared_test_mode = 0;
            }
        }
        break;
    case cable_message:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_cable_message = millis();
            } else {
                pd_prot_dfp_timer_start_time_cable_message = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_cable_message = 0;
            } else {
                pd_prot_dfp_timer_start_time_cable_message = 0;
            }
        }
        break;
    case chunking_not_supported:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunking_not_supported = millis();
            } else {
                pd_prot_dfp_timer_start_time_chunking_not_supported = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunking_not_supported = 0;
            } else {
                pd_prot_dfp_timer_start_time_chunking_not_supported = 0;
            }
        }
        break;
    case chunk_recevier_request:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_recevier_request = millis();
            } else {
                pd_prot_dfp_timer_start_time_chunk_recevier_request = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_recevier_request = 0;
            } else {
                pd_prot_dfp_timer_start_time_chunk_recevier_request = 0;
            }
        }
        break;
    case chunk_recevier_response:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_recevier_response = millis();
            } else {
                pd_prot_dfp_timer_start_time_chunk_recevier_response = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_recevier_response = 0;
            } else {
                pd_prot_dfp_timer_start_time_chunk_recevier_response = 0;
            }
        }
        break;
    case chunk_sender_request:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_sender_request = millis();
            } else {
                pd_prot_dfp_timer_start_time_chunk_sender_request = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_sender_request = 0;
            } else {
                pd_prot_dfp_timer_start_time_chunk_sender_request = 0;
            }
        }
        break;
    case chunk_sender_response:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_sender_response = millis();
            } else {
                pd_prot_dfp_timer_start_time_chunk_sender_response = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_chunk_sender_response = 0;
            } else {
                pd_prot_dfp_timer_start_time_chunk_sender_response = 0;
            }
        }
        break;
    case data_reset:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_data_reset = millis();
            } else {
                pd_prot_dfp_timer_start_time_data_reset = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_data_reset = 0;
            } else {
                pd_prot_dfp_timer_start_time_data_reset = 0;
            }
        }
        break;
    case data_reset_fail:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_data_reset_fail = millis();
            } else {
                pd_prot_dfp_timer_start_time_data_reset_fail = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_data_reset_fail = 0;
            } else {
                pd_prot_dfp_timer_start_time_data_reset_fail = 0;
            }
        }
        break;
    case data_reset_fail_ufp:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_data_reset_fail_ufp = millis();
            } else {
                pd_prot_dfp_timer_start_time_data_reset_fail_ufp = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_data_reset_fail_ufp = 0;
            } else {
                pd_prot_dfp_timer_start_time_data_reset_fail_ufp = 0;
            }
        }
        break;
    case discover_identity:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_discover_identity = millis();
            } else {
                pd_prot_dfp_timer_start_time_discover_identity = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_discover_identity = 0;
            } else {
                pd_prot_dfp_timer_start_time_discover_identity = 0;
            }
        }
        break;
    case dr_swap_hard_reset:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_dr_swap_hard_reset = millis();
            } else {
                pd_prot_dfp_timer_start_time_dr_swap_hard_reset = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_dr_swap_hard_reset = 0;
            } else {
                pd_prot_dfp_timer_start_time_dr_swap_hard_reset = 0;
            }
        }
        break;
    case dr_swap_wait:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_dr_swap_wait = millis();
            } else {
                pd_prot_dfp_timer_start_time_dr_swap_wait = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_dr_swap_wait = 0;
            } else {
                pd_prot_dfp_timer_start_time_dr_swap_wait = 0;
            }
        }
        break;
    case enter_usb:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_enter_usb = millis();
            } else {
                pd_prot_dfp_timer_start_time_enter_usb = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_enter_usb = 0;
            } else {
                pd_prot_dfp_timer_start_time_enter_usb = 0;
            }
        }
        break;
    case enter_usb_wait:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_enter_usb_wait = millis();
            } else {
                pd_prot_dfp_timer_start_time_enter_usb_wait = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_enter_usb_wait = 0;
            } else {
                pd_prot_dfp_timer_start_time_enter_usb_wait = 0;
            }
        }
        break;
    case enter_epr:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_enter_epr = millis();
            } else {
                pd_prot_dfp_timer_start_time_enter_epr = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_enter_epr = 0;
            } else {
                pd_prot_dfp_timer_start_time_enter_epr = 0;
            }
        }
        break;
    case epr_soruce_cable_discovvery:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery = millis();
            } else {
                pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery = 0;
            } else {
                pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery = 0;
            }
        }
        break;
    case fisrt_source_cap:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fisrt_source_cap = millis();
            } else {
                pd_prot_dfp_timer_start_time_fisrt_source_cap = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fisrt_source_cap = 0;
            } else {
                pd_prot_dfp_timer_start_time_fisrt_source_cap = 0;
            }
        }
        break;
    case fr_swap_5v:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fr_swap_5v = millis();
            } else {
                pd_prot_dfp_timer_start_time_fr_swap_5v = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fr_swap_5v = 0;
            } else {
                pd_prot_dfp_timer_start_time_fr_swap_5v = 0;
            }
        }
        break;
    case fr_swap_complete:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fr_swap_complete = millis();
            } else {
                pd_prot_dfp_timer_start_time_fr_swap_complete = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fr_swap_complete = 0;
            } else {
                pd_prot_dfp_timer_start_time_fr_swap_complete = 0;
            }
        }
        break;
    case fr_swap_init:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fr_swap_init = millis();
            } else {
                pd_prot_dfp_timer_start_time_fr_swap_init = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_fr_swap_init = 0;
            } else {
                pd_prot_dfp_timer_start_time_fr_swap_init = 0;
            }
        }
        break;
    case hard_reset:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_hard_reset = millis();
            } else {
                pd_prot_dfp_timer_start_time_hard_reset = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_hard_reset = 0;
            } else {
                pd_prot_dfp_timer_start_time_hard_reset = 0;
            }
        }
        break;
    case hard_reset_complete:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_hard_reset_complete = millis();
            } else {
                pd_prot_dfp_timer_start_time_hard_reset_complete = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_hard_reset_complete = 0;
            } else {
                pd_prot_dfp_timer_start_time_hard_reset_complete = 0;
            }
        }
        break;
    case source_epr_keep_alive:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_source_epr_keep_alive = millis();
            } else {
                pd_prot_dfp_timer_start_time_source_epr_keep_alive = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_source_epr_keep_alive = 0;
            } else {
                pd_prot_dfp_timer_start_time_source_epr_keep_alive = 0;
            }
        }
        break;
    case sink_epr_keep_alive:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sink_epr_keep_alive = millis();
            } else {
                pd_prot_dfp_timer_start_time_sink_epr_keep_alive = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sink_epr_keep_alive = 0;
            } else {
                pd_prot_dfp_timer_start_time_sink_epr_keep_alive = 0;
            }
        }
        break;
    case no_responce:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_no_responce = millis();
            } else {
                pd_prot_dfp_timer_start_time_no_responce = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_no_responce = 0;
            } else {
                pd_prot_dfp_timer_start_time_no_responce = 0;
            }
        }
        break;
    case pps_request:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_pps_request = millis();
            } else {
                pd_prot_dfp_timer_start_time_pps_request = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_pps_request = 0;
            } else {
                pd_prot_dfp_timer_start_time_pps_request = 0;
            }
        }
        break;
    case pps_timeout:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_pps_timeout = millis();
            } else {
                pd_prot_dfp_timer_start_time_pps_timeout = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_pps_timeout = 0;
            } else {
                pd_prot_dfp_timer_start_time_pps_timeout = 0;
            }
        }
        break;
    case prot_err_hard_reset:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_prot_err_hard_reset = millis();
            } else {
                pd_prot_dfp_timer_start_time_prot_err_hard_reset = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_prot_err_hard_reset = 0;
            } else {
                pd_prot_dfp_timer_start_time_prot_err_hard_reset = 0;
            }
        }
        break;
    case prot_err_soft_reset:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_prot_err_soft_reset = millis();
            } else {
                pd_prot_dfp_timer_start_time_prot_err_soft_reset = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_prot_err_soft_reset = 0;
            } else {
                pd_prot_dfp_timer_start_time_prot_err_soft_reset = 0;
            }
        }
        break;
    case pr_swap_wait:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_pr_swap_wait = millis();
            } else {
                pd_prot_dfp_timer_start_time_pr_swap_wait = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_pr_swap_wait = 0;
            } else {
                pd_prot_dfp_timer_start_time_pr_swap_wait = 0;
            }
        }
        break;
    case ps_hard_reset:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_ps_hard_reset = millis();
            } else {
                pd_prot_dfp_timer_start_time_ps_hard_reset = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_ps_hard_reset = 0;
            } else {
                pd_prot_dfp_timer_start_time_ps_hard_reset = 0;
            }
        }
        break;
    case spr_ps_source_off:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_spr_ps_source_off = millis();
            } else {
                pd_prot_dfp_timer_start_time_spr_ps_source_off = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_spr_ps_source_off = 0;
            } else {
                pd_prot_dfp_timer_start_time_spr_ps_source_off = 0;
            }
        }
        break;
    case epr_ps_source_off:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_epr_ps_source_off = millis();
            } else {
                pd_prot_dfp_timer_start_time_epr_ps_source_off = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_epr_ps_source_off = 0;
            } else {
                pd_prot_dfp_timer_start_time_epr_ps_source_off = 0;
            }
        }
        break;
    case ps_source_on:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_ps_source_on = millis();
            } else {
                pd_prot_dfp_timer_start_time_ps_source_on = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_ps_source_on = 0;
            } else {
                pd_prot_dfp_timer_start_time_ps_source_on = 0;
            }
        }
        break;
    case spr_ps_transition:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_spr_ps_transition = millis();
            } else {
                pd_prot_dfp_timer_start_time_spr_ps_transition = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_spr_ps_transition = 0;
            } else {
                pd_prot_dfp_timer_start_time_spr_ps_transition = 0;
            }
        }
        break;
    case epr_ps_transition:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_epr_ps_transition = millis();
            } else {
                pd_prot_dfp_timer_start_time_epr_ps_transition = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_epr_ps_transition = 0;
            } else {
                pd_prot_dfp_timer_start_time_epr_ps_transition = 0;
            }
        }
        break;
    case receive:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_receive = millis();
            } else {
                pd_prot_dfp_timer_start_time_receive = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_receive = 0;
            } else {
                pd_prot_dfp_timer_start_time_receive = 0;
            }
        }
        break;
    case receive_responce:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_receive_responce = millis();
            } else {
                pd_prot_dfp_timer_start_time_receive_responce = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_receive_responce = 0;
            } else {
                pd_prot_dfp_timer_start_time_receive_responce = 0;
            }
        }
        break;
    case retry:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_retry = millis();
            } else {
                pd_prot_dfp_timer_start_time_retry = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_retry = 0;
            } else {
                pd_prot_dfp_timer_start_time_retry = 0;
            }
        }
        break;
    case sender_responce:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sender_responce = millis();
            } else {
                pd_prot_dfp_timer_start_time_sender_responce = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sender_responce = 0;
            } else {
                pd_prot_dfp_timer_start_time_sender_responce = 0;
            }
        }
        break;
    case sink_delay:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sink_delay = millis();
            } else {
                pd_prot_dfp_timer_start_time_sink_delay = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sink_delay = 0;
            } else {
                pd_prot_dfp_timer_start_time_sink_delay = 0;
            }
        }
        break;
    case sink_tx:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sink_tx = millis();
            } else {
                pd_prot_dfp_timer_start_time_sink_tx = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sink_tx = 0;
            } else {
                pd_prot_dfp_timer_start_time_sink_tx = 0;
            }
        }
        break;
    case soft_reset:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_soft_reset = millis();
            } else {
                pd_prot_dfp_timer_start_time_soft_reset = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_soft_reset = 0;
            } else {
                pd_prot_dfp_timer_start_time_soft_reset = 0;
            }
        }
        break;
    case scr_holds_bus:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_scr_holds_bus = millis();
            } else {
                pd_prot_dfp_timer_start_time_scr_holds_bus = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_scr_holds_bus = 0;
            } else {
                pd_prot_dfp_timer_start_time_scr_holds_bus = 0;
            }
        }
        break;
    case swap_sink_ready:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_swap_sink_ready = millis();
            } else {
                pd_prot_dfp_timer_start_time_swap_sink_ready = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_swap_sink_ready = 0;
            } else {
                pd_prot_dfp_timer_start_time_swap_sink_ready = 0;
            }
        }
        break;
    case swap_source_start:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_swap_source_start = millis();
            } else {
                pd_prot_dfp_timer_start_time_swap_source_start = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_swap_source_start = 0;
            } else {
                pd_prot_dfp_timer_start_time_swap_source_start = 0;
            }
        }
        break;
    case transmit:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_transmit = millis();
            } else {
                pd_prot_dfp_timer_start_time_transmit = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_transmit = 0;
            } else {
                pd_prot_dfp_timer_start_time_transmit = 0;
            }
        }
        break;
    case type_c_send_source_cap:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_type_c_send_source_cap = millis();
            } else {
                pd_prot_dfp_timer_start_time_type_c_send_source_cap = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_type_c_send_source_cap = 0;
            } else {
                pd_prot_dfp_timer_start_time_type_c_send_source_cap = 0;
            }
        }
        break;
    case type_c_sink_wait_cap:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_type_c_sink_wait_cap = millis();
            } else {
                pd_prot_dfp_timer_start_time_type_c_sink_wait_cap = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_type_c_sink_wait_cap = 0;
            } else {
                pd_prot_dfp_timer_start_time_type_c_sink_wait_cap = 0;
            }
        }
        break;
    case vconn_source_discharge:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_discharge = millis();
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_discharge = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_discharge = 0;
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_discharge = 0;
            }
        }
        break;
    case vconn_source_off:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_off = millis();
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_off = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_off = 0;
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_off = 0;
            }
        }
        break;
    case vconn_source_on:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_on = millis();
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_on = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_on = 0;
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_on = 0;
            }
        }
        break;
    case vconn_source_timeout:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_timeout = millis();
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_timeout = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_source_timeout = 0;
            } else {
                pd_prot_dfp_timer_start_time_vconn_source_timeout = 0;
            }
        }
        break;
    case vconn_swap_wait:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_swap_wait = millis();
            } else {
                pd_prot_dfp_timer_start_time_vconn_swap_wait = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vconn_swap_wait = 0;
            } else {
                pd_prot_dfp_timer_start_time_vconn_swap_wait = 0;
            }
        }
        break;
    case vdm_busy:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_busy = millis();
            } else {
                pd_prot_dfp_timer_start_time_vdm_busy = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_busy = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_busy = 0;
            }
        }
        break;
    case vdm_enter_mode:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_enter_mode = millis();
            } else {
                pd_prot_dfp_timer_start_time_vdm_enter_mode = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_enter_mode = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_enter_mode = 0;
            }
        }
        break;
    case vdm_exit_mode:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_exit_mode = millis();
            } else {
                pd_prot_dfp_timer_start_time_vdm_exit_mode = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_exit_mode = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_exit_mode = 0;
            }
        }
        break;
    case vdm_receiver_responce:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_receiver_responce = millis();
            } else {
                pd_prot_dfp_timer_start_time_vdm_receiver_responce = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_receiver_responce = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_receiver_responce = 0;
            }
        }
        break;
    case vdm_sender_responce:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_sender_responce = millis();
            } else {
                pd_prot_dfp_timer_start_time_vdm_sender_responce = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_sender_responce = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_sender_responce = 0;
            }
        }
        break;
    case vdm_wait_mode_entry:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_wait_mode_entry = millis();
            } else {
                pd_prot_dfp_timer_start_time_vdm_wait_mode_entry = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_wait_mode_entry = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_wait_mode_entry = 0;
            }
        }
        break;
    case vdm_wait_mode_exit:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_wait_mode_exit = millis();
            } else {
                pd_prot_dfp_timer_start_time_vdm_wait_mode_exit = millis();
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_wait_mode_exit = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_wait_mode_exit = 0;
            }
        }
        break;
    default:
        //do nothing
        break;
    }

    return;
}

//pd_prot_biuld_headder
//biulds the headders of messages for pd protocol interaction
//extended_msg: true=extended message false=nonextended messgae
//n_data_objects: number of data objects to be transmitted
//msg_id: message id for pd protocall shold be incermentd each message
//power_role: sets the port power role (can be src or sink)
//spec_revision: indecates supported protocall revision
//data_role: data role of port that the messgae is being transmitted from
//msg_type: 
uint16_t pd_prot_biuld_headder (bool extended_msg, uint16_t n_data_objects, uint16_t msg_id, enum pd_prot_port_power_role power_role, uint16_t spec_revision, enum ufp_dfp data_role, uint16_t msg_type) {
    //init local vars
    uint16_t headder_contents = 0;

    //set extended bit if msg is extended
    if (extended_msg) {
        headder_contents = 0x8000;
    }

    //mask n of data objects
    n_data_objects = n_data_objects & 0x0007;

    //shift n data objects to correct pos in headder
    n_data_objects = n_data_objects << 12;

    //add n data objects to headder
    headder_contents = headder_contents | n_data_objects;

    //mask msg id 
    msg_id = msg_id & 0x0007;

    //shift msg id to correct pos in header
    msg_id = msg_id << 9;

    //add msg_id to headder
    headder_contents = headder_contents | msg_id;

    //set port power role 
    if (power_role == src) {
        headder_contents = headder_contents | 0x0100;
    }

    //set spec revision 
    if (spec_revision == 1) {
        // do nothing leave bits at 0
    } else if (spec_revision == 2) {
        headder_contents = headder_contents | 0x0040;
    } else if (spec_revision == 3) {
        headder_contents = headder_contents | 0x0080;
    }

    //set port data role
    if (data_role == ufp) {
        //do nothing leave at 0
    } else if (data_role == dfp) {
        headder_contents = headder_contents | 0x0020;
    }

    //set message type
    msg_type = msg_type & 0x001F;

    //add message type to headder 
    headder_contents = headder_contents | msg_type;

    return headder_contents;

}

//pd_prot_biuld_ext_headder
//biulds the headders of extended messages for pd protocol interaction
//chunked: set true if message is chunked
//chunk_number: number of chunks in the message, use only when the cunked flag is set to ture
//request_chunk: reqwest for a certan chunk of a data message
//data_size: how many bytes in total the extended message is 
uint16_t pd_prot_biuld_ext_headder (bool chunked, uint16_t chunk_number, bool request_chunk, uint16_t data_size) {
    //init local vars
    uint16_t ext_headder_contents = 0;

    //set chunked bit
    if (chunked) {
        ext_headder_contents = ext_headder_contents | 0x8000;

        //mask chunk number
        chunk_number = chunk_number & 0x0007;

        //shift chunk nummber to correct place 
        chunk_number = chunk_number << 11;

        //add chunk number to header contents
        ext_headder_contents = ext_headder_contents | chunk_number;

        //set reqwest bit
        if (request_chunk) {
            ext_headder_contents = ext_headder_contents | 0x0400;
        }

    }

    //mask data size
    data_size = data_size & 0x001F;

    //add data size to headder
    ext_headder_contents = ext_headder_contents | data_size;

    return ext_headder_contents;
}

//pd_prot_message_type
//determines if the incoming message is extended or not
//returns 
//normal: message recived is not extended
//extended: message is extended
enum pd_prot_message_type_enum pd_prot_message_type (enum ufp_dfp ufp_dfp) {

    //select port to determine if its chunked
    if (ufp_dfp == ufp) {
        if ((pd_phy_ufp_last_recived_message_contents[0] & 0x80) == 0){
            return normal;
        } else {
            return extended;
        }
    } else {
        if ((pd_phy_dfp_last_recived_message_contents[0] & 0x80) == 0){
            return normal;
        } else {
            return extended;
        }
    }
}

//pd_prot_ext_msg_chunked
//determines if a extended message is chunked
//true: message is chunked
//false: message is not chunked
bool pd_prot_ext_msg_chunked (enum ufp_dfp ufp_dfp) {

    //select port to determine if its chunked
    if (ufp_dfp == ufp) {
        if ((pd_phy_ufp_last_recived_message_contents[2] & 0x80) == 0) {
            return false;
        } else {
            return true;
        }
    } else {
        if ((pd_phy_dfp_last_recived_message_contents[2] & 0x80) == 0) {
            return false;
        } else {
            return true;
        }
    }

}

//pd_prot_etx_msg_n_chunks
//determines and returns the number of chunks in an extended message
int pd_prot_ext_msg_n_chunks (enum ufp_dfp ufp_dfp) {

    //detrmine port to chek
    if (ufp_dfp == ufp) {
        return ((pd_phy_ufp_last_recived_message_contents[2] & 0x01) << 8) | pd_phy_ufp_last_recived_message_contents[3];
    } else {
        return ((pd_phy_dfp_last_recived_message_contents[2] & 0x01) << 8) | pd_phy_dfp_last_recived_message_contents[3];
    }
}


//pd_prot_chek_soft_reset
//checks if the recived message is a soft reset command
//ufp_dfp: port to check
//true: soft reset recived
//false: message is not a soft reset command
bool pd_prot_check_soft_reset (enum ufp_dfp ufp_dfp) {

    if (ufp_dfp == ufp) {
        if ((pd_phy_ufp_last_recived_message_contents[1] & 0x1F) == 0x0D){
            return true;
        } else {
            return false;
        }
    } else {
        if ((pd_phy_dfp_last_recived_message_contents[1] & 0x1F) == 0x0D){
            return true;
        } else {
            return false;
        }
    }
}

//pd_prot_discard_message
//discards the most recently recived message of the selceted port
void pd_prot_discard_message (enum ufp_dfp ufp_dfp) {

    if (ufp_dfp == ufp) {
        //reset all recive vars for given port
        pd_prot_ufp_counter_message_id = 0;
        pd_phy_ufp_last_recived_message_id = 0;
        pd_phy_ufp_last_recived_message_lenght = 0;
        pd_phy_ufp_last_recived_message_type = sop;
        for (int i; i < 256; ++i) {
            pd_phy_ufp_last_recived_message_contents[i] = 0;
        }

    } else {
        //reset all recive vars for given port
        pd_prot_dfp_counter_message_id = 0;
        pd_phy_dfp_last_recived_message_id = 0;
        pd_phy_dfp_last_recived_message_lenght = 0;
        pd_phy_dfp_last_recived_message_type = sop;
        for (int i; i < 256; ++i) {
            pd_phy_dfp_last_recived_message_contents[i] = 0;
        }
    }
}


void pd_prot_hard_reset_handeler (enum ufp_dfp ufp_dfp, bool from_policy_engine) {
    //discard last recived message
    pd_prot_discard_message(ufp_dfp);

    //check if reset was called for from the policy engine or PHY
    if (from_policy_engine) {
        pd_phy_send_hard_reset(ufp_dfp);
        pd_prot_timer_controler(ufp_dfp, hard_reset_complete, start);
    }

}


//pd_prot_set_last_message
//sets last message vars 
//this function must be called after createing/splitting a message
void pd_prot_set_last_message(enum ufp_dfp ufp_dfp, uint8_t message[256], uint8_t length_of_message) {
    if (ufp_dfp == ufp) {
        for (int i; i < 255; ++i) {
            pd_prot_ufp_last_message[i] = message[i];
        }
        
        pd_prot_ufp_last_message_length = length_of_message;
    } else if (ufp_dfp == dfp) {
        for (int i; i < 255; ++i) {
            pd_prot_dfp_last_message[i] = message[i];
        }
        
        pd_prot_dfp_last_message_length = length_of_message;
    }
}

//pd_prot_transmit_soucre_capibilitiys
//transmits source PDOs based on the selcted power cap of the port 
void pd_prot_transmit_soucre_capibilitiys (enum ufp_dfp ufp_dfp) {
    //init local vars
    uint8_t message[256];
    uint32_t temp = 0;
    int current_msg_id = 0;
    int n_pdo = 0;
    int n_bytes = 0;

    //get current message id
    if (ufp_dfp == ufp) {
        current_msg_id = pd_prot_head_ufp_message_id;
    } else if (ufp_dfp == dfp) {
        current_msg_id = pd_prot_head_dfp_message_id;
    }

    //set nmber of PDOs
    if (ufp_dfp == ufp) {
        if (pd_prot_ufp_current_power_cap == watts_100) {
            n_pdo = 5;
        } else if (pd_prot_ufp_current_power_cap == watts_65) {
            n_pdo = 4;
        } else if (pd_prot_ufp_current_power_cap == watts_40) {
            n_pdo = 3;
        } else if (pd_prot_ufp_current_power_cap == watts_20) {
            n_pdo = 1;
        } else if (pd_prot_ufp_current_power_cap == watts_10) {
            n_pdo = 1;
        }
    } else if (ufp_dfp == dfp) {
        if (pd_prot_dfp_current_power_cap == watts_100) {
            n_pdo = 5;
        } else if (pd_prot_dfp_current_power_cap == watts_65) {
            n_pdo = 4;
        } else if (pd_prot_dfp_current_power_cap == watts_40) {
            n_pdo = 3;
        } else if (pd_prot_dfp_current_power_cap == watts_20) {
            n_pdo = 1;
        } else if (pd_prot_dfp_current_power_cap == watts_10) {
            n_pdo = 1;
        }
    }

    //biuld headder
    uint16_t headder = pd_prot_biuld_headder(false, n_pdo, current_msg_id, src, 3, ufp_dfp, pd_prot_data_msg_source_capabilities);

    message[1] = headder & 0xFF;
    message[0] = (headder >> 8) & 0xFF;

    //append PDOs to message based on a ports given power cap
    if (ufp_dfp == ufp){
        if (pd_prot_ufp_current_power_cap == watts_100) {
            temp = pd_prot_pdo_vsafe_5v;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_9v;
            message[9] = temp & 0xFF;
            message[8] = (temp >> 8) & 0xFF;
            message[7] = (temp >> 16) & 0xFF;
            message[6] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_12v;
            message[13] = temp & 0xFF;
            message[12] = (temp >> 8) & 0xFF;
            message[11] = (temp >> 16) & 0xFF;
            message[10] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_15v;
            message[17] = temp & 0xFF;
            message[16] = (temp >> 8) & 0xFF;
            message[15] = (temp >> 16) & 0xFF;
            message[14] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_20v;
            message[21] = temp & 0xFF;
            message[20] = (temp >> 8) & 0xFF;
            message[19] = (temp >> 16) & 0xFF;
            message[18] = (temp >> 24) & 0xFF;

            n_bytes = 22;

        } else if (pd_prot_ufp_current_power_cap == watts_65) {
            temp = pd_prot_pdo_vsafe_5v;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_9v;
            message[9] = temp & 0xFF;
            message[8] = (temp >> 8) & 0xFF;
            message[7] = (temp >> 16) & 0xFF;
            message[6] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_12v;
            message[13] = temp & 0xFF;
            message[12] = (temp >> 8) & 0xFF;
            message[11] = (temp >> 16) & 0xFF;
            message[10] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_15v_at_65;
            message[17] = temp & 0xFF;
            message[16] = (temp >> 8) & 0xFF;
            message[15] = (temp >> 16) & 0xFF;
            message[14] = (temp >> 24) & 0xFF;

            n_bytes = 18;

        } else if (pd_prot_ufp_current_power_cap == watts_40) {
            temp = pd_prot_pdo_vsafe_5v;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_9v;
            message[9] = temp & 0xFF;
            message[8] = (temp >> 8) & 0xFF;
            message[7] = (temp >> 16) & 0xFF;
            message[6] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_12v_at_40;
            message[13] = temp & 0xFF;
            message[12] = (temp >> 8) & 0xFF;
            message[11] = (temp >> 16) & 0xFF;
            message[10] = (temp >> 24) & 0xFF;

            n_bytes = 14;

        } else if (pd_prot_ufp_current_power_cap == watts_20) {
            temp = pd_prot_pdo_vsafe_5v_at_20;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            n_bytes = 6;

        } else if (pd_prot_ufp_current_power_cap == watts_10) {
            temp = pd_prot_pdo_vsafe_5v_at_10;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            n_bytes = 6;
        }
    } else if (ufp_dfp == dfp){
        if (pd_prot_dfp_current_power_cap == watts_100) {
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_9v;
            message[9] = temp & 0xFF;
            message[8] = (temp >> 8) & 0xFF;
            message[7] = (temp >> 16) & 0xFF;
            message[6] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_12v;
            message[13] = temp & 0xFF;
            message[12] = (temp >> 8) & 0xFF;
            message[11] = (temp >> 16) & 0xFF;
            message[10] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_15v;
            message[17] = temp & 0xFF;
            message[16] = (temp >> 8) & 0xFF;
            message[15] = (temp >> 16) & 0xFF;
            message[14] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_20v;
            message[21] = temp & 0xFF;
            message[20] = (temp >> 8) & 0xFF;
            message[19] = (temp >> 16) & 0xFF;
            message[18] = (temp >> 24) & 0xFF;

            n_bytes = 22;

        } else if (pd_prot_dfp_current_power_cap == watts_65) {
            temp = pd_prot_pdo_vsafe_5v;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_9v;
            message[9] = temp & 0xFF;
            message[8] = (temp >> 8) & 0xFF;
            message[7] = (temp >> 16) & 0xFF;
            message[6] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_12v;
            message[13] = temp & 0xFF;
            message[12] = (temp >> 8) & 0xFF;
            message[11] = (temp >> 16) & 0xFF;
            message[10] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_15v_at_65;
            message[17] = temp & 0xFF;
            message[16] = (temp >> 8) & 0xFF;
            message[15] = (temp >> 16) & 0xFF;
            message[14] = (temp >> 24) & 0xFF;

            n_bytes = 18;

        } else if (pd_prot_dfp_current_power_cap == watts_40) {
            temp = pd_prot_pdo_vsafe_5v;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_9v;
            message[9] = temp & 0xFF;
            message[8] = (temp >> 8) & 0xFF;
            message[7] = (temp >> 16) & 0xFF;
            message[6] = (temp >> 24) & 0xFF;

            temp = pd_prot_pdo_12v_at_40;
            message[13] = temp & 0xFF;
            message[12] = (temp >> 8) & 0xFF;
            message[11] = (temp >> 16) & 0xFF;
            message[10] = (temp >> 24) & 0xFF;

            n_bytes = 14;

        } else if (pd_prot_dfp_current_power_cap == watts_20) {
            temp = pd_prot_pdo_vsafe_5v_at_20;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            n_bytes = 6;

        } else if (pd_prot_dfp_current_power_cap == watts_10) {
            temp = pd_prot_pdo_vsafe_5v_at_10;
            message[5] = temp & 0xFF;
            message[4] = (temp >> 8) & 0xFF;
            message[3] = (temp >> 16) & 0xFF;
            message[2] = (temp >> 24) & 0xFF;

            n_bytes = 6;

        }
    }

    //set last message vars for given port
    pd_prot_set_last_message(ufp_dfp, message, n_bytes);

    //tell pd phy to transmit the message 
    pd_phy_transmit(ufp_dfp, message, n_bytes);

    return;
}

//pd_prot_transmit_command
//transmits usbpd command messages
//ufp_dfp: port to send command from
//pd_prot_cont_msg_enum: what command to send
void pd_prot_transmit_command (enum ufp_dfp ufp_dfp, enum pd_prot_cont_msg_enum pd_prot_cont_msg_enum) {
    //init local vars
    uint8_t message[256];
    uint16_t selected_comand = 0;

    //select witch command to send
    switch (pd_prot_cont_msg_enum){
    case gotomin:
        selected_comand = pd_prot_cont_msg_gotomin;
        break;
    case accept:
        selected_comand = pd_prot_cont_msg_accept;
        break;
    case reject:
        selected_comand = pd_prot_cont_msg_reject;
        break;
    case ping:
        selected_comand = pd_prot_cont_msg_ping;
        break;
    case ps_rdy:
        selected_comand = pd_prot_cont_msg_ps_rdy;
        break;
    case get_source_cap:
        selected_comand = pd_prot_cont_msg_get_source_cap;
        break;
    case get_sink_cap:
        selected_comand = pd_prot_cont_msg_get_sink_cap;
        break;
    case dr_swap:
        selected_comand = pd_prot_cont_msg_dr_swap;
        break;
    case pr_swap:
        selected_comand = pd_prot_cont_msg_pr_swap;
        break;
    case vconn_swap:
        selected_comand = pd_prot_cont_msg_vconn_swap;
        break;
    case wait:
        selected_comand = pd_prot_cont_msg_wait;
        break;
    case soft_reset:
        selected_comand = pd_prot_cont_msg_soft_reset;
        break;
    case data_reset:
        selected_comand = pd_prot_cont_msg_data_reset;
        break;
    case data_reset_complete:
        selected_comand = pd_prot_cont_msg_data_reset_complete;
        break;
    case not_supported:
        selected_comand = pd_prot_cont_msg_not_supported;
        break;
    case fr_swap:
        selected_comand = pd_prot_cont_msg_fr_swap;
        break;
    case get_pps_status:
        selected_comand = pd_prot_cont_msg_get_pps_status;
        break;
    case get_country_codes:
        selected_comand = pd_prot_cont_msg_get_country_codes;
        break;
    case get_sink_cap_extended:
        selected_comand = pd_prot_cont_msg_get_sink_cap_extended;
        break;
    case get_source_info:
        selected_comand = pd_prot_cont_msg_get_souce_info;
        break;
    case get_revision:
        selected_comand = pd_prot_cont_msg_get_revision;
        break;
    }
    

    //biuld headder  
    uint16_t headder = pd_prot_biuld_headder(false, 0, 0, src, 3, ufp_dfp, selected_comand);

    //load headder in to array
    message[1] = headder & 0xFF;
    message[0] = (headder >> 8) & 0xFF;

    //set last message vars for a given port
    pd_prot_set_last_message(ufp_dfp, message, 2);

    //transmit the message
    pd_phy_transmit(ufp_dfp, message, 2);
    
    return;

}

//normal message state machine
void pd_prot_rx_state_machine(enum ufp_dfp ufp_dfp) {

    //check for soft reset
    if (pd_prot_check_soft_reset(ufp_dfp)) {
        pd_prot_discard_message(ufp_dfp);
    }

    //check if message id matches expected id
    //if not set current message id to last recived id
    if (ufp_dfp == ufp) {
        if (pd_phy_ufp_last_recived_message_id == pd_prot_ufp_counter_message_id){
            pd_prot_discard_message(ufp_dfp);
        } else {
            pd_prot_ufp_counter_message_id = pd_phy_ufp_last_recived_message_id;
        }
    } else {
        if (pd_phy_dfp_last_recived_message_id == pd_prot_dfp_counter_message_id){
            pd_prot_discard_message(ufp_dfp);
        } else {
            pd_prot_dfp_counter_message_id = pd_phy_dfp_last_recived_message_id;
        }
    }

    //pass to plicy engine

    return;

}

//chunked rx statemachine
void pd_prot_chunked_rx_state_machine(enum ufp_dfp ufp_dfp) {
    //init local vars



    //reset extended rx buffer and abort flags
    if (ufp_dfp == ufp) {
        pd_prot_ufp_abbort_flag = false;
        for (int i; i < 256; ++i) {
            pd_phy_ufp_last_recived_message_contents[i] = 0;
        }
        pd_phy_ufp_last_recived_message_lenght = 0;
        pd_phy_ufp_last_recived_message_type = sop;
    } else if (ufp_dfp == dfp) {
        pd_prot_dfp_abbort_flag = false;
        for (int i; i < 256; ++i) {
            pd_phy_dfp_last_recived_message_contents[i] = 0;
        }
        pd_phy_dfp_last_recived_message_lenght = 0;
        pd_phy_dfp_last_recived_message_type = sop;
    }

    if (pd_prot_message_type(ufp_dfp) == extended) {
        //determine if message is chunked
        if (pd_prot_ext_msg_chunked) {
            if (pd_prot_ext_msg_n_chunks(ufp_dfp) == 0) {

            }

        }
    } else {
        pd_prot_rx_state_machine(ufp_dfp);
    }


}










#endif // pd_prot_cpp