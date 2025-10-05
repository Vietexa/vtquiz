
#include "include/utils.hpp"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_render.h"
#include <string>
#include <SDL3/SDL_log.h>



void get_mpos(SDL_Renderer* rnd, float &u, float &v){


    float mouse_x,mouse_y;
    float outw,outh;
    
    std::string x_str, y_str;

    SDL_GetMouseState(&mouse_x, &mouse_y); // Get the raw coordinates
    SDL_RenderCoordinatesFromWindow(rnd, mouse_x,mouse_y,&u, &v); // Adapt them to their logical size

    x_str = std::to_string(u);
    y_str = std::to_string(v);

    SDL_Log("%s", (x_str + " " + y_str).c_str());

}




 