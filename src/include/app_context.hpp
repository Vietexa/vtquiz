#pragma once

#include "include/json.hpp"
#include <vector>

struct app_context{

    
nlohmann::json quiz_data_j;

std::vector<nlohmann::json> game_data_vec;

std::string button_name_str = "quiz_button_";

int total_quizes;


};