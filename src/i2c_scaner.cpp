//{usbc car module}
//{i2c_scanner.cpp}
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

#ifndef i2c_scanner_h
#define i2c_scanner_h

#include <Arduino.h>
#include <Wire.h>
#include "i2c_scanner.h"
#include "adc.h"
#include "display.h"
#include "io.h"
#include "pd/pd_phy.h"

uint8_t hub_placeholder = 0;


void bus_scan() {
    //init local vars
    int devices_found = 0;
    byte error, i;

    Serial.println("Begin scaning for all i2c devices...");

    for (int i; i < 127; ++i) {
        Wire.beginTransmission(i);
        error = Wire.endTransmission();

        if (error == 0){
            Serial.println("Device found at adres 0x");
            if (i < 16) {
                Serial.print("0");
            }
            Serial.println(i, HEX);
            Serial.println(" !");

            //add to device count
            if (i == iox_0_add || i == iox_1_add || i == adc_add || i == pd_phy_add_dfp || i == pd_phy_add_ufp || i == hub_placeholder || i == disp_add) {
                devices_found++;
            }
        } else if (error == 4) {
            Serial.println("Unkown error at addres 0x");
            if (i < 16) {
                Serial.println("0");
            }
            Serial.println(i, HEX);
        }
    }
    //ensure device count matches waht it shold 
    if (devices_found == 7){
        Serial.println("All expected i2c devices found");
    } else {
        Serial.println("Some i2c devices are missing from the bus");
    }
    return;
}


#endif // i2c_scanner_h