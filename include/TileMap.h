#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
//class TileMap;
#include "GameObject.h"
#include "TileSet.h"
#include <string>
#include <vector>
#include <fstream>

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);
    ~TileMap() override;

    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Render() override;


    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth();
    int GetHeight();
    int GetDepth();

    void Update(float dt) override;
    bool Is(std::string type) override;

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
    
};


#endif