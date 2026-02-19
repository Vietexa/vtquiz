
#include "SDL3/SDL_mouse.h"
#include "include/app_context.hpp"
#include "include/json.hpp"
#include "include/utils.hpp"
#include <fstream>

#define SDL_MAIN_USE_CALLBACKS 1 

#include <format>
#include "SDL3/SDL_timer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3/SDL_init.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#ifndef _WIN32
#include <X11/X.h>
#endif

#include <string>
#include <unordered_map>

#include "include/globals.hpp"
#include "include/gui.hpp"
#include "include/state.hpp"
#include "include/utils.hpp"
#include "include/event.hpp"

using json = nlohmann::json;

#define TARGET_FPS 60
#define FRAME_TIME (1000 / TARGET_FPS)

// global variables

// gui element containers
 std::unordered_map<std::string,Texture> textures;
 std::unordered_map<std::string, Button> buttons;
 std::unordered_map<std::string, Label> labels;
 std::unordered_map<std::string, Rectangle> rectangles;
 

 SDL_Window* window = nullptr;
 SDL_Renderer* renderer = nullptr;
 TTF_Font * txt_font = nullptr;
 state* state_ptr = nullptr;
 app_context* app_context_ptr = nullptr;
 offline_game_handler* offline_game_handler_ptr = nullptr;
 

 int window_size_x = 0;
 int window_size_y = 0;

 



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    
    window = SDL_CreateWindow("VTQuiz",1920, 1080, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    
    if (!window) {
        SDL_Log("Couldn't create the window: %s", SDL_GetError());  
        return SDL_APP_FAILURE;    
    }

    SDL_SetWindowFullscreen(window, true);

    renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer){

        SDL_Log("Couldn't create the renderer: %s", SDL_GetError());  
        return SDL_APP_FAILURE;    
    }

    SDL_SetRenderLogicalPresentation(renderer, 1920, 1080,SDL_LOGICAL_PRESENTATION_STRETCH);


    const char *name = SDL_GetRendererName(renderer);

        if (name) {
    SDL_Log("Renderer backend: %s", name);
        }

     if (!TTF_Init()) {
        SDL_Log("Couldn't initialize the TTF %s", SDL_GetError());
        return SDL_APP_FAILURE;
     }

        
     txt_font = TTF_OpenFont("assets/fonts/default.ttf", 24);
     if (!txt_font) {
        SDL_Log("Couldn't load font: %s", SDL_GetError());
        return SDL_APP_FAILURE;

    }

    state_ptr = new state;

    app_context_ptr = new app_context;

    std::ifstream game_data("assets/game_data.json");

    if (!game_data.is_open()){

        SDL_Log("Couldn't open game_data.json\n");
        return SDL_APP_FAILURE;

    }

    app_context_ptr->game_data_j = json::parse(game_data); // parse the file and save it to game_dat_j
    
    state_ptr->load_assets();
    state_ptr->sort_items();

    state_ptr->change_scene_id(main_menu_scene); // make it start at the main menu


return SDL_APP_CONTINUE; 
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    
   if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
   if(event->button.button == SDL_BUTTON_LEFT) get_mpos_norm(renderer, &state_ptr->mouse_pos_x, &state_ptr->mouse_pos_y); 
   }
    if (check_event(event) == 1 ) return SDL_APP_SUCCESS;
    
    if (event->type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) SDL_GetWindowSizeInPixels(window, &window_size_x, &window_size_y);

    return SDL_APP_CONTINUE; 
 }


SDL_AppResult SDL_AppIterate(void *appstate){  
   
    Uint32 frameStart;
    Uint32 frameTime;

    static Uint32 lastFpsTime = 0;
    static int frames = 0;
    static float fps = 0.0f;

    frameStart = SDL_GetTicks();
    

    state_ptr->render_scene();


    Uint32 now = SDL_GetTicks();

     frames++;
  
if (now - lastFpsTime >= 1000) {
    fps = frames * 1000.0f / (now - lastFpsTime);
    frames = 0;
    lastFpsTime = now;

    std::string fpsStr = std::format("{:.2f}", fps);

    labels.at("fps_counter").setText(fpsStr);
}

    frameTime = SDL_GetTicks() - frameStart;

    if (frameTime < FRAME_TIME) {
        SDL_Delay(FRAME_TIME - frameTime);
    }

    

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
    TTF_CloseFont(txt_font);
    TTF_Quit();
    delete state_ptr;
    delete app_context_ptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
