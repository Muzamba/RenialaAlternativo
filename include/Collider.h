#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

class Collider : public Component {
public:
    explicit Collider(GameObject& associated, const Vec2& scale = {1, 1}, const Vec2& offset = {0, 0});

    Rect box;

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void SetScale(const Vec2& scale);
    void SetOffset(const Vec2& offset);

private:
    Vec2 scale;
    Vec2 offset;
};


#endif //COLLIDER_H
