
#include "SDL3/SDL_mouse.h"
#include "include/utils.hpp"
#define SDL_MAIN_USE_CALLBACKS 1 


#include "SDL3/SDL_timer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3/SDL_init.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#ifndef _WIN32
#include <X11/X.h>
#endif

#include <string>
#include <unordered_map>

#include "include/globals.hpp"
#include "include/gui.hpp"
#include "include/state.hpp"
#include "include/utils.hpp"
#include "include/event.hpp"



 std::unordered_map<std::string,Texture> textures;
 std::unordered_map<std::string, Button> buttons;
 std::unordered_map<std::string, Label> labels;


 SDL_Window* window = nullptr;
 SDL_Renderer* renderer = nullptr;
 TTF_Font * txt_font = nullptr;
 state* state_ptr = nullptr;

 int window_size_x = 0;
 int window_size_y = 0;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    
    window = SDL_CreateWindow("VTQuiz",1920, 1080, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    
    if (!window) {
        SDL_Log("Couldn't create the window: %s", SDL_GetError());  
        return SDL_APP_FAILURE;    
    }

    SDL_SetWindowFullscreen(window, true);

    renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer){

        SDL_Log("Couldn't create the renderer: %s", SDL_GetError());  
        return SDL_APP_FAILURE;    
    }

    SDL_SetRenderLogicalPresentation(renderer, 1920, 1080,SDL_LOGICAL_PRESENTATION_STRETCH);


    const char *name = SDL_GetRendererName(renderer);

        if (name) {
    SDL_Log("Renderer backend: %s", name);
        }

     if (!TTF_Init()) {
        SDL_Log("Couldn't initialize the TTF %s", SDL_GetError());
        return SDL_APP_FAILURE;
     }

        
     txt_font = TTF_OpenFont("assets/fonts/default.ttf", 24);
     if (!txt_font) {
        SDL_Log("Couldn't load font: %s", SDL_GetError());
        return SDL_APP_FAILURE;

    }


    state_ptr = new state;
    state_ptr->load_assets();
    state_ptr->sort_items();

    state_ptr->change_scene_id(main_menu_scene);


return SDL_APP_CONTINUE; 
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    
   if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
   if(event->button.button == SDL_BUTTON_LEFT) get_mpos_norm(renderer, &state_ptr->mouse_pos_x, &state_ptr->mouse_pos_y); 
   }
    if (check_buttons(event) == 1 ) return SDL_APP_SUCCESS;
    
    if (event->type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) SDL_GetWindowSizeInPixels(window, &window_size_x, &window_size_y);

    return SDL_APP_CONTINUE; 
 }


SDL_AppResult SDL_AppIterate(void *appstate){  
    
  
   state_ptr->render_scene();
   
    SDL_Delay(10);

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
TTF_CloseFont(txt_font);
TTF_Quit();
delete state_ptr;
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);

}
