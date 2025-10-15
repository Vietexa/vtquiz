#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class Button {
public:
    Button(SDL_Renderer* renderer,
           TTF_Font* font,
           const std::string& text,
           float x, float y, float w, float h, char scene_id ,char priority);

    ~Button();

    char m_scene_id;
    char m_priority;
    
    void draw() const;
    bool wasClicked(const SDL_Event& e);
    void setText(const std::string& text);

    void setRect(float x, float y, float w, float h);
    const SDL_FRect& rect() const;
    
private:
    bool contains(float px, float py) const;

    SDL_Renderer* m_renderer = nullptr; 
    TTF_Font*  m_font  = nullptr;

    SDL_FRect m_rect{};
    SDL_Texture*  m_label = nullptr;
    int m_labelW = 0, m_labelH = 0;

    bool m_pressedInside = false;
};

class Label{
public:

Label(SDL_Renderer* renderer,TTF_Font* font, const std::string& text,float x, float y, char scene_id ,char priority);

~Label();

void setText(const std::string& text);
void draw();

char m_scene_id;
char m_priority;

private:
SDL_Renderer* m_renderer = nullptr; 
TTF_Font*  m_font = nullptr;
SDL_FRect m_rect{};
SDL_Texture*  m_label = nullptr;
int m_labelW = 0, m_labelH = 0;
float pos_x = 0, pos_y = 0;

};

extern std::unordered_map<std::string,SDL_Texture*> textures;
extern std::unordered_map<std::string, Button> buttons;
extern std::unordered_map<std::string, Label> labels;

