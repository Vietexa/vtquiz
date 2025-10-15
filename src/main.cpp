

#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_timer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <string>
#include <unordered_map>
#ifdef unix
#include <X11/X.h>
#endif

#define SDL_MAIN_USE_CALLBACKS 1 


#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include "include/gui.hpp"
#include "include/state.hpp"
#include "include/utils.hpp"


 std::unordered_map<std::string,SDL_Texture*> textures;
 std::unordered_map<std::string, Button> buttons;
 std::unordered_map<std::string, Label> labels;


 SDL_Window* window = nullptr;
 SDL_Renderer* renderer = nullptr;
 TTF_Font * txt_font = nullptr;
 state* state_ptr = nullptr;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    #ifdef unix
    setenv("SDL_VIDEODRIVER", "x11", 1);
    #endif

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("VTQuiz",1920, 1080, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, "opengl");

    if (!window || !renderer) {
        SDL_Log("Couldn't create the window or the renderer: %s", SDL_GetError());
        SDL_Log("Attempting to use software rendering as fallback...\n");
        renderer = SDL_CreateRenderer(window, "software");
    if (!window || !renderer){
    SDL_Log("Attempt 2: Couldn't create the window or the renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
    }
        
    }

    SDL_SetRenderLogicalPresentation(renderer,1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);
 
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

state_ptr->change_scene_id(1);


return SDL_APP_CONTINUE; 
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    SDL_Keycode key = event->key.key;

    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT) 
    get_mpos(renderer, state_ptr->mouse_pos_x, state_ptr->mouse_pos_y);
   
    if(state_ptr->current_id == 1){
        if (buttons.at("play").wasClicked(*event)) {
        state_ptr->mouse_pos_x = 0;
        state_ptr->mouse_pos_y = 0;
        SDL_Log("Button was clicked!");
        state_ptr->change_scene_id(2);
                 } 

    if (buttons.at("quit").wasClicked(*event)){
    return SDL_APP_SUCCESS;
    }

                }
    
if (state_ptr->current_id == 2){
        if (buttons.at("gb_menu").wasClicked(*event)) {
        state_ptr->mouse_pos_x = 0;
        state_ptr->mouse_pos_y = 0;
        SDL_Log("Button was clicked!");
        state_ptr->change_scene_id(1);
                 } 

                }
       

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
