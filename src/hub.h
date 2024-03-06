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
const uint16_t hub_reg_bc_en = 0x30D0;
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
const uint16_t hub_reg_usb20_hub_dn_dev_type2 = 0x3196;
const uint16_t hub_reg_usb2_susp_ind = 0x3197;
const uint16_t hub_reg_usb3_hub_ctl = 0x3840;
const uint16_t hub_reg_usb3_hub_ctl2 = 0x3841;
const uint16_t hub_reg_usb3_hub_ctl3 = 0x3842;
const uint16_t hub_reg_usb3_vbus_deb_period = 0x3843;
const uint16_t hub_reg_usb3_hub_ctl4 = 0x3844;
const uint16_t hub_reg_usb3_hub_ctl5 = 0x3849;
const uint16_t hub_reg_usb30_hub_stat = 0x3851;
const uint16_t hub_reg_usb30_hub_dn_speed_ind = 0x3852;
const uint16_t hub_reg_disable_usb3p1_dsport = 0x3855;
const uint16_t hub_reg_usb3_susp_ind = 0x3857;
const uint16_t hub_reg_usb3_prt_remap_en = 0x3858;
const uint16_t hub_reg_usb3_prt_remap_p1_p2 = 0x3860;
const uint16_t hub_reg_usb3_prt_remap_p3_p4 = 0x3861;
const uint16_t hub_reg_usb3_prt_remap_p5_p6 = 0x3862;
const uint16_t hub_reg_usb3_prt_remap_p7 = 0x3863;
const uint16_t hub_reg_link_pwr_state1 = 0x3870;
const uint16_t hub_reg_link_pwr_state2 = 0x3874;
const uint16_t hub_reg_pending_hp_max_value_lsb = 0x3878;
const uint16_t hub_reg_pending_hp_max_value_msb = 0x3879;
const uint16_t hub_reg_pm_entry_and_u1_residency_time = 0x387A;
const uint16_t hub_reg_u1_lfps_exit_lsb = 0x387B;
const uint16_t hub_reg_u1_lfps_exit_msb = 0x387C;
const uint16_t hub_reg_pm_lc_time_in_us_lsb = 0x387D;
const uint16_t hub_reg_pm_lc_time_in_us_msb = 0x387E;
const uint16_t hub_reg_usb3_prt_cfg_sel1 = 0x3C00;
const uint16_t hub_reg_usb3_prt_cfg_sel2 = 0x3C04;
const uint16_t hub_reg_usb3_prt_cfg_sel3 = 0x3C08;
const uint16_t hub_reg_usb3_prt_cfg_sel4 = 0x3C0C;
const uint16_t hub_reg_usb3_prt_cfg_sel5 = 0x3C10;
const uint16_t hub_reg_usb3_prt_cfg_sel6 = 0x3C14;
const uint16_t hub_reg_usb3_prt_cfg_sel7 = 0x3C18;
const uint16_t hub_reg_ocs_sel1 = 0x3C20;
const uint16_t hub_reg_ocs_sel2 = 0x3C24;
const uint16_t hub_reg_ocs_sel3 = 0x3C28;
const uint16_t hub_reg_ocs_sel4 = 0x3C2A;
const uint16_t hub_reg_ocs_sel5 = 0x3C30;
const uint16_t hub_reg_ocs_sel6 = 0x3C34;
const uint16_t hub_reg_ocs_sel7 = 0x3C38;
const uint16_t hub_reg_usb3_port_split_en = 0x3C48;
const uint16_t hub_reg_flex_cfg1 = 0x411A;
const uint16_t hub_reg_flex_cfg2 = 0x411B;
const uint16_t hub_reg_runtime_flags2 = 0x411D;
const uint16_t hub_reg_usb2_default_pidm = 0x411E;
const uint16_t hub_reg_usb2_default_pidl = 0x411F;
const uint16_t hub_reg_usb3_default_pidm = 0x4120;
const uint16_t hub_reg_usb3_default_pidl = 0x4121;
const uint16_t hub_reg_hfc_en = 0x4130;
const uint16_t hub_reg_runtime_flags = 0x4134;
const uint16_t hub_reg_bc_vbus_dis_time = 0x4135;
const uint16_t hub_reg_detatch_timer_a_lsb = 0x413C;
const uint16_t hub_reg_detatch_timer_a_msb = 0x413D;
const uint16_t hub_reg_detatch_timer_b_lsb = 0x413E;
const uint16_t hub_reg_detatch_timer_b_msb = 0x413F;
const uint16_t hub_reg_bb_pf_pin = 0x4142;
const uint16_t hub_reg_otp_lock = 0x414E;
const uint16_t hub_reg_prtpwr1_usb3_split = 0x416A;
const uint16_t hub_reg_prtpwr2_usb3_split = 0x416B;
const uint16_t hub_reg_prtpwr3_usb3_split = 0x416C;
const uint16_t hub_reg_prtpwr4_usb3_split = 0x416D;
const uint16_t hub_reg_prtpwr5_usb3_split = 0x416E;
const uint16_t hub_reg_prtpwr6_usb3_split = 0x416F;
const uint16_t hub_reg_prtpwr7_usb3_split = 0x4170;
const uint16_t hub_reg_usb3_port_split_timeout = 0x4171;
const uint16_t hub_reg_bc_cdp2sdp_dis_time = 0x4175;
const uint16_t hub_reg_usb3_port_split_toggle_time = 0x4176;
const uint16_t hub_reg_bc_cfg_p1 = 0x4178;
const uint16_t hub_reg_bc_cfg_p2 = 0x4179;
const uint16_t hub_reg_bc_cfg_p3 = 0x417A;
const uint16_t hub_reg_bc_cfg_p4 = 0x417B;
const uint16_t hub_reg_bc_cfg_p5 = 0x417C;
const uint16_t hub_reg_bc_cfg_p6 = 0x417D;
const uint16_t hub_reg_bc_cfg_p7 = 0x417E;
const uint16_t hub_reg_udc_bcd_usb_lsb = 0x42D0;
const uint16_t hub_reg_udc_bcd_usb_msb = 0x41D1;
const uint16_t hub_reg_hfc_vid_lsb = 0x42D6;
const uint16_t hub_reg_hfc_vid_msb = 0x42D7;
const uint16_t hub_reg_hfc_pid_lsb = 0x42D8;
const uint16_t hub_reg_hfc_pid_msb = 0x42D9;
const uint16_t hub_reg_hfc_did_lsb = 0x42DA;
const uint16_t hub_reg_hfc_did_msb = 0x42DB;
const uint16_t hub_reg_usb3_bcd_usb_lsb = 0x4442;
const uint16_t hub_reg_usb3_bcd_usb_msb = 0x4443;
const uint16_t hub_reg_usb3_vid_lsb = 0x4448;
const uint16_t hub_reg_usb3_vid_msb = 0x4449;
const uint16_t hub_reg_usb3_pid_lsb = 0x444A;
const uint16_t hub_reg_usb3_pid_msb = 0x444B;
const uint16_t hub_reg_usb3_did_lsb = 0x444C;
const uint16_t hub_reg_usb3_did_msb = 0x444D;
const uint16_t hub_reg_usb3_nbr_prts = 0x44A2;
const uint16_t hub_reg_usb3_compound = 0x44A3;
const uint16_t hub_reg_usb3_bpwron2pwrgood = 0x44A5;
const uint16_t hub_reg_usb3_nrd = 0x44AA;
const uint16_t hub_reg_ss_p0_afe_test_in4 = 0x6086;
const uint16_t hub_reg_up_rise_fall_adj = 0x60C8;
const uint16_t hub_reg_hs_up_boot = 0x60CA;
const uint16_t hub_reg_hs_up_sense = 0x60CC;
const uint16_t hub_reg_ss_p0_ltssm_state = 0x61C0;
const uint16_t hub_reg_ss_p0_test_pipe_dc = 0x61C1;
const uint16_t hub_reg_ss_p0_test_pipe_tx_pat = 0x61C3;
const uint16_t hub_reg_ss_p0_test_pipe_pipe_ctl_0 = 0x61D0;
const uint16_t hub_reg_ss_p1_afe_test_in4 = 0x6486;
const uint16_t hub_reg_p1_rise_fall_adj = 0x64C8;
const uint16_t hub_reg_hs_p1_boost = 0x64CA;
const uint16_t hub_reg_hs_p1_sense = 0x64CC;
const uint16_t hub_reg_ss_p1_ltssm_state = 0x65C0;
const uint16_t hub_reg_ss_p1_test_pipe_dc = 0x65C1;
const uint16_t hub_reg_ss_p1_test_pipe_tx_pat = 0x65C3;
const uint16_t hub_reg_ss_p1_test_pipe_pipe_ctl_0 = 0x65D0;
const uint16_t hub_reg_ss_p2_afe_test_in4 = 0x6886;
const uint16_t hub_reg_p2_rise_fall_adj = 0x68C8;
const uint16_t hub_reg_hs_p2_boost = 0x68CA;
const uint16_t hub_reg_hs_p2_sense = 0x68CC;
const uint16_t hub_reg_ss_p2_ltssm_state = 0x69C0;
const uint16_t hub_reg_ss_p2_test_pipe_dc = 0x69C1;
const uint16_t hub_reg_ss_p2_test_pipe_tx_pat = 0x69C3;
const uint16_t hub_reg_ss_p2_test_pipe_pipe_ctl_0 = 0x69D0;
const uint16_t hub_reg_ss_p3_afe_test_in4 = 0x6C86;
const uint16_t hub_reg_p3_rise_fall_adj = 0x6CC8;
const uint16_t hub_reg_hs_p3_boost = 0x6CCA;
const uint16_t hub_reg_hs_p3_sense = 0x6CCC;
const uint16_t hub_reg_ss_p3_ltssm_state = 0x6DC0;
const uint16_t hub_reg_ss_p3_test_pipe_dc = 0x6DC1;
const uint16_t hub_reg_ss_p3_test_pipe_tx_pat = 0x6DC3;
const uint16_t hub_reg_ss_p3_test_pipe_pipe_ctl_0 = 0x6DD0;
const uint16_t hub_reg_ss_p4_afe_test_in4 = 0x7086;
const uint16_t hub_reg_p4_rise_fall_adj = 0x70C8;
const uint16_t hub_reg_hs_p4_boost = 0x70CA;
const uint16_t hub_reg_hs_p4_sense = 0x70CC;
const uint16_t hub_reg_ss_p4_ltssm_state = 0x71C0;
const uint16_t hub_reg_ss_p4_test_pipe_dc = 0x71C1;
const uint16_t hub_reg_ss_p4_test_pipe_tx_pat = 0x71C3;
const uint16_t hub_reg_ss_p4_test_pipe_pipe_ctl_0 = 0x71D0;
const uint16_t hub_reg_ss_p5_afe_test_in4 = 0x7486;
const uint16_t hub_reg_p5_rise_fall_adj = 0x74C8;
const uint16_t hub_reg_hs_p5_boost = 0x74CA;
const uint16_t hub_reg_hs_p5_sense = 0x74CC;
const uint16_t hub_reg_ss_p5_ltssm_state = 0x75C0;
const uint16_t hub_reg_ss_p5_test_pipe_dc = 0x75C1;
const uint16_t hub_reg_ss_p5_test_pipe_tx_pat = 0x75C3;
const uint16_t hub_reg_ss_p5_test_pipe_pipe_ctl_0 = 0x75D0;
const uint16_t hub_reg_ss_p6_afe_test_in4 = 0x7886;
const uint16_t hub_reg_p6_rise_fall_adj = 0x78C8;
const uint16_t hub_reg_hs_p6_boost = 0x78CA;
const uint16_t hub_reg_hs_p6_sense = 0x78CC;
const uint16_t hub_reg_ss_p6_ltssm_state = 0x79C0;
const uint16_t hub_reg_ss_p6_test_pipe_dc = 0x79C1;
const uint16_t hub_reg_ss_p6_test_pipe_tx_pat = 0x79C3;
const uint16_t hub_reg_ss_p6_test_pipe_pipe_ctl_0 = 0x79D0;
const uint16_t hub_reg_ss_p7_afe_test_in4 = 0x7C86;
const uint16_t hub_reg_p7_rise_fall_adj = 0x7CC8;
const uint16_t hub_reg_hs_p7_boost = 0x7CCA;
const uint16_t hub_reg_hs_p7_sense = 0x7CCC;
const uint16_t hub_reg_ss_p7_ltssm_state = 0x7DC0;
const uint16_t hub_reg_ss_p7_test_pipe_dc = 0x7DC1;
const uint16_t hub_reg_ss_p7_test_pipe_tx_pat = 0x7DC3;
const uint16_t hub_reg_ss_p7_test_pipe_pipe_ctl_0 = 0x7DD0;

//setup consts 
//time in ms
const uint8_t hub_over_current_lockout_bypas_time = 0x0A;

//fuction defines
void hub_send_reboot();
void hub_send_usb_attach();
void hub_send_usb_attach_with_smbus_active();
void hub_send_command_register_accsess_command();
void hub_send_otp_write();
void hub_send_otp_read();
void hub_init();



#endif // hub_h