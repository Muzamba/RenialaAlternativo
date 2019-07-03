#include "GameObject.h"
#include "Camera.h"

GameObject::GameObject() : box(), started(false), anlgleDeg(0), isDead(false) {
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt) {
    //box.x = box.x + Camera::pos.x;
    //box.y = box.y + Camera::pos.y;
    for(uint i = 0; i < components.size();i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for(auto & component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    std::shared_ptr<Component> temp(cpt);
	components.push_back(temp);
	if(started) {
		temp->Start();
	}
}

void GameObject::RemoveComponent(Component* cpt) {
    for(auto it = components.begin(); it != components.end();++it) {
        if((*it).get() == cpt){
            components.erase(it);
            break;
        }
    }
}

Component* GameObject::GetComponent(const std::string& type) {
    Component* temp = nullptr;
    for(auto & component : components) {
        if(component->Is(type)) {
            temp = component.get();
            break;
        }
    }
    return temp;
}

void GameObject::setBox(int x,int y,int w,int h) {
    box.pos.x = x;
    box.pos.y = y;
    box.size.x = w;
    box.size.y = h;
}

void GameObject::Start() {
    for(auto & component : components) {
        component->Start();
    }
    started = true;
}

void GameObject::NotifyCollision(GameObject &other) {
    for (auto& component : components) {
        component->NotifyCollision(other);
    }

}
