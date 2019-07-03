#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <string>
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <memory>
//class Music;


class Music {
public:
    Music();
    Music(std::string file);
    virtual ~Music();

    void Play(int times = -1) const;
    void Stop(int msToStop = 1500) const;
    void Open(std::string file);
    bool IsOpen() const;

private:
    std::shared_ptr<Mix_Music> music;
};

#endif
