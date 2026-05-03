#include "include/event.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_misc.h"
#include "SDL3/SDL_mouse.h"
#include "include/globals.hpp"
#include "include/gui.hpp"
#include "include/offline_game.hpp"
#include "include/state.hpp"
#include <string>

inline std::string format_index(){
if (offline_game_handler_ptr->index < 10 && offline_game_handler_ptr->index >= 0){
 std::string padding = "0"; 
 return padding + std::to_string(offline_game_handler_ptr->index);
}
else return std::to_string(offline_game_handler_ptr->index);
}

inline std::string format_wrong_index(){
if (offline_game_handler_ptr->wrong_answer_index < 10 && offline_game_handler_ptr->wrong_answer_index >= 0){
 std::string padding = "0"; 
 return padding + std::to_string(offline_game_handler_ptr->wrong_answer_index);
}
else return std::to_string(offline_game_handler_ptr->wrong_answer_index);
}

inline std::string get_current_question(){
 int question_index = offline_game_handler_ptr->index;
 std::string current_question = offline_game_handler_ptr->questions.at(question_index).question;
 return current_question;
}

inline std::string get_current_wrong_question(){
 int question_index = offline_game_handler_ptr->wrong_answer_index;
 std::string current_question = offline_game_handler_ptr->wrong_answers_q.at(question_index).question;
 return current_question;
}


int check_event(SDL_Event *event){
//check if a button was pressed or even if keys were pressed

    
    switch(state_ptr->current_id){

    case main_menu_scene:
       
    if (buttons.at("play_offline").wasClicked(*event)) {
        state_ptr->change_scene_id(offline_game_scene);

        if(!offline_game_handler_ptr){
        offline_game_handler_ptr = new offline_game_handler;
        }
        
        offline_game_handler_ptr->current_subscene = offline_game_handler::select_quiz_subscene;
        

        return 0;
    }

    else if (buttons.at("credits").wasClicked(*event)){
        state_ptr->change_scene_id(credits_scene);
        return 0;
    } 

    else if (buttons.at("quit").wasClicked(*event)){
     return 1;
    } 

    break;

    case finish_game_scene:

    if (buttons.at("back_menu").wasClicked(*event)){ 
    state_ptr->change_scene_id(main_menu_scene);
    delete offline_game_handler_ptr;
    return 0;
    }

    break;
    


    case offline_game_scene:

    if (offline_game_handler_ptr->current_subscene == offline_game_handler::select_quiz_subscene){
    for (int i = 0; i < app_context_ptr->total_quizes; i++){

        if (buttons.at(app_context_ptr->button_name_str + std::to_string(i)).wasClicked(*event)){
        offline_game_handler_ptr->current_quiz = i;

        offline_game_handler_ptr->load_game_data();

        labels.at("current_question").setText(get_current_question());
        offline_game_handler_ptr->current_subscene = offline_game_handler::game_subscene;
        }

    }
}


    if (buttons.at("back_menu").wasClicked(*event)){ 
        labels.at("question_index").setText("00");
        if (offline_game_handler_ptr){
            delete offline_game_handler_ptr;
            offline_game_handler_ptr = nullptr;
        }


    state_ptr->change_scene_id(main_menu_scene);
    return 0;

    }

if (offline_game_handler_ptr->current_subscene == offline_game_handler::game_subscene){


    if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && offline_game_handler_ptr->is_round_in_progress){
            if(event->button.button == SDL_BUTTON_LEFT && state_ptr->mouse_pos_y < 1000 && state_ptr->mouse_pos_y > 80){

            offline_game_handler_ptr->saved_mouse_pos_x = state_ptr->mouse_pos_x;
            offline_game_handler_ptr->saved_mouse_pos_y = state_ptr->mouse_pos_y;

            offline_game_handler_ptr->register_pos();
        }
            else if (event->button.button == SDL_BUTTON_RIGHT && state_ptr->d_mouse_pos_y < 1000 && state_ptr->d_mouse_pos_y > 80){
            offline_game_handler_ptr->debug_pos_x = state_ptr->d_mouse_pos_x;
            offline_game_handler_ptr->debug_pos_y = state_ptr->d_mouse_pos_y;
            SDL_Log("xpos: %f, ypos: %f, width: %f, height: %f\n",offline_game_handler_ptr->debug_pos_x, offline_game_handler_ptr->debug_pos_y, offline_game_handler_ptr->debug_width, offline_game_handler_ptr->debug_height);
        }
    }

    

    if (buttons.at("continue").wasClicked(*event) ){

        if(offline_game_handler_ptr->index + 1 < offline_game_handler_ptr->questions.size()){
            offline_game_handler_ptr->index += 1;
            labels.at("question_index").setText(format_index());
            labels.at("current_question").setText(get_current_question());
        } 
        
     }

    else if (buttons.at("previous_question").wasClicked(*event)){ 
       
        if(offline_game_handler_ptr->index > 0){
            offline_game_handler_ptr->index -= 1;
            labels.at("question_index").setText(format_index());
            labels.at("current_question").setText(get_current_question());
            }      
     
     }

    else if (buttons.at("finish").wasClicked(*event) && offline_game_handler_ptr->is_round_in_progress){ 
        for (int i = 0; i < offline_game_handler_ptr->questions.size(); i++){
            if (i < offline_game_handler_ptr->registered_positions.size()){
                if (offline_game_handler_ptr->check_answer_pos(i)) {
                    offline_game_handler_ptr->correct_answers += 1;
                }
                else{
                    offline_game_handler_ptr->wrong_answers += 1;
                    offline_game_handler_ptr->wrong_answers_q.push_back(offline_game_handler_ptr->questions.at(i));
                    offline_game_handler_ptr->wrong_answer_textures.push_back(offline_game_handler_ptr->background_textures.at(i));
                }
                SDL_Log("Correct answers: %d, Wrong answers: %d",offline_game_handler_ptr->correct_answers, offline_game_handler_ptr->wrong_answers);
                
            }
        }
        offline_game_handler_ptr->is_round_in_progress = false;
        std::string correct_answears_str = std::to_string(offline_game_handler_ptr->correct_answers);
        std::string total_answears_str = std::to_string(offline_game_handler_ptr->registered_positions.size());
        labels.at("display_score").setText("You got " + correct_answears_str + "/" + total_answears_str + " answers right!");
        offline_game_handler_ptr->current_subscene = offline_game_handler::final_menu_subscene;
     }

if (event->type == SDL_EVENT_KEY_DOWN){

    if (event->key.key == SDLK_E) {
    offline_game_handler_ptr->toggle_debug();
    }

    if (offline_game_handler_ptr->debug_mode == true){
        switch (event->key.key){

            case SDLK_W: 
            offline_game_handler_ptr->debug_height += 50;
            break;

            case SDLK_A: 
            offline_game_handler_ptr->debug_width -= 50;
            break;

            case SDLK_S:
            offline_game_handler_ptr->debug_height -= 50;
            break;

            case SDLK_D: 
            offline_game_handler_ptr->debug_width += 50;
            break;
        }
    }
}



}

if (offline_game_handler_ptr->current_subscene == offline_game_handler::final_menu_subscene){
    // only allow this button to be clicked if you're in the right subscene and there's one or more questions wrong
    if (buttons.at("show_results").wasClicked(*event) && offline_game_handler_ptr->wrong_answers != 0){
        labels.at("question_index").setText(format_wrong_index());
        labels.at("current_question").setText(get_current_wrong_question());
        offline_game_handler_ptr->current_subscene = offline_game_handler::results_subscene;
    }
}

if (offline_game_handler_ptr->current_subscene == offline_game_handler::results_subscene){

    if (buttons.at("previous_question").wasClicked(*event)){ 
       
        if(offline_game_handler_ptr->wrong_answer_index > 0){
            offline_game_handler_ptr->wrong_answer_index -= 1;
            labels.at("question_index").setText(format_wrong_index());
            labels.at("current_question").setText(get_current_wrong_question());
            }      
     
     }

    else if (buttons.at("continue").wasClicked(*event) ){

        if(offline_game_handler_ptr->wrong_answer_index + 1 < offline_game_handler_ptr->wrong_answers_q.size()){
            offline_game_handler_ptr->wrong_answer_index += 1;
            labels.at("question_index").setText(format_wrong_index());
            labels.at("current_question").setText(get_current_wrong_question());
        } 
        
     }

    else if(buttons.at("finish").wasClicked(*event)){
        labels.at("question_index").setText("00");
        offline_game_handler_ptr->current_subscene = 0;
        offline_game_handler_ptr->wrong_answer_index = 0;

        if (offline_game_handler_ptr){
            delete offline_game_handler_ptr;
            offline_game_handler_ptr = nullptr;
        }

    state_ptr->change_scene_id(main_menu_scene);
   
    }

    

}


    break;



    case credits_scene:

   if (buttons.at("back_menu").wasClicked(*event)) {state_ptr->change_scene_id(main_menu_scene);
    return 0;
   }
   else if (buttons.at("github").wasClicked(*event)) {
    SDL_OpenURL("https://github.com/Vietexa/vtquiz/");
    return 0;
   }
   else if (buttons.at("vietexadotcom").wasClicked(*event)) {
    SDL_OpenURL("https://vietexa.com/");
   return 0;
   }
   
    break;

    default : return 0;
    
}

return 0;

}