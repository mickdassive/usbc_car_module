//{usbc car module}
//{pd_power_cont.h}
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

#ifndef pd_power_cont_h
#define pd_power_cont_h

#include <Arduino.h>
#include "pd_phy.h"

//port info vars 
extern int pd_power_cont_ufp_current_voltage;
extern int pd_power_cont_dfp_current_voltage;
extern bool pd_power_cont_ufp_allow_output;
extern bool pd_power_cont_dfp_allow_output;

//function defines
void pd_power_cont_return_to_base_state (enum ufp_dfp ufp_dfp);
void pd_power_cont_en_vsafe5v (enum ufp_dfp ufp_dfp);
void pd_power_cont_en_9v (enum ufp_dfp ufp_dfp);
void pd_power_cont_en_12v (enum ufp_dfp ufp_dfp);
void pd_power_cont_en_15v (enum ufp_dfp ufp_dfp);
void pd_power_cont_en_20v (enum ufp_dfp ufp_dfp);
bool pd_power_cont_pgood (enum ufp_dfp ufp_dfp, int voltage);
bool pd_power_cont_self_check ();




#endif // pd_power_cont_h