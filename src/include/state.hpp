
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"

class state{

public:
state(SDL_Renderer* renderer, TTF_Font* font);
void load_assets();
void switch_state(unsigned char id);
void render_scene();
unsigned char current_id = 0;
float mouse_pos_x = 0;
float mouse_pos_y = 0;
private:
void render_main_menu();
void render_game();
void render_credits();
void render_marker();
SDL_Renderer* m_renderer;
TTF_Font* m_font;

};