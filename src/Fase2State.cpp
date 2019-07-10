#include "Fase2State.h"
#include "Camera.h"
#include "Collider.h"
#include "Collision.h"
#include "CameraFollower.h"
#include "InputManager.h"

Fase2State::Fase2State() : State() {
    this->textColetar = nullptr;
	this->mostrarTexto = false;
	quitRequested = false;
}

void Fase2State::LoadAssets() {
	GameObject* gobg = new GameObject();
	Sprite* sprite = new Sprite(*gobg, "assets/img/ocean.jpg");
	gobg->AddComponent(sprite);
	gobg->AddComponent(new CameraFollower(*gobg));
	objectArray.emplace_back(gobg);
}

void Fase2State::LoadPlataformas() {}

void Fase2State::Update(float dt) {
    Camera::Update(dt);
	UpdateArray(dt);

	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		popRequested = true;
	}

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

    for (unsigned int i = 0; i < objectArray.size(); i++) {
		Collider* colliderA = (Collider*)objectArray[i]->GetComponent("Collider");
		if (colliderA != nullptr) {
			for (unsigned int j = i + 1; j < objectArray.size(); j++) {
				Collider* colliderB = (Collider*)objectArray[j]->GetComponent("Collider");
				if (colliderB != nullptr && Collision::IsColliding(colliderA->box, colliderB->box, DegreesToRad(objectArray[i]->anlgleDeg), DegreesToRad(objectArray[j]->anlgleDeg))) {
					objectArray[i]->NotifyCollision(*objectArray[j]);
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}
			}
		}
	}
}

void Fase2State::Render() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->GetComponent("Text")) {
			if(mostrarTexto)
				objectArray[i]->Render();
		}
		else {
			objectArray[i]->Render();
		}
	}
}

void Fase2State::Pause() {}

void Fase2State::Resume() {
	popRequested = false;
}