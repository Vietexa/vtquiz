#include "include/event.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_misc.h"
#include "include/globals.hpp"
#include "include/gui.hpp"
#include "include/state.hpp"


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