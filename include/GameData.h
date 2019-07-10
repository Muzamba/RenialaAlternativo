#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "GameObject.h"
#include "Physic.h"
#include "State.h"
#include "Talisma.h"
#include "Timer.h"
#include <memory>
#include <vector>

class GameData {
public:
    static bool playerVictory;
    static std::weak_ptr<GameObject> player;
    static std::shared_ptr<GameObject> hud;
	static std::vector<Talisma*> talismaArray;
	static State* state;
	static bool playerContaisTalisma;
	static Rect& talismaColidido;
	void LoadTalismas();
};


#endif //GAMEDATA_H
