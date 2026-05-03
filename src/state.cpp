#include "include/state.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "include/gui.hpp"
#include "include/globals.hpp"
#include "include/offline_game.hpp"
#include <algorithm>
#include <string>
#include <vector>


std::vector<std::string> raw_element_ids_s0;
std::vector<std::string> raw_element_ids_s1;
std::vector<std::string> raw_element_ids_s2;
std::vector<std::string> raw_element_ids_s3;

void render_main_menu(void);
void render_offline_game(void);
void render_credits(void);


void (*scene_ptr)(void);


void render_marker(){
    
    if(offline_game_handler_ptr->registered_positions[offline_game_handler_ptr->index].x_pos != 0
    && offline_game_handler_ptr->registered_positions[offline_game_handler_ptr->index].y_pos != 0){
    
        float pos_x = 0;
        float pos_y = 0;
        
        pos_x = offline_game_handler_ptr->registered_positions[offline_game_handler_ptr->index].x_pos;
        pos_y = offline_game_handler_ptr->registered_positions[offline_game_handler_ptr->index].y_pos;
    

    float rect_x = pos_x - 25; // draw it in the middle
    float rect_y = pos_y - 25;
    
    
    SDL_FRect rect = {rect_x ,rect_y ,50,50};
    SDL_RenderTexture(renderer, textures.at("marker").m_texture, nullptr, &rect);
    }


}

void render_wrong_marker(){
    float x = offline_game_handler_ptr->wrong_answers_q.at(offline_game_handler_ptr->wrong_answer_index).answer_x;
    float y = offline_game_handler_ptr->wrong_answers_q.at(offline_game_handler_ptr->wrong_answer_index).answer_y;

    float width = offline_game_handler_ptr->wrong_answers_q.at(offline_game_handler_ptr->wrong_answer_index).answer_width;
    float height = offline_game_handler_ptr->wrong_answers_q.at(offline_game_handler_ptr->wrong_answer_index).answer_height;

    float inner_w = 50.0f;
    float inner_h = 50.0f;

    float inner_x = x + (width  - inner_w)  / 2.0f;
    float inner_y = y + (height - inner_h) / 2.0f;


    SDL_FRect rect = {inner_x, inner_y ,50,50};
    SDL_RenderTexture(renderer, textures.at("marker").m_texture, nullptr, &rect);
}




// gui function wrappers

void add_button(std::string id, char priority, char scene_id, std::string content, float x, float y, float width, float height ){

 buttons.try_emplace(id, renderer, txt_font, content, x, y, width, height, scene_id, priority);
    if(priority >= 0 && scene_id >= 0){
    std::string element_id = "button|";
    switch(scene_id){
    case main_menu_scene:
    raw_element_ids_s0.push_back(element_id + id);
    break;
    case finish_game_scene: 
    raw_element_ids_s1.push_back(element_id + id);
    break;
    case offline_game_scene: 
    raw_element_ids_s2.push_back(element_id + id);
    break;
    case credits_scene:
     raw_element_ids_s3.push_back(element_id + id);
    break;}
}

}

void add_label(std::string id, char priority, char scene_id, const std::string& content, float x, float y, float width, float height){
    
    // add it to the unordered map with the following params
    labels.try_emplace(id, renderer, txt_font, content, x, y, width, height, scene_id, priority);

    //add it to its designated scene based on scene_id
    if (priority >= 0 && scene_id >= 0){
    std::string element_id = "label|"; //when adding it, also include "label|" as a tag to be used when it gets sorted
    switch(scene_id){
    case main_menu_scene:
    raw_element_ids_s0.push_back(element_id + id);
    break;
    case finish_game_scene: 
    raw_element_ids_s1.push_back(element_id + id);
    break;
    case offline_game_scene: 
    raw_element_ids_s2.push_back(element_id + id);
    break;
    case credits_scene: 
    raw_element_ids_s3.push_back(element_id + id);
    break;}
}
}


void add_texture(std::string id, std::string path, char priority, char scene_id, float x, float y, float height, float width, bool has_destination){


textures.try_emplace(id, path, priority, scene_id, x, y, width, height, has_destination);


if(priority >= 0 && scene_id >= 0){
    std::string element_id = "texture|"; 
    switch(scene_id){
    case main_menu_scene:
    raw_element_ids_s0.push_back(element_id + id);
    break;
    case finish_game_scene: 
    raw_element_ids_s1.push_back(element_id + id);
    break;
    case offline_game_scene: 
    raw_element_ids_s2.push_back(element_id + id);
    break;
    case credits_scene: 
    raw_element_ids_s3.push_back(element_id + id);
    break;}
}
}

void add_rectangle(std::string id, char priority, char scene_id,  float x, float y, float width, float height){
    
    rectangles.try_emplace(id, priority, scene_id, x, y, width, height);

    if(priority >= 0 && scene_id >= 0){
    std::string element_id = "rectangle|";
    switch(scene_id){
    case main_menu_scene:
    raw_element_ids_s0.push_back(element_id + id);
    break;
    case finish_game_scene: 
    raw_element_ids_s1.push_back(element_id + id);
    break;
    case offline_game_scene: 
    raw_element_ids_s2.push_back(element_id + id);
    break;
    case credits_scene: 
    raw_element_ids_s3.push_back(element_id + id);
    break;}
}
}

//Sort each item by priority
void state::sort_items() { 
    
 auto compare_elements = [&](const std::string& a, const std::string& b) -> bool {
        
std::string a_element_id = a.substr(0,a.find("|"));
std::string b_element_id = b.substr(0,b.find("|"));

std::string a_id = a.substr(a.find("|") + 1);
std::string b_id = b.substr(b.find("|") + 1);


int a_priority = 0;
int b_priority = 0;

if (a_element_id == "button"){
const Button& A = buttons.at(a_id);
a_priority = A.m_priority;
}
else if(a_element_id == "label"){
const Label& A = labels.at(a_id);
a_priority = A.m_priority;
}
else if (a_element_id == "texture") {
const Texture& A = textures.at(a_id);
a_priority = A.m_priority;
}
else if (a_element_id == "rectangle") {
const Rectangle& A = rectangles.at(a_id);
a_priority = A.m_priority;
}
else {return false;}

 
if (b_element_id == "button"){
const Button& B = buttons.at(b_id);
b_priority = B.m_priority;
}
else if(b_element_id == "label"){
const Label& B = labels.at(b_id);
b_priority = B.m_priority;
}
else if (b_element_id == "texture") {
const Texture& B = textures.at(b_id);
b_priority = B.m_priority;
}
else if (b_element_id == "rectangle") {
const Rectangle& B = rectangles.at(b_id);
b_priority = B.m_priority;
}
else {return false;}

return a_priority < b_priority;

 };

//sorth each scene with the logic from the lambda function (compare_elements)
if (!raw_element_ids_s0.empty()){
std::sort(raw_element_ids_s0.begin(), raw_element_ids_s0.end(), compare_elements);
}

if (!raw_element_ids_s1.empty()){
std::sort(raw_element_ids_s1.begin(), raw_element_ids_s1.end(), compare_elements);
}
        
if (!raw_element_ids_s2.empty()){
std::sort(raw_element_ids_s2.begin(), raw_element_ids_s2.end(), compare_elements);
}

if (!raw_element_ids_s3.empty()){
std::sort(raw_element_ids_s3.begin(), raw_element_ids_s3.end(), compare_elements);
}

     
}

// Change the scene id and assign to the function pointer the right function for it
void state::change_scene_id(unsigned char id){

    if (id == current_id){
        SDL_Log("Error: You can't change the game state to the one it's already in\n");
        return;
    }
    
    current_id = id;
    
    switch (current_id) {
    case main_menu_scene:
    scene_ptr = render_main_menu;
    break;
    case offline_game_scene:
    scene_ptr = render_offline_game;
    break;
    case credits_scene:
    scene_ptr = render_credits;
    break;
    default:
    SDL_Log("Error: The scene id doesn't exist\n");
    break;
    }
    
   
}

void render_results_subscene(){
    SDL_RenderTexture(renderer,offline_game_handler_ptr->wrong_answer_textures[offline_game_handler_ptr->wrong_answer_index],NULL,&offline_game_handler_ptr->texture_dst);
    
    for (const std::string& element : raw_element_ids_s2) {
        std::string element_id = element.substr(0, element.find("|"));
        std::string id = element.substr(element.find("|") + 1);
        if (element_id == "button") buttons.at(id).draw();
        else if (element_id == "label") labels.at(id).draw();
        else if (element_id == "rectangle") rectangles.at(id).draw_border(0,0,0,255);
        else if (element_id == "texture") textures.at(id).draw();
    }
    render_wrong_marker();
    


}

void render_select_quiz_scene(){
    std::string btn_name = "quiz_button_";

    for (int i = 0; i < app_context_ptr->total_quizes; i++){
        buttons.at(btn_name + std::to_string(i)).draw();
    }
    buttons.at("back_menu").draw();

}

void render_game_scene(){

    SDL_RenderTexture(renderer,offline_game_handler_ptr->background_textures[offline_game_handler_ptr->index],NULL,&offline_game_handler_ptr->texture_dst);
    for (const std::string& element : raw_element_ids_s2) {
        std::string element_id = element.substr(0, element.find("|"));
        std::string id = element.substr(element.find("|") + 1);
        if (element_id == "button") buttons.at(id).draw();
        else if (element_id == "label") labels.at(id).draw();
        else if (element_id == "rectangle") rectangles.at(id).draw_border(0,0,0,255);
        else if (element_id == "texture") textures.at(id).draw();
    }

    render_marker();
    offline_game_handler_ptr->draw_debug_rect();
}

void render_final_score_scene(){

buttons.at("back_menu").draw();

//only display the button if the player got something wrong
if (offline_game_handler_ptr->wrong_answers != 0){
buttons.at("show_results").draw();
}
labels.at("display_score").draw();
// only display that message if the player got something wrong
if (offline_game_handler_ptr->wrong_answers != 0){
labels.at("final_info").draw();
}

}




// call the function pointer to render the scene
void state::render_scene(){ 
scene_ptr();
 }


// Render the scenes
void render_main_menu(){

SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);

// i know, it's redundant, this is certainly not the best design
for (const std::string& element : raw_element_ids_s0) {
    std::string element_id = element.substr(0, element.find("|"));
    std::string id = element.substr(element.find("|") + 1);
    if (element_id == "button") buttons.at(id).draw();
    else if (element_id == "label") labels.at(id).draw();
    else if (element_id == "rectangle") rectangles.at(id).draw_border(0,0,0,255);
    else if (element_id == "texture") textures.at(id).draw();
    
    }
 
SDL_RenderPresent(renderer);
}




void render_offline_game(){

SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);

switch (offline_game_handler_ptr->current_subscene){

    case offline_game_handler::select_quiz_subscene:
    render_select_quiz_scene();
    break;
    case offline_game_handler::game_subscene:
    render_game_scene();
    break;
    case offline_game_handler::final_menu_subscene:
    render_final_score_scene();
    break;
    case offline_game_handler::results_subscene:
    render_results_subscene();
    break;

}
    

SDL_RenderPresent(renderer);

 }

 

 void render_credits(){
SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);

for (const std::string& element : raw_element_ids_s3) {
    std::string element_id = element.substr(0, element.find("|"));
    std::string id = element.substr(element.find("|") + 1);
    if (element_id == "button") buttons.at(id).draw();
    else if (element_id == "label") labels.at(id).draw();
    else if (element_id == "rectangle") rectangles.at(id).draw_border(0,0,0,255);
    else if (element_id == "texture") textures.at(id).draw();
    }

SDL_RenderPresent(renderer);

 }

 





