#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"
#include "Geometric.h"


class Physic : public Component {
public:
friend class Gravidade;
    enum Type {CHAO, JOGADOR};
    Physic(GameObject& associated, Type tipo);
    ~Physic();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    
    void NotifyCollision(GameObject& other);
private:
    Type tipo;
    int dirMovimentoX;
    int dirMovimentoY;
    char jumps;
    Vec2 posAnteriorPlayer;
};





#endif
