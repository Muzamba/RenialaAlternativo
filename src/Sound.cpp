#include <utility>

#include <utility>

#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject& associated) : Component(associated), chunk(nullptr), channel(0) {
}

Sound::Sound(GameObject& associated, std::string file) : Component(associated), chunk(nullptr), channel(0) {
    
    Open(std::move(file));
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk.get(), times - 1);
}

void Sound::Stop() {
    if(chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    chunk = nullptr;
    chunk = Resources::GetSound(std::move(file));
}

Sound::~Sound() {
    if(chunk != nullptr) {
        Stop();
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {
}

void Sound::Render() {
}

bool Sound::Is(std::string file) {
    return file == "Sound";
}

bool Sound::IsPlaying() {
    return !Mix_Playing(channel);
}

float Sound::GetLength() {
    Uint32 points = 0;
    Uint32 frames = 0;
    int freq = 0;
    Uint16 fmt = 0;
    int chans = 0;

    if (!Mix_QuerySpec(&freq, &fmt, &chans))
        return 0;


    points = (chunk->alen / ((fmt & 0xFF) / 8));

    frames = (points / chans);

    return (float)frames / freq;

}
