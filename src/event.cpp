#include "include/event.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_misc.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_scancode.h"
#include "include/globals.hpp"
#include "include/gui.hpp"
#include "include/offline_game.hpp"
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
        offline_game_handler_ptr = new offline_game_handler;
        

        float pos_x = 200;
        float pos_y = 200;

        offline_game_handler_ptr->answers[0] = {500,500,500,500};
    
        for (int i = 1; i < 5; i++){
            offline_game_handler_ptr->answers[i] = {pos_x, pos_y, 200, 200};
            pos_x += 100;
            pos_y += 100;
            SDL_Log("answear coordinates: x: %f y:%f", pos_x, pos_y);
        }

        for (int i = 0; i < offline_game_handler_ptr->answers.size(); i++){

            offline_game_handler_ptr->registered_positions[i] = {0,0};

        }

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
        
        if (offline_game_handler_ptr){
            delete offline_game_handler_ptr;
            offline_game_handler_ptr = nullptr;
        }


    state_ptr->change_scene_id(main_menu_scene);
    return 0;

    }

    
    if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && offline_game_handler_ptr->is_round_in_progress){
        if(event->button.button == SDL_BUTTON_LEFT && state_ptr->mouse_pos_y < 980){

            offline_game_handler_ptr->saved_mouse_pos_x = state_ptr->mouse_pos_x;
            offline_game_handler_ptr->saved_mouse_pos_y = state_ptr->mouse_pos_y;

            offline_game_handler_ptr->register_pos();
        }
    }

     if (buttons.at("continue").wasClicked(*event)){

        if(offline_game_handler_ptr->index < offline_game_handler_ptr->answers.size()){
            offline_game_handler_ptr->index += 1;
            SDL_Log("Index: %d\n", offline_game_handler_ptr->index);
        } 
        
     }

     if (buttons.at("previous_question").wasClicked(*event)){ 
       
        if(offline_game_handler_ptr->index >= 0){
            offline_game_handler_ptr->index -= 1;
            SDL_Log("Index: %d\n", offline_game_handler_ptr->index);
            }      
     
     }

     if (buttons.at("finish").wasClicked(*event) && offline_game_handler_ptr->is_round_in_progress){ 
        for (int i = 0; i < offline_game_handler_ptr->answers.size(); i++){
            if (i <= offline_game_handler_ptr->registered_positions.size()){
                if (offline_game_handler_ptr->check_answer_pos(i)) {
                    offline_game_handler_ptr->correct_answers += 1;
                }
                else{
                    offline_game_handler_ptr->wrong_answers += 1;
                }
                SDL_Log("Correct answers: %d, Wrong answers: %d",offline_game_handler_ptr->correct_answers, offline_game_handler_ptr->wrong_answers);
                
            }
        }
        offline_game_handler_ptr->is_round_in_progress = false;
     }

    if(event->type == SDL_EVENT_KEY_DOWN){

        switch(event->key.scancode){

            case SDL_SCANCODE_W:
            state_ptr->debug_buf_h += 50;
            break;

            case SDL_SCANCODE_S:
            state_ptr->debug_buf_h -= 50;
            break;

            case SDL_SCANCODE_A:
            state_ptr->debug_buf_w += 50;
            break;

            case SDL_SCANCODE_D:
            state_ptr->debug_buf_w -= 50;
            break;

            default: break;
        }

        
    }


    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        if (event->button.button == SDL_BUTTON_RIGHT ) {
            get_mpos_norm(renderer, &state_ptr->mpos_debug_x, &state_ptr->mpos_debug_y);
            SDL_Log("x:%f y:%f w:%f h:%f\n", state_ptr->mpos_debug_x, state_ptr->mpos_debug_y , state_ptr->debug_rect_w, state_ptr->debug_rect_h);
            state_ptr->debug_rect_w = state_ptr->debug_buf_w;
            state_ptr->debug_rect_h = state_ptr->debug_buf_h;
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