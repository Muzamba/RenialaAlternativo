#include "Gravidade.h"
#include "Collider.h"
#include "Player.h"


Gravidade::Gravidade(GameObject& associated, float acel) : Component(associated), acelY(acel), velocidade(0), toggle(false) {

}

Gravidade::~Gravidade() {

}

void Gravidade::Update(float dt) {
	if(timer.Get() < 5.0f){
		timer.Update(dt);
	}else {
		auto physic = (Physic*)associated.GetComponent("Physic");
	

		//if (toggle) {
			velocidade += acelY * dt;
			if(velocidade > 500){
				velocidade = 500;
			}
			associated.box.pos.y = associated.box.pos.y + velocidade * dt;// + acelY * dt * dt / 2;
			if(physic){
				if(velocidade > 0) {
					if(physic) {
						physic->dirMovimentoY = -1;
					}
				} else {
					if(physic) {
						physic->dirMovimentoY = 1;
					}
				}
			}
		//}
		//else {
		//	velocidade = 0;
		//	if(physic) {
		//		physic->dirMovimentoY = 0;
		//	}
		//}

		toggle = true;
	}
	
}

void Gravidade::Render() {

}

bool Gravidade::Is(std::string type) {
	return type == "Gravidade";
}

void Gravidade::SetAceleration(float newAcel) {
	acelY = newAcel;
}

void Gravidade::SetVelocidade(float newVelo) {
	velocidade = newVelo;
}

void Gravidade::Jump() {
	toggle = true;
}


void Gravidade::NotifyCollision(GameObject& other) {
	
	//printf("%lf %lf", collider->box.size.x, collider->box.size.y);
}

bool Gravidade::GetGrounded() {
	return toggle;
}

float Gravidade::GetVelocidade() {
	return velocidade;
}
