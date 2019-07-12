#ifndef TALISMA_H
#define TALISMA_h

#include "GameObject.h"
#include "Geometric.h"
#include "Sprite.h"
#include "Timer.h"
#include <unordered_map>
#include <string>
#include "Sound.h"
#include "Camera.h"

class Talisma : public Component {
public:
    //passar os itens como parametro
    Talisma(GameObject& associated, std::string textfile, std::string imgfileInGame, std::string imgfileNoAnim, std::string imgfileHUD, Camera::FASE fase, int indice = 0);
    ~Talisma();
    void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
    bool talismaAdicionado;
    Camera::FASE fase;
    bool coletado;
    bool animacao;

private:
    int mouseX, mouseY;
    std::string talismaFile;
    //Sprite *talismaInGame;
    //Sprite *talismaNoAnim;
    //Sprite *talismaHUD;
    std::unordered_map<std::string,Sprite*> spriTable;
    Sprite *atual;
    GameObject* texto;
    std::string text;
    void ReadText(std::string textfile);
    Rect rangeText;
    bool exibeTexto;
    int indice;
    Timer timer;
    bool ligaBrilho;
    Sound* sound;
};

#endif
