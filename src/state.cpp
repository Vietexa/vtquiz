#include "include/state.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "include/gui.hpp"
#include "include/global.hpp"
#include <algorithm>
#include <string>
#include <vector>


#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080



std::vector<std::string> button_ids_s1;
std::vector<std::string> button_ids_s2;
std::vector<std::string> button_ids_s3;

std::vector<std::string> label_ids_s1;
std::vector<std::string> label_ids_s2;
std::vector<std::string> label_ids_s3;

std::vector<std::string> texture_ids_s1;
std::vector<std::string> texture_ids_s2;
std::vector<std::string> texture_ids_s3;


void state::render_marker(){

    float rect_x, rect_y; // the pos of the marker
    float rect_w, rect_h ; // its width and height
    rect_w = rect_h = 50;

    if (mouse_pos_x < 0 || mouse_pos_y < 0 || mouse_pos_x > WINDOW_SIZE_X || mouse_pos_y > WINDOW_SIZE_Y){ // check boundaries
        mouse_pos_x = 0;
        mouse_pos_y = 0;
        SDL_Log("The area selected exceeds the rendering space. Please select a position within the rendering space.\n");
        return;
    }

    rect_x = mouse_pos_x -  rect_w / 2; // draw it in the middle
    rect_y = mouse_pos_y - rect_h / 2;

    

    SDL_FRect rect = {rect_x ,rect_y ,rect_w,rect_h};
    SDL_RenderTexture(renderer,textures.at("marker").m_texture, NULL, &rect);

}


// function wrappers
void add_button(std::string id, char priority, char scene_id, std::string content, int x, int y ){
buttons.try_emplace(id, renderer, txt_font, content, x, y, 200, 60, scene_id, priority);
if(priority >= 0 && scene_id >= 0){
    switch(scene_id){
    case 1: button_ids_s1.push_back(id);
    break;
    case 2: button_ids_s2.push_back(id);
    break;
    case 3: button_ids_s3.push_back(id);
    break;}
}

}

void add_label(std::string label_id, char priority, char scene_id, const std::string& content, float x, float y){
labels.try_emplace(label_id, renderer, txt_font, content, x, y, scene_id, priority);

if(priority >= 0 && scene_id >= 0){
    switch(scene_id){
    case 1: label_ids_s1.push_back(label_id);
    break;
    case 2: label_ids_s2.push_back(label_id);
    break;
    case 3: label_ids_s3.push_back(label_id);
    break;}
}
}

void add_texture(std::string id, std::string path, char priority, char scene_id){
textures.try_emplace(id, path, priority, scene_id);

if(priority >= 0 && scene_id >= 0){
    switch(scene_id){
    case 1: texture_ids_s1.push_back(id);
    break;
    case 2: texture_ids_s2.push_back(id);
    break;
    case 3: texture_ids_s3.push_back(id);
    break;}
}
}

void state::sort_items() {
    
    auto button_compare = [&](const std::string& a, const std::string& b) -> bool {
        auto it_a = buttons.find(a);
        auto it_b = buttons.find(b);

        const Button& A = it_a->second;
        const Button& B = it_b->second;
        return A.m_priority < B.m_priority;
    };

    
    if (!button_ids_s1.empty())
        std::sort(button_ids_s1.begin(), button_ids_s1.end(), button_compare);

    if (!button_ids_s2.empty())
        std::sort(button_ids_s2.begin(), button_ids_s2.end(), button_compare);

    if (!button_ids_s3.empty())
        std::sort(button_ids_s3.begin(), button_ids_s3.end(), button_compare);

   
    auto label_compare = [&](const std::string& a, const std::string& b) -> bool {
        auto it_a = labels.find(a);
        auto it_b = labels.find(b);
        
        const Label& A = it_a->second;
        const Label& B = it_b->second;
        return A.m_priority < B.m_priority;
    };

    if (!label_ids_s1.empty())
        std::sort(label_ids_s1.begin(), label_ids_s1.end(), label_compare);

    if (!label_ids_s2.empty())
        std::sort(label_ids_s2.begin(), label_ids_s2.end(), label_compare);

    if (!label_ids_s3.empty())
        std::sort(label_ids_s3.begin(), label_ids_s3.end(), label_compare);



auto texture_compare = [&](const std::string& a, const std::string& b) -> bool {
        auto it_a = textures.find(a);
        auto it_b = textures.find(b);

        const Texture& A = it_a->second;
        const Texture& B = it_b->second;
        return A.m_priority < B.m_priority;
    };

    if (!texture_ids_s1.empty())
        std::sort(texture_ids_s1.begin(), texture_ids_s1.end(), button_compare);

    if (!texture_ids_s2.empty())
        std::sort(texture_ids_s2.begin(), texture_ids_s2.end(), button_compare);

    if (!texture_ids_s3.empty())
        std::sort(texture_ids_s3.begin(), texture_ids_s3.end(), button_compare);

        
}


void state::change_scene_id(unsigned char id){ // You change the state 

    if (id == current_id){
        SDL_Log("Error: You can't change the game state to the one it's already in\n");
        return;
    }
    else{ current_id = id;}
   
}

void state::load_assets(){

add_label("TEST",2,1,"Welcome to VTQuiz!", 850, 520);
add_button("play",0,1, "Play", 850, 620);
add_button("credits",0,1, "Credits", 850, 720);
add_button("quit",0,1, "Quit", 850, 820);

add_texture("background","./assets/png_files/image.png", 0, 2);
add_texture("marker", "./assets/png_files/s_marker.png", -1, -1);
add_button("gb_menu",1,2, "Go Back", 100, 1000);
add_label("test_label",2,2,"Did the label get created?", 200, 300);
}


void state::render_scene(){ // You render the scene that corresponds to the state
unsigned char s_id = current_id;

switch (s_id){

case 1: render_main_menu();
break;

case 2: render_game();
break;


case 3: render_credits();
break;
}

 }


void state::render_main_menu(){

    SDL_SetRenderDrawColor(renderer,0,0,0, 255);
    SDL_RenderClear(renderer);

    for (const std::string& button_id : button_ids_s1) {
        auto it = buttons.find(button_id);
        if (it == buttons.end()) {
          SDL_Log("render_scene: missing button id (s1): '%s'", button_id.c_str());
         continue;
        }
     it->second.draw();
    }

    for (const std::string& label_id : label_ids_s1) {
        auto it = labels.find(label_id);
        if (it == labels.end()) {
        SDL_Log("render_scene: missing label id (s1): '%s'", label_id.c_str());
        continue;
        }
    it->second.draw();
    }

    for (const std::string& texture_id : texture_ids_s1) {
        auto it = textures.find(texture_id);
        if (it == textures.end()) {
          SDL_Log("render_scene: missing texture id (s1): '%s'", texture_id.c_str());
         continue;
        }
    SDL_RenderTexture(renderer,textures.at(texture_id).m_texture, NULL, NULL);
    }

SDL_RenderPresent(renderer);

}



 void state::render_game(){

SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);


for (const std::string& texture_id : texture_ids_s2) {
        auto it = textures.find(texture_id);
        if (it == textures.end()) {
          SDL_Log("render_scene: missing texture id (s1): '%s'", texture_id.c_str());
         continue;
        }
    SDL_RenderTexture(renderer,textures.at(texture_id).m_texture, NULL, NULL);
    }

for (const std::string& label_id : label_ids_s2) {
auto it = labels.find(label_id);
if (it == labels.end()) {
SDL_Log("render_scene: missing label id (s2): '%s'", label_id.c_str());
continue;}
it->second.draw();
}

    for (const std::string& button_id : button_ids_s2) {
auto it = buttons.find(button_id);
if (it == buttons.end()) {
SDL_Log("render_scene: missing button id (s2): '%s'", button_id.c_str());
continue;}
it->second.draw();
}

if (mouse_pos_x != 0 && mouse_pos_y != 0) render_marker();

SDL_RenderPresent(renderer);

 }



 void state::render_credits(){
SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);

for (const std::string& button_id : button_ids_s3) {
auto it = buttons.find(button_id);
if (it == buttons.end()) {
SDL_Log("render_scene: missing button id (s3): '%s'", button_id.c_str());
continue;}
it->second.draw();
}

for (const std::string& label_id : label_ids_s3) {
auto it = labels.find(label_id);
if (it == labels.end()) {
SDL_Log("render_scene: missing label id (s3): '%s'", label_id.c_str());
continue;}
it->second.draw();
}

for (const std::string& texture_id : texture_ids_s3) {
        auto it = textures.find(texture_id);
        if (it == textures.end()) {
          SDL_Log("render_scene: missing texture id (s1): '%s'", texture_id.c_str());
         continue;
        }
    SDL_RenderTexture(renderer,textures.at(texture_id).m_texture, NULL, NULL);
    }

SDL_RenderPresent(renderer);

 }
