#ifndef TALISMA_H
#define TALISMA_h

#include "GameObject.h"
#include "Geometric.h"
#include "Sprite.h"
#include "Timer.h"
#include <unordered_map>
#include <string>
#include "Sound.h"


class Talisma : public Component {
public:
    //passar os itens como parametro
    Talisma(GameObject& associated, std::string textfile, std::string imgfileInGame, std::string imgfileNoAnim, std::string imgfileHUD, int indice = 0);
    ~Talisma();
    void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
    bool talismaAdicionado;

private:
    int mouseX, mouseY;
    bool coletado;
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
    bool animacao;
    Sound* sound;

};

#endif
