#ifndef TALISMA_H
#define TALISMA_h

#include "GameObject.h"
#include "Geometric.h"
#include "Sprite.h"



class Talisma : public Component {
public:
    //passar os itens como parametro
    Talisma(GameObject& associated, std::string imgfile, std::string textfile, int indice = 0);
    ~Talisma();
    void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
    bool talismaAdicionado;

private:
    int mouseX, mouseY;
    bool coletado;
    std::string talismaFile;
    Sprite *talisma;
    GameObject* texto;
    std::string text;
    void ReadText(std::string textfile);
    Rect rangeText;
    bool exibeTexto;
    int indice;
};

#endif
