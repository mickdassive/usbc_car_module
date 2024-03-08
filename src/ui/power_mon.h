//{usbc car module}
//{power_mon.h}
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

#ifndef power_mon_h
#define power_mon_h

//const for resistor values used
// value in ohms
const int power_mon_21v_r1 = 10000;
const int power_mon_21v_r2 = 1000;
const float power_mon_21v_rs = 0.0015;
const int power_mon_5v_r1 = 10000;
const int power_mon_5v_r2 = 5000;
const float power_mon_5v_rs = 0.01;
const int power_mon_f_c_r1 = 10000;
const int power_mon_f_c_r2 = 1000;
const float power_mon_f_c_rs = 0.01;
const int power_mon_b_c_r1 = 10000;
const int power_mon_b_c_r2 = 1000;
const float power_mon_b_c_rs = 0.01;

//enum for difrent power "zones"
enum power_mon_zones {
    back_c,
    front_c,
    usb_a,
    system_total
};

//enum for volts,watts,amps
enum power_mon_v_a_w {
    volts,
    amps,
    watts
};

//function defines
void power_mon_calc_and_display(power_mon_zones zone, power_mon_v_a_w v_a_w);

#endif // power_mon_h