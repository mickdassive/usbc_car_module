//{usbc car module}
//{debug.h}
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

#ifndef debug_h
#define debug_h

#include <Arduino.h>

//var defines
enum debug_level {
    full,
    partal_hub,
    partal_pd_phy,
    partal_pd_prot,
    partal_io,
    partal_adc,
    partal_disp,
    partal_i2c,
    partal_power_cont,
    partal_can_bus,
    partal_wifi,
    none
    };

extern enum debug_level debug_level = none;

//function define
void debug_msg(enum debug_level, char* debug_message, bool include_num, int num_include);
void set_debug_level(enum debug_level);


#endif // debug_h