#ifndef SPRITE_H
#define SPRITE_H
//class Sprite;

#include <string>
#include <iostream>
#include <cmath>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Timer.h"
#include <memory>


class Sprite : public Component {
public:
    explicit Sprite(GameObject& associated, float frameTime = 1, int frameCount = 1, float secondsToSelfDestuct = 0, Vec2 multi = {1,1});
    Sprite(GameObject& associated, std::string file, int p_x = 0, int p_y = 0, float frameTime = 1, int frameCount = 1, float secondsToSelfDestuct = 0, Vec2 multi = {1,1});
    ~Sprite() override;

    void Open(std::string file, int p_x, int p_y);
    void SetClip(int x, int y, int w, int h);

    void Render() override;
    void Render(float x, float y);
    bool Is(std::string type) override;
    void Update(float dt) override;

    int GetWidth() const;
    int GetHeight() const;

    bool IsOpen() const;

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);

    void SetFlip(bool flip);

    void SetAlphaChannel(unsigned int alpha);
    void SetCamMulti(Vec2 multi);



private:
    std::shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
    bool flip;

    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    Timer selfDestructCount;
    float secondsToSelfDestruct;
    Vec2 multi;
};

#endif