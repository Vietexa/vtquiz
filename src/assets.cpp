#include "include/assets.hpp"

#include "include/state.hpp"




void state::load_assets(){
const float first_btn_s0_y = 450;

// Main Menu
add_label("welcome_label",2,main_menu_scene,"Welcome to VTQuiz!", 900, first_btn_s0_y);
add_button("play_online",0,main_menu_scene, "Play Online", 900, first_btn_s0_y + 100);
add_button("play_offline",0,main_menu_scene, "Play Offline", 900, first_btn_s0_y + 200);
add_button("credits",0,main_menu_scene, "Credits", 900, first_btn_s0_y + 300);
add_button("quit",0,main_menu_scene, "Quit", 900, first_btn_s0_y + 400);

// Online Game
add_button("back_menu",1,online_game_scene, "Go Back", 50, 1000);


// Offline Game
add_texture("background","./assets/png_files/image.png", 0, offline_game_scene,0,0,0,0,false);
add_texture("marker", "./assets/png_files/s_marker.png", -1, -1,0,0,0,0,false);
add_button("back_menu",1,offline_game_scene, "Go Back", 50, 1000);


// Credits
add_label("credits_label", 1, credits_scene, "This game was created by Vietexa and its source code is available on Github under the GPLv3 license.",500, 500);
add_button("github",1,credits_scene, "Github", 400, 600);
add_button("vietexadotcom",1,credits_scene, "vietexa.com", 800, 600);
add_button("back_menu",1,credits_scene, "Go Back", 50, 1000);
}