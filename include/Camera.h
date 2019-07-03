#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Geometric.h"




class Camera {
public:
    static void Fallow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

public:
    static Vec2 pos;
    static Vec2 speed;
private:
    static GameObject* focus;
};


#endif // CAMERA_H