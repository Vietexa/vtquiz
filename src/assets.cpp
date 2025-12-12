#include "include/assets.hpp"

#include "include/state.hpp"




void state::load_assets(){

// Main Menu
add_label("welcome_label",2,1,"Welcome to VTQuiz!", 900, 400);
add_button("play",0,1, "Play", 900, 500);
add_button("credits",0,1, "Credits", 900, 600);
add_button("quit",0,1, "Quit", 900, 700);

// Game
add_texture("background","./assets/png_files/image.png", 0, 2,0,0,0,0,false);
add_texture("marker", "./assets/png_files/s_marker.png", -1, -1,0,0,0,0,false);
add_button("back_menu_g",1,2, "Go Back", 50, 1000);


// Credits
add_label("credits_label", 1, 3, "This game was created by Vietexa and its source code is available on Github under the GPLv3 license.",500, 500);
add_button("github",1,3, "Github", 400, 600);
add_button("vietexadotcom",1,3, "vietexa.com", 800, 600);
add_button("back_menu_c",1,3, "Go Back", 50, 1000);
}