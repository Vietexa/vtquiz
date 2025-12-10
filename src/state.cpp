#include "include/state.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "include/utils.hpp"
#include "include/gui.hpp"
#include "include/globals.hpp"
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>


std::vector<std::string> raw_element_ids_s1;
std::vector<std::string> raw_element_ids_s2;
std::vector<std::string> raw_element_ids_s3;

std::vector<std::string> button_ids_s1;
std::vector<std::string> button_ids_s2;
std::vector<std::string> button_ids_s3;

void render_main_menu(void);
void render_game(void);
void render_credits(void);


void (*scene_ptr[4])(void){
render_main_menu,
render_game,
render_credits
};



void render_marker(){

    float rect_x, rect_y; // the pos of the marker
    float rect_w, rect_h ; // its width and height
    rect_w = rect_h = 50;

    float raw_pos_x = state_ptr->mouse_pos_x;
    float raw_pos_y =state_ptr-> mouse_pos_y;

    norm_to_raw(&raw_pos_x, &raw_pos_y);

    rect_x = raw_pos_x -  rect_w / 2; // draw it in the middle
    rect_y = raw_pos_y - rect_h / 2;


    
    SDL_FRect rect = {rect_x ,rect_y ,rect_w,rect_h};
    SDL_RenderTexture(renderer,textures.at("marker").m_texture, NULL, &rect);

}



// function wrappers
void add_button(std::string id, char priority, char scene_id, std::string content, float x, float y ){

 float raw_pos_x = conv_to_raw_x(x);
 float raw_pos_y = conv_to_raw_y(y);

 buttons.try_emplace(id, renderer, txt_font, content, raw_pos_x, raw_pos_y, 200, 60, scene_id, priority);
if(priority >= 0 && scene_id >= 0){
std::string element_id = "button|";
    switch(scene_id){
    case 1: 
    raw_element_ids_s1.push_back(element_id + id);
    button_ids_s1.push_back(id);
    break;
    case 2: 
    raw_element_ids_s2.push_back(element_id + id);
    button_ids_s2.push_back(id);
    break;
    case 3: raw_element_ids_s3.push_back(element_id + id);
    button_ids_s3.push_back(id);
    break;}
}

}

void add_label(std::string label_id, char priority, char scene_id, const std::string& content, float x, float y){
    
    float raw_pos_x = conv_to_raw_x(x);
    float raw_pos_y = conv_to_raw_y(y);

    labels.try_emplace(label_id, renderer, txt_font, content, raw_pos_x, raw_pos_y, scene_id, priority);

if(priority >= 0 && scene_id >= 0){
    std::string element_id = "label|";
    switch(scene_id){
    case 1: raw_element_ids_s1.push_back(element_id + label_id);
    break;
    case 2: raw_element_ids_s2.push_back(element_id + label_id);
    break;
    case 3: raw_element_ids_s3.push_back(element_id + label_id);
    break;}
}
}

void add_texture(std::string id, std::string path, char priority, char scene_id){

textures.try_emplace(id, path, priority, scene_id);

if(priority >= 0 && scene_id >= 0){
    std::string element_id = "texture|";
    switch(scene_id){
    case 1: raw_element_ids_s1.push_back(element_id + id);
    break;
    case 2: raw_element_ids_s2.push_back(element_id + id);
    break;
    case 3: raw_element_ids_s3.push_back(element_id + id);
    break;}
}
}

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
else {return false;}

return a_priority < b_priority;

 };

    
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


void state::change_scene_id(unsigned char id){ // You change the state 

    if (id == current_id){
        SDL_Log("Error: You can't change the game state to the one it's already in\n");
        return;
    }
    else{ current_id = id;}
   
}

void state::load_assets(){

// Main Menu
add_label("welcome_label",2,1,"Welcome to VTQuiz!", 0.45, 0.38);
add_button("play",0,1, "Play", 0.45, 0.48);
add_button("credits",0,1, "Credits", 0.45, 0.58);
add_button("quit",0,1, "Quit", 0.45, 0.68);

// Game
add_texture("background","./assets/png_files/image.png", 0, 2);
add_texture("marker", "./assets/png_files/s_marker.png", -1, -1);
add_button("back_menu_g",1,2, "Go Back", 0.1, 0.9);


// Credits
add_label("credits_label", 1, 3, "This game was created by Vietexa and its source code is available on Github under the GPLv3 license.",0.1, 0.28);
add_button("github",1,3, "Github", 0.45, 0.38);
add_button("vietexadotcom",1,3, "vietexa.com", 0.45, 0.48);
add_button("back_menu_c",1,3, "Go Back", 0.1, 0.9);
}


void state::render_scene(){ // You render the scene that corresponds to the state
unsigned char s_id = current_id;

scene_ptr[s_id]();

 }


void render_main_menu(){

SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);

for (const std::string& element : raw_element_ids_s1) {
    std::string element_id = element.substr(0, element.find("|"));
    std::string id = element.substr(element.find("|") + 1);
    if (element_id == "button") buttons.at(id).draw();
    else if (element_id == "label") labels.at(id).draw();
    else if (element_id == "texture") SDL_RenderTexture(renderer,textures.at(id).m_texture, NULL, NULL);
    }
 
SDL_RenderPresent(renderer);
}



void render_game(){

SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);


for (const std::string& element : raw_element_ids_s2) {
    std::string element_id = element.substr(0, element.find("|"));
    std::string id = element.substr(element.find("|") + 1);
    if (element_id == "button") buttons.at(id).draw();
    else if (element_id == "label") labels.at(id).draw();
    else if (element_id == "texture") SDL_RenderTexture(renderer,textures.at(id).m_texture, NULL, NULL);
    }

if (state_ptr->mouse_pos_x != 0 && state_ptr->mouse_pos_y != 0) render_marker();

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
    else if (element_id == "texture") SDL_RenderTexture(renderer,textures.at(id).m_texture, NULL, NULL);
    }

SDL_RenderPresent(renderer);

 }
