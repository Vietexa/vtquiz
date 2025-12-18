#include "include/event.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_misc.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_scancode.h"
#include "include/globals.hpp"
#include "include/gui.hpp"
#include "include/state.hpp"
#include "include/utils.hpp"


int check_buttons(SDL_Event *event){

    
    switch(state_ptr->current_id){

    case main_menu_scene:
       
    if (buttons.at("play_online").wasClicked(*event)) {
        state_ptr->change_scene_id(online_game_scene);
        return 0;
    }

    if (buttons.at("play_offline").wasClicked(*event)) {
        state_ptr->change_scene_id(offline_game_scene);
        return 0;
    }

    if (buttons.at("credits").wasClicked(*event)){
        state_ptr->change_scene_id(credits_scene);
        return 0;
    } 

    if (buttons.at("quit").wasClicked(*event)){
     return 1;
    } 

    break;

    case online_game_scene:

    if (buttons.at("back_menu").wasClicked(*event)){ 
    state_ptr->change_scene_id(main_menu_scene);
    return 0;
    }

    break;
    


    case offline_game_scene:


    if (buttons.at("back_menu").wasClicked(*event)){ 
    state_ptr->change_scene_id(main_menu_scene);
    return 0;
    }

    if(event->type == SDL_EVENT_KEY_DOWN){
        if (event->key.scancode == SDL_SCANCODE_W){
            state_ptr->debug_rect_h += 50;
            state_ptr->debug_rect_w += 50;
            // SDL_Log("The size has been increased. Current size: w:%f h:%f\n", state_ptr->debug_rect_w, state_ptr->debug_rect_h);
        }
        else if (event->key.scancode == SDL_SCANCODE_S){

            state_ptr->debug_rect_h -= 50;
            state_ptr->debug_rect_w -= 50;
            //SDL_Log("The size has been decreased. Current size: w:%f h:%f\n", state_ptr->debug_rect_w, state_ptr->debug_rect_h);


        }
    }


    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        if (event->button.button == SDL_BUTTON_RIGHT ) {
            get_mpos_norm(renderer, &state_ptr->mpos_debug_x, &state_ptr->mpos_debug_y);
            SDL_Log("x:%f y:%f w:%f h:%f\n", state_ptr->mpos_debug_x, state_ptr->mpos_debug_y , state_ptr->debug_rect_w, state_ptr->debug_rect_h);
        }
    }

    break;



    case credits_scene:

   if (buttons.at("back_menu").wasClicked(*event)) {state_ptr->change_scene_id(main_menu_scene);
    return 0;
   }
   if (buttons.at("github").wasClicked(*event)) {
    SDL_OpenURL("https://github.com/Vietexa/vtquiz/");
    return 0;
   }
   if (buttons.at("vietexadotcom").wasClicked(*event)) {
    SDL_OpenURL("https://vietexa.com/");
   return 0;
   }
   
    break;

    default : return 0;
    
}

return 0;

}