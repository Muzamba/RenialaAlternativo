#include <utility>

#include <utility>

#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"


Sprite::Sprite(GameObject& associated, float frameTime, int frameCount, float secondsToSelfDestuct, Vec2 multi) :   Component(associated),
                                                                                                        texture(nullptr),
                                                                                                        width(0),
                                                                                                        height(0),
                                                                                                        clipRect(),
                                                                                                        scale(1, 1),
                                                                                                        flip(false),
                                                                                                        frameCount(frameCount),
                                                                                                        currentFrame(0),
                                                                                                        timeElapsed(0),
                                                                                                        frameTime(frameTime),
                                                                                                        selfDestructCount(),
                                                                                                        secondsToSelfDestruct(secondsToSelfDestuct),
                                                                                                        multi(multi)
                                                                                                         {
}

Sprite::Sprite(GameObject& associated ,std::string file,int p_x, int p_y, float frameTime, int frameCount, float secondsToSelfDestuct, Vec2 multi) :   Component(associated),
                                                                                                                                            texture(nullptr),
                                                                                                                                            width(0),
                                                                                                                                            height(0),
                                                                                                                                            clipRect(),
                                                                                                                                            scale(1, 1),
                                                                                                                                            flip(false),
                                                                                                                                            frameCount(frameCount),
                                                                                                                                            currentFrame(0),
                                                                                                                                            timeElapsed(0),
                                                                                                                                            frameTime(frameTime),
                                                                                                                                            selfDestructCount(),
                                                                                                                                            secondsToSelfDestruct(secondsToSelfDestuct),
                                                                                                                                            multi(multi)
                                                                                                                                            {
    Open(std::move(file), p_x, p_y);
}

Sprite::~Sprite() = default;

void Sprite::Open(std::string file, int p_x, int p_y) {
    texture = Resources::GetImage(std::move(file));
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    associated.box.size.x = GetWidth() * scale.x;
    associated.box.size.y = GetHeight() * scale.y;
    Vec2 centro = Vec2(p_x, p_y);
    Vec2 ponto = Vec2(centro.x - (associated.box.size.x / 2), centro.y - (associated.box.size.y / 2));
    associated.box.pos = ponto;
    SetClip(0, 0, GetWidth(), GetHeight());
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.h = h;
    clipRect.w = w;
    clipRect.x = x;
    clipRect.y = y;
}

void Sprite::Render() {

    Render(associated.box.pos.x - multi.x * Camera::pos.x, associated.box.pos.y - multi.y * Camera::pos.y);
}

int Sprite::GetHeight() const{

    return height;
}

int Sprite::GetWidth() const{
    return width / frameCount;
}

bool Sprite::IsOpen() const{
    return texture != nullptr;
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::Update(float dt) {
    timeElapsed += dt;
    if(timeElapsed > frameTime) {
        currentFrame++;
        if(currentFrame >= frameCount) {
            currentFrame = 0;
        }
        SetClip(currentFrame * GetWidth(), clipRect.y, GetWidth(),GetHeight());
        timeElapsed = 0;
    }

    if (secondsToSelfDestruct > 0.0f) {
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct) {
            associated.RequestDelete();
        }
    }

}

void Sprite::Render(float x, float y) {
    SDL_Rect dstRect;
    dstRect.x = std::lrint(x);
    dstRect.y = std::lrint(y);
    dstRect.w = std::lrint(clipRect.w * scale.x);
    dstRect.h = std::lrint(clipRect.h * scale.y);
    if(flip) {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.anlgleDeg, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.anlgleDeg, nullptr, SDL_FLIP_NONE);
    }
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) {
        scale.x = scaleX;
    }

    if (scaleY != 0) {
        scale.y = scaleY;
    }

    associated.box.size.x = GetWidth() * scale.x;
    associated.box.size.y = GetHeight() * scale.y;
    Vec2 centro = Vec2(associated.box.pos.x + (GetWidth() / 2.0f), associated.box.pos.y + (GetHeight() / 2.0f));
    Vec2 ponto = Vec2(centro.x - (associated.box.size.x / 2.0f), centro.y - (associated.box.size.y / 2.0f));
    associated.box.pos.x = ponto.x;
    associated.box.pos.y = ponto.y;
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}

void Sprite::SetFrameCount(int frameCount) {
    this->frameCount = frameCount;
    currentFrame = 0;
    timeElapsed = 0;

    associated.box.size.x = GetWidth() * scale.x;
    associated.box.size.y = GetHeight() * scale.y;
    Vec2 centro = associated.box.centro();
    Vec2 ponto = Vec2(centro.x - (associated.box.size.x / 2), centro.y - (associated.box.size.y / 2));
    associated.box.pos = ponto;
    SetClip(0, 0, GetWidth(), GetHeight());

}

void Sprite::SetFrame(int frame) {
    if (frame < frameCount) {
        currentFrame = frame;
        SetClip(currentFrame * GetWidth(), clipRect.y, GetWidth(),GetHeight());
    }
}

void Sprite::SetFlip(bool flip) {
    this->flip = flip;
}

void Sprite::SetAlphaChannel(unsigned int alpha) {

    SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture.get(), alpha);
    
}

void Sprite::SetCamMulti(Vec2 multi) {
    this->multi = multi;
}


