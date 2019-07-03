#ifndef PLATAFORMA_MOVEL_H
#define PLATAFORMA_MOVEL_H

#include "Plataforma.h"
#include "Timer.h"
#include "Geometric.h"


class PlataformaMovel : public Plataforma {
public:
    enum Movimentacao{VERTICAL, HORIZONTAL, DIAGONAL};
    PlataformaMovel(GameObject& associated, TileSet *tileSet, std::string tileMapFile, Movimentacao move = HORIZONTAL, float amplitude = 1, float freq = 1);
    ~PlataformaMovel();
    void Update(float dt) override;
	void Render() override;
    void NotifyCollision(GameObject& other) override;
private:
    Timer timer;
    /*setar valores de 0 a 1*/
    Movimentacao move;
    Vec2 posInicial;
    float amplitude;
    float freq;
    float deltaMov;

};

#endif