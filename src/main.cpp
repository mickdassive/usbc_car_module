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

#ifndef main_cpp
#define main_cpp

#include <Arduino.h>
#include <Wire.h>
#include "main_defines.h"
#include "adc.h"
#include "ui/display.h"
#include "ui/power_mon.h"
#include "pd/pd_phy.h"
#include "pd/pd_power_cont.h"
#include "pd/pd_prot.h"
#include "io.h"
#include "hub.h"
#include "i2c_scanner.h"


//firmware version
const char* firmware_version = "V 0.1";

//boot sucsessful var
int boot_sucsesful = 0;



void setup() {

  //begin serial
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Serial started");
  Serial.print("Firmware version: ");
  Serial.print(firmware_version);
  Serial.println(" ");

  //begin i2c
  Wire.begin(sda.pin_number, scl.pin_number);
  Wire.setClock(400000);
  Serial.println("I2c strated");

  //begin scaning i2c bus for all devices
  if (bus_scan()) {
    ++boot_sucsesful;
  }

  //begin GPIO inits for on and offboard 
  io_gpio_init();
  Serial.println("GPIO init complete");

  //set onboard led to low to not be annoying
  io_call(onboard_led, write, low);

  //bgegin init for ADC
  //adc_init(false);
  Serial.println("ADC init and self cal complete");

  //begin init for display
  disp_init();
  Serial.println("Display init complete");

  //begin USB hub chip init
  hub_init();
  Serial.println("USB-hub init complete");

  //begin USB-PD power supply check 
  Serial.println("Begin PSU self chek");
  if (pd_power_cont_self_check()) {
    Serial.println("UFP&DFP voltages within safe range");
    ++boot_sucsesful;
  } else {
    Serial.println("PSU self check failed");
  }
  //send psu back to base state
  pd_power_cont_return_to_base_state(ufp);
  pd_power_cont_return_to_base_state(dfp);

  //begin init for USB-PD PHYs
  pd_phy_init();
  Serial.println("USB-PD PHY UFP&DFP init complete");


  //determine if boot was sucsessful
  if (boot_sucsesful >= 2) {
    //do nothing
  } else {
    Serial.println("Boot falled in one or more ways !!!!!!!!!");
    while (boot_sucsesful != 2)  {
      io_call(onboard_led, write, high);
      delay(100);
      io_call(onboard_led, write, low);
      delay(100);
    }
  }
  
}



void loop() {
  //see if intrupt was flaged and run the handeler
  if (io_interupt_flag) {
    io_intrupt_handeler();
  }

}


#endif // main_cpp