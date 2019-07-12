#include "Player.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Collider.h"
#include "Gravidade.h"
#include "Physic.h"
#include "Game.h"


Player::Player(GameObject& associated) : Component(associated), atual(nullptr), grounded(false), jumps(0) {
	associated.AddComponent(this);

	auto sprite = new Sprite(associated, "assets/img/idle.png", 100, 100, 0.1f, 4);
	sprite->SetScale(2, 2);
	spriteMap["idle"] = sprite;
	atual = sprite;

	sprite = new Sprite(associated, "assets/img/walk.png", 100, 100, 0.1f, 4);
	sprite->SetScale(2, 2);
	spriteMap["walk"] = sprite;

	sprite = new Sprite(associated, "assets/img/jump.png", 100, 100, 0.27f, 6);
	sprite->SetScale(2, 2);
	spriteMap["jump"] = sprite;

	sprite = new Sprite(associated, "assets/img/item.png", 100, 100, 0.111f, 9);
	sprite->SetScale(2, 2);
	spriteMap["item"] = sprite;

	soundMap["walk"] = new Sound(associated, "assets/sound/Passos2.ogg");
	soundMap["item"] = new Sound(associated,"assets/sound/COLETA DE ITEM.ogg");
	//associated.AddComponent(soundMap["walk"]);


	associated.AddComponent(new Collider(associated, {1/8.0f, 1/2.8f}, {0,10}));

	associated.AddComponent(new Physic(associated, Physic::JOGADOR));
	auto gravidade = new Gravidade(associated, 800);
	associated.AddComponent(gravidade);

	soundPassos = false;
	pegarItem = false;
	dialogo = false;
	
	//associated.box.pos = {300,300};

}

Player::~Player() {
	delete spriteMap["idle"];
	delete spriteMap["walk"];
	delete spriteMap["jump"];	
}

void Player::Update(float dt) {
	if(!dialogo){
	static bool one = true;
	
	if(pegarItem){
		atual = spriteMap["item"];
		static bool one2 = true;
		if (one2) {
			one2 = false;
			soundMap["walk"]->Stop();
			soundMap["item"]->Play(1);
		}
		if(animacaoItem.Get() < 2.0f){
			animacaoItem.Update(dt);
		} else {
			animacaoItem.Restart();
			pegarItem = false;
			one2 = true;
			one = true;
			
		}
		
	} else {
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
			spriteMap["item"]->SetFlip(false);
			soundPassos = true;
		}
		else if (im.IsKeyDown(A_KEY)) {	
			atual = spriteMap["walk"];
			atual->SetFlip(true);
			spriteMap["idle"]->SetFlip(true);
			spriteMap["jump"]->SetFlip(true);
			spriteMap["item"]->SetFlip(true);
			soundPassos = true;
		} else {
			soundPassos = false;
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
		soundPassos = false;
		//soundMap["walk"]->Stop();
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
	}

	
	atual->Update(dt);
	static bool control = false;
	if(soundPassos and one) {
		soundMap["walk"]->Play(-1);
		//soundMap["test"]->Play();
		one = false;
		control = true;
	} else if(!soundPassos and control){
		soundMap["walk"]->Stop();
		control = false;
		one = true;
	}
	} else {
		atual = spriteMap["idle"];
		soundMap["walk"]->Stop();
		atual->Update(dt);
	}

}

void Player::Render() {
	
	atual->Render();
}

bool Player::Is(std::string type) {
	return type == "Player";
}

void Player::NotifyCollision(GameObject& other) {
	jumps = 0;
	//soundPassos = false;
}