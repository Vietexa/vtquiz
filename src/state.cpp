#include "include/state.hpp"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "include/gui.hpp"

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080

state::state(SDL_Renderer* renderer,TTF_Font* p_txt_font) : m_renderer(renderer), m_font(p_txt_font){

}


void state::switch_state(unsigned char id){ // You change the state 

    if (id == current_id){
        SDL_Log("Error: You can't change the game state to the one it's already in\n");
        return;
    }
    else{ current_id = id;}
   

}

void state::load_assets(){
labels.try_emplace("greet",m_renderer, m_font, "Welcome to VTQuiz!", 850, 520);
buttons.try_emplace("play", m_renderer, m_font, "Play", 850, 620, 200, 60);
buttons.try_emplace("credits",m_renderer, m_font, "Credits", 850, 720, 200, 60);
buttons.try_emplace("quit", m_renderer, m_font, "Quit", 850, 820, 200, 60);

textures.try_emplace("background",IMG_LoadTexture(m_renderer, "./assets/png_files/image.png"));
textures.try_emplace("marker",IMG_LoadTexture(m_renderer, "./assets/png_files/s_marker.png"));
buttons.try_emplace("gb_menu",m_renderer, m_font, "Go Back", 100, 1000, 200, 60);
labels.try_emplace("test_label",m_renderer, m_font, "Did the label get created?", 200, 300);
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
    SDL_RenderTexture(m_renderer,textures.at("marker"), NULL, &rect);

}


void state::render_main_menu(){
current_id = 1;
SDL_SetRenderDrawColor(m_renderer,0,0,0, 255);
SDL_RenderClear(m_renderer);
labels.at("greet").draw();
buttons.at("play").draw();
buttons.at("credits").draw();
buttons.at("quit").draw();
SDL_RenderPresent(m_renderer);

}

void state::render_game(){
    current_id = 2;
    SDL_SetRenderDrawColor(m_renderer,0,0,0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderTexture(m_renderer,textures["background"], NULL, NULL);
    if (mouse_pos_x != 0 && mouse_pos_y != 0) render_marker();
    buttons.at("gb_menu").draw();
    labels.at("test_label").draw();
    SDL_RenderPresent(m_renderer);
   
}

void state::render_credits(){



}