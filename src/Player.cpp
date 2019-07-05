#include "Player.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Collider.h"
#include "Gravidade.h"
#include "Physic.h"
#include "Game.h"


Player::Player(GameObject& associated) : Component(associated), atual(nullptr), grounded(false), jumps(0) {
	associated.AddComponent(this);

	auto sprite = new Sprite(associated, "assets/img/idle.png", 100, 100, 0.08f, 4);
	sprite->SetScale(2, 2);
	spriteMap["idle"] = sprite;
	atual = sprite;

	sprite = new Sprite(associated, "assets/img/walk.png", 100, 100, 0.08f, 4);
	sprite->SetScale(2, 2);
	spriteMap["walk"] = sprite;

	sprite = new Sprite(associated, "assets/img/jump.png", 100, 100, 0.27f, 6);
	sprite->SetScale(2, 2);
	spriteMap["jump"] = sprite;

	associated.AddComponent(new Collider(associated, {1/8.0f, 1/2.8f}, {0,10}));

	associated.AddComponent(new Physic(associated, Physic::JOGADOR));
	auto gravidade = new Gravidade(associated, 800);
	associated.AddComponent(gravidade);
	
	//associated.box.pos = {300,300};

}

Player::~Player() {
	
}

void Player::Update(float dt) {
	
	auto& im = InputManager::GetInstance();
	auto gravidade = (Gravidade*)associated.GetComponent("Gravidade");
	//atual = spriteMap["idle"];
	if (gravidade->GetVelocidade() < 0.1f  and gravidade->GetVelocidade() > -0.1f) {
		atual = spriteMap["idle"];
		if (im.IsKeyDown(D_KEY)) {
			atual = spriteMap["walk"];
			atual->SetFlip(false);
			spriteMap["idle"]->SetFlip(false);
			spriteMap["jump"]->SetFlip(false);
		}
		else if (im.IsKeyDown(A_KEY)) {	
			atual = spriteMap["walk"];
			atual->SetFlip(true);
			spriteMap["idle"]->SetFlip(true);
			spriteMap["jump"]->SetFlip(true);
		}
		spriteMap["jump"]->SetFrame(2);
		if (im.KeyPress(W_KEY) && jumps < 2) {
			//if (gravidade->GetGrounded()) {
			atual = spriteMap["jump"];
			atual->SetFrame(0);
			jumps++;
			//}
		}
	} else {
		atual = spriteMap["jump"];
		if (im.KeyPress(W_KEY) and jumps < 2) {
			//if (gravidade->GetGrounded()) {
			atual = spriteMap["jump"];
			atual->SetFrame(0);
			jumps++;
			//}

		}
		if (im.IsKeyDown(D_KEY)) {
			atual->SetFlip(false);
			spriteMap["idle"]->SetFlip(false);
		} else if (im.IsKeyDown(A_KEY)) {	
			atual->SetFlip(true);
			spriteMap["idle"]->SetFlip(true);
		}
	}

	
	atual->Update(dt);



}

void Player::Render() {
	
	atual->Render();
}

bool Player::Is(std::string type) {
	return type == "Player";
}

void Player::NotifyCollision(GameObject& other) {
	jumps = 0;
}