#include "Resources.h"
#include "Game.h"
std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::pair<std::string,int>, std::shared_ptr<TTF_Font>, pair_hash> Resources::fontTable;
std::unordered_map<std::string,std::shared_ptr<TileSet>> Resources::tileSetTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    auto temp = Resources::imageTable.find(file);
    if(temp == Resources::imageTable.end()) {
        SDL_Texture* texture = nullptr;
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer() , file.c_str());
        if(texture == nullptr) {
            std::cout << "Erro ao carregar imagem: " << file <<"\n";
            std::cout << SDL_GetError() << "\n";
            return nullptr;
        }
        auto tex = std::shared_ptr<SDL_Texture>(texture,[](SDL_Texture* tex){ SDL_DestroyTexture(tex);});
        Resources::imageTable.insert({file, tex});
        return tex;
    } else {
        return temp->second;
    }
}

void Resources::ClearImages() {

    for(auto it = imageTable.begin();it != imageTable.end();) {
        if((*it).second.unique()) {

            imageTable.erase(it);
            it = imageTable.begin();

        } else {
            it++;
        }

    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {

    auto temp = Resources::musicTable.find(file);
    if(temp == Resources::musicTable.end()) {
        Mix_Music* music = nullptr;
        music = Mix_LoadMUS(file.c_str());
        if(music == nullptr) {
        std::cout << "Falha ao abrir a musica: " << file << "\n";
        std::cout << SDL_GetError() << "\n";
        return nullptr;
        }
        auto mus = std::shared_ptr<Mix_Music>(music, [](Mix_Music* mus){ Mix_FreeMusic(mus);});
        Resources::musicTable.insert({file, mus});
        return mus;
    } else {
        return temp->second;
    }
}

void Resources::ClearMusics() {
    for(auto it = musicTable.begin();it != musicTable.end();) {
        if((*it).second.unique()) {

            musicTable.erase(it);
            it = musicTable.begin();

        } else {
            it++;
        }

    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {

    auto temp = Resources::soundTable.find(file);
    if(temp == Resources::soundTable.end()) {
        Mix_Chunk* sound = nullptr;
        sound = Mix_LoadWAV(file.c_str());
        if(sound == nullptr) {
        std::cout << "Falha ao abrir o som: " << file << "\n";
        std::cout << SDL_GetError() << "\n";
        return nullptr;
        }
        auto sou = std::shared_ptr<Mix_Chunk>(sound,[](Mix_Chunk* sou){ Mix_FreeChunk(sou);});
        Resources::soundTable.insert({file, sou});
        return sou;
    } else {
        return temp->second;
    }
}

void Resources::ClearSounds() {
    for(auto it = soundTable.begin();it != soundTable.end();) {
        if((*it).second.unique()) {
            soundTable.erase(it);
            it = soundTable.begin();
        } else {
            it++;
        }
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::pair<std::string,int> key) {
    auto temp = Resources::fontTable.find(key);
    if(temp == Resources::fontTable.end()) {
        TTF_Font* font = nullptr;
        font = TTF_OpenFont(key.first.c_str(), key.second);
        if(font == nullptr) {
            std::cout << "Erro ao carregar font: " << key.first <<"\n";
            std::cout << TTF_GetError() << "\n";
            return nullptr;
        }
        auto fon = std::shared_ptr<TTF_Font>(font,[](TTF_Font* font){ TTF_CloseFont(font);});
        Resources::fontTable[key] = fon;
        return fon;
    } else {
        return temp->second;
    }
}

void Resources::ClearFonts() {
    for(auto it = fontTable.begin();it != fontTable.end();) {
        if((*it).second.unique()) {
            fontTable.erase(it);
            it = fontTable.begin();
        } else {
            it++;
        }
    }
}


std::shared_ptr<TileSet> Resources::GetTileSet(std::string file) {
    auto temp = Resources::tileSetTable.find(file);
    if(temp == Resources::tileSetTable.end()) {
        TileSet* tileSet = nullptr;
        tileSet = new TileSet(32,32,file);
        auto tile = std::shared_ptr<TileSet>(tileSet);
        Resources::tileSetTable.insert({file, tile});
        return tile;
    } else {
        return temp->second;
    }
}
void Resources::ClearTileSets() {
    for(auto it = Resources::tileSetTable.begin();it != Resources::tileSetTable.end();) {
        if((*it).second.unique()) {
            Resources::tileSetTable.erase(it);
            it = Resources::tileSetTable.begin();
        } else {
            it++;
        }

    }
}
