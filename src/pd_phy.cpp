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

#ifndef dp_phy_cpp
#define dp_phy_cpp

#include <Arduino.h>
#include <Wire.h>
#include "pd_phy.h"


//pd counters
int pd_phy_head_ufp_message_id = 0;
int pd_phy_head_dfp_message_id = 0;

//pd counter vars for ufp
//usb-if docs page 289
int pd_phy_ufp_counter_busy = 0;
int pd_phy_ufp_counter_caps = 0;
int pd_phy_ufp_counter_discover_identity = 0;
int pd_phy_ufp_counter_hard_reset = 0;
int pd_phy_ufp_counter_message_id = 0;
int pd_phy_ufp_counter_retry = 0;

//pd counter vars for dfp
//usb-if docs page 289
int pd_phy_dfp_counter_busy = 0;
int pd_phy_dfp_counter_caps = 0;
int pd_phy_dfp_counter_discover_identity = 0;
int pd_phy_dfp_counter_hard_reset = 0;
int pd_phy_dfp_counter_message_id = 0;
int pd_phy_dfp_counter_retry = 0;


//pd timer start times for ufp
//usb-if docs page 271
unsigned long pd_phy_ufp_timer_start_time_ac_temp_update = 0;
unsigned long pd_phy_ufp_timer_start_time_bist_cont_mode = 0;
unsigned long pd_phy_ufp_timer_start_time_shared_test_mode = 0;
unsigned long pd_phy_ufp_timer_start_time_cable_message = 0;
unsigned long pd_phy_ufp_timer_start_time_chunking_not_supported = 0;
unsigned long pd_phy_ufp_timer_start_time_chunk_recevier_request = 0;
unsigned long pd_phy_ufp_timer_start_time_chunk_recevier_response = 0;
unsigned long pd_phy_ufp_timer_start_time_chunk_sender_request = 0;
unsigned long pd_phy_ufp_timer_start_time_chunk_sender_response = 0;
unsigned long pd_phy_ufp_timer_start_time_data_reset = 0;
unsigned long pd_phy_ufp_timer_start_time_data_reset_fail = 0;
unsigned long pd_phy_ufp_timer_start_time_data_reset_fail_ufp = 0;
unsigned long pd_phy_ufp_timer_start_time_discover_identity = 0;
unsigned long pd_phy_ufp_timer_start_time_dr_swap_hard_reset = 0;
unsigned long pd_phy_ufp_timer_start_time_dr_swap_wait = 0;
unsigned long pd_phy_ufp_timer_start_time_enter_usb = 0;
unsigned long pd_phy_ufp_timer_start_time_enter_usb_wait = 0;
unsigned long pd_phy_ufp_timer_start_time_enter_epr = 0;
unsigned long pd_phy_ufp_timer_start_time_epr_soruce_cable_discovvery = 0;
unsigned long pd_phy_ufp_timer_start_time_fisrt_source_cap = 0;
unsigned long pd_phy_ufp_timer_start_time_fr_swap_5v = 0;
unsigned long pd_phy_ufp_timer_start_time_fr_swap_complete = 0;
unsigned long pd_phy_ufp_timer_start_time_fr_swap_init = 0;
unsigned long pd_phy_ufp_timer_start_time_hard_reset = 0;
unsigned long pd_phy_ufp_timer_start_time_hard_reset_complete = 0;
unsigned long pd_phy_ufp_timer_start_time_source_epr_keep_alive = 0;
unsigned long pd_phy_ufp_timer_start_time_sink_epr_keep_alive = 0;
unsigned long pd_phy_ufp_timer_start_time_no_responce = 0;
unsigned long pd_phy_ufp_timer_start_time_pps_request = 0;
unsigned long pd_phy_ufp_timer_start_time_pps_timeout = 0;
unsigned long pd_phy_ufp_timer_start_time_prot_err_hard_reset = 0;
unsigned long pd_phy_ufp_timer_start_time_prot_err_soft_reset = 0;
unsigned long pd_phy_ufp_timer_start_time_pr_swap_wait = 0;
unsigned long pd_phy_ufp_timer_start_time_ps_hard_reset = 0;
unsigned long pd_phy_ufp_timer_start_time_spr_ps_source_off = 0;
unsigned long pd_phy_ufp_timer_start_time_epr_ps_source_off = 0;
unsigned long pd_phy_ufp_timer_start_time_ps_source_on = 0;
unsigned long pd_phy_ufp_timer_start_time_spr_ps_transition = 0;
unsigned long pd_phy_ufp_timer_start_time_epr_ps_transition = 0;
unsigned long pd_phy_ufp_timer_start_time_receive = 0;
unsigned long pd_phy_ufp_timer_start_time_receive_responce = 0;
unsigned long pd_phy_ufp_timer_start_time_retry = 0;
unsigned long pd_phy_ufp_timer_start_time_sender_responce = 0;
unsigned long pd_phy_ufp_timer_start_time_sink_delay = 0;
unsigned long pd_phy_ufp_timer_start_time_sink_tx = 0;
unsigned long pd_phy_ufp_timer_start_time_soft_reset = 0;
unsigned long pd_phy_ufp_timer_start_time_scr_holds_bus = 0;
unsigned long pd_phy_ufp_timer_start_time_swap_sink_ready = 0;
unsigned long pd_phy_ufp_timer_start_time_swap_source_start = 0;
unsigned long pd_phy_ufp_timer_start_time_transmit = 0;
unsigned long pd_phy_ufp_timer_start_time_type_c_send_source_cap = 0;
unsigned long pd_phy_ufp_timer_start_time_type_c_sink_wait_cap = 0;
unsigned long pd_phy_ufp_timer_start_time_vconn_source_discharge = 0;
unsigned long pd_phy_ufp_timer_start_time_vconn_source_off = 0;
unsigned long pd_phy_ufp_timer_start_time_vconn_source_on = 0;
unsigned long pd_phy_ufp_timer_start_time_vconn_source_timeout = 0;
unsigned long pd_phy_ufp_timer_start_time_vconn_swap_wait = 0;
unsigned long pd_phy_ufp_timer_start_time_vdm_busy = 0;
unsigned long pd_phy_ufp_timer_start_time_vdm_enter_mode = 0;
unsigned long pd_phy_ufp_timer_start_time_vdm_exit_mode = 0;
unsigned long pd_phy_ufp_timer_start_time_vdm_receiver_responce = 0;
unsigned long pd_phy_ufp_timer_start_time_vdm_sender_responce = 0;
unsigned long pd_phy_ufp_timer_start_time_vdm_wait_mode_entry = 0;
unsigned long pd_phy_ufp_timer_start_time_vdm_wait_mode_exit = 0;

//pd timer start times for dfp
//usb-if docs page 271
unsigned long pd_phy_dfp_timer_start_time_ac_temp_update = 0;
unsigned long pd_phy_dfp_timer_start_time_bist_cont_mode = 0;
unsigned long pd_phy_dfp_timer_start_time_shared_test_mode = 0;
unsigned long pd_phy_dfp_timer_start_time_cable_message = 0;
unsigned long pd_phy_dfp_timer_start_time_chunking_not_supported = 0;
unsigned long pd_phy_dfp_timer_start_time_chunk_recevier_request = 0;
unsigned long pd_phy_dfp_timer_start_time_chunk_recevier_response = 0;
unsigned long pd_phy_dfp_timer_start_time_chunk_sender_request = 0;
unsigned long pd_phy_dfp_timer_start_time_chunk_sender_response = 0;
unsigned long pd_phy_dfp_timer_start_time_data_reset = 0;
unsigned long pd_phy_dfp_timer_start_time_data_reset_fail = 0;
unsigned long pd_phy_dfp_timer_start_time_data_reset_fail_ufp = 0;
unsigned long pd_phy_dfp_timer_start_time_discover_identity = 0;
unsigned long pd_phy_dfp_timer_start_time_dr_swap_hard_reset = 0;
unsigned long pd_phy_dfp_timer_start_time_dr_swap_wait = 0;
unsigned long pd_phy_dfp_timer_start_time_enter_usb = 0;
unsigned long pd_phy_dfp_timer_start_time_enter_usb_wait = 0;
unsigned long pd_phy_dfp_timer_start_time_enter_epr = 0;
unsigned long pd_phy_dfp_timer_start_time_epr_soruce_cable_discovvery = 0;
unsigned long pd_phy_dfp_timer_start_time_fisrt_source_cap = 0;
unsigned long pd_phy_dfp_timer_start_time_fr_swap_5v = 0;
unsigned long pd_phy_dfp_timer_start_time_fr_swap_complete = 0;
unsigned long pd_phy_dfp_timer_start_time_fr_swap_init = 0;
unsigned long pd_phy_dfp_timer_start_time_hard_reset = 0;
unsigned long pd_phy_dfp_timer_start_time_hard_reset_complete = 0;
unsigned long pd_phy_dfp_timer_start_time_source_epr_keep_alive = 0;
unsigned long pd_phy_dfp_timer_start_time_sink_epr_keep_alive = 0;
unsigned long pd_phy_dfp_timer_start_time_no_responce = 0;
unsigned long pd_phy_dfp_timer_start_time_pps_request = 0;
unsigned long pd_phy_dfp_timer_start_time_pps_timeout = 0;
unsigned long pd_phy_dfp_timer_start_time_prot_err_hard_reset = 0;
unsigned long pd_phy_dfp_timer_start_time_prot_err_soft_reset = 0;
unsigned long pd_phy_dfp_timer_start_time_pr_swap_wait = 0;
unsigned long pd_phy_dfp_timer_start_time_ps_hard_reset = 0;
unsigned long pd_phy_dfp_timer_start_time_spr_ps_source_off = 0;
unsigned long pd_phy_dfp_timer_start_time_epr_ps_source_off = 0;
unsigned long pd_phy_dfp_timer_start_time_ps_source_on = 0;
unsigned long pd_phy_dfp_timer_start_time_spr_ps_transition = 0;
unsigned long pd_phy_dfp_timer_start_time_epr_ps_transition = 0;
unsigned long pd_phy_dfp_timer_start_time_receive = 0;
unsigned long pd_phy_dfp_timer_start_time_receive_responce = 0;
unsigned long pd_phy_dfp_timer_start_time_retry = 0;
unsigned long pd_phy_dfp_timer_start_time_sender_responce = 0;
unsigned long pd_phy_dfp_timer_start_time_sink_delay = 0;
unsigned long pd_phy_dfp_timer_start_time_sink_tx = 0;
unsigned long pd_phy_dfp_timer_start_time_soft_reset = 0;
unsigned long pd_phy_dfp_timer_start_time_scr_holds_bus = 0;
unsigned long pd_phy_dfp_timer_start_time_swap_sink_ready = 0;
unsigned long pd_phy_dfp_timer_start_time_swap_source_start = 0;
unsigned long pd_phy_dfp_timer_start_time_transmit = 0;
unsigned long pd_phy_dfp_timer_start_time_type_c_send_source_cap = 0;
unsigned long pd_phy_dfp_timer_start_time_type_c_sink_wait_cap = 0;
unsigned long pd_phy_dfp_timer_start_time_vconn_source_discharge = 0;
unsigned long pd_phy_dfp_timer_start_time_vconn_source_off = 0;
unsigned long pd_phy_dfp_timer_start_time_vconn_source_on = 0;
unsigned long pd_phy_dfp_timer_start_time_vconn_source_timeout = 0;
unsigned long pd_phy_dfp_timer_start_time_vconn_swap_wait = 0;
unsigned long pd_phy_dfp_timer_start_time_vdm_busy = 0;
unsigned long pd_phy_dfp_timer_start_time_vdm_enter_mode = 0;
unsigned long pd_phy_dfp_timer_start_time_vdm_exit_mode = 0;
unsigned long pd_phy_dfp_timer_start_time_vdm_receiver_responce = 0;
unsigned long pd_phy_dfp_timer_start_time_vdm_sender_responce = 0;
unsigned long pd_phy_dfp_timer_start_time_vdm_wait_mode_entry = 0;
unsigned long pd_phy_dfp_timer_start_time_vdm_wait_mode_exit = 0;




#endif // dp_phy_cpp