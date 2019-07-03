#ifndef PLATARFORMA_H
#define PLATARFORMA_H

#include <fstream>
#include <string>

#include "TileSet.h"
#include "TileMap.h"
#include "Component.h"


class Plataforma : public Component{
public:
    enum PlataformaTipo {FIXA};
    Rect box;
    Plataforma(GameObject& associated, TileSet *tileSet, std::string tileMapFile, Vec2 scale = { 1,1 });
    ~Plataforma();
	bool Is(std::string type);
    
    protected:
        TileSet *tileSet;
        TileMap *tileMap;
        std::string tileMapFile;
        
        Vec2 scale;
};

#endif