//{usbc car module}
//{defines.cpp}
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

#include <Arduino.h>
#include <wire.h>
#include "display_defines.cpp"

//display init function
void disp_init() {
  //wake up display controler
  Wire.beginTransmission(disp_base_add);
  Wire.write(disp_shutdown);
  Wire.write(disp_up_rst);
  Wire.endTransmission();

  //tell display controler to self address
  Wire.beginTransmission(disp_base_add);
  Wire.write(disp_self_add);
  Wire.write(0x01);
  Wire.endTransmission();

  //wake display from shutdown after self addressing
  Wire.beginTransmission(disp_add);
  Wire.write(disp_shutdown);
  Wire.write(disp_up);
  Wire.endTransmission();

  //set disp controler decode mode to raw
  Wire.beginTransmission(disp_add);
  Wire.write(disp_decode_mode);
  Wire.write(0x00); //decode mode raw
  Wire.endTransmission();

  //set display scan limit
  Wire.beginTransmission(disp_add);
  Wire.write(disp_scan_limit);
  Wire.write(0x07); //scan all digits
  Wire.endTransmission();

  //set display intensity
  Wire.beginTransmission(disp_add);
  Wire.write(disp_global_intensity);
  Wire.write(disp_intense_defult);
  Wire.endTransmission();

  return;
}

//display balnk function just writes 0s to the first 4 digit registers but keeps the status leds
void disp_blank() {
  Wire.beginTransmission(disp_add);
  Wire.write(disp_digit_0);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  return;
}

//set disply brightness
//desired_brightness: brightness of display from 0-255
void disp_bright(uint8_t desired_brightness) {
  Wire.beginTransmission(disp_add);
  Wire.write(disp_global_intensity);
  Wire.write(desired_brightness);
  Wire.endTransmission();

  return;
}

//display write function
//will only work with flaots and ints
void disp_write(float input) {
  
}

//read current led state
uint8_t read_current_led_state (enum led_names){
  
}


//led control
//led_names: name of led to control
//led_on_off: set desired led state
void led_control(struct leds, enum led_on_off){

  if (led_on_off == on) {
    switch (leds.name) {
      case ("watts"):

      break;
      case (amps):

      break;
      case (volts):

      break;
      case (usb_c_back):

      break;
      case (usb_c_front):

      break;
      case (usb_a):

      break;
      case (system_power):

      break;
      case (watts_10):

      break;
      case (watts_20):

      break;
      case (watts_40):

      break;
      case (watts_65):

      break;
      case (watts_100):

      break;
    }
  } else if (led_on_off = off) {

  }
  return 0;
}

