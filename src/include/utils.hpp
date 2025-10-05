
#pragma once

#include "SDL3/SDL_render.h"


struct HotRect{
float x,y,w,h;
}; 



extern void get_mpos(SDL_Renderer* rnd, float& u, float& v);
bool hit_rect_norm(float u, float v, HotRect r);


