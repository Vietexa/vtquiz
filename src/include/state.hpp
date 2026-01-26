#pragma once
#include <string>

void add_button(std::string id, char priority, char scene_id, std::string content, float x, float y, float width = 250, float height = 50);
void add_label(std::string label_id, char priority, char scene_id, const std::string& content, float x, float y, float width = 1, float height = 1);
void add_texture(std::string id, std::string path, char priority, char scene_id, float x, float y, float height, float width, bool has_destination);
void add_rectangle(std::string id, char priority, char scene_id,  float x, float y, float width, float height);

enum scene_ids{main_menu_scene, online_game_scene, offline_game_scene, credits_scene};



class state{

public:
void load_assets();
void sort_items();
void change_scene_id(unsigned char id);
void render_scene();
unsigned char current_id = -1;
float mouse_pos_x = 0;
float mouse_pos_y = 0;

float mpos_debug_x;
float mpos_debug_y;
float debug_buf_w = 50;
float debug_buf_h = 50;
float debug_rect_w;
float debug_rect_h;
private:
void render_main_menu();
void render_game();
void render_credits();
void render_marker();

};