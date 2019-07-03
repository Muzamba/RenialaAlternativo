#include "PlataformaMovel.h"
#include "Geometric.h"
#include <cmath>
#include "Timer.h"
#include "Player.h"
#include "Collider.h"

PlataformaMovel::PlataformaMovel(GameObject& associated, TileSet *tileSet, std::string tileMapFile, Movimentacao move, float amplitude, float freq) : Plataforma(associated, tileSet, tileMapFile) {
    this->amplitude = amplitude;
    this->freq = freq;
    this->deltaMov = 0;
    
    posInicial = associated.box.pos;
    timer.Restart(); 
    this->move = move;
}

PlataformaMovel::~PlataformaMovel() {}

void PlataformaMovel::Update(float dt) {
    timer.Update(dt);
    float aux;
    
    switch (move)
    {
    case HORIZONTAL:
        aux = posInicial.x + amplitude + amplitude * cos(timer.Get() * 2 * PI * freq);
        deltaMov = aux - associated.box.pos.x;
        associated.box.pos.x = aux;
        break;
    case VERTICAL:
        aux = posInicial.y + amplitude + amplitude * cos(timer.Get() * 2 * PI * freq);
        deltaMov = aux - associated.box.pos.y;
        associated.box.pos.y = aux;
        break;
    case DIAGONAL:
        break;
    default:
        break;
    }
}

void PlataformaMovel::Render() {
    tileMap->Render();
}

void PlataformaMovel::NotifyCollision(GameObject& other) {
    auto player = (Player*)other.GetComponent("Player");
    auto colliderOther = (Collider*)other.GetComponent("Collider");
    auto collider = (Collider*)associated.GetComponent("Collider");
    uint dif;
    auto valorX = (other.box.size.x - colliderOther->box.size.x)/2;


    if(player){
        switch (move) {
            case HORIZONTAL:
                other.box.pos.x += deltaMov;
                break;
            case VERTICAL:
                other.box.pos.y += deltaMov;
                break;
            case DIAGONAL:
                break;
        }
    }
    
    
}