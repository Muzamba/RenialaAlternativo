#ifndef TRAB5_7_PLAYER_H
#define TRAB5_7_PLAYER_H

#include "Component.h"
#include <unordered_map>
#include <memory>
#include "Sprite.h"
#include "Geometric.h"


class Player : public Component {
public:
    Player(GameObject& associated);
    ~Player();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

	void NotifyCollision(GameObject& other);

private:
	//Vec2d speed;
    Sprite* atual;
    std::unordered_map<std::string,Sprite*> spriteMap;
    bool grounded;
	int jumps;
    
};


#endif //TRAB5_7_PLAYER_H
