#include "include/gui.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <string>

Button::Button(SDL_Renderer* renderer,
               TTF_Font* font,
               const std::string& text,
               float x, float y, float w, float h, char scene_id ,char priority)
    : m_renderer(renderer), m_font(font), m_scene_id(scene_id), m_priority(priority)
{
    m_rect = {x, y, w, h};
    setText(text);
}

Button::~Button() {
    if (m_label) SDL_DestroyTexture(m_label);
}

void Button::draw() const {
    SDL_SetRenderDrawColor(m_renderer, 80, 120, 200, 255);
    SDL_RenderFillRect(m_renderer, &m_rect);

    if (m_label) {
        SDL_FRect dst{
            m_rect.x + (m_rect.w - m_labelW) * 0.5f,
            m_rect.y + (m_rect.h - m_labelH) * 0.5f,
            static_cast<float>(m_labelW),
            static_cast<float>(m_labelH)
        };
        SDL_RenderTexture(m_renderer, m_label, nullptr, &dst);
    }
}

bool Button::wasClicked(const SDL_Event& e) {
    switch (e.type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (e.button.button == SDL_BUTTON_LEFT &&
            contains(e.button.x, e.button.y)) {
            m_pressedInside = true;
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (e.button.button == SDL_BUTTON_LEFT) {
            bool clicked = m_pressedInside && contains(e.button.x, e.button.y);
            m_pressedInside = false;
            return clicked;
        }
        break;

    default: break;
    }
    return false;
}

void Button::setText(const std::string& text) {
    if (m_label) {
        SDL_DestroyTexture(m_label);
        m_label = nullptr;
    }

    SDL_Color white{255,255,255,255};
    SDL_Surface* surf = TTF_RenderText_Blended(m_font, text.c_str() , text.size(), white);
    if (!surf) {
        SDL_Log("TTF_RenderText_Blended failed: %s", SDL_GetError());
        return;
    }

    m_label = SDL_CreateTextureFromSurface(m_renderer, surf);
    if (!m_label) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        SDL_DestroySurface(surf);
        return;
    }
    
    m_labelW = surf->w;
    m_labelH = surf->h;
    SDL_DestroySurface(surf);
}

void Button::setRect(float x, float y, float w, float h) {
    m_rect = {x, y, w, h};
}

const SDL_FRect& Button::rect() const {
    return m_rect;
}

bool Button::contains(float px, float py) const {
float l_pos_x = 0;
float l_pos_y = 0;

SDL_RenderCoordinatesFromWindow(m_renderer, px,py,&l_pos_x, &l_pos_y);


    return l_pos_x >= m_rect.x && l_pos_x <= m_rect.x + m_rect.w &&
           l_pos_y >= m_rect.y && l_pos_y <= m_rect.y + m_rect.h;
}


Label::Label(SDL_Renderer* renderer ,TTF_Font* font, const std::string& text, float x, float y, char scene_id ,char priority)
: m_renderer(renderer), m_font(font), m_scene_id(scene_id), m_priority(priority){
pos_x = x;
pos_y = y;
setText(text);
} 

Label::~Label(){
     if (m_label) SDL_DestroyTexture(m_label);
}


void Label::setText(const std::string& text) {
    if (m_label) {
        SDL_DestroyTexture(m_label);
        m_label = nullptr;
    }

    SDL_Color white{255,255,255,255};
    SDL_Surface* surf = TTF_RenderText_Blended(m_font, text.c_str() , text.size(), white);
    if (!surf) {
        SDL_Log("TTF_RenderText_Blended failed: %s", SDL_GetError());
        return;
    }

    m_label = SDL_CreateTextureFromSurface(m_renderer, surf);
    if (!m_label) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        SDL_DestroySurface(surf);
        return;
    }
 

    m_labelW = surf->w;
    m_labelH = surf->h;
    SDL_DestroySurface(surf);
}

void Label::draw(){

m_rect = {pos_x,pos_y,(float)m_labelW, (float)m_labelH};
SDL_RenderTexture(m_renderer,m_label,nullptr,&m_rect);
}




