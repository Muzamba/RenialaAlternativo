#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Timer.h"
#include "Physic.h"
#include "GameObject.h"
#include <memory>

class GameData {
public:
    bool playerVictory = false;
    std::weak_ptr<GameObject> player;
};


#endif //GAMEDATA_H
