
#include "include/utils.hpp"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_render.h"
#include "include/globals.hpp"
#include <SDL3/SDL_log.h>


void get_mpos_norm(SDL_Renderer* rnd, float *store_pos_x, float * store_pos_y){

    float pos_x_raw;
    float pos_y_raw;

    float pos_x_norm;
    float pos_y_norm;
    
    SDL_GetMouseState(&pos_x_raw, &pos_y_raw); // Get the raw coordinates
    
    pos_x_norm = pos_x_raw / screen_width;
    pos_y_norm = pos_y_raw / screen_height;

    *store_pos_x = pos_x_norm;
    *store_pos_y = pos_y_norm;

  SDL_Log("%f %f", pos_x_norm, pos_y_norm);

}

void norm_to_raw(float *norm_pos_x, float *norm_pos_y){

 *norm_pos_x *= screen_width;
 *norm_pos_y *= screen_height;


}

void raw_to_norm (float *raw_pos_x, float *raw_pos_y){

 *raw_pos_x /= screen_width;
 *raw_pos_y /= screen_height;


}

float conv_to_norm_x(float raw_value){

    
    return raw_value / screen_width;


}

float conv_to_norm_y(float raw_value){

    
    return raw_value / screen_height;


}

float conv_to_raw_x(float norm_value){

    
    return norm_value * screen_width;


}

float conv_to_raw_y(float norm_value){

    
    return norm_value * screen_height;


}





 