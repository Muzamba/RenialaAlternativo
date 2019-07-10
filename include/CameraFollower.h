#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H


#include "Component.h"
#include "GameObject.h"

class CameraFollower : public Component {
public:
    CameraFollower(GameObject& go, int x = 0, int y = 0);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void SetXY(int x, int y);
    int xTela;
    int yTela;
private:
};


#endif // CAMERAFOLLOWER_H