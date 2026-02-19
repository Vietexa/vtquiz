#include "include/assets.hpp"
#include "include/state.hpp"



struct VerticalLayout {
    
    int y;
    int step;

    int next() {
        int out = y;
        y += step;
        return out;
    }

    void set_again(int y_pos, int step_counter){
        y = y_pos;
        step = step_counter;
    }
};




void state::load_assets(){

VerticalLayout layout{375, 80};



// Main Menu
add_label("welcome_label",2,main_menu_scene,"Welcome to VTQuiz!", 870, layout.next());
add_label("fps_counter",2,main_menu_scene,"", 1, 1);
add_button("play_online",0,main_menu_scene, "Play Online", 870, layout.next());
add_button("play_offline",0,main_menu_scene, "Play Offline", 870, layout.next());
add_button("credits",0,main_menu_scene, "Credits", 870, layout.next());
add_button("quit",0,main_menu_scene, "Quit", 870, layout.next());

// Online Game

add_button("back_menu",3,online_game_scene, "Go Back", 50, 1020);
add_label("info",2,online_game_scene,"Coming soon!", 1, 1);

// Offline Game
add_label("current_question",2,offline_game_scene,"", 800, 100);
add_label("fps_counter",2,offline_game_scene,"", 1, 1);
add_label("question_index",2,offline_game_scene,"00", 1880, 0);
add_texture("background","./assets/png_files/image.png", 0, offline_game_scene,0,0,0,0,false);
add_texture("marker", "./assets/png_files/s_marker.png", -1, -1,0,0,0,0,false);
add_button("back_menu",3,offline_game_scene, "Main Menu", 50, 1020);
add_button("finish",3,offline_game_scene, "Finish", 1600, 1020);
add_button("continue",3,offline_game_scene, "Continue", 1300, 1020);
add_button("previous_question",3,offline_game_scene, "Previous Question", 1000, 1020);
add_rectangle("border",1,offline_game_scene,0,0,0,0);

// Credits
add_label("fps_counter",2,credits_scene,"", 1, 1);
add_label("credits_label", 1, credits_scene, "This game was created by Vietexa and its source code is available on Github under the GPLv3 license.",500, 400);
add_button("github",1,credits_scene, "Github", 700, 500);
add_button("vietexadotcom",1,credits_scene, "vietexa.com", 1100, 500);
add_button("back_menu",3,credits_scene, "Go Back", 50, 1020);
}