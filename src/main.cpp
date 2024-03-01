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

/*
extern "C" {
  #include "user_interface.h"
}
*/
#include <Arduino.h>
#include <Wire.h>
#include "main_defines.h"
#include "adc.h"
#include "display.h"
#include "pd_phy.h"
#include "iox.h"
#include "i2c_scanner.h"


//firmware version
const char* firmware_version = "V 0.1";

/*
//io intrupt rutine
void IRAM_ATTR ioISR() {

}
*/


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

  //begin GPIO inits for on and offboard 
  gpio_init();
  Serial.println("GPIO init complete");

  //begin scaning i2c bus for all devices
  bus_scan();
  
  //bgegin init for ADC
  //adc_init(false);
  Serial.println("ADC init and self cal complete");

  //begin init for display
  disp_init();
  Serial.println("Display init complete");

  //begin USB hub chip init

  Serial.println("USB-hub init complete");

  //begin init for USB-PD PHYs
  pd_phy_init();
  Serial.println("USB-PD PHY UFP&DFP init complete");


  //begin USB-PD power supply check 

  Serial.println("UFP&DFP voltage outputs within safe range");

  
}

void loop() {
  io_call(onboard_led, write, high);
  delay(rand() % (1000-1+1)+1);
  io_call(onboard_led, write, low);
  delay(rand() % (1000-1+1)+1);
}


#endif // main_cpp