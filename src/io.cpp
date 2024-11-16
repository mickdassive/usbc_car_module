//{usbc car module}
//{io.cpp}
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

#ifndef io_cpp
#define io_cpp

#include <Arduino.h>
#include <Wire.h>
#include "io.h"
#include "adc.h"
#include "pd/pd_power_cont.h"
#include "pd/pd_phy.h"
#include "pd/pd_prot.h"

//iox interrupt register values
uint8_t iox_0_port_0_interrupt = 0xFF;
uint8_t iox_0_port_1_interrupt = 0xFF;
uint8_t iox_1_port_0_interrupt = 0xFF;
uint8_t iox_1_port_1_interrupt = 0xFF;
uint8_t io_interrupt_counter = 0;

//button info defines
bool io_unit_btn_pressed = false;
unsigned long io_unit_btn_pressed_time = 0;
bool io_mode_btn_pressed = false;
unsigned long io_mode_btn_pressed_time = 0;
bool io_src_btn_pressed = false;
unsigned long io_src_btn_pressed_time = 0;

//message received interrupt flags
bool io_interrupt_ufp_msg_received = false;
bool io_interrupt_dfp_msg_received = false;

/**
 * Reads the current input/output state from the specified port and IOX number.
 *
 * @param port The port number (0 or 1) to read from.
 * @param iox_num The IOX number (0 or 1) to read from.
 * @return The current IO state as a uint8_t value.
 */
uint8_t io_read_current_io_state(int port, int iox_num) {

  debug_msg(partal_io, "io_read_current_io_state called, reading current IO state of given io expander", false, 0);

  uint8_t iox_address = (iox_num == 0) ? iox_0_add : iox_1_add;
  uint8_t iox_input_port_register = (port == 0) ? iox_input_port_0 : iox_input_port_1;

  Wire.beginTransmission(iox_address);
  Wire.write(iox_input_port_register);
  Wire.endTransmission();

  Wire.requestFrom(iox_address, 1);
  return Wire.read();
}

/**
 * @brief Performs read or write operations on a pin.
 * 
 * This function allows you to read or write to a pin, either onboard or offboard.
 * 
 * @param pin_needed The pin structure containing information about the pin to be operated on.
 * @param read_write Specifies whether to perform a read or write operation.
 * @param high_low Specifies whether to set the pin high or low (applicable for write operations).
 * @return If performing a read operation, returns the value read from the pin. If performing a write operation, returns 0.
 */
int io_call(struct pin pin_needed, enum read_write read_write, enum high_low high_low) {

  debug_msg(partal_io, "io_call called, making pin call", false, 0);

  if (pin_needed.onboard) {
    if (read_write == write) {
      if (high_low == high) {
        digitalWrite(pin_needed.pin_number, HIGH);

      } else if (high_low == low) {
        digitalWrite(pin_needed.pin_number, LOW);
        
      } else {
        // Error handling for invalid high_low value

      }
    } else if (read_write == read) {
      int read_value = digitalRead(pin_needed.pin_number);
      return read_value;

    } else {
      // Error handling for invalid read_write value

    }

  } else {
    if (read_write == write) {
      uint8_t current = io_read_current_io_state(pin_needed.port, pin_needed.iox_number);
      uint8_t output = 0b00000000;
      uint8_t mask_not = ~pin_needed.mask;

      if (high_low == high) {
        output = current | pin_needed.mask;

      } else if (high_low == low) {
        output = current & mask_not;

      } else {
        // Error handling for invalid high_low value

      }

      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);

      } else {
        Wire.beginTransmission(iox_1_add);

      }

      if (pin_needed.port == 0) {
        Wire.write(iox_output_port_0);

      } else {
        Wire.write(iox_output_port_1);

      }

      Wire.write(output);
      Wire.endTransmission();

    } else if (read_write == read) {

      uint8_t readval = 0;
      uint8_t output_byte = 0;

      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);

      } else {
        Wire.beginTransmission(iox_1_add);

      }

      if (pin_needed.port == 0) {
        Wire.write(iox_input_port_0);

      } else if (pin_needed.port == 1) {
        Wire.write(iox_input_port_1);

      }

      Wire.endTransmission();
      
      if (pin_needed.iox_number == 0) {
        Wire.requestFrom(iox_0_add, 1);

      } else {
        Wire.requestFrom(iox_1_add, 1);

      }

      readval = Wire.read();
      output_byte = readval & pin_needed.mask;

      if (output_byte == 0) {
        return LOW;

      } else {
        return HIGH;

      }
    }
  }
  return 0;
}

/**
 * @brief Initializes the GPIO pins for input/output and sets up interrupt masks for IO expanders.
 * 
 * This function initializes the GPIO pins based on the pin mode specified for each pin. It sets the pin mode for each pin,
 * configures interrupt masks for IO expanders, and sets all outputs of IO expanders to low.
 * 
 */
void io_gpio_init() {

  debug_msg(partal_io, "io_gpio_init called, setting up pins", false, 0);

  //init vars
  uint8_t iox_0_port_0_pinmode = 0x00;
  uint8_t iox_0_port_1_pinmode = 0x00;
  uint8_t iox_1_port_0_pinmode = 0x00;
  uint8_t iox_1_port_1_pinmode = 0x00;

  //begin iterating through pins
  for (size_t i = 1; i < sizeof(pin_names[0]); i++) {

    switch (pin_names[i]->pin_mode) {
    default:
      // Error handling for unexpected pin_mode value
      debug_msg(partal_io, "Unexpected pin_mode value", false, 0);
      break;
    case in:
      if (pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, INPUT);

      }
      //no need to do anything to the iox, all pins default to input
      break;
    
    case out:
      if (pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, OUTPUT);

      } else {
        if (pin_names[i]->iox_number == 0) {
          if (pin_names[i]->port == 0) {
            iox_0_port_0_pinmode |= pin_names[i]->mask;

          } else {
            iox_0_port_1_pinmode |= pin_names[i]->mask;

          }
        } else {
          if (pin_names[i]->port == 0) {
            iox_1_port_0_pinmode |= pin_names[i]->mask;

          } else {
            iox_1_port_1_pinmode |= pin_names[i]->mask;

          }
        }
      }
      
      break;

    case bi_dir:
      //do nothing, only used for i2c coms which are defined elsewhere 
      break;
    
    case intr: //setup interrupts for checking when io state is changed
      if(pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, INPUT);
        attachInterrupt(digitalPinToInterrupt(pin_names[i]->pin_number), io_pin_interrupt_flagger, RISING);

      } else {
        if (pin_names[i]->iox_number == 0) { //setup intupt registers for external pins
          if (pin_names[i]->port == 0) {
            iox_0_port_0_interrupt |= ~pin_names[i]->mask;

          } else {
            iox_0_port_1_interrupt |= pin_names[i]->mask;

          }
        } else {
          if (pin_names[i]->port == 0) {
            iox_1_port_0_interrupt |= pin_names[i]->mask;

          } else {
            iox_1_port_1_interrupt |= pin_names[i]->mask;

          }
        }
      }  
      break;
    case empty_pin:
      //do nothing
      break;
    }  
  }

  //set all outputs of ioxs low
  //write to output at iox 0 port 0
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_output_port_0);
  Wire.write(0x00);
  Wire.endTransmission();

  //write to output at iox 0 port 1
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_output_port_1);
  Wire.write(0x00);
  Wire.endTransmission();

  //write to output at iox 1 port 0
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_output_port_0);
  Wire.write(0x00);
  Wire.endTransmission();

  //write to output at iox 1 port 1
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_output_port_1);
  Wire.write(0x00);
  Wire.endTransmission();


  //begin writing pinmodes to ioxs 
  //write pinmode to iox 0 port 0 
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_config_port_0);
  Wire.write(iox_0_port_0_pinmode);
  Wire.endTransmission();

  //write pinmode to iox 0 port 1 
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_config_port_1);
  Wire.write(iox_0_port_1_pinmode);
  Wire.endTransmission();

  //write pinmode to iox 1 port 0 
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_config_port_0);
  Wire.write(iox_1_port_0_pinmode);
  Wire.endTransmission();

  //write pinmode to iox 1 port 1 
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_config_port_1);
  Wire.write(iox_1_port_1_pinmode);
  Wire.endTransmission();


  //write to ioxs interrupt mask registers
  //write mask to iox 0 port 0
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(iox_0_port_0_interrupt);
  Wire.endTransmission();

  //write mask to iox 0 port 1
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_mask_register_1);
  Wire.write(iox_0_port_1_interrupt);
  Wire.endTransmission();

  //write mask to iox 1 port 0
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(iox_1_port_0_interrupt);
  Wire.endTransmission();

  //write mask to iox 1 port 1
  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_int_mask_register_1);
  Wire.write(iox_1_port_1_interrupt);
  Wire.endTransmission();

  debug_msg(partal_io, "pins have been initialized", false, 0);

  return;
};

/**
 * @brief Configures the IO expanders for interrupt handling.
 * 
 * This function configures the IO expanders for interrupt handling by setting the interrupt mask registers
 * and enabling the desired interrupt pins.
 * 
 */
void io_de_assert_iox_int () {

  debug_msg(partal_io, "io_de_assert_iox_int called, reseting and setting interrupt masks", false, 0);
  
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(0xFF);
  Wire.write(0xFF);
  Wire.endTransmission();

  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(0xFF);
  Wire.write(0xFF);
  Wire.endTransmission();

  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(iox_0_port_0_interrupt);
  Wire.write(iox_0_port_1_interrupt);
  Wire.endTransmission();

  Wire.beginTransmission(iox_1_add);
  Wire.write(iox_int_mask_register_0);
  Wire.write(iox_1_port_0_interrupt);
  Wire.write(iox_1_port_1_interrupt);
  Wire.endTransmission();
}

/**
 * Determines the interrupt source based on the values read from the interrupt registers of IOX 0 and IOX 1.
 * 
 * @return The pin struct representing the interrupt source. If no interrupt source is detected, an empty struct is returned.
 */
struct pin io_determine_interrupt_source() {

  debug_msg(partal_io, "io_determine_interrupt_source called", false, 0);
  struct pin* intrupt_spurce_to_return = &empty_struct_pin;

  //init local vars
  uint8_t iox_0_int_reg_0_value = 0;
  uint8_t iox_0_int_reg_1_value = 0;
  uint8_t iox_1_int_reg_0_value = 0;
  uint8_t iox_1_int_reg_1_value = 0;

  //read interrupt register values from iox 0  
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_stat_register_0);
  Wire.endTransmission();

  Wire.requestFrom(iox_0_add, 2);
  iox_0_int_reg_0_value = Wire.read();
  iox_0_int_reg_1_value = Wire.read();
  Wire.endTransmission();

  //begin iterateing thru the possable pins
  for (size_t i = 1; i < sizeof(pin_names[0]); i++) {

    //check if the current pin is an itrupt pin
    if (pin_names[i]->pin_mode == intr) {

      //check witch io expeander the pin is on 
      if (pin_names[i]->iox_number == 0){

        //check what port the pin is on
        if (pin_names[i]->port == 0) {

          //chek if pin is the intrupt souce
          if ((pin_names[i]->mask & iox_0_int_reg_0_value) != 0) {
            //store current pin
            intrupt_spurce_to_return = pin_names[i];

          }
        }

        //check if current pin is on port 1
        else if (pin_names[i]->port == 1) {

          //chek if pin is the intrupt souce
          if ((pin_names[i]->mask & iox_0_int_reg_1_value) != 0) {
            //store current pin
            intrupt_spurce_to_return = pin_names[i];

            // store pin for the case that thare is more than one intrupt soucre
            iox_0_int_reg_1_value = (pin_names[i]->mask  ^ iox_0_int_reg_1_value);
          }
        }
      }
      else if (pin_names[i]->iox_number == 1){

        //check if current pin is on port 0
        if (pin_names[i]->port == 0) {

          //chek if pin is the intrupt souce
          if ((pin_names[i]->mask & iox_1_int_reg_0_value) != 0) {
            //store current pin
            intrupt_spurce_to_return = pin_names[i];

            // store pin for the case that thare is more than one intrupt soucre
            iox_1_int_reg_0_value = (pin_names[i]->mask  ^ iox_1_int_reg_0_value);
          }
        }

        //check if current pin is on port 1
        else if (pin_names[i]->port == 1) {

          //chek if pin is the intrupt souce
          if ((pin_names[i]->mask & iox_1_int_reg_1_value) != 0) {
            //store current pin
            intrupt_spurce_to_return = pin_names[i];

            // store pin for the case that thare is more than one intrupt soucre
            iox_1_int_reg_1_value = (pin_names[i]->mask  ^ iox_1_int_reg_1_value);
          }
        }
      }
    }
  }

  if (iox_0_int_reg_0_value + iox_0_int_reg_1_value + iox_1_int_reg_0_value + iox_1_int_reg_1_value != 0) {
    //reset irupt flag if thare are no more wating intrupts
  }


  /*

  //check if interrupt came from other iox
  if ((iox_0_int_reg_0_value & iox_1_int.mask) != 0) {
    //read interrupt register values from iox 1
    Wire.beginTransmission(iox_1_add);
    Wire.write(iox_int_stat_register_0);
    Wire.endTransmission();

    Wire.requestFrom(iox_1_add, 2);
    iox_1_int_reg_0_value = Wire.read();
    iox_1_int_reg_1_value = Wire.read();
    Wire.endTransmission();

    //determine if interrupt came from adc or f/b pgood
    if ((iox_1_int_reg_1_value & adc_alert.mask) != 0) {
      return adc_alert;
    } else if ((iox_1_int_reg_0_value & f_usbc_pgood.mask) != 0) {
      return f_usbc_pgood;
    } else if ((iox_1_int_reg_0_value & b_usbc_pgood.mask) != 0) {
      return b_usbc_pgood;
    }
  }

  //determine if interrupt came from source btn, unit btn, mode btn, display, or ufp/dfp pd phy alert
  if ((iox_0_int_reg_1_value & src_btn.mask) != 0) {
    return src_btn;
  } else if ((iox_0_int_reg_1_value & unit_btn.mask) != 0) {
    return unit_btn;
  } else if ((iox_0_int_reg_1_value & mode_btn.mask) != 0) {
    return mode_btn;
  } else if ((iox_0_int_reg_1_value & disp_irq.mask) != 0) {
    return disp_irq;
  } else if ((iox_0_int_reg_1_value & ufp_alert_n.mask) != 0) {
    return ufp_alert_n;
  } else if ((iox_0_int_reg_1_value & dfp_alert_n.mask) != 0) {
    return dfp_alert_n;
  }

  return empty_struct_pin;

  */
};


/**
 * @brief Sets the interrupt flag.
 * 
 * This function sets the interrupt flag `io_interrupt_flag` to true.
 */
void ICACHE_RAM_ATTR io_pin_interrupt_flagger () {
  debug_msg(partal_io, "interrupt flag set", false, 0);
  incr
  return;
}

/**
 * @brief Handles the interrupt events for IO operations.
 * 
 * This function is responsible for handling various interrupt events related to IO operations.
 * It determines the interrupt source and performs the corresponding actions based on the source.
 * The function also prints debug messages to the Serial monitor for each interrupt event.
 * 
 */
void io_intrupt_handeler () {

  io_interrupt_flag = false;

  //prefetch inturupt values
  char interrupt_source = io_determine_interrupt_source().pin_ident;
  
  if (interrupt_source == 'x') { //adc alert

    //prefetch data
    enum adc_channel adc_alert_source = adc_determine_alert_source();

    debug_msg(partal_io, "ADC alert intrupt recived", false, 0);
    //determine channel that flagged the alert 
    if (adc_alert_source == ch0) {
      //21V csp do nothing
      debug_msg(partal_io, "recived ADC 21V intrupt", false, 0);
    } else if (adc_alert_source == ch1) {
      //21V csn do nothing 
      debug_msg(partal_io, "recived ADC 21V csn intrupt", false, 0);     
    } else if (adc_alert_source == ch2) {
      //5V csp do nothing
      debug_msg(partal_io, "recived ADC 5V intrupt", false, 0);
    } else if (adc_alert_source == ch3) {
      //5V csn do nothing
      debug_msg(partal_io, "recived adc 5V csn intrupt", false, 0);
    } else if (adc_alert_source == ch4) {
      //ufp csp
      debug_msg(partal_io, "recived UFP csp intrupt", false, 0);
      //turn off power to port if out of range
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)){
        //do nothing if pgood
        debug_msg(partal_power_cont, "UFP csp intupt recived but voltage is good", false, 0);
      } else {
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
        debug_msg(partal_power_cont, "UFP csp intrupt recived voltage out of range turning off output", false, 0);
      }
    } else if (adc_alert_source == ch5) {
      //ufp csn
      debug_msg(partal_io, "recived UFP csn intrupt", false, 0);
      //turn off power to port if out of range
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)){
        //do nothing if pgood    
        debug_msg(partal_power_cont, "recived UFP csn intrupt but voltage is good", false, 0);    
      } else {
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
        debug_msg(partal_power_cont, "UFP csn intrupt recived voltage out of range turning off output", false, 0);
      }
    } else if (adc_alert_source == ch6) {
      //dfp csp
      debug_msg(partal_io, "recived DFP csp intrupt", false, 0);
      //turn off port power if out of range 
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)) {
        //do nothing if power good
        debug_msg(partal_power_cont, "recived DFP intrupt but voltage is good", false, 0);
      } else {
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
        debug_msg(partal_power_cont, "DFP csp intrupt recived voltage out of range turning off output", false, 0);
      }
    } else if (adc_alert_source == ch7) {
      //dfp csn
      debug_msg(partal_io, "recived DFP csn intrupt", false, 0);
      //turn port power off if out of range
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)){
        //do nnothing if power good 
        debug_msg(partal_power_cont, "recived DFP csn intrupt but voltage is good", false, 0);
      } else {
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
        debug_msg(partal_power_cont, "DFP csn intrup recived voltage out of range turning off output", false, 0);
      }
    }

    //clear adc alert
    adc_clear_event_flags();
    debug_msg(partal_adc, "adc event register cleard", false, 0);

  } else if (interrupt_source == 'q') { //f usbc pgood
    // read pin to see if high or low
    debug_msg(partal_io, "UFP psu pgood intrupt recived", false, 0);
    if (io_call(f_usbc_pgood, read, read_mode) == 1) {
      //set allow output to  true
      pd_power_cont_dfp_allow_output = true;
      debug_msg(partal_power_cont, "UFP psu pgood true allowing output", false, 0);
    } else if (io_call(f_usbc_pgood, read, read_mode) == 0){
      //set allow output to false 
      pd_power_cont_dfp_allow_output = false;
      debug_msg(partal_power_cont, "UFP psu pgood false stopping output", false, 0);
    }
  } else if (interrupt_source == 'j') { //b usbc pgood
    // read pin to see if high or low
    debug_msg(partal_io, "DFP psu pgood intrupt recived", false, 0);
    if (io_call(b_usbc_pgood, read, read_mode) == 1) {
      //set allow output to  true
      pd_power_cont_ufp_allow_output = true;
      debug_msg(partal_power_cont, "DFP psu pgood true allowing output", false, 0);
    } else if (io_call(b_usbc_pgood, read, read_mode)){
      //set allow output to false 
      pd_power_cont_ufp_allow_output = false;
      debug_msg(partal_power_cont, "DFP psu pgood false stopping output", false, 0);
    }
  } else if (interrupt_source == '4') { //source buttion
    io_src_btn_pressed = true;
    debug_msg(partal_io, "recived source buttion intrupt", false, 0);
  } else if (interrupt_source == '3') { //unit buttion
    io_unit_btn_pressed = true;
    debug_msg(partal_io, "recived unit buttion intrupt", false, 0);
  } else if (interrupt_source == '5') { //mode buttion
    io_mode_btn_pressed = true;
    debug_msg(partal_io, "recived mode buttion intrupt", false, 0);
  } else if (interrupt_source == '2') { //display itrupt
    //do nothing, not used 
    debug_msg(partal_io, "recived display intrupt", false, 0);
  } else if (interrupt_source == '0') { //ufp alert n
    debug_msg(partal_io, "recived UFP pd PHY intrupt", false, 0);

    //determine alert type

    //prefetch data
    enum pd_phy_alert_type ufp_phy_interupt_source = pd_phy_alert_type(ufp);

    if (ufp_phy_interupt_source == vendor_defined_extended) {
      // do nothing
      debug_msg(partal_pd_phy, "recived UFP pd PHY vendor defined extended intrupt", false, 0);
    } else if (ufp_phy_interupt_source == extended_status_changed) {
      // do nothing
      debug_msg(partal_pd_phy, "recived UFP pd PHY extended status changed intrupt", false, 0);
    } else if (ufp_phy_interupt_source == beginning_sop_message_status) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY beginning sop message status intrupt, beginning reading messgae", false, 0);
      pd_phy_receive_message(ufp);
    } else if (ufp_phy_interupt_source == vbus_sink_disconnect_detected) {
      //do nothing?
      debug_msg(partal_pd_phy, "recived UFP pd PHY vbus sink disconnect detected intrupt", false, 0);
    } else if (ufp_phy_interupt_source == rx_buffer_overflow) {
      //reset recive buffer
      debug_msg(partal_pd_phy, "recived UFP pd PHY rx buffer overflow intrupt, reseting buffer", false, 0);
      pd_phy_send_reset_receive_buffer(ufp);
    } else if (ufp_phy_interupt_source == vbus_voltage_low) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY vbus voltage low intrupt", false, 0);
      //see if power is actuly bad
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)) {
        //do nothing
        debug_msg(partal_power_cont, "recived UFP pd PHY vbus voltage low intrupt but voltage is good", false, 0);
      } else {
        //turn port power off
        debug_msg(partal_power_cont, "recived UFP pd PHY vbus voltage low intrupt voltage out of range turning off output", false, 0);
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
      }
    } else if (ufp_phy_interupt_source == vbus_voltage_high) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY vbus voltage high intrupt", false, 0);
      //see if power is actuly bad
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)) {
        //do nothing
        debug_msg(partal_power_cont, "recived UFP pd PHY vbus voltage high intrupt but voltage is good", false, 0);
      } else {
        //turn port power off
        debug_msg(partal_power_cont, "recived UFP pd PHY vbus voltage high intrupt voltage out of range turning off output", false, 0);
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
      }
    } else if (ufp_phy_interupt_source == transmit_sop_message_successful) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY transmit sop message successful intrupt", false, 0);
      debug_msg(partal_pd_prot, "recived UFP pd PHY transmit sop message successful intrupt setting good crc flag", false, 0);

      //hit good crc flag
      pd_prot_ufp_last_good_crc = true;
      

    } else if (ufp_phy_interupt_source == transmit_sop_message_discarded) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY transmit sop message discarded intrupt, retansmitting message", false, 0);
      //retransmit message if discarded
      pd_phy_transmit(ufp, pd_prot_ufp_last_message, pd_prot_ufp_last_message_length);

    } else if (ufp_phy_interupt_source == transmit_sop_message_failed) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY transmit sop message failed intrupt", false, 0);
      //retransmit message if retransmit counter hasent reached its threshold
      if (pd_prot_ufp_counter_retry <= pd_prot_counter_th_retry) {
        debug_msg(partal_pd_prot, "recived UFP pd PHY transmit sop message failed intrupt and retry counter below treshold, retransmitting message, current vlaue of counter to follow", true, pd_prot_ufp_counter_retry);
        pd_phy_transmit(ufp, pd_prot_ufp_last_message, pd_prot_ufp_last_message_length);
      } else {
        //set retransmit failled flag
        debug_msg(partal_pd_prot, "recived UFP pd PHY transmit sop message failed intrupt and retry counter above treshold, setting retransmit failled flag, current value of counter to follow", true, pd_prot_ufp_counter_retry);
        pd_prot_ufp_retransit_failled = true;
      }
      
      //add to retrasnmit counter
      ++pd_prot_ufp_counter_retry;
      debug_msg(partal_pd_prot, "recived UFP pd PHY transmit sop message failed intrupt, adding to retry counter", false, 0);

    } else if (ufp_phy_interupt_source == received_hard_reset) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY received hard reset intrupt", false, 0);
      debug_msg(partal_pd_prot, "recived UFP pd PHY received hard reset intrupt, calling hard reset handeler", false, 0);
      pd_prot_hard_reset_handeler(ufp, false);
    } else if (ufp_phy_interupt_source == received_sop_message_status) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY received sop message status intrupt", false, 0);
      debug_msg(partal_pd_prot, "recived UFP pd PHY received sop message status intrupt, setting messgae received flag and reading message contents into buffer", false, 0);
      //set message received flag and read message contents
      io_interrupt_ufp_msg_received = true;
      pd_phy_receive_message(ufp);

    } else if (ufp_phy_interupt_source == port_power_status_changed) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY port power status changed intrupt", false, 0);
      // do nothing?
    } else if (ufp_phy_interupt_source == cc_status_alert) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY cc status alert intrupt", false, 0);
      // determine if port is in attached or detached state 
      if (pd_phy_ufp_attached) {
        debug_msg(partal_pd_phy, "recived UFP pd PHY cc status alert intrupt, starting detach sequence", false, 0);
        //complete detach sequence
        pd_phy_complete_detach(ufp);
      } else {
        debug_msg(partal_pd_phy, "recived UFP pd PHY cc status alert intrupt, starting attach sequence", false, 0);
        // complete attach
        pd_phy_complete_attach(ufp);
      }
    } else if (ufp_phy_interupt_source == extended_timer_expired) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY extended timer expired intrupt", false, 0);
      // do nothing
    } else if (ufp_phy_interupt_source == extended_source_frs) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY extended source frs intrupt", false, 0);
      // do nothing
    } else if (ufp_phy_interupt_source == extended_sink_frs) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY extended sink frs intrupt", false, 0);
      // do nothing
    } else if (ufp_phy_interupt_source == force_discharge_failed) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY force discharge failed intrupt", false, 0);
      debug_msg(partal_power_cont, "recived UFP pd PHY force discharge failed intrupt, turning off power", false, 0);
      // turn port power supply off
      pd_power_cont_return_to_base_state(ufp);
    } else if (ufp_phy_interupt_source == auto_discharge_failed) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY auto discharge failed intrupt", false, 0);
      // do nothing for now
    } else if (ufp_phy_interupt_source == internal_or_external_vbus_over_current_protection_fault) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY internal or external vbus over current protection fault intrupt", false, 0);
      debug_msg(partal_power_cont, "recived UFP pd PHY internal or external vbus over current protection fault intrupt, turning off and reseting power", false, 0);
      // turn of power and stop allowing output 
      pd_power_cont_return_to_base_state(ufp);
      pd_power_cont_ufp_allow_output = false;
    } else if (ufp_phy_interupt_source == internal_or_external_vbus_over_voltage_protection_fault) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY internal or external vbus over voltage protection fault intrupt", false, 0);
      debug_msg(partal_power_cont, "recived UFP pd PHY internal or external vbus over voltage protection fault intrupt, turning off and reseting power", false, 0);
      //turn off power and stop allowing output
      pd_power_cont_return_to_base_state(ufp);
      pd_power_cont_ufp_allow_output = false;
    } else if (ufp_phy_interupt_source == i2c_error) {
      debug_msg(partal_pd_phy, "recived UFP pd PHY i2c error intrupt, flushing buffers", false, 0);
      //reset rx & tx buffers
      pd_phy_send_reset_receive_buffer(ufp);
      pd_phy_send_reset_transmit_buffer(ufp);
    }

    debug_msg(partal_pd_phy, "clearing UFP pd PHY alert flags", false, 0);

    pd_phy_clear_alert(ufp);
    pd_phy_clear_fault(ufp);
    pd_phy_clear_extended_alert(ufp);

  } else if (interrupt_source == '?') { //dfp alert n

    //prefetch data
    enum pd_phy_alert_type dfp_phy_interupt_source = pd_phy_alert_type(dfp);

    debug_msg(partal_io, "recived DFP pd PHY intrupt", false, 0);
    if (dfp_phy_interupt_source == vendor_defined_extended) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY vendor defined extended intrupt", false, 0);
      // do nothing
    } else if (dfp_phy_interupt_source == extended_status_changed) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY extended status changed intrupt", false, 0);
      // do nothing
    } else if (dfp_phy_interupt_source == beginning_sop_message_status) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY beginning sop message status intrupt, beginning reading message", false, 0);
      pd_phy_receive_message(dfp);
      
    } else if (dfp_phy_interupt_source == vbus_sink_disconnect_detected) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY vbus sink disconnect detected intrupt", false, 0);
      //do nothing?
    } else if (dfp_phy_interupt_source == rx_buffer_overflow) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY rx buffer overflow intrupt, flushing buffer", false, 0);
      //reset receive buffer
      pd_phy_send_reset_receive_buffer(dfp);
    } else if (dfp_phy_interupt_source == vbus_voltage_low) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY vbus voltage low intrupt", false, 0);
      //see if power is actuly bad
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)) {
        //do nothing
        debug_msg(partal_power_cont, "recived DFP pd PHY vbus voltage low intrupt but voltage is good", false, 0);
      } else {
        debug_msg(partal_power_cont, "recived DFP pd PHY vbus voltage low intrupt voltage out of range turning off output", false, 0);
        //turn port power off
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
      }
    } else if (dfp_phy_interupt_source == vbus_voltage_high) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY vbus voltage high intrupt", false, 0);
      //see if power is actuly bad
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)) {
        //do nothing
        debug_msg(partal_power_cont, "recived DFP pd PHY vbus voltage high intrupt but voltage is good", false, 0);
      } else {
        debug_msg(partal_power_cont, "recived DFP pd PHY vbus voltage high intrupt voltage out of range turning off output", false, 0);
        //turn port power off
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
      }
    } else if (dfp_phy_interupt_source == transmit_sop_message_successful) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY transmit sop message successful intrupt", false, 0);
      debug_msg(partal_pd_prot, "recived DFP pd PHY transmit sop message successful intrupt setting good crc flag", false, 0);

      //hit good crc flag
      pd_prot_dfp_last_good_crc = true;

    } else if (dfp_phy_interupt_source == transmit_sop_message_discarded) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY transmit sop message discarded intrupt, retransmitting message", false, 0);
      //retransmmit message if discarded
      pd_phy_transmit(dfp, pd_prot_dfp_last_message, pd_prot_dfp_last_message_length);
      
    } else if (dfp_phy_interupt_source == transmit_sop_message_failed) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY transmit sop message failed intrupt", false, 0);
      //retransmit message if retransmit counter hasent reached its threshold
      if (pd_prot_dfp_counter_retry <= pd_prot_counter_th_retry) {
        debug_msg(partal_pd_prot, "recived DFP pd PHY transmit sop message failed intrupt and retry counter below treshold, retransmitting message, counter value to follow", true, pd_prot_dfp_counter_retry);
        pd_phy_transmit(dfp, pd_prot_dfp_last_message, pd_prot_dfp_last_message_length);
      } else {
        debug_msg(partal_pd_prot, "recived DFP pd PHY transmit sop message failed intrupt and retry counter above treshold, setting retransmit failled flag, counter value to follow", true, pd_prot_dfp_counter_retry);
        //set retransmit failled flag
        pd_prot_dfp_retransit_failled = true;
      }
      
      //add to retrasnmit counter
      ++pd_prot_ufp_counter_retry;
      debug_msg(partal_pd_prot, "recived DFP pd PHY transmit sop message failed intrupt, adding to retry counter", false, 0);

    } else if (dfp_phy_interupt_source == received_hard_reset) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY received hard reset intrupt", false, 0);
      debug_msg(partal_pd_prot, "recived DFP pd PHY received hard reset intrupt, calling hard reset handeler", false, 0);
      pd_prot_hard_reset_handeler(dfp, false);
    } else if (dfp_phy_interupt_source == received_sop_message_status) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY received sop message status intrupt", false, 0);
      debug_msg(partal_pd_prot, "recived DFP pd PHY received sop message status intrupt, setting messgae received flag and reading message contents into buffer", false, 0);
      //set message received flag and read message contents
      io_interrupt_dfp_msg_received = true;
      pd_phy_receive_message(dfp);
    } else if (dfp_phy_interupt_source == port_power_status_changed) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY port power status changed intrupt", false, 0);
      // do nothing?
    } else if (dfp_phy_interupt_source == cc_status_alert) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY cc status alert intrupt", false, 0);
      // determine if port is in attched or detached state 
      if (pd_phy_dfp_attached) {
        debug_msg(partal_pd_phy, "recived DFP pd PHY cc status alert intrupt, starting detach sequence", false, 0);
        //complete detach sequence
        pd_phy_complete_detach(dfp);
      } else {
        debug_msg(partal_pd_phy, "recived DFP pd PHY cc status alert intrupt, starting attach sequence", false, 0);
        // complete attach
        pd_phy_complete_attach(dfp);
      }
    } else if (dfp_phy_interupt_source == extended_timer_expired) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY extended timer expired intrupt", false, 0);
      // do nothing
    } else if (dfp_phy_interupt_source == extended_source_frs) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY extended source frs intrupt", false, 0);
      // do nothing
    } else if (dfp_phy_interupt_source == extended_sink_frs) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY extended sink frs intrupt", false, 0);
      // do nothing
    } else if (dfp_phy_interupt_source == force_discharge_failed) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY force discharge failed intrupt", false, 0);
      debug_msg(partal_power_cont, "recived DFP pd PHY force discharge failed intrupt, turning off power", false, 0);
      // turn port power supply off
      pd_power_cont_return_to_base_state(dfp);
    } else if (dfp_phy_interupt_source == auto_discharge_failed) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY auto discharge failed intrupt", false, 0);
      // do nothing for now
    } else if (dfp_phy_interupt_source == internal_or_external_vbus_over_current_protection_fault) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY internal or external vbus over current protection fault intrupt", false, 0);
      debug_msg(partal_power_cont, "recived DFP pd PHY internal or external vbus over current protection fault intrupt, turning off and reseting power", false, 0);
      // turn of power and stop allowing output 
      pd_power_cont_return_to_base_state(dfp);
      pd_power_cont_dfp_allow_output = false;
    } else if (dfp_phy_interupt_source == internal_or_external_vbus_over_voltage_protection_fault) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY internal or external vbus over voltage protection fault intrupt", false, 0);
      debug_msg(partal_power_cont, "recived DFP pd PHY internal or external vbus over voltage protection fault intrupt, turning off and reseting power", false, 0);
      //turn off power and stop allowing output
      pd_power_cont_return_to_base_state(dfp);
      pd_power_cont_dfp_allow_output = false;
    } else if (dfp_phy_interupt_source == i2c_error) {
      debug_msg(partal_pd_phy, "recived DFP pd PHY i2c error intrupt, flushing buffers", false, 0);
      //reset rx & tx buffers
          pd_phy_send_reset_receive_buffer(dfp);
          pd_phy_send_reset_transmit_buffer(dfp);
        }

        debug_msg(partal_pd_phy, "clearing DFP pd PHY alert flags", false, 0);

        pd_phy_clear_alert(dfp);
        pd_phy_clear_fault(dfp);
        pd_phy_clear_extended_alert(dfp);

      }

      debug_msg(partal_io, "deasserting iox interrupts", false, 0);

      //deassert iox_interrupts
      io_de_assert_iox_int();

  return;

}


#endif // io_cpp