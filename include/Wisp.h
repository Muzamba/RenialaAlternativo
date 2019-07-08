#ifndef WISP_H
#define WISP_H

#include "Component.h"
#include "Player.h"
#include "Geometric.h"
#include <memory>


class Wisp : public Component {
public:
    Wisp(GameObject& associated, std::weak_ptr<GameObject> player);

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
private:
    std::weak_ptr<GameObject> player;
    Vec2 posRel;
    GameObject* luz;
};

#endif //WISP_H
