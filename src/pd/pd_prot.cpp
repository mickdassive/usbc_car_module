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
#include "gmp.h"
#include "pd_prot.h"
#include "pd_phy.h"

//typedef ans setup for 2048 bit numbers
typedef mpz_t uint2048_t;

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
uint8_t pd_prot_ufp_last_message[255];
int pd_prot_ufp_last_message_length = 0;
uint8_t pd_prot_dfp_last_message[255];
int pd_prot_dfp_last_message_length = 0;

//selcted port power (in watts)
extern enum pd_prot_power_cap_enum pd_prot_ufp_current_power_cap = watts_100;
extern enum pd_prot_power_cap_enum pd_prot_dfp_current_power_cap = watts_100;

//split message to be transmitted info
extern uint8_t pd_prot_split_bytes[255];
extern int pd_prot_split_bytes_length = 0;


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

//pd_prot_split_mesage
//splits a fully biult message (in GMP base 10 char encodeing) in to its individual bytes and stores them in the acompanying vars
//sets contents of both
//pd_prot_split_bytes_length
//pd_prot_split_bytes
void pd_prot_split_message(char* incoming_message) {
    //init local vars
    uint2048_t message;
    mpz_init2(message, 2048);
    size_t length_of_message = 0;
    uint8_t reverse_array[255];

    //covert string back to uint2048_t
    mpz_set_str(message, incoming_message, 10);

    //reset split message buffer
    for (int i; i < 255; ++i) {
        pd_prot_split_bytes[i] = 0;
    }

    //reset legth of split message var
    pd_prot_split_bytes_length = 0;

    //determine the length of the message 
    length_of_message = mpz_sizeinbase(message, 255);

    //set leght of split message var
    pd_prot_split_bytes_length = length_of_message;

    //itterate thru the message and add to reversed split message array
    for (int i; i < length_of_message; ++i) {
        //save the least singnifgant message byte to array
        reverse_array[i] = mpz_get_ui(message) & 0xFF;

        //shift message to the next byte
        mpz_tdiv_q_2exp(message, message, 8);
    }

    //reverse the array and return it
    for (int i; i < length_of_message; ++i) {
        pd_prot_split_bytes[i] = reverse_array[length_of_message - i - 1];
    }

    mpz_clear(message);

    return;

}

//pd_prot_set_last_message
//sets last message vars 
//this function must be called after createing/splitting a message
void pd_prot_set_last_message(enum ufp_dfp ufp_dfp) {
    if (ufp_dfp == ufp) {
        for (int i; i < 255; ++i) {
            pd_prot_ufp_last_message[i] = pd_prot_split_bytes[i];
        }
        
        pd_prot_ufp_last_message_length = pd_prot_split_bytes_length;
    } else if (ufp_dfp == dfp) {
        for (int i; i < 255; ++i) {
            pd_prot_dfp_last_message[i] = pd_prot_split_bytes[i];
        }
        
        pd_prot_dfp_last_message_length = pd_prot_split_bytes_length;
    }
}

//pd_prot_transmit_soucre_capibilitiys
//transmits source PDOs based on the selcted power cap of the port 
void pd_prot_transmit_soucre_capibilitiys (enum ufp_dfp ufp_dfp) {
    //init local vars
    uint2048_t message;
    mpz_init2(message, 2048);
    mpz_t temp_pdo_0;
    mpz_init(temp_pdo_0);
    mpz_t temp_pdo_1;
    mpz_init(temp_pdo_1);
    mpz_t temp_pdo_2;
    mpz_init(temp_pdo_2);
    mpz_t temp_pdo_3;
    mpz_init(temp_pdo_3);
    mpz_t temp_pdo_4;
    mpz_init(temp_pdo_4);
    char* message_string;
    int current_msg_id = 0;
    int n_pdo = 0;

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

    //conver headder to uint2048_t data type and add it to message
    mpz_set_ui(message, headder);

    //append PDOs to message based on a ports given power cap
    if (ufp_dfp == ufp){
        if (pd_prot_ufp_current_power_cap == watts_100) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v);
            mpz_ior(message, message, temp_pdo_0);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_9v);
            mpz_ior(message, message, temp_pdo_1);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_12v);
            mpz_ior(message, message, temp_pdo_2);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_15v);
            mpz_ior(message, message, temp_pdo_3);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_20v);
            mpz_ior(message, message, temp_pdo_4);

        } else if (pd_prot_ufp_current_power_cap == watts_65) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v);
            mpz_ior(message, message, temp_pdo_0);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_9v);
            mpz_ior(message, message, temp_pdo_1);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_12v);
            mpz_ior(message, message, temp_pdo_2);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_15v_at_65);
            mpz_ior(message, message, temp_pdo_3);

        } else if (pd_prot_ufp_current_power_cap == watts_40) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v);
            mpz_ior(message, message, temp_pdo_0);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_9v);
            mpz_ior(message, message, temp_pdo_1);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_12v_at_40);
            mpz_ior(message, message, temp_pdo_2);

        } else if (pd_prot_ufp_current_power_cap == watts_20) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v_at_20);
            mpz_ior(message, message, temp_pdo_0);

        } else if (pd_prot_ufp_current_power_cap == watts_10) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v_at_10);
            mpz_ior(message, message, temp_pdo_0);
        }
    } else if (ufp_dfp == dfp){
        if (pd_prot_dfp_current_power_cap == watts_100) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v);
            mpz_ior(message, message, temp_pdo_0);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_9v);
            mpz_ior(message, message, temp_pdo_1);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_12v);
            mpz_ior(message, message, temp_pdo_2);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_15v);
            mpz_ior(message, message, temp_pdo_3);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_20v);
            mpz_ior(message, message, temp_pdo_4);

        } else if (pd_prot_dfp_current_power_cap == watts_65) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v);
            mpz_ior(message, message, temp_pdo_0);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_9v);
            mpz_ior(message, message, temp_pdo_1);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_12v);
            mpz_ior(message, message, temp_pdo_2);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_15v_at_65);
            mpz_ior(message, message, temp_pdo_3);
        } else if (pd_prot_dfp_current_power_cap == watts_40) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v);
            mpz_ior(message, message, temp_pdo_0);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_9v);
            mpz_ior(message, message, temp_pdo_1);

            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_12v_at_40);
            mpz_ior(message, message, temp_pdo_2);

        } else if (pd_prot_dfp_current_power_cap == watts_20) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v_at_20);
            mpz_ior(message, message, temp_pdo_0);

        } else if (pd_prot_dfp_current_power_cap == watts_10) {
            mpz_mul_2exp(message, message, 32);
            mpz_set_ui(temp_pdo_0, pd_prot_pdo_vsafe_5v_at_10);
            mpz_ior(message, message, temp_pdo_0);

        }
    }
    
    //conver message to string
    message_string = mpz_get_str(NULL, 10, message);

    //clear gmp vars
    mpz_clear(message);
    mpz_clear(temp_pdo_0);
    mpz_clear(temp_pdo_1);
    mpz_clear(temp_pdo_2);
    mpz_clear(temp_pdo_3);
    mpz_clear(temp_pdo_4);

    //send message to splitter
    pd_prot_split_message(message_string);

    //set last message vars for given port
    pd_prot_set_last_message(ufp_dfp);

    //tell pd phy to transmit the message 
    pd_phy_transmit(ufp_dfp, pd_prot_split_bytes, pd_prot_split_bytes_length);

    return;
}

void pd_prot_transmit_soft_reset (ufp_dfp ufp_dfp) {
    //init local vars
    mpz_t message;
    mpz_init2(message, 16);
    char* message_string;
    

    //biuld headder  
    uint16_t headder = pd_prot_biuld_headder(false, 0, 0, src, 3, ufp_dfp, pd_prot_cont_msg_soft_reset);

    //convert headder to mpz
    mpz_set_ui(message, headder);

    //convert message to string
    message_string = mpz_get_str(NULL, 10, message);

    //clean up mpz vars
    mpz_clear(message);

    //split the message
    pd_prot_split_message(message_string);

    //set last message vars for a given port
    pd_prot_set_last_message(ufp_dfp);

    //transmit the message
    pd_phy_transmit(ufp_dfp, pd_prot_split_bytes, pd_prot_split_bytes_length);
    
    return;

}









#endif // pd_prot_cpp