#include "Text.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"



Text::Text(GameObject &associated, std::string fontFile, int fontSize, Text::TextStyle style, std::string text,
           SDL_Color color) :   Component(associated), font(nullptr), fontFile(fontFile), fontSize(fontSize),
                                style(style), text(text), color(color), texture(nullptr) {
    RemakeTexture();

}

Text::~Text() {
    if(texture) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {

}

void Text::Render() {
    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = associated.box.size.x;
    clipRect.h = associated.box.size.y;

    SDL_Rect dstRect;
    dstRect.x = associated.box.pos.x - Camera::pos.x;
    dstRect.y = associated.box.pos.y - Camera::pos.y;
    dstRect.w = associated.box.size.x;
    dstRect.h = associated.box.size.y;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.anlgleDeg, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(std::string type) {
    return type == "Text";
}

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(Text::TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFile(std::string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if(texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    int w = 0;
    int h = 0;
    SDL_Surface* surface = nullptr;
    font = Resources::GetFont({fontFile, fontSize});

    switch (style) {
        case SOLID:
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);

            texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            associated.box.size = {w,h};
            SDL_FreeSurface(surface);
            break;


        case SHADED:
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0,0,0,0});
            texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            associated.box.size = {w,h};
            SDL_FreeSurface(surface);
            break;

        case BLENDED:
            surface = TTF_RenderText_Blended(font.get(),text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            associated.box.size = {w,h};
            SDL_FreeSurface(surface);
            break;

        default:
            break;
    }


}
