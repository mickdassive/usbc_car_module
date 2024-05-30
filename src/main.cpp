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
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
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


//wifi defines
const char* ssid = "baahome";
const char* password = "!!!abahome12345!!!";
const int wifi_wait_time = 1000; 
bool wifi_dhcp_enabled = true;
IPAddress ip(0, 0, 0, 0);
IPAddress gateway(0, 0, 0, 0);
IPAddress subnet(255, 255, 255, 0);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer httpServer(80);

//firmware version
const char* firmware_version = "V 0.1";

//boot successful var
int boot_successful = 0;



void setup() {

  //begin serial
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Serial started");
  Serial.print("Firmware version: ");
  Serial.print(firmware_version);
  Serial.println(" ");

  //ask on the console 
  Serial.println("Press any key to enable or configure Wi-Fi...");
  unsigned long wifistartTime = millis();
  while (millis() - wifistartTime < wifi_wait_time) {
    if (Serial.available()) {
      Serial.read(); // Consume the keypress

      Serial.println("Wi-Fi menu");
      Serial.println("1) Enable Wi-Fi");
      Serial.println("2) Configure Wi-Fi");

      char key = Serial.read(); // Read the keypress
      if (key == '1') {
        Serial.println("Initializing Wi-Fi...");
        if (wifi_dhcp_enabled) {
          WiFi.begin(ssid, password);
        } else {
          WiFi.config(ip, gateway, subnet);
          WiFi.begin(ssid, password);
        }
                  
                  
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          Serial.println("Connecting to WiFi...");
        }
                
        Serial.println("Connected to WiFi");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
                
        MDNS.begin("esp8266");
        httpUpdater.setup(&httpServer); // This line initializes the OTA update server
        httpServer.begin();
        MDNS.addService("http", "tcp", 80);
        Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", "esp8266");
        break;
      } else if (key == '2') {
        Serial.println("Use DHCP? (y/n)");
        while (true) {
          if (Serial.available()) {
            char input = Serial.read();
            Serial.print("You entered: ");
            Serial.println(input);
            Serial.println("Press enter to confirm");
            while (true) {
              if (Serial.available() && Serial.read() == '\n') {
                if (input == 'y' || input == 'Y') {
                  wifi_dhcp_enabled = true;
                } else if (input == 'n' || input == 'N') {
                  wifi_dhcp_enabled = false;
                } else {
                  Serial.println("Invalid key. Please try again.");
              break;
              }
              delay(100); // Add a small delay to avoid excessive looping
            }
            break;
          }
          delay(100); // Add a small delay to avoid excessive looping
        }

        if (!wifi_dhcp_enabled) {
          Serial.println("Enter IP address (format: xxx.xxx.xxx.xxx):");
          String ipString = Serial.readStringUntil('\n');
          ip.fromString(ipString);

          Serial.println("Enter subnet mask (format: xxx.xxx.xxx.xxx):");
          String subnetString = Serial.readStringUntil('\n');
          subnet.fromString(subnetString);

          Serial.println("Enter gateway (format: xxx.xxx.xxx.xxx):");
          String gatewayString = Serial.readStringUntil('\n');
          gateway.fromString(gatewayString);
        }
        Serial.println("Invalid key. Please try again.");
      }
    }
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi not enabled");
  }



  //begin i2c
  Wire.begin(sda.pin_number, scl.pin_number);
  Wire.setClock(400000);
  Serial.println("I2c started");

  //begin scanning i2c bus for all devices
  if (bus_scan()) {
    ++boot_successful;
  }

  //begin GPIO inits for on and offboard 
  io_gpio_init();
  Serial.println("GPIO init complete");

  //set onboard led to low to not be annoying
  io_call(onboard_led, write, low);

  //begin init for ADC
  //adc_init(false);
  Serial.println("ADC init and self cal complete");

  //begin init for display
  disp_init();
  Serial.println("Display init complete");

  //begin USB hub chip init
  hub_init();
  Serial.println("USB-hub init complete");

  //begin USB-PD power supply check 
  Serial.println("Begin PSU self check");
  if (pd_power_cont_self_check()) {
    Serial.println("UFP&DFP voltages within safe range");
    ++boot_successful;
  } else {
    Serial.println("PSU self check failed");
  }
  //send psu back to base state
  pd_power_cont_return_to_base_state(ufp);
  pd_power_cont_return_to_base_state(dfp);

  //begin init for USB-PD PHYs
  pd_phy_init();
  Serial.println("USB-PD PHY UFP&DFP init complete");

  /*
    //determine if boot was successful
  if (boot_successful >= 2) {
    //do nothing
  } else {
    Serial.println("Boot failed in one or more ways !!!!!!!!!");
    while (boot_successful != 2)  {
      io_call(onboard_led, write, high);
      delay(100);
      io_call(onboard_led, write, low);
      delay(100);
    }
  }
  */
  
}



void loop() {

  //run update server
  if (WiFi.status() == WL_CONNECTED) {
    httpServer.handleClient();
    MDNS.update();
  }

  //see if interrupt was flagged and run the handler
  if (io_interrupt_flag) {
    io_intrupt_handeler();
  }

}


#endif // main_cpp