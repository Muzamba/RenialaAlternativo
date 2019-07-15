#ifndef FASE3_H
#define FASE3_H

#include "State.h"
#include "Music.h"

class Fase3 : public State {
public:
	Fase3();
	virtual ~Fase3();

	void LoadAssets() override;
	void LoadPlataformas();
	void LoadBg();
	void LoadCenarioFrente();
	void LoadCenarioAtras();

	void Update(float dt) override;
	void Render() override;
	
	void Start() override;
	void Pause() override;
	void Resume() override;
private:
	GameObject* fadeIn;
	GameObject* fadeOut;
	Music* musica;
	std::vector<std::shared_ptr<GameObject>> frontArray;

};



#endif //FASE3_H