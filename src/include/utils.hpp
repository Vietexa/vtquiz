
#pragma once

#include "SDL3/SDL_render.h"

void get_mpos_norm(SDL_Renderer* rnd, float *store_pos_x, float * store_pos_y);

void norm_to_raw(float *norm_pos_x, float *norm_pos_y);
void raw_to_norm (float *raw_pos_x, float *raw_pos_y);

float conv_to_norm_x(float raw_value);
float conv_to_norm_y(float raw_value);

float conv_to_raw_x(float norm_value);
float conv_to_raw_y(float norm_value);


