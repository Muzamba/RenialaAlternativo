#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Timer.h"
#include "Physic.h"
#include "GameObject.h"
#include "Dialogo.h"
#include <memory>

class GameData {
public:
    bool playerVictory = false;
    std::shared_ptr<GameObject> player;
    std::shared_ptr<GameObject> wisp;
    std::shared_ptr<GameObject> hud;
    std::shared_ptr<GameObject> dialogo;
};


#endif //GAMEDATA_H
