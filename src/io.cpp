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

//iox intrupt register values
uint8_t iox_0_port_0_interrupt = 0xFF;
uint8_t iox_0_port_1_interrupt = 0xFF;
uint8_t iox_1_port_0_interrupt = 0xFF;
uint8_t iox_1_port_1_interrupt = 0xFF;


//reads current pin state of the io expander outputs
//port: port of iox to read
//iox_num: number of iox to read from
uint8_t io_read_current_io_state(int port, int iox_num) {
  uint8_t iox_address = (iox_num == 0) ? iox_0_add : iox_1_add;
  uint8_t iox_output_register = (port == 0) ? iox_output_port_0 : iox_output_port_1;

  Wire.beginTransmission(iox_address);
  Wire.write(iox_output_register);
  Wire.endTransmission();

  Wire.requestFrom(iox_address, 1);
  return Wire.read();
}

//io_call function
//This function is used to read or write digital values to onboard or offboard IOs.
//pin_needed: a pin struct that defines the pin being read/written to
//read_write: a read_write enum value that specifies if the function should read or write
//high_low: a high_low enum value that specifies if the function should write a high or low value
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

//GPIO pin auto init for both iox and onborad pins
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
       // attachInterrupt(digitalPinToInterrupt(pin_names[i]->pin_number), ioISR, FALLING);
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


//de assert intrupt from the iox's 
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


//io_determine_intrupt_source
//determines the souce of an intrupt
//returns souce of intrupt from the pin struct
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
      io_deaseert_iox_int();
      return adc_alert;
    } else if ((iox_1_int_reg_0_value & f_usbc_pgood.mask) != 0) {
      io_deaseert_iox_int();
      return f_usbc_pgood;
    } else if ((iox_1_int_reg_0_value & b_usbc_pgood.mask) != 0) {
      io_deaseert_iox_int();
      return b_usbc_pgood;
    }
  }

  //determine if intertrupt came from source btn, unit btn, mode btn, display, or ufp/dfp pd phy alert
  if ((iox_0_int_reg_1_value & src_btn.mask) != 0) {
    io_deaseert_iox_int();
    return src_btn;
  } else if ((iox_0_int_reg_1_value & unit_btn.mask) != 0) {
    io_deaseert_iox_int();
    return unit_btn;
  } else if ((iox_0_int_reg_1_value & mode_btn.mask) != 0) {
    io_deaseert_iox_int();
    return mode_btn;
  } else if ((iox_0_int_reg_1_value & disp_irq.mask) != 0) {
    io_deaseert_iox_int();
    return disp_irq;
  } else if ((iox_0_int_reg_1_value & ufp_alert_n.mask) != 0) {
    io_deaseert_iox_int();
    return ufp_alert_n;
  } else if ((iox_0_int_reg_1_value & dfp_alert_n.mask) != 0) {
    io_deaseert_iox_int();
    return dfp_alert_n;
  }

  return empty_struct_pin;

};




#endif // io_cpp