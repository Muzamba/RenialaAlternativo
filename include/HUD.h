#ifndef HUD_H
#define HUD_H

#include "Component.h"


class HUD : public Component {
public:
    HUD(GameObject& associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);

};

#endif //HUD_H
