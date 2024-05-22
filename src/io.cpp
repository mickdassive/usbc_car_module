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

//iox intrupt register values
uint8_t iox_0_port_0_interrupt = 0xFF;
uint8_t iox_0_port_1_interrupt = 0xFF;
uint8_t iox_1_port_0_interrupt = 0xFF;
uint8_t iox_1_port_1_interrupt = 0xFF;
bool io_interupt_flag = false;

//buttion info defines
bool io_unit_btn_pressed = false;
unsigned long io_unit_btn_pressed_time = 0;
bool io_mode_btn_pressed = false;
unsigned long io_mode_btn_pressed_time = 0;
bool io_src_btn_pressed = false;
unsigned long io_src_btn_pressed_time = 0;

//message recived intrupt flags
bool io_intrupt_ufp_msg_recived = false;
bool io_intrupt_dfp_msg_recived = false;

/**
 * Reads the current input/output state from the specified port and IOX number.
 *
 * @param port The port number (0 or 1) to read from.
 * @param iox_num The IOX number (0 or 1) to read from.
 * @return The current IO state as a uint8_t value.
 */
uint8_t io_read_current_io_state(int port, int iox_num) {
  uint8_t iox_address = (iox_num == 0) ? iox_0_add : iox_1_add;
  uint8_t iox_output_register = (port == 0) ? iox_output_port_0 : iox_output_port_1;

  Wire.beginTransmission(iox_address);
  Wire.write(iox_output_register);
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

  //Check if the pin is onboard or offboard
  if (pin_needed.onboard == true) {
    //If the pin is onboard, check if we need to read or write
    if (read_write == write) {
      //If we need to write, check if we need to write high or low
      if (high_low == high) { //onborad digital write
        digitalWrite(pin_needed.pin_number, HIGH);
        
      } else if (high_low == low) { //onborad digital write low
        digitalWrite (pin_needed.pin_number, LOW);
        
      } else {
         //If high_low is not high or low, do something here (error handling?)
      }
    } else if (read_write == read) { //onboard digital read
      int read_value = digitalRead(pin_needed.pin_number);
      return(read_value);
    } else {
       //If read_write is not read or write, do something here (error handling?)
    }

  } else if (pin_needed.onboard == false){ //digital write to io expander
    
    if (read_write == write) {  //chek to see if we are writeing the the ioxepander

      //int local varibels
      uint8_t current = io_read_current_io_state(pin_needed.port, pin_needed.iox_number); //read and store the current state of the output register of the the given pin
      uint8_t output = 0b00000000;
      uint8_t mask_not = ~pin_needed.mask;

      //bitwise logic to ether set high or low a given pin
      if (high_low == high) {
        output = current | pin_needed.mask;
      } else if (high_low == low){
        output = current & mask_not;
      }

      //begin write to iox
      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);
      } else {
        Wire.beginTransmission(iox_1_add);
      }
        
      //write to selcted port
      if (pin_needed.port == 0) {
        Wire.write(iox_output_port_0);
      } else {
        Wire.write(iox_output_port_1);
      }
      
      Wire.write(output);

      Wire.endTransmission();

    } else if (read_write == read) {  //check to see if we are reading from the io expanders input
      
      //init local varibles
      uint8_t readval = 0b00000000;
      uint8_t output_byte = 0b00000000;
      
      //select witch iox to red from
      if (pin_needed.iox_number == 0) {
        Wire.beginTransmission(iox_0_add);
      } else {
        Wire.beginTransmission(iox_1_add);
      }
      
      //selcect port based on given pin
      if (pin_needed.port == 0) {
        Wire.write(iox_input_port_0);
      } else if (pin_needed.port == 1) {
        Wire.write(iox_input_port_1);
      }

      Wire.endTransmission();

      //begin reading from selcted iox
      if (pin_needed.iox_number == 0) {
        Wire.requestFrom(iox_0_add, 1);
      } else {
        Wire.requestFrom(iox_1_add, 1);
      }
      
      //read the given value from the i2c bus
      readval = Wire.read();

      //isolate the indivdual bit of the given pin bsed on its mask
      output_byte = readval & pin_needed.mask;

      //return high or low based on wether or not the byte is more than 0
      if (output_byte == 0) {
        return (LOW);
      } else {
        return (HIGH);
      }
      
    }

  } else { //return if input bad
    return 0;
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

  //init vars
  uint8_t iox_0_port_0_pinmode = 0x00;
  uint8_t iox_0_port_1_pinmode = 0x00;
  uint8_t iox_1_port_0_pinmode = 0x00;
  uint8_t iox_1_port_1_pinmode = 0x00;

  //begin iterationg thru pins
  for (uint i = 1; i < sizeof(pin_names[0]); i++) {

    //init local loop vars
    //struct pin* curent_pin = pin_names[i];

    switch (pin_names[i]->pin_mode)
    {
    case in:
      if (pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, INPUT);
      } else {
        if (pin_names[i]->iox_number == 0) {
          if (pin_names[i]->port == 0){
            iox_0_port_0_pinmode = pin_names[i]->mask | iox_0_port_0_pinmode;
          } else {
            iox_0_port_1_pinmode = pin_names[i]->mask | iox_0_port_1_pinmode;
          }
        } else {
          if (pin_names[i]->port == 0) {
            iox_1_port_0_pinmode = pin_names[i]->mask | iox_1_port_0_pinmode;
          } else {
            iox_1_port_1_pinmode = pin_names[i]->mask | iox_1_port_1_pinmode;
          }
        }
      }
      break;
    
    case out:
      if (pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, OUTPUT);
      }
      //no need to do anything to the iox all pins defult to output
      break;

    case bi_dir:
      //do nothing only used for i2c coms witch are defined else-ware 
      break;
    
    case intr: //setup iterups for cheking when io state is changed
      if(pin_names[i]->onboard) {
        pinMode(pin_names[i]->pin_number, INPUT);
        attachInterrupt(digitalPinToInterrupt(pin_names[i]->pin_number), io_pin_intrupt_flagger, RISING);
      }      
      break;
    case empty_pin:
      //do nothing
      break;
    }  

    // setup the interrupt masks for the io expanders
    if (pin_names[i]->allow_interrupt && !pin_names[i]->onboard) {
      if (pin_names[i]->iox_number == 0) {
        if (pin_names[i]->port == 0) {
          iox_0_port_0_interrupt = iox_0_port_0_interrupt ^ pin_names[i]->mask;
        } else {
          iox_0_port_1_interrupt = iox_0_port_1_interrupt ^ pin_names[i]->mask;
        }
      } else {
        if (pin_names[i]->port == 0) {
          iox_1_port_0_interrupt = iox_1_port_0_interrupt ^ pin_names[i]->mask;
        } else {
          iox_1_port_1_interrupt = iox_1_port_1_interrupt ^ pin_names[i]->mask;
        }
      }
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


  //begin writeing pinmodes to ioxs 
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


  //write to ioxs interup mask registers
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


  return;
};

/**
 * @brief Configures the IO expanders for interrupt handling.
 * 
 * This function configures the IO expanders for interrupt handling by setting the interrupt mask registers
 * and enabling the desired interrupt pins.
 * 
 */
void io_deaseert_iox_int () {
  
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
struct pin io_determine_intrupt_source() {
  //init local vars
  uint8_t iox_0_int_reg_0_value = 0;
  uint8_t iox_0_int_reg_1_value = 0;
  uint8_t iox_1_int_reg_0_value = 0;
  uint8_t iox_1_int_reg_1_value = 0;

  //read iterupt register values from iox 0  
  Wire.beginTransmission(iox_0_add);
  Wire.write(iox_int_stat_register_0);
  Wire.endTransmission();
  Wire.requestFrom(iox_0_add, 2);
  iox_0_int_reg_0_value = Wire.read();
  iox_0_int_reg_1_value = Wire.read();
  Wire.endTransmission();

  //chek if interupt came from other iox
  if ((iox_0_int_reg_0_value & iox_1_int.mask) != 0) {
    //read iterupt register values from iox 1
    Wire.beginTransmission(iox_1_add);
    Wire.write(iox_int_stat_register_0);
    Wire.endTransmission();
    Wire.requestFrom(iox_1_add, 2);
    iox_1_int_reg_0_value = Wire.read();
    iox_1_int_reg_1_value = Wire.read();
    Wire.endTransmission();

    //determine if iterupt came from adc or f/b pgood
    if ((iox_1_int_reg_1_value & adc_alert.mask) != 0) {
      return adc_alert;
    } else if ((iox_1_int_reg_0_value & f_usbc_pgood.mask) != 0) {
      return f_usbc_pgood;
    } else if ((iox_1_int_reg_0_value & b_usbc_pgood.mask) != 0) {
      return b_usbc_pgood;
    }
  }

  //determine if intertrupt came from source btn, unit btn, mode btn, display, or ufp/dfp pd phy alert
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

};


/**
 * @brief Sets the interrupt flag.
 * 
 * This function sets the interrupt flag `io_interupt_flag` to true.
 */
void io_pin_intrupt_flagger () {
  //set the intrupt flag
  io_interupt_flag = true;
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

  io_interupt_flag = false;

  if (io_determine_intrupt_source().pin_ident == 'x') { //adc alert
    //determine channel that flagged the alert 
    if (adc_determine_alert_source() == ch0) {
      //21V csp do nothing
      Serial.println("recived ADC 21V intrupt");
    } else if (adc_determine_alert_source() == ch1) {
      //21V csn do nothing 
      Serial.println("recived ADC 21V csn intrupt");     
    } else if (adc_determine_alert_source() == ch2) {
      //5V csp do nothing
      Serial.println("recived ADC 5V intrupt");    
    } else if (adc_determine_alert_source() == ch3) {
      //5V csn do nothing
      Serial.println("recived ADC 5V csn intrupt");   
    } else if (adc_determine_alert_source() == ch4) {
      //ufp csp
      //turn off power to port if out of range
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)){
        //do nothing if pgood
      } else {
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
        Serial.println("recived ADC UFP power bad intrupt");
      }
    } else if (adc_determine_alert_source() == ch5) {
      //ufp csn
      //turn off power to port if out of range
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)){
        //do nothing if pgood        
      } else {
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
        Serial.println("recived ADC UFP csn power bad intrupt");
      }
    } else if (adc_determine_alert_source() == ch6) {
      //dfp csp
      //turn off port power if out of range 
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)) {
        //do nothing if power good
      } else {
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
        Serial.println("recived ADC DFP power bad intrupt");
      }
    } else if (adc_determine_alert_source() == ch7) {
      //dfp csn
      //turn port power off if out of range
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)){
        //do nnothing if power good        
      } else {
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
        Serial.println("recived ADC DFP csn power bad intrupt");
      }
    }

    //clear adc alert
    adc_clear_event_flag();

  } else if (io_determine_intrupt_source().pin_ident == 'q') { //f usbc pgood
    // read pin to see if high or low
    if (io_call(f_usbc_pgood, read, read_mode) == 1) {
      //set allow output to  true
      pd_power_cont_dfp_allow_output = true;
      Serial.println("recived DFP PSU pgood intrupt");
    } else if (io_call(f_usbc_pgood, read, read_mode)){
      //set allow output to false 
      pd_power_cont_dfp_allow_output = false;
      Serial.println("recived DFP PSU pbad intrupt");
    }
  } else if (io_determine_intrupt_source().pin_ident == 'j') { //b usbc pgood
    // read pin to see if high or low
    if (io_call(b_usbc_pgood, read, read_mode) == 1) {
      //set allow output to  true
      pd_power_cont_ufp_allow_output = true;
      Serial.println("recived UFP PSU pgood intrupt");
    } else if (io_call(b_usbc_pgood, read, read_mode)){
      //set allow output to false 
      pd_power_cont_ufp_allow_output = false;
      Serial.println("recived UFP PSU pbad intrupt");
    }
  } else if (io_determine_intrupt_source().pin_ident == '4') { //source buttion
    io_src_btn_pressed = true;
    Serial.println("recived src buttion intrupt");
  } else if (io_determine_intrupt_source().pin_ident == '3') { //unit buttion
    io_unit_btn_pressed = true;
    Serial.println("recived unit buttion intrupt");
  } else if (io_determine_intrupt_source().pin_ident == '5') { //mode buttion
    io_mode_btn_pressed = true;
    Serial.println("recived mode buttion intrupt");
  } else if (io_determine_intrupt_source().pin_ident == '2') { //display itrupt
    //do nothing, not used 
    Serial.println("recived display intrupt (this sholdent happen)");
  } else if (io_determine_intrupt_source().pin_ident == '0') { //ufp alert n
    //determine alert type
    if (pd_phy_alert_type(ufp) == vendor_defined_extended) {
      // do nothing
      Serial.println("recived UFP pd PHY vendor defined extended intrupt");
    } else if (pd_phy_alert_type(ufp) == extended_status_cahnged) {
      // do nothing
      Serial.println("recived UFP pd PHY extended status changed intrupt");
    } else if (pd_phy_alert_type(ufp) == beginning_sop_message_status) {
      Serial.println("recived UFP pd PHY beggining sop message status intrupt");
      pd_phy_recive_message(ufp);
    } else if (pd_phy_alert_type(ufp) == vbus_sink_disconnect_detected) {
      //do nothing?
      Serial.println("recived UFP pd PHY vbus sink disconnect detected intrupt");
    } else if (pd_phy_alert_type(ufp) == rx_buffer_overflow) {
      //reset recive buffer
      pd_phy_send_reset_recive_buffer(ufp);
      Serial.println("recived UFP pd PHY RX buffer overflow intrupt");
    } else if (pd_phy_alert_type(ufp) == vbus_voltage_low) {
      Serial.println("recived UFP pd PHY vbus voltage low intrupt");
      //see if power is actuly bad
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)) {
        //do nothing
      } else {
        //turn port power off
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
      }
    } else if (pd_phy_alert_type(ufp) == vbus_voltage_high) {
      Serial.println("recived UFP pd PHY vbus voltage high intrupt");
      //see if power is actuly bad
      if (pd_power_cont_pgood(ufp, pd_power_cont_ufp_current_voltage)) {
        //do nothing
      } else {
        //turn port power off
        pd_power_cont_return_to_base_state(ufp);
        pd_power_cont_ufp_allow_output = false;
      }
    } else if (pd_phy_alert_type(ufp) == transmit_sop_message_succsessful) {
      Serial.println("recived UFP pd PHY transmit sop message susessful intrupt");

      //hit good crc flag
      pd_prot_ufp_last_good_crc = true;
      

    } else if (pd_phy_alert_type(ufp) == transmit_sop_message_discarded) {
      Serial.println("recived UFP pd PHY transmit sop message discarded intrupt");
      //retransmit message if discarded
      pd_phy_transmit(ufp, pd_prot_ufp_last_message, pd_prot_ufp_last_message_length);

    } else if (pd_phy_alert_type(ufp) == transmit_sop_message_failed) {
      Serial.println("recived UFP pd PHY transmit sop message failed intrupt");
      //retransmit message if retransmit counter hasent reached its threshold
      if (pd_prot_ufp_counter_retry <= pd_prot_counter_th_retry) {
        pd_phy_transmit(ufp, pd_prot_ufp_last_message, pd_prot_ufp_last_message_length);
      } else {
        //set retransmit failled flag
        pd_prot_ufp_retransit_failled = true;
      }
      
      //add to retrasnmit counter
      ++pd_prot_ufp_counter_retry;

    } else if (pd_phy_alert_type(ufp) == recived_hard_reset) {
      Serial.println("recived UFP pd PHY recived hard reset intrupt");
      pd_prot_hard_reset_handeler(ufp, false);
    } else if (pd_phy_alert_type(ufp) == recvied_sop_message_status) {
      Serial.println("recived UFP pd PHY recived sop message status intrupt");
      //set message recived flag and read message contents
      io_intrupt_ufp_msg_recived = true;
      pd_phy_recive_message(ufp);

    } else if (pd_phy_alert_type(ufp) == port_power_status_changed) {
      Serial.println("recived UFP pd PHY port power status changed intrupt");
      // do nothing?
    } else if (pd_phy_alert_type(ufp) == cc_status_alert) {
      Serial.println("recived UFP pd PHY cc status alert intrupt");
      // determine if port is in attched or detached state 
      if (pd_phy_ufp_attached) {
        //complite detach seqwince
        pd_phy_complite_detatch(ufp);
      } else {
        // complite attach
        pd_phy_complite_attach(ufp);
      }
    } else if (pd_phy_alert_type(ufp) == extended_timer_expired) {
      Serial.println("recived UFP pd PHY extended timer expired intrupt");
      // do nothing
    } else if (pd_phy_alert_type(ufp) == extended_souce_frs) {
      Serial.println("recived UFP pd PHY extended souce frs intrupt");
      // do nothing
    } else if (pd_phy_alert_type(ufp) == extended_sink_frs) {
      Serial.println("recived UFP pd PHY extended sink frs intrupt");
      // do nothing
    } else if (pd_phy_alert_type(ufp) == force_discharge_failled) {
      Serial.println("recived UFP pd PHY force discharge failled intrupt");
      // turn port power supply off
      pd_power_cont_return_to_base_state(ufp);
    } else if (pd_phy_alert_type(ufp) == auto_discahrge_failed) {
      Serial.println("recived UFP pd PHY auto discharge failled intrupt");
      // do nothing for now
    } else if (pd_phy_alert_type(ufp) == internal_or_external_vbus_over_current_protection_fault) {
      Serial.println("recived UFP pd PHY internal or external vbus over current protection fault intrupt");
      // turn of power and stop allowing output 
      pd_power_cont_return_to_base_state(ufp);
      pd_power_cont_ufp_allow_output = false;
    } else if (pd_phy_alert_type(ufp) == internal_or_external_vbus_over_voltage_protection_fault) {
      Serial.println("recived UFP pd PHY internal or external vbus over voltage protection fault intrupt");
      //turn off power and stop allowing output
      pd_power_cont_return_to_base_state(ufp);
      pd_power_cont_ufp_allow_output = false;
    } else if (pd_phy_alert_type(ufp) == i2c_error) {
      Serial.println("recived UFP pd PHY i2c error intrupt");
      //reset rx & tx buffers
      pd_phy_send_reset_recive_buffer(ufp);
      pd_phy_send_reset_transmit_buffer(ufp);
    }

    pd_phy_clear_alert(ufp);
    pd_phy_clear_fault(ufp);
    pd_phy_clear_extended_alert(ufp);

  } else if (io_determine_intrupt_source().pin_ident == '?') { //dfp alert n
    //determine alert type
    if (pd_phy_alert_type(dfp) == vendor_defined_extended) {
      Serial.println("recived DFP pd PHY vendor defined extended intrupt");
      // do nothing
    } else if (pd_phy_alert_type(dfp) == extended_status_cahnged) {
      Serial.println("recived DFP pd PHY extended status changed intrupt");
      // do nothing
    } else if (pd_phy_alert_type(dfp) == beginning_sop_message_status) {
      Serial.println("recived DFP pd PHY beggining sop message status intrupt");
      pd_phy_recive_message(dfp);
      
    } else if (pd_phy_alert_type(dfp) == vbus_sink_disconnect_detected) {
      Serial.println("recived DFP pd PHY vbus sink disconnect detected intrupt");
      //do nothing?
    } else if (pd_phy_alert_type(dfp) == rx_buffer_overflow) {
      Serial.println("recived DFP pd PHY RX buffer overflow intrupt");
      //reset recive buffer
      pd_phy_send_reset_recive_buffer(dfp);
    } else if (pd_phy_alert_type(dfp) == vbus_voltage_low) {
      Serial.println("recived DFP pd PHY vbus voltage low intrupt");
      //see if power is actuly bad
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)) {
        //do nothing
      } else {
        //turn port power off
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
      }
    } else if (pd_phy_alert_type(dfp) == vbus_voltage_high) {
      Serial.println("recived DFP pd PHY vbus voltage high intrupt");
      //see if power is actuly bad
      if (pd_power_cont_pgood(dfp, pd_power_cont_dfp_current_voltage)) {
        //do nothing
      } else {
        //turn port power off
        pd_power_cont_return_to_base_state(dfp);
        pd_power_cont_dfp_allow_output = false;
      }
    } else if (pd_phy_alert_type(dfp) == transmit_sop_message_succsessful) {
      Serial.println("recived DFP pd PHY transmit sop message susessful intrupt");

      //hit good crc flag
      pd_prot_dfp_last_good_crc = true;

    } else if (pd_phy_alert_type(dfp) == transmit_sop_message_discarded) {
      Serial.println("recived DFP pd PHY transmit sop message discarded intrupt");
      //retransmmit message if discarded
      pd_phy_transmit(dfp, pd_prot_dfp_last_message, pd_prot_dfp_last_message_length);
      
    } else if (pd_phy_alert_type(dfp) == transmit_sop_message_failed) {
      Serial.println("recived DFP pd PHY transmit sop message failed intrupt");
      //retransmit message if retransmit counter hasent reached its threshold
      if (pd_prot_dfp_counter_retry <= pd_prot_counter_th_retry) {
        pd_phy_transmit(dfp, pd_prot_dfp_last_message, pd_prot_dfp_last_message_length);
      } else {
        //set retransmit failled flag
        pd_prot_dfp_retransit_failled = true;
      }
      
      //add to retrasnmit counter
      ++pd_prot_ufp_counter_retry;

    } else if (pd_phy_alert_type(dfp) == recived_hard_reset) {
      Serial.println("recived DFP pd PHY recived hard reset intrupt");
      pd_prot_hard_reset_handeler(dfp, false);
    } else if (pd_phy_alert_type(dfp) == recvied_sop_message_status) {
      Serial.println("recived DFP pd PHY recived sop message status intrupt");
      //set message recived flag and read message contents
      io_intrupt_dfp_msg_recived = true;
      pd_phy_recive_message(dfp);
    } else if (pd_phy_alert_type(dfp) == port_power_status_changed) {
      Serial.println("recived DFP pd PHY extended sink frs intrupt");
      // do nothing?
    } else if (pd_phy_alert_type(dfp) == cc_status_alert) {
      Serial.println("recived DFP pd PHY cc status alert intrupt");
      // determine if port is in attched or detached state 
      if (pd_phy_dfp_attached) {
        //complite detach seqwince
        pd_phy_complite_detatch(dfp);
      } else {
        // complite attach
        pd_phy_complite_attach(dfp);
      }
    } else if (pd_phy_alert_type(dfp) == extended_timer_expired) {
      Serial.println("recived DFP pd PHY extended timer expired intrupt");
      // do nothing
    } else if (pd_phy_alert_type(dfp) == extended_souce_frs) {
      Serial.println("recived DFP pd PHY extended souce frs intrupt");
      // do nothing
    } else if (pd_phy_alert_type(dfp) == extended_sink_frs) {
      Serial.println("recived DFP pd PHY extended sink frs intrupt");
      // do nothing
    } else if (pd_phy_alert_type(dfp) == force_discharge_failled) {
      Serial.println("recived DFP pd PHY force discharge failled intrupt");
      // turn port power supply off
      pd_power_cont_return_to_base_state(dfp);
    } else if (pd_phy_alert_type(dfp) == auto_discahrge_failed) {
      Serial.println("recived DFP pd PHY auto discharge failled intrupt");
      // do nothing for now
    } else if (pd_phy_alert_type(dfp) == internal_or_external_vbus_over_current_protection_fault) {
      Serial.println("recived DFP pd PHY internal or external vbus over current protection fault intrupt");
      // turn of power and stop allowing output 
      pd_power_cont_return_to_base_state(dfp);
      pd_power_cont_dfp_allow_output = false;
    } else if (pd_phy_alert_type(dfp) == internal_or_external_vbus_over_voltage_protection_fault) {
      Serial.println("recived DFP pd PHY internal or external vbus over voltage protection fault intrupt");
      //turn off power and stop allowing output
      pd_power_cont_return_to_base_state(dfp);
      pd_power_cont_dfp_allow_output = false;
    } else if (pd_phy_alert_type(dfp) == i2c_error) {
      Serial.println("recived DFP pd PHY i2c error intrupt");
      //reset rx & tx buffers
      pd_phy_send_reset_recive_buffer(dfp);
      pd_phy_send_reset_transmit_buffer(dfp);
    }

    pd_phy_clear_alert(dfp);
    pd_phy_clear_fault(dfp);
    pd_phy_clear_extended_alert(dfp);

  }
  //deasert iox_intrupts
  io_deaseert_iox_int();

  return;

}




#endif // io_cpp