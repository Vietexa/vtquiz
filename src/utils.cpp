
#include "include/utils.hpp"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_render.h"
#include "include/globals.hpp"
#include <SDL3/SDL_log.h>


void get_mpos_norm(SDL_Renderer* rnd, float *store_pos_x, float * store_pos_y){

    float pos_x_raw;
    float pos_y_raw;

    SDL_GetMouseState(&pos_x_raw, &pos_y_raw); // Get the raw coordinates

    SDL_RenderCoordinatesFromWindow(renderer, pos_x_raw, pos_y_raw, store_pos_x, store_pos_y );


    SDL_Log("%f %f", *store_pos_x, *store_pos_y);

}






 