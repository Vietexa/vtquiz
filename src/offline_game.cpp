#include "include/offline_game.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3_image/SDL_image.h"
#include "include/globals.hpp"
#include "include/state.hpp"



//Offline game scene logic

void offline_game_handler::load_game_data(){
    questions.clear();
    registered_positions.clear();
    int loop_index;
    std::string texture_default_n = "texture_";
    for (const auto& item : app_context_ptr->game_data_j["questions"]) {
        question q;
        q.question = item.value("question", "");
        q.image = item.value("image", "");
        q.answer_x = item.value("answer_x", 0);
        q.answer_y = item.value("answer_y", 0);
        q.answer_width = item.value("answer_width", 0);
        q.answer_height = item.value("answer_height", 0);

        questions.push_back(q);

        SDL_Texture* texture = IMG_LoadTexture(renderer, q.image.c_str());
        background_textures.push_back(texture);
    }
    
    registered_positions.resize(questions.size(), {0,0});


    state_ptr->sort_items();

    
   /* for (const auto& q : questions) {
        SDL_Log("%s, %s, %d, %d, %d, %d,",q.question.c_str(),q.image.c_str(),q.answer_x, q.answer_y, q.answer_width, q.answer_height);
    } */


}

bool offline_game_handler::check_answer_pos(int index){
    SDL_Log("This is the index: %d", index);
    if (index >= questions.size()){
        SDL_Log("Error: the answear position couldn't be checked because the index exceeds the size of the vector\n");
        return false;
    }

    if (index >= registered_positions.size()){
        SDL_Log("Error: the registered position couldn't be checked because the index exceeds the size of the vector\n");
        return false;
    }

    float registered_pos_x = registered_positions.at(index).x_pos;
    float registered_pos_y = registered_positions.at(index).y_pos;

    float lg_r_pos_x;
    float lg_r_pos_y;

    float ans_x_pos = questions.at(index).answer_x;
    float ans_y_pos = questions.at(index).answer_y;
    float ans_width = questions.at(index).answer_width;
    float ans_height = questions.at(index).answer_height;
    
    SDL_RenderCoordinatesFromWindow(renderer, registered_pos_x , registered_pos_y, &lg_r_pos_x, &lg_r_pos_y);
    
    return lg_r_pos_x >= ans_x_pos && lg_r_pos_x <= ans_x_pos + ans_width &&
           lg_r_pos_y >= ans_y_pos && lg_r_pos_y <= ans_y_pos + ans_height;
   
}

void offline_game_handler::register_pos(){

    if(state_ptr->current_id == offline_game_scene){

        if (index >= registered_positions.size()) return;

        registered_positions[index] = {saved_mouse_pos_x, saved_mouse_pos_y};

    }
       

}