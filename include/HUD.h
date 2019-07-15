#ifndef HUD_H
#define HUD_H

#include "Component.h"
#include "GameObject.h"
#include <vector>
#include <memory>


class HUD : public Component {
public:
    HUD(GameObject& associated);
    virtual ~HUD();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void AddTalisma(GameObject* talisma);
    int faltaQuantos();
private:
    std::vector<std::shared_ptr<GameObject>> talismas;
    GameObject* hud;
};

#endif //HUD_H
