#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject;
#include <memory>
#include <vector>
#include "Component.h"
#include "Geometric.h"
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"


class GameObject {
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(const std::string& type);
    void setBox(int x,int y, int w, int h);
    void Start();

    void NotifyCollision(GameObject& other);

public:
    Rect box;
    bool started;
    double anlgleDeg;

private:
    std::vector <std::shared_ptr<Component>> components;
    bool isDead;
};

#endif
