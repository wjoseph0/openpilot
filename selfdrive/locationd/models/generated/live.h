#pragma once
#include "rednose/helpers/common_ekf.h"
extern "C" {
void live_update_3(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_19(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_2714802068492241900);
void live_err_fun(double *nom_x, double *delta_x, double *out_96665132751560794);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_2605052904035754317);
void live_H_mod_fun(double *state, double *out_3692718289037827957);
void live_f_fun(double *state, double dt, double *out_7345228907681221007);
void live_F_fun(double *state, double dt, double *out_3833152988937618278);
void live_h_3(double *state, double *unused, double *out_4101132706754811536);
void live_H_3(double *state, double *unused, double *out_2298300243013620082);
void live_h_4(double *state, double *unused, double *out_3127605059410681720);
void live_H_4(double *state, double *unused, double *out_5796093150641478831);
void live_h_9(double *state, double *unused, double *out_5491423035914101298);
void live_H_9(double *state, double *unused, double *out_8118598694512334801);
void live_h_10(double *state, double *unused, double *out_6909327430124214579);
void live_H_10(double *state, double *unused, double *out_1922580938065757629);
void live_h_12(double *state, double *unused, double *out_7908037218373706570);
void live_H_12(double *state, double *unused, double *out_7902648662380688400);
void live_h_31(double *state, double *unused, double *out_3391249270290199279);
void live_H_31(double *state, double *unused, double *out_5227558887237268579);
void live_h_32(double *state, double *unused, double *out_135067325676613068);
void live_H_32(double *state, double *unused, double *out_2882480409415400939);
void live_h_13(double *state, double *unused, double *out_1457322929581671174);
void live_H_13(double *state, double *unused, double *out_8551933550931122823);
void live_h_14(double *state, double *unused, double *out_5491423035914101298);
void live_H_14(double *state, double *unused, double *out_8118598694512334801);
void live_h_19(double *state, double *unused, double *out_6804508701109221948);
void live_H_19(double *state, double *unused, double *out_5895465528094785634);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}