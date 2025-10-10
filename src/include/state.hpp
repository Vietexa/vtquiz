
class state{

public:
void load_assets();
void change_scene_id(unsigned char id);
void render_scene();
unsigned char current_id = 0;
float mouse_pos_x = 0;
float mouse_pos_y = 0;
private:
void render_main_menu();
void render_game();
void render_credits();
void render_marker();

};