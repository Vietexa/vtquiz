

#pragma once

#include "SDL3/SDL_render.h"
#include <string>
#include <vector>




struct question {
    std::string question;
    std::string image;
    int answer_x;
    int answer_y;
    int answer_width;
    int answer_height;
};

struct registered_position{

float x_pos;
float y_pos;

};

class offline_game_handler{

public:

std::vector<registered_position> registered_positions;
std::vector <question> questions;
std::vector <SDL_Texture*> background_textures;

float saved_mouse_pos_x = 0;
float saved_mouse_pos_y = 0;

int index = 0;

bool is_round_in_progress = true;
int correct_answers = 0;
int wrong_answers = 0;
int subscene = 0;



void load_game_data();
bool check_answer_pos(int index);
void register_pos();

private:


};