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
#include "ui/display.h"
#include "io.h"
#include "hub.h"
#include "pd/pd_phy.h"

uint8_t hub_placeholder = 0;

//scans i2c bus and dermines if all devicesa are present
//true = passed, all devices present
//false = failed missing one or more devices
bool bus_scan() {
    // Initialize local variables
    int devices_found = 0;
    byte error;

    Serial.println("Begin scanning for all I2C devices...");

    // Loop through possible I2C device addresses
    for (int i = 0; i < 127; ++i) {
        Wire.beginTransmission(i);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("Device found at address 0x");
            if (i < 16) {
                Serial.print("0");
            }
            Serial.println(i, HEX);
            Serial.println(" !");

            // Add to device count if it matches expected addresses
            if (i == iox_0_add || i == iox_1_add || i == adc_add || i == pd_phy_add_dfp || i == pd_phy_add_ufp || i == hub_addr || i == disp_add) {
                devices_found++;
            }
        } else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (i < 16) {
                Serial.print("0");
            }
            Serial.println(i, HEX);
        }
        
        // Add a small delay between transmissions
        delay(5);
    }
    
    // Ensure device count matches what is expected
    if (devices_found == 7) {
        Serial.println("All expected I2C devices found");
        return true;
    } else {
        Serial.println("Some I2C devices are missing from the bus");
        return false;
    }
}


#endif // i2c_scanner_h