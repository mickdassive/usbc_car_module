//{usbc car module}
//{hub.h}
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

#ifndef hub_h
#define hub_h

#include <Arduino.h>

const uint8_t hub_addr = 0x2D;
const uint16_t hub_reg_dev_rev = 0x0800;
const uint16_t hub_reg_dev_id = 0x0801;
const uint16_t hub_reg_clock_ctl = 0x0804;
const uint16_t hub_reg_util_config1 = 0x080A;
const uint16_t hub_reg_clock_detect = 0x080B;
const uint16_t hub_reg_gpio_16_23_pd = 0x082D;
const uint16_t hub_reg_gpio_8_12_pd = 0x082E;
const uint16_t hub_reg_gpio_1_7_pd = 0x082F;
const uint16_t hub_reg_gpio_16_23_dir = 0x0831;
const uint16_t hub_reg_gpio_8_12_dir = 0x0832;
const uint16_t hub_reg_gpio_1_7_dir = 0x0833;
const uint16_t hub_reg_gpio_16_23_out = 0x0835;
const uint16_t hub_reg_gpio_8_12_out = 0x0836;
const uint16_t hub_reg_gpio_1_7_out = 0x0837;
const uint16_t hub_reg_gpio_16_23_in = 0x0839;
const uint16_t hub_reg_gpio_8_12_in = 0x083A;
const uint16_t hub_reg_gpio_1_7_in = 0x083B;
const uint16_t hub_reg_gpio_16_23_pu = 0x083D;
const uint16_t hub_reg_gpio_8_12_pu = 0x083E;
const uint16_t hub_reg_gpio_1_7_pu = 0x083F;
const uint16_t hub_reg_usb2_ocs_stat = 0x0900;
const uint16_t hub_reg_usb3_ocs_stat = 0x0902;
const uint16_t hub_reg_gpio_72_pd = 0x096E;
const uint16_t hub_reg_gpio_64_71_pd = 0x096F;
const uint16_t hub_reg_gpio_72_dir = 0x0972;
const uint16_t hub_reg_gpio_64_71_dir = 0x0973;
const uint16_t hub_reg_gpio_72_out = 0x0976;
const uint16_t hub_reg_gpio_64_71_out = 0x0977;
const uint16_t hub_reg_gpio_72_in = 0x097A;
const uint16_t hub_reg_gpio_64_72_in = 0x097B;
const uint16_t hub_reg_gpio_72_pu = 0x097E;
const uint16_t hub_reg_gpio_64_72_pu = 0x097F;
const uint16_t hub_reg_pf0_ctl = 0x0A10;
const uint16_t hub_reg_pf1_ctl = 0x0A11;
const uint16_t hub_reg_pf2_ctl = 0x0A12;
const uint16_t hub_reg_pf3_ctl = 0x0A13;
const uint16_t hub_reg_pf4_ctl = 0x0A14;
const uint16_t hub_reg_pf5_ctl = 0x0A15;
const uint16_t hub_reg_pf6_ctl = 0x0A16;
const uint16_t hub_reg_pf7_ctl = 0x0A17;
const uint16_t hub_reg_pf8_ctl = 0x0A18;
const uint16_t hub_reg_pf9_ctl = 0x0A19;
const uint16_t hub_reg_pf10_ctl = 0x0A1A;
const uint16_t hub_reg_pf11_ctl = 0x0A1B;
const uint16_t hub_reg_pf12_ctl = 0x0A1C;
const uint16_t hub_reg_pf13_ctl = 0x0A1D;
const uint16_t hub_reg_pf14_ctl = 0x0A1E;
const uint16_t hub_reg_pf15_ctl = 0x0A1F;
const uint16_t hub_reg_pf16_ctl = 0x0A20;
const uint16_t hub_reg_usb2_vidl = 0x3000;
const uint16_t hub_reg_usb2_vidm = 0x3001;
const uint16_t hub_reg_usb2_pidl = 0x3002;
const uint16_t hub_reg_usb2_pidm = 0x3003;
const uint16_t hub_reg_usb2_didl = 0x3004;
const uint16_t hub_reg_usb2_didm = 0x3005;
const uint16_t hub_reg_hub_cfg_1 = 0x3006;
const uint16_t hub_reg_hub_cfg_2 = 0x3007;
const uint16_t hub_reg_hub_cfg_3 = 0x3008;
const uint16_t hub_reg_usb2_nrd = 0x3009;
const uint16_t hub_reg_pds = 0x300A;
const uint16_t hub_reg_pdb = 0x300B;
const uint16_t hub_reg_mfr_str_index = 0x3013;
const uint16_t hub_reg_prd_str_index = 0x3014;
const uint16_t hub_reg_ser_str_index = 0x3015;
const uint16_t hub_reg_bc = 0x30D0;
const uint16_t hub_reg_start_lockout_timer_reg = 0x30E1;
const uint16_t hub_reg_ocs_min_width = 0x30EA;
const uint16_t hub_reg_ocs_inactive_timer = 0x30EB;
const uint16_t hub_reg_prt_swap = 0x30FA;
const uint16_t hub_reg_usb2_prt_remap_12 = 0x30FB;
const uint16_t hub_reg_usb2_prt_remap_34 = 0x30FC;
const uint16_t hub_reg_usb2_prt_remap_56 = 0x30FD;
const uint16_t hub_reg_usb2_prt_remap_7 = 0x30FE;
const uint16_t hub_reg_hub_cmd_stat = 0x30FF;
const uint16_t hub_reg_usb2_link_state1_3 = 0x3100;
const uint16_t hub_reg_usb2_link_state4_7 = 0x3101;
const uint16_t hub_reg_usb2_hub_ctl = 0x3104;
const uint16_t hub_reg_usb2_bcdusb_msb = 0x3108;
const uint16_t hub_reg_usb2_bcdusb_lsb = 0x3109;
const uint16_t hub_reg_usb2_hub_addr = 0x3150;
const uint16_t hub_reg_usb2_remote_wake = 0x3151;
const uint16_t hub_reg_embed_test = 0x318C;
const uint16_t hub_reg_embed_test_port_sel = 0x318D;
const uint16_t hub_reg_connect_cfg = 0x318E;
const uint16_t hub_reg_usb20_hub_stat = 0x3194;
const uint16_t hub_reg_usb20_hub_dn_dev_type1 = 0x3195;



#endif // hub_h