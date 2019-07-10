#include "State.h"



State::State() : popRequested(false), quitRequested(false), started(false) {
}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *object) {
    std::shared_ptr<GameObject> temp(object);
    objectArray.push_back(temp);
    if(started) {
        temp->Start();
    }
    std::weak_ptr<GameObject> retorno(temp);
    return retorno;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object) {
    for(auto & i : objectArray) {
        if(i.get() == object) {
            std::weak_ptr<GameObject> retorno(i);
            return retorno;
        }
    }
    std::weak_ptr<GameObject> retorno;
    return retorno;
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for(unsigned int i = 0;i < objectArray.size();++i) {
        objectArray[i]->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for(unsigned int i = 0;i < objectArray.size();++i) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for(unsigned int i = 0;i < objectArray.size();++i) {
        objectArray[i]->Render();
    }
}

