#ifndef DIALOGO_H
#define DIALOGO_H

#include "Component.h"
#include <unordered_map>
#include "Sprite.h"
#include "Timer.h"



class Dialogo : public Component {
public:
    Dialogo(GameObject& associated);
    virtual ~Dialogo();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void Begin(std::string text, std::string quem);

    bool on;
private:
    GameObject* face;
    GameObject* box;
    GameObject* button;
    GameObject* texto;
    std::string quem;
    std::unordered_map<std::string,Sprite*> faceTable;
    Timer timer;
};


#endif // DIALOGO_H