#include "Plataforma.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Game.h"
#include "Camera.h"
#include "Collider.h"
#include "Physic.h"

Plataforma::Plataforma(GameObject& associated, TileSet *tileSet, std::string tileMapFile, Vec2 scale) : Component(associated) {
    this->scale = scale;
    this->tileMap = tileMap;
    this->tileSet = tileSet;
    this->tileMapFile = tileMapFile;

    tileMap = new TileMap(associated, tileMapFile, tileSet);

    associated.box.size.x = tileSet->GetTileWidth() * tileMap->GetWidth();
    associated.box.size.y = tileSet->GetTileHeight() * tileMap->GetHeight();
    std::cout << "Width: " << tileSet->GetTileWidth() << " Height: " << tileSet->GetTileHeight() << std::endl;

    //associated.AddComponent(tileMap);
    
    associated.AddComponent(new Collider(associated));
    associated.AddComponent(this);
    associated.AddComponent(new Physic(associated, Physic::CHAO));
    //std::cout << "x: " << associated.box.pos.x << " y: " << associated.box.pos.y << " w: " << associated.box.size.x << " h: " << associated.box.size.y << std::endl;
    //adicionar collider
}

Plataforma::~Plataforma() {}


bool Plataforma::Is(std::string type) {
    return type == "Plataforma";
}