#include "include/state.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3_image/SDL_image.h"
#include "include/gui.hpp"
#include "include/global.hpp"


#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080


// function wrappers
void add_button(std::string id, std::string content, int x, int y ){
buttons.try_emplace(id, renderer, txt_font, content, x, y, 200, 60);
}

void add_button(std::string id, std::string content, int x, int y, int width, int height){
buttons.try_emplace(id, renderer, txt_font, content, x, y, width, height);
}

void add_label(std::string id, std::string content, int x, int y ){
labels.try_emplace(id, renderer, txt_font, content,x, y);
}

void add_texture(std::string id, std::string path){
textures.try_emplace(id, IMG_LoadTexture(renderer,path.c_str()));
}




void state::change_scene_id(unsigned char id){ // You change the state 

    if (id == current_id){
        SDL_Log("Error: You can't change the game state to the one it's already in\n");
        return;
    }
    else{ current_id = id;}
   

}

void state::load_assets(){

add_label("greet","Welcome to VTQuiz!", 850, 520);
add_button("play", "Play", 850, 620);
add_button("credits", "Credits", 850, 720);
add_button("quit", "Quit", 850, 820);

add_texture("background","./assets/png_files/image.png");
add_texture("marker", "./assets/png_files/s_marker.png");
add_button("gb_menu", "Go Back", 100, 1000);
add_label("test_label","Did the label get created?", 200, 300);
}





void state::render_scene(){ // You render the scene that corresponds to the state
unsigned char s_id = current_id;

switch(s_id){
    case 0: 
    SDL_Log("Warning: ID = 0 doesn't have any scene");
    break;
    case 1:
    render_main_menu();
    break;
    case 2:
    render_game();
    break;
    case 3:
    render_credits();
    break;
    default:  SDL_Log("Error: Invalid ID. There is no scene with the ID specified\n");
    break;
    }

}


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
    SDL_RenderTexture(renderer,textures.at("marker"), NULL, &rect);

}


void state::render_main_menu(){
SDL_SetRenderDrawColor(renderer,0,0,0, 255);
SDL_RenderClear(renderer);
labels.at("greet").draw();
buttons.at("play").draw();
buttons.at("credits").draw();
buttons.at("quit").draw();
SDL_RenderPresent(renderer);

}

void state::render_game(){
    SDL_SetRenderDrawColor(renderer,0,0,0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer,textures["background"], NULL, NULL);
    if (mouse_pos_x != 0 && mouse_pos_y != 0) render_marker();
    buttons.at("gb_menu").draw();
    labels.at("test_label").draw();
    SDL_RenderPresent(renderer);
   
}

void state::render_credits(){



}