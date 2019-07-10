#pragma once
#include <memory>
#include "Sprite.h"
#include "State.h"
#include "TestState.h"
#include "Text.h"

using namespace std;

class Fase2State : public State {
public:
    Fase2State();
    void LoadAssets();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
    shared_ptr<Text> textColetar;
	shared_ptr<Sprite> spriteFinal_ptr;
	void LoadPlataformas();
	bool mostrarTexto;
	GameObject *textColetarObj;
};