#include <utility>

#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet) :  Component(associated),
                                                                                tileSet(tileSet),
                                                                                mapWidth(0),
                                                                                mapHeight(0),
                                                                                mapDepth(0) {
    Load(file);
}

void TileMap::Load(const std::string& file) {
    std::ifstream arquivo;
    std::string linha;
    arquivo.open(file);
    if(arquivo.is_open() && arquivo.good()) {
        arquivo >> mapWidth;
        arquivo.seekg(1, std::ifstream::cur);
        arquivo >> mapHeight;
        arquivo.seekg(1, std::ifstream::cur);
        arquivo >> mapDepth;
        arquivo.seekg(2, std::ifstream::cur);
        int temp = 0;
        for(int cont3 = 0;cont3 < mapDepth;++cont3) {
            for(int cont1 = 0;cont1 < mapHeight;++cont1) {
                for(int cont2 = 0;cont2 < mapWidth;++cont2) {
                    arquivo >> temp;
                    tileMatrix.push_back(temp - 1);
                    arquivo.seekg(1, std::ifstream::cur);
                }
                arquivo.seekg(1, std::ifstream::cur);
            }
            arquivo.seekg(1, std::ifstream::cur);
        }
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    //this->tileSet->~TileSet();  // Verificar com monitor
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[z * (mapWidth * mapHeight) + x + y * mapWidth];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    int cont3 = 0;
    for(int cont1 = 0;cont1 < mapHeight;++cont1) {
        for(int cont2 = 0;cont2 < mapWidth;++cont2) {
            tileSet->RenderTile(tileMatrix[cont3 + (mapWidth * mapHeight * layer)],cont2 * tileSet->GetTileWidth() - cameraX + associated.box.pos.x , cont1 * tileSet->GetTileHeight() - cameraY + associated.box.pos.y);
            cont3++;
        }
    }
}

void TileMap::Render() {
    int multi = 1;

    for(int cont1 = 0;cont1 < mapDepth;++cont1) {
        RenderLayer(cont1, std::round(Camera::pos.x * multi), std::round(Camera::pos.y * multi));
        multi++;
    }
}

int TileMap::GetDepth() {
    return mapDepth;
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

void TileMap::Update(float dt) {
}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

TileMap::~TileMap() {
    delete tileSet;
}

