#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <string>
#include "Component.h"
//class Sound;
#include "GameObject.h"
#include <memory>

class Sound : public Component{
public:
    explicit Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);

    ~Sound() override;

    void Play(int times = 1);
    bool IsPlaying();
    void Stop();
    void Open(std::string file);
    bool IsOpen();
    float GetLength();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel;
};

#endif