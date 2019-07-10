#include "ArvoreState.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "PlataformaFixa.h"
#include "Physic.h"
#include "PlataformaMovel.h"
#include "Talisma.h"
#include "Game.h"
#include "CameraFollower.h"
#include "HUD.h"
#include "Fase2.h"
#include "FadeOut.h"
#include "Wisp.h"
#include "ArvoreComponent.h"
#include "Dialogo.h"



ArvoreState::ArvoreState() : State() {

}


ArvoreState::~ArvoreState() {

}
    


void ArvoreState::LoadAssets() {
    GameObject* bg = new GameObject();

    auto bgS = new Sprite(*bg, "assets/img/cenarioArvore/fundo_arvore.png");
    bgS->SetScale(3.742690f,3.75f);
    bg->AddComponent(bgS);
    bg->AddComponent(new CameraFollower(*bg));
    AddObject(bg);

    Camera::pos = {0,0};
    
    arvore = new GameObject();
    auto component = new ArvoreComponent(*arvore);
    AddObject(arvore);
    
    GameObject* goPlat = new GameObject();
	TileSet* tile = new TileSet(32, 32, "assets/img/chao1.png");
	PlataformaFixa* plat = new PlataformaFixa(*goPlat,tile, "assets/map/Arvore/plat1.txt");
	goPlat->box.pos.y = 624;
	goPlat->box.pos.x = 0;
	AddObject(goPlat);

    goPlat = new GameObject();
	plat = new PlataformaFixa(*goPlat,tile, "assets/map/Arvore/plat2.txt");
	goPlat->box.pos.y = 624;
	goPlat->box.pos.x = 1120;
	AddObject(goPlat);

    goPlat = new GameObject();
	plat = new PlataformaFixa(*goPlat,tile, "assets/map/Arvore/plat3.txt");
	goPlat->box.pos.y = 688;
	goPlat->box.pos.x = 1120 - 64;
	AddObject(goPlat);


    GameObject* goplayer = new GameObject();
	Player* player = new Player(*goplayer);
	goplayer->box.pos.x = 0;//300;
	goplayer->box.pos.y = 0;
	Camera::Fallow(goplayer);
	auto p = AddObject(goplayer).lock();
	Game::GetInstance().playerStatus.player = p;

	//GameObject* goWisp = new GameObject();
	//Wisp* wisp = new Wisp(*goWisp, p, false);
	//AddObject(goWisp);

    GameObject* limiteEsq = new GameObject();
    limiteEsq->box.size = {32, 32 * 20};
    limiteEsq->AddComponent(new Collider(*limiteEsq));
    limiteEsq->AddComponent(new Physic(*limiteEsq,Physic::CHAO));
    limiteEsq->box.pos = {-32, 0} ;
    AddObject(limiteEsq); 

    GameObject* limiteDir = new GameObject();
    limiteDir->box.size = {32, 32 * 20};
    limiteDir->AddComponent(new Collider(*limiteDir));
    limiteDir->AddComponent(new Physic(*limiteDir,Physic::CHAO));
    limiteDir->box.pos = {40* 32, 0} ;
    AddObject(limiteDir); 

    GameObject* goDia = new GameObject();
    goDia->AddComponent(new Dialogo(*goDia));
    Game::GetInstance().playerStatus.dialogo = AddObject(goDia).lock();

}


void ArvoreState::Update(float dt) {
    UpdateArray(dt);
    //arvore->Update(dt);

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
    for(unsigned int i = 0;i < objectArray.size();++i) {
        auto collider1 = (Collider*)objectArray[i]->GetComponent("Collider");
        if(collider1 != nullptr) {
            for (uint j = i + 1; j < objectArray.size(); ++j) {
                auto collider2 = (Collider*)objectArray[j]->GetComponent("Collider");
                if(collider2 != nullptr) {
                    bool aux = Collision::IsColliding(collider1->box, collider2->box,
                                                      DegreesToRad(objectArray[i]->anlgleDeg),
                                                      DegreesToRad(objectArray[j]->anlgleDeg));
                    if(aux) {
                        objectArray[i]->NotifyCollision(*objectArray[j]);
                        objectArray[j]->NotifyCollision(*objectArray[i]);
                    }

                }
            }
        }
    }
}


void ArvoreState::Render() {
    //arvore->Render();
    RenderArray();
}



void ArvoreState::Start() {
    LoadAssets();
	StartArray();
}


void ArvoreState::Pause() {

}


void ArvoreState::Resume() {

}