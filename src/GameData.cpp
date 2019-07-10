#include "GameData.h"
#include "Camera.h"

std::weak_ptr<GameObject> GameData::player;
std::shared_ptr<GameObject> GameData::hud;
State *GameData::state = nullptr;

std::vector<Talisma*> GameData::talismaArray;
bool GameData::playerContaisTalisma = false;
Rect& GameData::talismaColidido = *(new Rect());
