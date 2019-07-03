#ifndef PLATAFORMFIXA_H
#define PLATAFORMFIXA_H

#include "Plataforma.h"
#include "GameObject.h"
#include "Geometric.h"

class PlataformaFixa : public Plataforma{
public:
    enum PlataformaTipo{NORMAL, DESAPARECE};
    PlataformaFixa(GameObject& associated, TileSet *tileSet, std::string tileMapFile, PlataformaTipo tipo = NORMAL, Vec2 scale = { 1,1 });
    ~PlataformaFixa();
    void Update(float dt) override;
	void Render() override;
    void NotifyCollision(GameObject& other) override;
private:
    Timer tempoSumida,tempoColidindo;
    bool missing;
    bool colidindo;
    Vec2 posInicial;
    bool desceu;
    PlataformaTipo tipo;
};


# endif
