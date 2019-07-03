#include "PlataformaFixa.h"
#include "Collider.h"

PlataformaFixa::PlataformaFixa(GameObject& associated, TileSet *tileSet, std::string tileMapFile, PlataformaTipo tipo, Vec2 scale) : Plataforma(associated, tileSet, tileMapFile, scale) {
    missing = false;
    colidindo = false;
    desceu = false;
    posInicial = associated.box.centro();
    this->tipo = tipo;
}

PlataformaFixa::~PlataformaFixa() {}

void PlataformaFixa::Update(float dt) {
    if(tipo == DESAPARECE) {
        if(missing) {
            tempoSumida.Update(dt);
            if(tempoSumida.Get() >= 10.0){
                tempoSumida.Restart();
                missing = false;
                //associated.AddComponent( new TileMap(associated, tileMapFile, tileSet));
                associated.AddComponent( new Collider(associated));
            }
        }

        if(colidindo){
            tempoColidindo.Update(dt);
            if(tempoColidindo.Get() >= 5.0f) {
                tempoColidindo.Restart();
                missing = true;
                //associated.RemoveComponent(associated.GetComponent("TileMap"));
                associated.RemoveComponent(associated.GetComponent("Collider"));
            }
        } else {
            tempoColidindo.Restart();
        }
        colidindo = false;
    }
    /*
    if(colidindo && !desceu) {
        if(associated.box.GetCentro().y < posInicial.y + 2.0) {
            associated.box.SetCentro(associated.box.GetCentro() + Vec2d(0, 0.1));   
        }else{
            desceu = true;
        }
    }
    if(!colidindo && desceu) {
        if(associated.box.GetCentro().y >= posInicial.y) {
            associated.box.SetCentro(associated.box.GetCentro() - Vec2d(0, 0.1));
        }else {
            desceu = false;
        }
    }
    */

    colidindo = false;
}

void PlataformaFixa::Render() {
    if(!missing){
        tileMap->Render();
    }
}

void PlataformaFixa::NotifyCollision(GameObject& other) {
    auto player = other.GetComponent("Player");
    if (player) {
        if(tipo == DESAPARECE) {
            colidindo = true;

        }
    }
    
}