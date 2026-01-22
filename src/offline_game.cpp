#include "include/offline_game.hpp"
#include "SDL3/SDL_log.h"
#include "include/globals.hpp"
#include "include/state.hpp"
#include <strings.h>



bool offline_game_handler::check_answer_pos(int index){
    SDL_Log("This is the index: %d", index);
    if (index > answers.size()){
        SDL_Log("Error: the answear position couldn't be checked because the index exceeds the size of the vector\n");
        return false;
    }

    if (index > registered_positions.size()){
        SDL_Log("Error: the registered position couldn't be checked because the index exceeds the size of the vector\n");
        return false;
    }

    float registered_pos_x = registered_positions.at(index).x_pos;
    float registered_pos_y = registered_positions.at(index).y_pos;

    float lg_r_pos_x;
    float lg_r_pos_y;

    float ans_x_pos = answers.at(index).x_pos;
    float ans_y_pos = answers.at(index).y_pos;
    float ans_width = answers.at(index).width;
    float ans_height = answers.at(index).height;
    
    SDL_RenderCoordinatesFromWindow(renderer, registered_pos_x , registered_pos_y, &lg_r_pos_x, &lg_r_pos_y);
    
    return lg_r_pos_x >= ans_x_pos && lg_r_pos_x <= ans_x_pos + ans_width &&
           lg_r_pos_y >= ans_y_pos && lg_r_pos_y <= lg_r_pos_y + ans_height;
   
}

void offline_game_handler::register_pos(){

    if(state_ptr->current_id == offline_game_scene){

        if (index > registered_positions.size()) return;

        registered_positions[index] = {saved_mouse_pos_x, saved_mouse_pos_y};

    }
       

}