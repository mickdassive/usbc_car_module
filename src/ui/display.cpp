//{usbc car module}
//{display.cpp}
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

#ifndef display_cpp
#define display_cpp

#include <Arduino.h>
#include <Wire.h>
#include <string>
#include "display.h"
#include "pd/pd_phy.h"


/**
 * @brief Initializes the display controller.
 * 
 * This function wakes up the display controller, sets the self-addressing mode,
 * wakes up the display, sets the decode mode to raw, sets the display scan limit,
 * and sets the display intensity.
 * 
 * @return void
 */
void disp_init() {

  debug_msg(partal_disp, "disp_init called", false, 0);

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

/**
 * Clears the display by sending blank data to the firdt 4 digits of display module.
 */
void disp_blank() {

  debug_msg(partal_disp, "disp_blank called", false, 0);

  Wire.beginTransmission(disp_add);
  Wire.write(disp_digit_0);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  return;
}

/**
 * Sets the brightness of the display.
 *
 * @param desired_brightness The desired brightness level (0-255).
 */
void disp_write(float input) {

  debug_msg(partal_disp, "disp_write called, with value", true, input);

  //init local vars
  int digit_binary_array[4];
  int digit_binary_array_dp = 0;
  

  //begin moving indvidual digits to a vector array
  std::string numStr = std::to_string(input);
  std::vector<int> digits;

  for (char c : numStr) {
    if (c != '.') {
      int digit = c - '0';
      digits.push_back(digit);
    }
  }
  digits.push_back(-1);

  // create & calculate legth of digit array
  int digit_array_size = digits.size();
  int digit_array[digit_array_size];

  //move digit info to a "normal" array
  for (int i = 0; i < digit_array_size; ++i) {
    digit_array[i] = digits[i];
  }

  //convert digits to digits that the display can output
  for (int i = 0; i < digit_array_size; i++) {

    switch (digit_array[i]){
      case 0:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_0;
      break;
    case 1:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_1;
      break;
    case 2:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_2;
      break;
    case 3:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_3;
      break;
    case 4:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_4;
      break;
    case 5:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_5;
      break;
    case 6:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_6;
      break;
    case 7:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_7;
      break;
    case 8:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_8;
      break;
    case 9:
      digit_binary_array[(i - digit_binary_array_dp)] = disp_num_9;
      break;
    case -1:
      digit_binary_array[(i - 1)] | disp_num_dp;
      digit_binary_array_dp++;
      break;
  }

  //send digits to the display
  Wire.beginTransmission(disp_add);
  Wire.write(disp_digit_0);
  for (int i = 0; i < 4; ++i) {
    Wire.write(digit_binary_array[i]);
  }
  Wire.endTransmission();
  
  }
  return;

}

/**
 * @brief Writes the state of a specific LED on the display.
 *
 * This function writes the state of a specific LED on the display by updating the corresponding digit register.
 *
 * @param leds The structure containing the LED information, including the digit and mask.
 * @param led_on_off The state of the LED, either "on" or "off".
 */
void disp_bright(uint8_t desired_brightness) {

  debug_msg(partal_disp, "disp_bright called, setting brightness with value", true, desired_brightness);

  Wire.beginTransmission(disp_add);
  Wire.write(disp_global_intensity);
  Wire.write(desired_brightness);
  Wire.endTransmission();

  return;
}

/**
 * Writes a floating-point number to the display.
 *
 * This function takes a floating-point number as input and converts it into a format that can be displayed on the screen.
 * It separates the individual digits of the number and converts them into binary values that correspond to the display's segments.
 * The decimal point is also handled and displayed correctly.
 *
 * @param input The floating-point number to be displayed.
 */
void disp_led_write (struct leds leds, enum on_off led_on_off) {

  debug_msg(partal_disp, "disp_led_write called", false, 0);

  //init local vars
  uint8_t current_register_value = 0x0;
  uint8_t value_to_write = 0x0;

  //determine what digit of the display register the desired led is
  //& read the respective digit register
  Wire.beginTransmission(disp_add);
  if (leds.digit == 6) {
    Wire.write(disp_digit_6);
  }
  else if (leds.digit == 7) {
    Wire.write(disp_digit_7);
  }
  Wire.endTransmission();

  Wire.requestFrom(disp_add, 1);
  current_register_value = Wire.read();
  Wire.endTransmission();

  //mask and set bits
  if (led_on_off == on) {
    value_to_write = current_register_value | leds.mask;
  } else if (led_on_off == off) {
    value_to_write = current_register_value ^ leds.mask;
  } 

  //write new value to registers
  Wire.beginTransmission(disp_add);
  if (leds.digit == 6) {
    Wire.write(disp_digit_6);
  } else if (leds.digit == 7) {
    Wire.write(disp_digit_7);
  }
  Wire.write(value_to_write);
  Wire.endTransmission();

  
  return;
}

#endif // display_cpp