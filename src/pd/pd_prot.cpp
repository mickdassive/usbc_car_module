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
#include "pd_power_cont.h"
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
unsigned long pd_prot_ufp_timer_start_time_no_response = 0;
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
unsigned long pd_prot_ufp_timer_start_time_receive_response = 0;
unsigned long pd_prot_ufp_timer_start_time_retry = 0;
unsigned long pd_prot_ufp_timer_start_time_sender_response = 0;
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
unsigned long pd_prot_ufp_timer_start_time_vdm_receiver_response = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_sender_response = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_wait_mode_entry = 0;
unsigned long pd_prot_ufp_timer_start_time_vdm_wait_mode_exit = 0;
unsigned long pd_prot_ufp_timer_start_time_source_pps_comm = 0;

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
unsigned long pd_prot_dfp_timer_start_time_no_response = 0;
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
unsigned long pd_prot_dfp_timer_start_time_receive_response = 0;
unsigned long pd_prot_dfp_timer_start_time_retry = 0;
unsigned long pd_prot_dfp_timer_start_time_sender_response = 0;
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
unsigned long pd_prot_dfp_timer_start_time_vdm_receiver_response = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_sender_response = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_wait_mode_entry = 0;
unsigned long pd_prot_dfp_timer_start_time_vdm_wait_mode_exit = 0;
unsigned long pd_prot_dfp_timer_start_time_source_pps_comm = 0;

//retransmit vars
bool pd_prot_ufp_retransit_failed = false;
bool pd_prot_dfp_retransit_failed = false;
uint8_t pd_prot_ufp_last_message [255];
int pd_prot_ufp_last_message_length = 0;
uint8_t pd_prot_dfp_last_message [255];
int pd_prot_dfp_last_message_length = 0;

//previous policy engine state vars
enum pd_port_policy_engine_state_enum pd_prot_ufp_pe_prev_state;
enum pd_port_policy_engine_state_enum pd_prot_dfp_pe_prev_state;

//selected port power (in watts)
enum pd_prot_power_cap_enum pd_prot_ufp_current_power_cap = watts_100;
enum pd_prot_power_cap_enum pd_prot_dfp_current_power_cap = watts_100;

//vars for sink necgotiation
int pd_prot_ufp_negotiated_sink_voltage;
bool pd_prot_ufp_negotiated_sink_met; //true if we can souce the negotiated voltage
int pd_prot_dfp_negotiated_sink_voltage;
bool pd_prot_dfp_negotiated_sink_met; //true if we can souce the negotiated voltage

//abort flags
bool pd_prot_ufp_abort_flag = false;
bool pd_prot_dfp_abort_flag = false;

//flags for the policy engine
bool pd_prot_ufp_last_good_crc = false;
bool pd_prot_dfp_last_good_crc = false;
enum ufp_dfp pd_prot_ufp_pe_port_data_role = dfp;
enum ufp_dfp pd_prot_dfp_pe_port_data_role = dfp;
enum pd_port_policy_engine_state_enum pd_prot_ufp_pe_current_state = pe_src_startup;
enum pd_port_policy_engine_state_enum pd_prot_dfp_pe_current_state = pe_src_startup;




/**
 * @brief Handles the timer events for the PD protocol.
 * 
 * This function is responsible for handling various timer events in the PD protocol.
 * It checks the elapsed time for each timer and performs the corresponding actions.
 * 
 */
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
    else if (((current_time - pd_prot_ufp_timer_start_time_chunk_recevier_request) > pd_prot_timer_th_chunk_receiver_request) && pd_prot_ufp_timer_start_time_chunk_recevier_request != 0) {
        //chunk_recevier_request
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_chunk_recevier_request) > pd_prot_timer_th_chunk_receiver_request) && pd_prot_dfp_timer_start_time_chunk_recevier_request != 0) {
        //chunk_recevier_request
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_chunk_recevier_response) > pd_prot_timer_th_chunk_receiver_response) && pd_prot_ufp_timer_start_time_chunk_recevier_response != 0) {
        //chunk_recevier_response
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_chunk_recevier_response) > pd_prot_timer_th_chunk_receiver_response) && pd_prot_dfp_timer_start_time_chunk_recevier_response != 0) {
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
    else if (((current_time - pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery) > pd_prot_timer_th_epr_source_cable_discovery) && pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery != 0) {
        //epr_soruce_cable_discovvery
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery) > pd_prot_timer_th_epr_source_cable_discovery) && pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery != 0) {
        //epr_soruce_cable_discovvery
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_first_source_cap) > pd_prot_timer_th_first_source_cap) && pd_prot_ufp_timer_start_time_first_source_cap != 0) {
        //fisrt_source_cap
        if (pd_prot_ufp_counter_caps < pd_prot_counter_th_caps) {
            pd_prot_ufp_pe_current_state = pe_src_send_capabilitiys;
        }
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_first_source_cap) > pd_prot_timer_th_first_source_cap) && pd_prot_dfp_timer_start_time_first_source_cap != 0) {
        //fisrt_source_cap
        if (pd_prot_dfp_counter_caps < pd_prot_counter_th_caps) {
            pd_prot_dfp_pe_current_state = pe_src_send_capabilitiys;
        }
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
        pd_prot_ufp_pe_current_state = pe_src_transition_to_dflt;
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_hard_reset) > pd_prot_timer_th_hard_reset) && pd_prot_dfp_timer_start_time_hard_reset != 0) {
        //hard_reset
        pd_prot_dfp_pe_current_state = pe_src_transition_to_dflt;
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
    else if (((current_time - pd_prot_ufp_timer_start_time_no_response) > pd_prot_timer_th_no_response) && pd_prot_ufp_timer_start_time_no_response != 0) {
        //no_responce

        //reatct to noresponce 
        if (pd_prot_ufp_counter_hard_reset < pd_prot_counter_th_hard_reset) {
            if (pd_phy_ufp_attached && pd_prot_ufp_negotiated_sink_met) {
                pd_prot_ufp_pe_current_state = error_recovery;
            } else {
                pd_prot_ufp_pe_current_state = pe_src_hard_reset;
            }
        } else {
            pd_prot_ufp_pe_current_state = pe_src_disabled;
        }
        

    }
    else if (((current_time - pd_prot_dfp_timer_start_time_no_response) > pd_prot_timer_th_no_response) && pd_prot_dfp_timer_start_time_no_response != 0) {
        //no_responce

        //reatct to noresponce 
        if (pd_prot_dfp_counter_hard_reset < pd_prot_counter_th_hard_reset) {
            if (pd_phy_dfp_attached && pd_prot_dfp_negotiated_sink_met) {
                pd_prot_dfp_pe_current_state = error_recovery;
            } else {
                pd_prot_dfp_pe_current_state = pe_src_hard_reset;
            }
        } else {
            pd_prot_dfp_pe_current_state = pe_src_disabled;
        }
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
    else if (((current_time - pd_prot_ufp_timer_start_time_receive_response) > pd_prot_timer_th_receive_response) && pd_prot_ufp_timer_start_time_receive_response != 0) {
        //receive_responce
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_receive_response) > pd_prot_timer_th_receive_response) && pd_prot_dfp_timer_start_time_receive_response != 0) {
        //receive_responce
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_retry) > pd_prot_timer_th_retry) && pd_prot_ufp_timer_start_time_retry != 0) {
        //retry
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_retry) > pd_prot_timer_th_retry) && pd_prot_dfp_timer_start_time_retry != 0) {
        //retry
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_sender_response) > pd_prot_timer_th_sender_response) && pd_prot_ufp_timer_start_time_sender_response != 0) {
        //sender_responce
        
        //transition policy engine to pe_src_hard_reset
        pd_prot_ufp_pe_current_state = pe_src_hard_reset;
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_sender_response) > pd_prot_timer_th_sender_response) && pd_prot_dfp_timer_start_time_sender_response != 0) {
        //sender_responce

        //transition policy engine to pe_src_hard_reset
        pd_prot_dfp_pe_current_state = pe_src_hard_reset;
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

        //transition to pe_src_send_capabilitiys
        pd_prot_ufp_pe_current_state = pe_src_send_capabilitiys;
    
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_swap_source_start) > pd_prot_timer_th_swap_source_start) && pd_prot_dfp_timer_start_time_swap_source_start != 0) {
        //swap_source_start

        //transition to pe_src_send_capabilitiys
        pd_prot_dfp_pe_current_state = pe_src_send_capabilitiys;
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
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_receiver_response) > pd_prot_timer_th_vdm_receiver_response) && pd_prot_ufp_timer_start_time_vdm_receiver_response != 0) {
        //vdm_receiver_response
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_receiver_response) > pd_prot_timer_th_vdm_receiver_response) && pd_prot_dfp_timer_start_time_vdm_receiver_response != 0) {
        //vdm_receiver_response
    }
    else if (((current_time - pd_prot_ufp_timer_start_time_vdm_sender_response) > pd_prot_timer_th_vdm_sender_response) && pd_prot_ufp_timer_start_time_vdm_sender_response != 0) {
        //vdm_sender_responce
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_vdm_sender_response) > pd_prot_timer_th_vdm_sender_response) && pd_prot_dfp_timer_start_time_vdm_sender_response != 0) {
        //vdm_sender_response
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
    else if (((current_time - pd_prot_ufp_timer_start_time_source_pps_comm) > pd_prot_timer_th_source_pps_comm) && pd_prot_ufp_timer_start_time_source_pps_comm != 0) {
        //source_pps_comm
        pd_prot_ufp_pe_current_state = pe_src_hard_reset;
    }
    else if (((current_time - pd_prot_dfp_timer_start_time_source_pps_comm) > pd_prot_timer_th_source_pps_comm) && pd_prot_dfp_timer_start_time_source_pps_comm != 0) {
        //source_pps_comm
        pd_prot_dfp_pe_current_state = pe_src_hard_reset;
    }


    return;
}

/**
 * Controls the timer for a specific PD protocol event.
 *
 * @param ufp_dfp The prt to contrtol (UFP or DFP).
 * @param name The name of the timer to start or stop.
 * @param start_stop Specifies whether to start or stop the timer.
 */
void pd_prot_timer_controler (enum ufp_dfp ufp_dfp, enum pd_prot_timer_names name, enum pd_prot_timer_start_stop start_stop) {
    //slect witch timer to start or stop 
    switch (name) {
    case ac_temp_update:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_ac_temp_update == 0) {
                    pd_prot_ufp_timer_start_time_ac_temp_update = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_ac_temp_update == 0) {
                    pd_prot_dfp_timer_start_time_ac_temp_update = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_bist_cont_mode == 0) {
                    pd_prot_ufp_timer_start_time_bist_cont_mode = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_bist_cont_mode == 0) {
                    pd_prot_dfp_timer_start_time_bist_cont_mode = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_shared_test_mode == 0) {
                    pd_prot_ufp_timer_start_time_shared_test_mode = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_shared_test_mode == 0) {
                    pd_prot_dfp_timer_start_time_shared_test_mode = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_cable_message == 0) {
                    pd_prot_ufp_timer_start_time_cable_message = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_cable_message == 0) {
                    pd_prot_dfp_timer_start_time_cable_message = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_chunking_not_supported == 0) {
                    pd_prot_ufp_timer_start_time_chunking_not_supported = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_chunking_not_supported == 0) {
                    pd_prot_dfp_timer_start_time_chunking_not_supported = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_chunk_recevier_request == 0) {
                    pd_prot_ufp_timer_start_time_chunk_recevier_request = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_chunk_recevier_request == 0) {
                    pd_prot_dfp_timer_start_time_chunk_recevier_request = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_chunk_recevier_response == 0) {
                    pd_prot_ufp_timer_start_time_chunk_recevier_response = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_chunk_recevier_response == 0) {
                    pd_prot_dfp_timer_start_time_chunk_recevier_response = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_chunk_sender_request == 0) {
                    pd_prot_ufp_timer_start_time_chunk_sender_request = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_chunk_sender_request == 0) {
                    pd_prot_dfp_timer_start_time_chunk_sender_request = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_chunk_sender_response == 0) {
                    pd_prot_ufp_timer_start_time_chunk_sender_response = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_chunk_sender_response == 0) {
                    pd_prot_dfp_timer_start_time_chunk_sender_response = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_data_reset == 0) {
                    pd_prot_ufp_timer_start_time_data_reset = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_data_reset == 0) {
                    pd_prot_dfp_timer_start_time_data_reset = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_data_reset_fail == 0) {
                    pd_prot_ufp_timer_start_time_data_reset_fail = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_data_reset_fail == 0) {
                    pd_prot_dfp_timer_start_time_data_reset_fail = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_data_reset_fail_ufp == 0) {
                    pd_prot_ufp_timer_start_time_data_reset_fail_ufp = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_data_reset_fail_ufp == 0) {
                    pd_prot_dfp_timer_start_time_data_reset_fail_ufp = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_discover_identity == 0) {
                    pd_prot_ufp_timer_start_time_discover_identity = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_discover_identity == 0) {
                    pd_prot_dfp_timer_start_time_discover_identity = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_dr_swap_hard_reset == 0) {
                    pd_prot_ufp_timer_start_time_dr_swap_hard_reset = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_dr_swap_hard_reset == 0) {
                    pd_prot_dfp_timer_start_time_dr_swap_hard_reset = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_dr_swap_wait == 0) {
                    pd_prot_ufp_timer_start_time_dr_swap_wait = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_dr_swap_wait == 0) {
                    pd_prot_dfp_timer_start_time_dr_swap_wait = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_enter_usb == 0) {
                    pd_prot_ufp_timer_start_time_enter_usb = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_enter_usb == 0) {
                    pd_prot_dfp_timer_start_time_enter_usb = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_enter_usb_wait == 0) {
                    pd_prot_ufp_timer_start_time_enter_usb_wait = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_enter_usb_wait == 0) {
                    pd_prot_dfp_timer_start_time_enter_usb_wait = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_enter_epr == 0) {
                    pd_prot_ufp_timer_start_time_enter_epr = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_enter_epr == 0) {
                    pd_prot_dfp_timer_start_time_enter_epr = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery == 0) {
                    pd_prot_ufp_timer_start_time_epr_soruce_cable_discovvery = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery == 0) {
                    pd_prot_dfp_timer_start_time_epr_soruce_cable_discovvery = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_fisrt_source_cap == 0) {
                    pd_prot_ufp_timer_start_time_fisrt_source_cap = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_fisrt_source_cap == 0) {
                    pd_prot_dfp_timer_start_time_fisrt_source_cap = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_fr_swap_5v == 0) {
                    pd_prot_ufp_timer_start_time_fr_swap_5v = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_fr_swap_5v == 0) {
                    pd_prot_dfp_timer_start_time_fr_swap_5v = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_fr_swap_complete == 0) {
                    pd_prot_ufp_timer_start_time_fr_swap_complete = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_fr_swap_complete == 0) {
                    pd_prot_dfp_timer_start_time_fr_swap_complete = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_fr_swap_init == 0) {
                    pd_prot_ufp_timer_start_time_fr_swap_init = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_fr_swap_init == 0) {
                    pd_prot_dfp_timer_start_time_fr_swap_init = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_hard_reset == 0) {
                    pd_prot_ufp_timer_start_time_hard_reset = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_hard_reset == 0) {
                    pd_prot_dfp_timer_start_time_hard_reset = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_hard_reset_complete == 0) {
                    pd_prot_ufp_timer_start_time_hard_reset_complete = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_hard_reset_complete == 0) {
                    pd_prot_dfp_timer_start_time_hard_reset_complete = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_source_epr_keep_alive == 0) {
                    pd_prot_ufp_timer_start_time_source_epr_keep_alive = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_source_epr_keep_alive == 0) {
                    pd_prot_dfp_timer_start_time_source_epr_keep_alive = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_sink_epr_keep_alive == 0) {
                    pd_prot_ufp_timer_start_time_sink_epr_keep_alive = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_sink_epr_keep_alive == 0) {
                    pd_prot_dfp_timer_start_time_sink_epr_keep_alive = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_no_response == 0) {
                    pd_prot_ufp_timer_start_time_no_response = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_no_response == 0) {
                    pd_prot_dfp_timer_start_time_no_response = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_no_response = 0;
            } else {
                pd_prot_dfp_timer_start_time_no_response = 0;
            }
        }
        break;
    
    case pps_request:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_pps_request == 0) {
                    pd_prot_ufp_timer_start_time_pps_request = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_pps_request == 0) {
                    pd_prot_dfp_timer_start_time_pps_request = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_pps_timeout == 0) {
                    pd_prot_ufp_timer_start_time_pps_timeout = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_pps_timeout == 0) {
                    pd_prot_dfp_timer_start_time_pps_timeout = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_prot_err_hard_reset == 0) {
                    pd_prot_ufp_timer_start_time_prot_err_hard_reset = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_prot_err_hard_reset == 0) {
                    pd_prot_dfp_timer_start_time_prot_err_hard_reset = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_prot_err_soft_reset == 0) {
                    pd_prot_ufp_timer_start_time_prot_err_soft_reset = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_prot_err_soft_reset == 0) {
                    pd_prot_dfp_timer_start_time_prot_err_soft_reset = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_pr_swap_wait == 0) {
                    pd_prot_ufp_timer_start_time_pr_swap_wait = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_pr_swap_wait == 0) {
                    pd_prot_dfp_timer_start_time_pr_swap_wait = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_ps_hard_reset == 0) {
                    pd_prot_ufp_timer_start_time_ps_hard_reset = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_ps_hard_reset == 0) {
                    pd_prot_dfp_timer_start_time_ps_hard_reset = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_spr_ps_source_off == 0) {
                    pd_prot_ufp_timer_start_time_spr_ps_source_off = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_spr_ps_source_off == 0) {
                    pd_prot_dfp_timer_start_time_spr_ps_source_off = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_epr_ps_source_off == 0) {
                    pd_prot_ufp_timer_start_time_epr_ps_source_off = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_epr_ps_source_off == 0) {
                    pd_prot_dfp_timer_start_time_epr_ps_source_off = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_ps_source_on == 0) {
                    pd_prot_ufp_timer_start_time_ps_source_on = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_ps_source_on == 0) {
                    pd_prot_dfp_timer_start_time_ps_source_on = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_spr_ps_transition == 0) {
                    pd_prot_ufp_timer_start_time_spr_ps_transition = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_spr_ps_transition == 0) {
                    pd_prot_dfp_timer_start_time_spr_ps_transition = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_epr_ps_transition == 0) {
                    pd_prot_ufp_timer_start_time_epr_ps_transition = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_epr_ps_transition == 0) {
                    pd_prot_dfp_timer_start_time_epr_ps_transition = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_receive == 0) {
                    pd_prot_ufp_timer_start_time_receive = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_receive == 0) {
                    pd_prot_dfp_timer_start_time_receive = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_receive = 0;
            } else {
                pd_prot_dfp_timer_start_time_receive = 0;
            }
        }
        break;
        case receive_response:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_receive_response == 0) {
                    pd_prot_ufp_timer_start_time_receive_response = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_receive_response == 0) {
                    pd_prot_dfp_timer_start_time_receive_response = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_receive_response = 0;
            } else {
                pd_prot_dfp_timer_start_time_receive_response = 0;
            }
        }
        break;
    
    case retry:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_retry == 0) {
                    pd_prot_ufp_timer_start_time_retry = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_retry == 0) {
                    pd_prot_dfp_timer_start_time_retry = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_retry = 0;
            } else {
                pd_prot_dfp_timer_start_time_retry = 0;
            }
        }
        break;
    
    case sender_response:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_sender_response == 0) {
                    pd_prot_ufp_timer_start_time_sender_response = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_sender_response == 0) {
                    pd_prot_dfp_timer_start_time_sender_response = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_sender_response = 0;
            } else {
                pd_prot_dfp_timer_start_time_sender_response = 0;
            }
        }
        break;
    
    case sink_delay:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_sink_delay == 0) {
                    pd_prot_ufp_timer_start_time_sink_delay = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_sink_delay == 0) {
                    pd_prot_dfp_timer_start_time_sink_delay = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_sink_tx == 0) {
                    pd_prot_ufp_timer_start_time_sink_tx = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_sink_tx == 0) {
                    pd_prot_dfp_timer_start_time_sink_tx = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_soft_reset == 0) {
                    pd_prot_ufp_timer_start_time_soft_reset = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_soft_reset == 0) {
                    pd_prot_dfp_timer_start_time_soft_reset = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_scr_holds_bus == 0) {
                    pd_prot_ufp_timer_start_time_scr_holds_bus = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_scr_holds_bus == 0) {
                    pd_prot_dfp_timer_start_time_scr_holds_bus = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_swap_sink_ready == 0) {
                    pd_prot_ufp_timer_start_time_swap_sink_ready = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_swap_sink_ready == 0) {
                    pd_prot_dfp_timer_start_time_swap_sink_ready = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_swap_source_start == 0) {
                    pd_prot_ufp_timer_start_time_swap_source_start = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_swap_source_start == 0) {
                    pd_prot_dfp_timer_start_time_swap_source_start = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_transmit == 0) {
                    pd_prot_ufp_timer_start_time_transmit = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_transmit == 0) {
                    pd_prot_dfp_timer_start_time_transmit = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_type_c_send_source_cap == 0) {
                    pd_prot_ufp_timer_start_time_type_c_send_source_cap = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_type_c_send_source_cap == 0) {
                    pd_prot_dfp_timer_start_time_type_c_send_source_cap = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_type_c_sink_wait_cap == 0) {
                    pd_prot_ufp_timer_start_time_type_c_sink_wait_cap = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_type_c_sink_wait_cap == 0) {
                    pd_prot_dfp_timer_start_time_type_c_sink_wait_cap = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vconn_source_discharge == 0) {
                    pd_prot_ufp_timer_start_time_vconn_source_discharge = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vconn_source_discharge == 0) {
                    pd_prot_dfp_timer_start_time_vconn_source_discharge = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vconn_source_off == 0) {
                    pd_prot_ufp_timer_start_time_vconn_source_off = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vconn_source_off == 0) {
                    pd_prot_dfp_timer_start_time_vconn_source_off = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vconn_source_on == 0) {
                    pd_prot_ufp_timer_start_time_vconn_source_on = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vconn_source_on == 0) {
                    pd_prot_dfp_timer_start_time_vconn_source_on = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vconn_source_timeout == 0) {
                    pd_prot_ufp_timer_start_time_vconn_source_timeout = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vconn_source_timeout == 0) {
                    pd_prot_dfp_timer_start_time_vconn_source_timeout = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vconn_swap_wait == 0) {
                    pd_prot_ufp_timer_start_time_vconn_swap_wait = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vconn_swap_wait == 0) {
                    pd_prot_dfp_timer_start_time_vconn_swap_wait = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vdm_busy == 0) {
                    pd_prot_ufp_timer_start_time_vdm_busy = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vdm_busy == 0) {
                    pd_prot_dfp_timer_start_time_vdm_busy = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vdm_enter_mode == 0) {
                    pd_prot_ufp_timer_start_time_vdm_enter_mode = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vdm_enter_mode == 0) {
                    pd_prot_dfp_timer_start_time_vdm_enter_mode = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vdm_exit_mode == 0) {
                    pd_prot_ufp_timer_start_time_vdm_exit_mode = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vdm_exit_mode == 0) {
                    pd_prot_dfp_timer_start_time_vdm_exit_mode = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vdm_receiver_response == 0) {
                    pd_prot_ufp_timer_start_time_vdm_receiver_response = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vdm_receiver_response == 0) {
                    pd_prot_dfp_timer_start_time_vdm_receiver_response = millis();
                }
            }
            } else {
                if (ufp_dfp == ufp) {
                    pd_prot_ufp_timer_start_time_vdm_receiver_response = 0;
                } else {
                    pd_prot_dfp_timer_start_time_vdm_receiver_response = 0;
                }
            }
        break;
    
    case vdm_sender_responce:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_vdm_sender_response == 0) {
                    pd_prot_ufp_timer_start_time_vdm_sender_response = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vdm_sender_response == 0) {
                    pd_prot_dfp_timer_start_time_vdm_sender_response = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_sender_response = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_sender_responce = 0;
            }
        }
        break;
    
    case vdm_wait_mode_entry:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_vdm_wait_mode_entry == 0) {
                    pd_prot_ufp_timer_start_time_vdm_wait_mode_entry = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vdm_wait_mode_entry == 0) {
                    pd_prot_dfp_timer_start_time_vdm_wait_mode_entry = millis();
                }
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
                if (pd_prot_ufp_timer_start_time_vdm_wait_mode_exit == 0) {
                    pd_prot_ufp_timer_start_time_vdm_wait_mode_exit = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_vdm_wait_mode_exit == 0) {
                    pd_prot_dfp_timer_start_time_vdm_wait_mode_exit = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_vdm_wait_mode_exit = 0;
            } else {
                pd_prot_dfp_timer_start_time_vdm_wait_mode_exit = 0;
            }
        }
        break;

    case source_pps_comm:
        if (start_stop == start) {
            if (ufp_dfp == ufp) {
                if (pd_prot_ufp_timer_start_time_source_pps_comm == 0) {
                    pd_prot_ufp_timer_start_time_source_pps_comm = millis();
                }
            } else {
                if (pd_prot_dfp_timer_start_time_source_pps_comm == 0) {
                    pd_prot_dfp_timer_start_time_source_pps_comm = millis();
                }
            }
        } else {
            if (ufp_dfp == ufp) {
                pd_prot_ufp_timer_start_time_source_pps_comm = 0;
            } else {
                pd_prot_dfp_timer_start_time_source_pps_comm = 0;
            }
        }
        break;

    }
    
    return;
}

/**
 * @brief Builds the header contents for a PD protocol message.
 *
 * This function constructs the header contents for a PD protocol message based on the provided parameters.
 *
 * @param extended_msg A boolean indicating whether the message is extended or not.
 * @param n_data_objects The number of data objects in the message.
 * @param msg_id The message ID.
 * @param power_role The power role of the port.
 * @param spec_revision The specification revision.
 * @param data_role The data role of the port.
 * @param msg_type The message type.
 * @return The header contents for the PD protocol message.
 */
uint16_t pd_prot_build_header (bool extended_msg, uint16_t n_data_objects, uint16_t msg_id, enum pd_prot_port_power_role power_role, uint16_t spec_revision, enum ufp_dfp data_role, uint16_t msg_type) {
    //init local vars
    uint16_t header_contents = 0;

    //set extended bit if msg is extended
    if (extended_msg) {
        header_contents = 0x8000;
    }

    //mask n of data objects
    n_data_objects = n_data_objects & 0x0007;

    //shift n data objects to correct pos in header
    n_data_objects = n_data_objects << 12;

    //add n data objects to header
    header_contents = header_contents | n_data_objects;

    //mask msg id 
    msg_id = msg_id & 0x0007;

    //shift msg id to correct pos in header
    msg_id = msg_id << 9;

    //add msg_id to header
    header_contents = header_contents | msg_id;

    //set port power role 
    if (power_role == src) {
        header_contents = header_contents | 0x0100;
    }

    //set spec revision 
    if (spec_revision == 1) {
        // do nothing leave bits at 0
    } else if (spec_revision == 2) {
        header_contents = header_contents | 0x0040;
    } else if (spec_revision == 3) {
        header_contents = header_contents | 0x0080;
    }

    //set port data role
    if (data_role == ufp) {
        //do nothing leave at 0
    } else if (data_role == dfp) {
        header_contents = header_contents | 0x0020;
    }

    //set message type
    msg_type = msg_type & 0x001F;

    //add message type to header 
    header_contents = header_contents | msg_type;

    return header_contents;

}

/**
 * @brief Builds the extended header for PD protocol.
 *
 * This function builds the extended header for PD protocol based on the provided parameters.
 *
 * @param chunked         A boolean indicating whether the message is chunked or not.
 * @param chunk_number    The chunk number if the message is chunked.
 * @param request_chunk   A boolean indicating whether the chunk is a request chunk or not.
 * @param data_size       The size of the data in the message.
 *
 * @return The built extended header as a 16-bit unsigned integer.
 */
uint16_t pd_prot_build_ext_header (bool chunked, uint16_t chunk_number, bool request_chunk, uint16_t data_size) {
    //init local vars
    uint16_t ext_header_contents = 0;

    //set chunked bit
    if (chunked) {
        ext_header_contents = ext_header_contents | 0x8000;

        //mask chunk number
        chunk_number = chunk_number & 0x0007;

        //shift chunk number to correct place 
        chunk_number = chunk_number << 11;

        //add chunk number to header contents
        ext_header_contents = ext_header_contents | chunk_number;

        //set request bit
        if (request_chunk) {
            ext_header_contents = ext_header_contents | 0x0400;
        }

    }

    //mask data size
    data_size = data_size & 0x001F;

    //add data size to header
    ext_header_contents = ext_header_contents | data_size;

    return ext_header_contents;
}

/**
 * @brief Determines the message type for the given UFP/DFP port.
 * 
 * This function checks the received message contents for the specified UFP/DFP port
 * and determines whether the message type is normal or extended. The message type is
 * determined based on the most significant bit (MSB) of the first byte of the received
 * message contents.
 * 
 * @param ufp_dfp The UFP/DFP port to check.
 * @return The message type, either normal or extended.
 */
enum pd_prot_message_type_enum pd_prot_message_type (enum ufp_dfp ufp_dfp) {

    //select port to determine if its chunked
    if (ufp_dfp == ufp) {
        if ((pd_phy_ufp_last_received_message_contents[0] & 0x80) == 0){
            return normal;
        } else {
            return extended;
        }
    } else {
        if ((pd_phy_dfp_last_received_message_contents[0] & 0x80) == 0){
            return normal;
        } else {
            return extended;
        }
    }
}

/**
 * Determines if the received PD message is chunked.
 * 
 * @param ufp_dfp The enum value representing the port type (ufp or dfp).
 * @return True if the message is chunked, false otherwise.
 */
bool pd_prot_ext_msg_chunked (enum ufp_dfp ufp_dfp) {

    //select port to determine if its chunked
    if (ufp_dfp == ufp) {
        if ((pd_phy_ufp_last_received_message_contents[2] & 0x80) == 0) {
            return false;
        } else {
            return true;
        }
    } else {
        if ((pd_phy_dfp_last_received_message_contents[2] & 0x80) == 0) {
            return false;
        } else {
            return true;
        }
    }

}

/**
 * @brief Calculates the number of chunks in an extended message.
 * 
 * This function calculates the number of chunks in an extended message based on the type of port (ufp or dfp).
 * 
 * @param ufp_dfp The type of port (ufp or dfp).
 * @return The number of chunks in the extended message.
 */
int pd_prot_ext_msg_n_chunks (enum ufp_dfp ufp_dfp) {

    //determine port to check
    if (ufp_dfp == ufp) {
        return ((pd_phy_ufp_last_received_message_contents[2] & 0x01) << 8) | pd_phy_ufp_last_received_message_contents[3];
    } else {
        return ((pd_phy_dfp_last_received_message_contents[2] & 0x01) << 8) | pd_phy_dfp_last_received_message_contents[3];
    }
}

/**
 * @brief Checks if a soft reset has occurred.
 * 
 * This function checks if a soft reset has occurred based on the received message contents.
 * 
 * @param ufp_dfp The type of device (UFP or DFP).
 * @return True if a soft reset has occurred, false otherwise.
 */
bool pd_prot_check_soft_reset (enum ufp_dfp ufp_dfp) {

    if (ufp_dfp == ufp) {
        if ((pd_phy_ufp_last_received_message_contents[1] & 0x1F) == 0x0D){
            return true;
        } else {
            return false;
        }
    } else {
        if ((pd_phy_dfp_last_received_message_contents[1] & 0x1F) == 0x0D){
            return true;
        } else {
            return false;
        }
    }
}

/**
 * @brief Discards the message and resets receive variables for a given port.
 * 
 * This function is used to discard the message and reset all receive variables for a given port.
 * It takes an enum parameter `ufp_dfp` which specifies whether the port is UFP (Upstream Facing Port) or DFP (Downstream Facing Port).
 * If the port is UFP, it resets the receive variables for UFP. If the port is DFP, it resets the receive variables for DFP.
 * 
 * @param ufp_dfp The enum value specifying the port type (UFP or DFP).
 */
void pd_prot_discard_message (enum ufp_dfp ufp_dfp) {

    if (ufp_dfp == ufp) {
        //reset all receive vars for given port
        pd_prot_ufp_counter_message_id = 0;
        pd_phy_ufp_last_received_message_id = 0;
        pd_phy_ufp_last_received_message_length = 0;
        pd_phy_ufp_last_received_message_type = sop;
        for (int i; i < 256; ++i) {
            pd_phy_ufp_last_received_message_contents[i] = 0;
        }

    } else {
        //reset all receive vars for given port
        pd_prot_dfp_counter_message_id = 0;
        pd_phy_dfp_last_received_message_id = 0;
        pd_phy_dfp_last_received_message_length = 0;
        pd_phy_dfp_last_received_message_type = sop;
        for (int i; i < 256; ++i) {
            pd_phy_dfp_last_received_message_contents[i] = 0;
        }
    }
}

/**
 * @brief Determines the last data message type based on the selected port.
 * 
 * @param ufp_dfp The selected port (ufp or dfp).
 * @return The last data message type.
 */
enum pd_prot_data_msg_enum pd_prot_determine_last_data_message_type (enum ufp_dfp ufp_dfp){
    
    //select port to check
    if(ufp_dfp == ufp) {
        if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_alert) == pd_prot_data_msg_alert) {
            return alert;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_battery_status) == pd_prot_data_msg_battery_status) {
            return battery_status;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_bist) == pd_prot_data_msg_bist) {
            return bist;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_enter_usb) == pd_prot_data_msg_enter_usb) {
            return enter_usb_msg;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_epr_request) == pd_prot_data_msg_epr_request) {
            return epr_request;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_get_country_info) == pd_prot_data_msg_get_country_info) {
            return get_country_info;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_per_mode) == pd_prot_data_msg_per_mode) {
            return per_mode;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_request) == pd_prot_data_msg_request) {
            return request;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_sink_capabilities) == pd_prot_data_msg_sink_capabilities) {
            return sink_capabilitiys;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_source_capabilities) == pd_prot_data_msg_source_capabilities) {
            return sounce_capabilitiys;
        } else if ((pd_phy_ufp_last_received_message_contents[1] & pd_prot_data_msg_source_info) == pd_prot_data_msg_source_info) {
            return source_info;
        }
    } else {
        if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_alert) == pd_prot_data_msg_alert) {
            return alert;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_battery_status) == pd_prot_data_msg_battery_status) {
            return battery_status;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_bist) == pd_prot_data_msg_bist) {
            return bist;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_enter_usb) == pd_prot_data_msg_enter_usb) {
            return enter_usb_msg;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_epr_request) == pd_prot_data_msg_epr_request) {
            return epr_request;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_get_country_info) == pd_prot_data_msg_get_country_info) {
            return get_country_info;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_per_mode) == pd_prot_data_msg_per_mode) {
            return per_mode;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_request) == pd_prot_data_msg_request) {
            return request;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_sink_capabilities) == pd_prot_data_msg_sink_capabilities) {
            return sink_capabilitiys;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_source_capabilities) == pd_prot_data_msg_source_capabilities) {
            return sounce_capabilitiys;
        } else if ((pd_phy_dfp_last_received_message_contents[1] & pd_prot_data_msg_source_info) == pd_prot_data_msg_source_info) {
            return source_info;
        }
    }
    return void_msg;
}

/*
enum pd_prot_power_cap_enum pd_prot_pdo_determiner (enum ufp_dfp ufp_dfp) {
    
}

*/


void pd_prot_hard_reset_handeler (enum ufp_dfp ufp_dfp, bool from_policy_engine) {
    //discard last recived message
    pd_prot_discard_message(ufp_dfp);

    //check if reset was called for from the policy engine or PHY
    if (from_policy_engine) {
        pd_phy_send_hard_reset(ufp_dfp);
        pd_prot_timer_controler(ufp_dfp, hard_reset_complete, start);
    } else {
        //pd_prot_hard_reset_handler_pt_2(ufp_dfp);
    }

}


/**
 * @brief Sets the last message for the specified UFP/DFP.
 * 
 * This function sets the last message for the specified UFP (Upstream Facing Port) or DFP (Downstream Facing Port).
 * The last message is stored in an array and its length is also updated.
 * 
 * @param ufp_dfp The UFP/DFP for which to set the last message.
 * @param message The message to be set as the last message.
 * @param length_of_message The length of the message.
 */
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

/**
 * @brief Transmits the source capabilities message for the specified UFP/DFP port.
 *
 * This function builds and transmits a message containing the source capabilities for the specified UFP/DFP port.
 * The message includes the number of PDOs and the current message ID. The PDOs are appended to the message based on
 * the given power capability of the port.
 *
 * @param ufp_dfp The type of port (UFP or DFP) for which to transmit the source capabilities.
 */
void pd_prot_transmit_source_capabilities (enum ufp_dfp ufp_dfp) {
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
    uint16_t headder = pd_prot_build_header(false, n_pdo, current_msg_id, src, 3, ufp_dfp, pd_prot_data_msg_source_capabilities);

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

/**
 * @brief Decodes the sink capabilities message and determines if the negotiated sink voltage can be met.
 * 
 * This function decodes the sink capabilities message received from the UFP (Upstream Facing Port) or DFP (Downstream Facing Port).
 * It determines the number of PDOs in the message and checks if the negotiated sink voltage can be met within a certain tolerance.
 * If the negotiated sink voltage can be met, it sets the corresponding variables (`pd_prot_ufp_negotiated_sink_met` and `pd_prot_ufp_negotiated_sink_voltage`
 * for UFP, `pd_prot_dfp_negotiated_sink_met` and `pd_prot_dfp_negotiated_sink_voltage` for DFP) to true and the negotiated voltage value.
 * Otherwise, it sets the variables to false and 0.
 * 
 * @param ufp_dfp The type of port (UFP or DFP) for which to decode the sink capabilities.
 */
void pd_prot_decode_sink_capabilities (enum ufp_dfp ufp_dfp) {
    //init local vars
    int n_pdo = 0;
    u_int32_t sink_pdo = 0;
    u_int16_t headder = 0;
    u_int16_t voltage = 0;
    
    //check how many PDOs are in the message
    if (ufp_dfp == ufp) {
        headder = pd_phy_ufp_last_received_message_contents[1];
        headder = pd_phy_ufp_last_received_message_contents[0] << 8 | headder;
        n_pdo = ((headder >> 12) & 0x0007);

        if (n_pdo == 1) {
            //if only one pdo go straight to vsafe5v
            pd_prot_ufp_negotiated_sink_met = true;
            pd_prot_ufp_negotiated_sink_voltage = 5;
            return;

        } else {
            //if more than one pdo determine if they can be met
            sink_pdo = (pd_phy_dfp_last_received_message_contents[6] << 24);
            sink_pdo = (pd_phy_dfp_last_received_message_contents[7] << 16) | sink_pdo;
            sink_pdo = (pd_phy_dfp_last_received_message_contents[8] << 8) | sink_pdo;
            sink_pdo = pd_phy_dfp_last_received_message_contents[9] | sink_pdo;

            if ((sink_pdo & 0xC0000000) >> 30 == 0x00) {
                //decode voltage portion of message
                voltage = (sink_pdo >> 10) & 9;
                voltage = voltage * 0.05;

                //check if voltage can be met within 10% of the requested voltage
                if (abs(voltage - 5) <= 0.5) {
                    pd_prot_ufp_negotiated_sink_met = true;
                    pd_prot_ufp_negotiated_sink_voltage = 5;
                    return;
                } else if (abs(voltage - 9) <= 0.9) {
                    pd_prot_ufp_negotiated_sink_met = true;
                    pd_prot_ufp_negotiated_sink_voltage = 9;
                    return;
                } else if (abs(voltage - 12) <= 1.2) {
                    pd_prot_ufp_negotiated_sink_met = true;
                    pd_prot_ufp_negotiated_sink_voltage = 12;
                    return;
                } else if (abs(voltage - 15) <= 1.5) {
                    pd_prot_ufp_negotiated_sink_met = true;
                    pd_prot_ufp_negotiated_sink_voltage = 15;
                    return;
                } else if (abs(voltage - 20) <= 2) {
                    pd_prot_ufp_negotiated_sink_met = true;
                    pd_prot_ufp_negotiated_sink_voltage = 20;
                    return;
                } else {
                    pd_prot_ufp_negotiated_sink_met = false;
                    pd_prot_ufp_negotiated_sink_voltage = 0;
                    return;
                }
            } else {
                pd_prot_ufp_negotiated_sink_met = false;
                pd_prot_ufp_negotiated_sink_voltage = 0;
                return;
            }
        }
        
    } else {
        headder = pd_phy_dfp_last_received_message_contents[1];
        headder = pd_phy_dfp_last_received_message_contents[0] << 8 | headder;
        n_pdo = ((headder >> 12) & 0x0007);

        if (n_pdo == 1) {
            //if only one pdo go straight to vsafe5v
            pd_prot_dfp_negotiated_sink_met = true;
            pd_prot_dfp_negotiated_sink_voltage = 5;
            return;

        } else {
            //if more than one pdo determine if they can be met
            sink_pdo = (pd_phy_dfp_last_received_message_contents[6] << 24);
            sink_pdo = (pd_phy_dfp_last_received_message_contents[7] << 16) | sink_pdo;
            sink_pdo = (pd_phy_dfp_last_received_message_contents[8] << 8) | sink_pdo;
            sink_pdo = pd_phy_dfp_last_received_message_contents[9] | sink_pdo;

            if ((sink_pdo & 0xC0000000) >> 30 == 0x00) {
                //decode voltage portion of message
                voltage = (sink_pdo >> 10) & 9;
                voltage = voltage * 0.05;

                //check if voltage can be met within 10% of the requested voltage
                if (abs(voltage - 5) <= 0.5) {
                    pd_prot_dfp_negotiated_sink_met = true;
                    pd_prot_dfp_negotiated_sink_voltage = 5;
                    return;
                } else if (abs(voltage - 9) <= 0.9) {
                    pd_prot_dfp_negotiated_sink_met = true;
                    pd_prot_dfp_negotiated_sink_voltage = 9;
                    return;
                } else if (abs(voltage - 12) <= 1.2) {
                    pd_prot_dfp_negotiated_sink_met = true;
                    pd_prot_dfp_negotiated_sink_voltage = 12;
                    return;
                } else if (abs(voltage - 15) <= 1.5) {
                    pd_prot_dfp_negotiated_sink_met = true;
                    pd_prot_dfp_negotiated_sink_voltage = 15;
                    return;
                } else if (abs(voltage - 20) <= 2) {
                    pd_prot_dfp_negotiated_sink_met = true;
                    pd_prot_dfp_negotiated_sink_voltage = 20;
                    return;
                } else {
                    pd_prot_dfp_negotiated_sink_met = false;
                    pd_prot_dfp_negotiated_sink_voltage = 0;
                    return;
                }
            } else {
                pd_prot_dfp_negotiated_sink_met = false;
                pd_prot_dfp_negotiated_sink_voltage = 0;
                return;
            }
        }
    }

    return;
}

/**
 * @brief Transmits a PD protocol command.
 *
 * This function transmits a PD protocol command based on the provided command type.
 *
 * @param ufp_dfp The type of port (UFP or DFP) to transmit the command on.
 * @param pd_prot_cont_msg_enum The PD protocol command type to transmit.
 */
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
    case soft_reset_msg:
        selected_comand = pd_prot_cont_msg_soft_reset;
        break;
    case data_reset_msg:
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
    uint16_t headder = pd_prot_build_header(false, 0, 0, src, 3, ufp_dfp, selected_comand);

    //load headder in to array
    message[1] = headder & 0xFF;
    message[0] = (headder >> 8) & 0xFF;

    //set last message vars for a given port
    pd_prot_set_last_message(ufp_dfp, message, 2);

    //transmit the message
    pd_phy_transmit(ufp_dfp, message, 2);
    
    return;

}

/**
 * @brief Handles the receive state machine for the PD protocol.
 *
 * This function is responsible for processing received messages and performing
 * necessary checks and actions based on the message content and the current
 * state of the protocol. It checks for soft reset, verifies the message ID,
 * and passes the message to the policy engine for further processing.
 *
 * @param ufp_dfp The role of the device (UFP or DFP) for which the receive
 *                state machine is being executed.
 */
void pd_prot_rx_state_machine(enum ufp_dfp ufp_dfp) {

    //check for soft reset
    if (pd_phy_ufp_last_received_message_id == pd_prot_ufp_counter_message_id){
        pd_prot_discard_message(ufp_dfp);
    }

    //check if message id matches expected id
    //if not set current message id to last received id
    if (ufp_dfp == ufp) {
        if (pd_phy_ufp_last_received_message_id == pd_prot_ufp_counter_message_id){
            pd_prot_discard_message(ufp_dfp);
        } else {
            pd_prot_ufp_counter_message_id = pd_phy_ufp_last_received_message_id;
        }
    } else {
        if (pd_phy_dfp_last_received_message_id == pd_prot_dfp_counter_message_id){
            pd_prot_discard_message(ufp_dfp);
        } else {
            pd_prot_dfp_counter_message_id = pd_phy_dfp_last_received_message_id;
        }
    }

    //pass to plicy engine

    return;

}


/*
/**
 * @brief Handles the state machine for receiving chunked messages in the PD protocol.
 * 
 * This function is responsible for managing the reception of chunked messages in the PD protocol.
 * It resets the extended receive buffer and abort flags based on the UFP/DFP type.
 * If the received message is an extended message and is chunked, it performs additional checks.
 * Otherwise, it calls the `pd_prot_rx_state_machine` function to handle the reception of non-chunked messages.
 * 
 * @param ufp_dfp The type of UFP/DFP (UFP or DFP).
 *
void pd_prot_chunked_rx_state_machine(enum ufp_dfp ufp_dfp) {
    //init local vars



    //reset extended rx buffer and abort flags
    if (ufp_dfp == ufp) {
        pd_phy_ufp_last_received_message_contents[i] = 0;
        pd_phy_ufp_last_received_message_length = 0;
        pd_phy_ufp_last_received_message_type = sop;
    } else if (ufp_dfp == dfp) {
        pd_phy_dfp_last_received_message_contents[i] = 0;
        pd_phy_dfp_last_received_message_length = 0;
        pd_phy_dfp_last_received_message_type = sop;
    }

    if (pd_prot_message_type(ufp_dfp) == extended) {
        //determine if message is chunked
        if (pd_prot_ext_msg_chunked(ufp_dfp)) {
            if (pd_prot_ext_msg_n_chunks(ufp_dfp) == 0) {

            }

        }
    } else {
        pd_prot_rx_state_machine(ufp_dfp);
    }


}
*/



/**
 * @brief Implements the policy engine for the source port in the PD protocol.
 * 
 * This function is responsible for handling the state transitions and actions
 * of the source port policy engine in the PD protocol. It takes an argument
 * `ufp_dfp` which specifies whether the port is a UFP (Upstream Facing Port)
 * or a DFP (Downstream Facing Port).
 * 
 * @param ufp_dfp The type of the port (UFP or DFP).
 */
void pd_prot_src_port_policy_engine (enum ufp_dfp ufp_dfp) {

    if (ufp_dfp == ufp) {
        switch (pd_prot_ufp_pe_current_state) {
            case pe_src_hard_reset_recived:
                if (pd_prot_ufp_pe_prev_state != pe_src_hard_reset_recived) {
                    // start timers
                    pd_prot_timer_controler(ufp_dfp, ps_hard_reset, start);
                    pd_prot_timer_controler(ufp_dfp, no_responce, start);

                    pd_power_cont_en_vsafe5v(ufp_dfp);
                }
                break;
            case pe_src_transition_to_dflt:
                if (pd_prot_ufp_pe_prev_state != pe_src_transition_to_dflt) {
                    // kill vconn power
                    pd_phy_vconn_cont(ufp_dfp, off);

                    // set port data role to dfp
                    pd_prot_ufp_pe_port_data_role = dfp;

                    //turn off psu
                    pd_power_cont_return_to_base_state(ufp_dfp);

                    //start psu at vsafe5v again
                    pd_power_cont_en_vsafe5v(ufp_dfp);
                }

                //check exit condition
                if (pd_power_cont_pgood(ufp_dfp, 5)) {
                    //turn vconn back on
                    pd_phy_vconn_cont(ufp_dfp, on);

                    //transistion to pe_src_startup
                    pd_prot_ufp_pe_current_state = pe_src_startup;
                }
                break;
            case pe_src_startup:
                if (pd_prot_ufp_pe_prev_state != pe_src_startup) {
                    // reset caps counter
                    pd_prot_ufp_counter_caps = 0;

                    //reset message id counter
                    pd_prot_ufp_counter_message_id = 0;
                }

                
                break;
            case pe_src_discovery:
                if (pd_prot_ufp_pe_prev_state != pe_src_discovery) {
                    pd_prot_timer_controler(ufp_dfp, fisrt_source_cap, start);
                    if ((pd_prot_ufp_counter_caps == pd_prot_counter_th_caps) && (pd_prot_ufp_counter_hard_reset == pd_prot_counter_th_hard_reset)) {
                        pd_prot_ufp_pe_current_state = pe_src_disabled;
                    }
                }
                break;
            case pe_src_send_capabilitiys:
                // send source capabilities 
                pd_prot_transmit_source_capabilities(ufp);

                //incriment caps counter
                pd_prot_ufp_counter_caps++;

                
                // check if we got a good crc 
                if (pd_prot_ufp_last_good_crc) {
                    // reset the crc flag
                    pd_prot_ufp_last_good_crc = false;

                    //start and stop timers
                    pd_prot_timer_controler(ufp_dfp, no_responce, stop);
                    pd_prot_timer_controler(ufp_dfp, sender_response, start);

                    //reset counters
                    pd_prot_ufp_counter_caps = 0;

                    // transition to negotiations once we recive a sink_capabilitiys message
                    if (pd_phy_ufp_last_received_message_length != 0 && pd_prot_determine_last_data_message_type(ufp) == sink_capabilitiys) {
                        pd_prot_ufp_pe_current_state = pe_src_negotiate_capabilitiys;
                    }
                }


                break;
            case pe_src_disabled:
                if (pd_prot_ufp_pe_prev_state != pe_src_disabled) {
                    pd_power_cont_return_to_base_state(ufp_dfp);
                }
                break;
            case pe_src_negotiate_capabilitiys:
                if (pd_prot_ufp_pe_prev_state != pe_src_negotiate_capabilitiys) {
                    pd_prot_decode_sink_capabilities(ufp_dfp);
                    if (pd_prot_ufp_negotiated_sink_met) {
                        pd_prot_ufp_pe_current_state = pe_src_transition_supply;
                    } else {
                        pd_prot_transmit_command(ufp_dfp, reject);
                        pd_prot_ufp_pe_current_state = pe_src_capabilitiy_response;
                    }
                }
                break;
            case pe_src_transition_supply:
                if (pd_prot_ufp_pe_prev_state != pe_src_transition_supply) {
                    //send accept message
                    pd_prot_transmit_command(ufp_dfp, accept);

                    //trnsistion the supply
                    if(pd_prot_ufp_negotiated_sink_voltage == 5) {
                        pd_power_cont_en_vsafe5v(ufp_dfp);
                    } else if (pd_prot_ufp_negotiated_sink_voltage == 5 && pd_power_cont_ufp_current_voltage == 5) {
                        //do nothing
                    } else if (pd_prot_ufp_negotiated_sink_voltage == 9) {
                        pd_power_cont_en_9v(ufp_dfp);
                    } else if (pd_prot_ufp_negotiated_sink_voltage == 12) {
                        pd_power_cont_en_12v(ufp_dfp);
                    } else if (pd_prot_ufp_negotiated_sink_voltage == 15) {
                        pd_power_cont_en_15v(ufp_dfp);
                    } else if (pd_prot_ufp_negotiated_sink_voltage == 20) {
                        pd_power_cont_en_20v(ufp_dfp);
                    }
                }

                //check if the ps is in pgood state
                if (pd_power_cont_pgood(ufp_dfp, pd_prot_ufp_negotiated_sink_voltage)) {
                    //transmit ps_rdy
                    pd_prot_transmit_command(ufp_dfp, ps_rdy);

                    //transiton to pe_src_rdy
                    pd_prot_ufp_pe_current_state = pe_src_ready;
                }
                break;
            case pe_src_ready:
                if (pd_prot_ufp_pe_prev_state != pe_src_ready) {
                    //start timers
                    pd_prot_timer_controler(ufp_dfp, discover_identity, start);
                    pd_prot_timer_controler(ufp_dfp, source_pps_comm, start);
                }

                //check exit states
                if (pd_prot_message_type(ufp_dfp) == get_source_cap) {
                    //transition to pe_src_send_capabilitiys
                    pd_prot_ufp_pe_current_state = pe_src_send_capabilitiys;
                } else if (pd_prot_message_type(ufp_dfp) == request) {
                    //transition to pe_src_negotiate_capabilitiy
                    pd_prot_ufp_pe_current_state = pe_src_negotiate_capabilitiys;
                }
                break;
            case pe_src_epr_keep_alive:
                if (pd_prot_ufp_pe_prev_state != pe_src_epr_keep_alive) {
                    // something
                }
                break;
            case pe_src_get_sink_cap:
                if (pd_prot_ufp_pe_prev_state != pe_src_get_sink_cap) {
                    // something
                }
                break;
            case pe_src_give_souce_cap:
                if (pd_prot_ufp_pe_prev_state != pe_src_give_souce_cap) {
                    // something
                }
                break;
            case pe_src_capabilitiy_response:
                if (pd_prot_ufp_pe_prev_state != pe_src_capabilitiy_response) {
                    //send a reject message 
                    pd_prot_transmit_command(ufp_dfp, reject);
                }

                //check exit conditions
                if (pd_prot_ufp_negotiated_sink_met) {
                    //transition to placy engine to pe_src_ready
                    pd_prot_ufp_pe_current_state = pe_src_ready;
                    
                } 
                break;
            case pe_src_wait_new_capabilitiys:
                if (pd_prot_ufp_pe_prev_state != pe_src_wait_new_capabilitiys) {
                    // something
                }
                break;
            case pe_src_hard_reset:
                if (pd_prot_ufp_pe_prev_state != pe_src_hard_reset) {
                    //send hard reset via phy
                    pd_phy_send_hard_reset(ufp_dfp);
                    
                    //start timers
                    pd_prot_timer_controler(ufp_dfp, no_responce, start);
                    pd_prot_timer_controler(ufp_dfp, ps_hard_reset, start);

                    //incriment counters
                    pd_prot_ufp_counter_hard_reset++;

                }
                break;
            case error_recovery:
                if (pd_prot_ufp_pe_prev_state != error_recovery) {
                    // something
                }
                break;  
        }
        pd_prot_ufp_pe_prev_state = pd_prot_ufp_pe_current_state; // update previous state

    }
}









#endif // pd_prot_cpp