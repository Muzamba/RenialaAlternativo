#include "Music.h"
#include "Resources.h"


Music::Music() : music(nullptr) {
}


Music::Music(std::string file) : music(nullptr) {
    Open(file);
}

void Music::Play(int times) const{
    if(music == nullptr) {
        std::cout << "Nenhuma musica selecionada para tocar.\n";
        exit(0);
    }
    Mix_PlayMusic(music.get(), times);
}

void Music::Stop(int msToStop) const{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() const{
    if(music != nullptr) {
        return true;
    }
    return false;
}

Music::~Music() {
    Stop(0);
}