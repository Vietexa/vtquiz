

#pragma once

#include <string>
#include <unordered_map>


struct answer_position{
float x_pos;
float y_pos;
float width;
float height;
};

struct registered_position{

float x_pos;
float y_pos;

};

class offline_game_handler{

public:
std::unordered_map<int,answer_position> answers;
std::unordered_map<int, registered_position> registered_positions;
std::unordered_map<int, std::string> questions;

float saved_mouse_pos_x = 0;
float saved_mouse_pos_y = 0;

int index = 0;

bool is_round_in_progress = true;
int correct_answers = 0;
int wrong_answers = 0;



bool check_answer_pos(int index);
void register_pos();

private:


};