#ifndef BOXSTATE_H
#define BOXSTATE_H


#include "State.h"
#include "Text.h"

class BoxState : public State {
public:
	BoxState(std::string talismaFile, std::string descricao);
    ~BoxState();
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume()override;
private:
	std::string descricao;
	std::string talismaFile;
};

#endif
