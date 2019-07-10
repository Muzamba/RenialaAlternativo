#ifndef TRAB5_7_PLAYER_H
#define TRAB5_7_PLAYER_H

#include "Component.h"
#include <unordered_map>
#include <memory>
#include "Sprite.h"
#include "Geometric.h"
#include "Sound.h"
#include "Timer.h"


class Player : public Component {
public:
    Player(GameObject& associated);
    ~Player();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

	void NotifyCollision(GameObject& other);

    bool pegarItem;
private:
	//Vec2d speed;
    Sprite* atual;
    std::unordered_map<std::string,Sprite*> spriteMap;
    std::unordered_map<std::string,Sound*> soundMap;
    bool grounded;
	int jumps;
    bool soundPassos;
    Timer animacaoItem;
    
};


#endif //TRAB5_7_PLAYER_H
