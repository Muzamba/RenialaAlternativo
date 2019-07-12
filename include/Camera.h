#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Geometric.h"




class Camera {
public:
    enum FASE{ARVORE, TRANSICAO, BONITA, FEIA, CAVERNA};
    static void Fallow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
    static void SetFase(FASE fase);

public:
    static Vec2 pos;
    static Vec2 speed;
    static FASE fase;
private:
    static GameObject* focus;
};


#endif // CAMERA_H