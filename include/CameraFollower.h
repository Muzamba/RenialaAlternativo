#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H


#include "Component.h"
#include "GameObject.h"

class CameraFollower : public Component {
public:
    CameraFollower(GameObject& go);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
};


#endif // CAMERAFOLLOWER_H