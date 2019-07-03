#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>


struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};


class Resources {
public:
    static  std::shared_ptr<SDL_Texture> GetImage(std::string file);
    static void ClearImages();
    
    static std::shared_ptr<Mix_Music> GetMusic(std::string file);
    static void ClearMusics();

    static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
    static void ClearSounds();

    static std::shared_ptr<TTF_Font> GetFont(std::pair<std::string,int> chave);
    static void ClearFonts();


private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
    static std::unordered_map<std::pair<std::string,int>, std::shared_ptr<TTF_Font>, pair_hash> fontTable;
};



#endif


