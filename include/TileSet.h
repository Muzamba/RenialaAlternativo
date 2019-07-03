#ifndef TILESET_H
#define TILESET_H

//class TileSet;
#include <string>
#include "Sprite.h"
#include "GameObject.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, const std::string& file);
    void RenderTile(unsigned index, float x, float y);

    int GetTileWidth();
    int GetTileHeight();

private:

    GameObject xablau;
    Sprite tileSet;
    int rows;
    int columns;

    int tileWidth;
    int tileHeight;
};


#endif