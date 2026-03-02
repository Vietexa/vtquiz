

#pragma once

#include "SDL3/SDL_rect.h"
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
std::vector <SDL_Texture*> wrong_answer_textures;
std::vector<question> wrong_answers_q;
SDL_FRect texture_dst = {0,80,1920,920};

// the saved mouse position after the logic found in event.cpp
float saved_mouse_pos_x = 0; 

// the saved mouse position after the logic found in event.cpp
float saved_mouse_pos_y = 0;

int index = 0;
int wrong_answer_index = 0;

bool is_round_in_progress = true;
int correct_answers = 0;
int wrong_answers = 0;

enum subscenes{
select_quiz_subscene,
game_subscene,
final_menu_subscene,
results_subscene
};

int current_subscene = 0;

int current_quiz = -1;

float debug_pos_x = 0;
float debug_pos_y = 0;
float debug_width = 50;
float debug_height = 50;
bool debug_mode = false;

SDL_FRect debug_rect;

~offline_game_handler();

void load_game_data();
bool check_answer_pos(int index);
void register_pos();
void draw_debug_rect();
bool toggle_debug();
void show_wrong_answers();

private:


};