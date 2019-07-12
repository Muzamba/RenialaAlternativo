#include "TransState.h"
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
#include "ArvoreState.h"
#include "Resources.h"
#include "TestState.h"
#include "Fase2.h"

TransState::TransState(int pos) : State() {
    Camera::SetFase(Camera::TRANSICAO); 
    mudaState = false;
    destino = nullptr;
    fadeOut = new GameObject();
    fadeOut->AddComponent(new FadeOut(*fadeOut, 0.25f));
    fadeIn = new GameObject();
    fadeIn->AddComponent(new FadeIn(*fadeIn, 0.25));
    switch (pos) {

    case 0: //cima
        Game::GetInstance().playerStatus.player->box.mudaCentro({1280/2, - 10});
        break;
    
    case 1://esquerda
         Game::GetInstance().playerStatus.player->box.mudaCentro({0,600});
        break;

    case 2://direita
        
        break;

    case 3://baixo
        Game::GetInstance().playerStatus.player->box.mudaCentro({640,700});
        break;
    }

}

TransState::~TransState() {
    delete fadeOut;
    delete fadeIn;;
}


void TransState::LoadAssets() {
    Camera::pos = {0,0};

    GameObject* bg = new GameObject();

    auto bgS = new Sprite(*bg, "assets/img/cenarioArvore/fundo_arvore.png");
    bgS->SetScale(3.742690f,3.75f);
    bg->AddComponent(bgS);
    bg->box.pos ={0,0};
    AddObject(bg);


    auto tileSet0 = Resources::GetTileSet("assets/img/chao1.png");
    auto tileSet1 = Resources::GetTileSet("assets/img/chao2.png");
    auto tileSet2 = Resources::GetTileSet("assets/img/chao3.png");
    auto tileSet3 = Resources::GetTileSet("assets/img/chao4.png");
    auto trans = Resources::GetTileSet("assets/img/transicao tiles.png");

    auto tPlat1 = Resources::GetTileSet("assets/img/plat_hor_2.png");
    auto tPlat2 = Resources::GetTileSet("assets/img/plat_hor_3.png");
    auto tPlat3 = Resources::GetTileSet("assets/img/plat_hor_4.png");

    auto go = new GameObject();
    go->box.pos = {-160, 624};
    go->box.size = {32 * 21, 32 * 3};
    go->AddComponent(new Collider(*go));
    go->AddComponent(new Physic(*go, Physic::CHAO));
    AddObject(go);


    GameObject* plat1 = new GameObject();
    TileMap* tileMap1 = new TileMap(*plat1, "assets/map/TransState/plat1.txt", tileSet1.get());
    plat1->AddComponent(tileMap1);
    plat1->box.pos = {0,624};
    AddObject(plat1);

    GameObject* plat2 = new GameObject();
    TileMap* tileMap2 = new TileMap(*plat2, "assets/map/TransState/plat2.txt", trans.get());
    plat2->AddComponent(tileMap2);
    plat2->box.pos = {320,624};
    AddObject(plat2);

    GameObject* plat3 = new GameObject();
    TileMap * tileMap3 = new TileMap(*plat3, "assets/map/TransState/plat3.txt", tileSet2.get());
    plat3->AddComponent(tileMap3);
    plat3->box.pos = {352,624};
    AddObject(plat3);

    GameObject* plat4 = new GameObject();
    new PlataformaFixa(*plat4, tileSet2.get(), "assets/map/TransState/plat4.txt");
    plat4->box.pos = {480+32,688};
    AddObject(plat4);

    GameObject* plat5 = new GameObject();
    new PlataformaFixa(*plat5, tileSet2.get(), "assets/map/TransState/plat5.txt");
    plat5->box.pos = {736-32,688};
    AddObject(plat5);

    GameObject* plat6 = new GameObject();
    TileMap * tileMap6 = new TileMap(*plat6, "assets/map/TransState/plat6.txt", tileSet2.get());
    plat6->AddComponent(tileMap6);
    plat6->box.pos = {800 -32,624};
    AddObject(plat6);

    go = new GameObject();
    go->box.pos = {800 - 32,624};
    go->box.size = {32 * 21, 32 * 3};
    go->AddComponent(new Collider(*go));
    go->AddComponent(new Physic(*go, Physic::CHAO));
    AddObject(go);

    GameObject* plat7 = new GameObject();
    TileMap * tileMap7 = new TileMap(*plat7, "assets/map/TransState/plat7.txt", trans.get());
    plat7->AddComponent(tileMap7);
    plat7->box.pos = {928,624};
    AddObject(plat7);

    GameObject* plat8 = new GameObject();
    TileMap * tileMap8 = new TileMap(*plat8, "assets/map/TransState/plat8.txt", tileSet3.get());
    plat8->AddComponent(tileMap8);
    plat8->box.pos = {960,624};
    AddObject(plat8);

    GameObject* plat9 = new GameObject();
    plat9->box.pos = {0, 0};
    new PlataformaFixa(*plat9,tileSet0.get(),"assets/map/TransState/plat9.txt");
    AddObject(plat9);

    GameObject* plat10 = new GameObject();
    plat10->box.pos = {736-32, 0};
    new PlataformaFixa(*plat10,tileSet0.get(),"assets/map/TransState/plat10.txt");
    AddObject(plat10);

    GameObject* plat11 = new GameObject();
    plat11->box.pos = {480 - 3*32,16 * 32};
    new PlataformaFixa(*plat11,tPlat1.get(),"assets/map/TransState/plat11.txt");
    AddObject(plat11);

    GameObject* plat12 = new GameObject();
    plat12->box.pos = {480 + 3*32, 2 * 32};
    new PlataformaMovel(*plat12,tPlat2.get(),"assets/map/TransState/plat12.txt", PlataformaMovel::VERTICAL, 32 * 7, 0.05f);
    AddObject(plat12);

    GameObject* plat13 = new GameObject();
    plat13->box.pos = {480 + 7*32, 16 * 32};
    new PlataformaFixa(*plat13,tPlat3.get(),"assets/map/TransState/plat13.txt");
    AddObject(plat13);

    static bool first = true;
    if (first){
        ((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Ha talismas a leste, ao sul e ao oeste!Quando coletar todos retorne a Arvore", "wisp");
        first = false;
    }

}

void TransState::Update(float dt) {
    UpdateArray(dt);

    auto& game = Game::GetInstance().playerStatus;
    game.player->Update(dt);
    game.wisp->Update(dt);
    game.hud->Update(dt);
    game.dialogo->Update(dt);

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

    if(!mudaState){
        if(Game::GetInstance().playerStatus.player->box.centro().y < -12){
            destino = new ArvoreState();
            mudaState = true;
            //popRequested = true;
        } else if(Game::GetInstance().playerStatus.player->box.centro().x < -10) {
            destino = new TestState();
            //popRequested = true;
            mudaState = true;
        }else if(Game::GetInstance().playerStatus.player->box.centro().y > 720) {
            mudaState = true;
            destino = new Fase2();
        }
    } else{
        static bool first = true;
        if(first){
            ((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
            first = false;
        }
        if( ((FadeOut*)fadeOut->GetComponent("FadeOut"))->timer.Get() > 0.25f) {
            popRequested = true;
            Game::GetInstance().Push(destino);
            first = true;
        }
    }

    //for(unsigned int i = 0;i < objectArray.size();++i) {
    //    auto collider1 = (Collider*)objectArray[i]->GetComponent("Collider");
    //    if(collider1 != nullptr) {
    //        for (unsigned int j = i + 1; j < objectArray.size(); ++j) {
    //            auto collider2 = (Collider*)objectArray[j]->GetComponent("Collider");
    //            if(collider2 != nullptr) {
    //                bool aux = Collision::IsColliding(collider1->box, collider2->box,
    //                                                  DegreesToRad(objectArray[i]->anlgleDeg),
    //                                                  DegreesToRad(objectArray[j]->anlgleDeg));
    //                if(aux) {
    //                    objectArray[i]->NotifyCollision(*objectArray[j]);
    //                    objectArray[j]->NotifyCollision(*objectArray[i]);
    //                }
//
    //            }
    //        }
    //    }
    //}
    auto collider1 = (Collider*)Game::GetInstance().playerStatus.player->GetComponent("Collider");
    for(unsigned int i = 0;i < objectArray.size();++i) {
        auto collider2 = (Collider*)objectArray[i]->GetComponent("Collider");
        if(collider2 != nullptr) {
            bool aux = Collision::IsColliding(collider1->box, collider2->box,
                                              DegreesToRad(Game::GetInstance().playerStatus.player->anlgleDeg),
                                              DegreesToRad(objectArray[i]->anlgleDeg));
            if(aux) {
                objectArray[i]->NotifyCollision(*Game::GetInstance().playerStatus.player);
                Game::GetInstance().playerStatus.player->NotifyCollision(*objectArray[i]);
            }
        }

    }
    fadeOut->Update(dt);
    fadeIn->Update(dt);
}

void TransState::Render() {
    RenderArray();
    auto& game = Game::GetInstance().playerStatus;
    game.player->Render();
    game.wisp->Render();
    game.hud->Render();
    game.dialogo->Render();
    fadeOut->Render();
    fadeIn->Render();

}


void TransState::Start() {
    LoadAssets();
	StartArray();
    ((FadeIn*)fadeIn->GetComponent("FadeIn"))->Begin();
}

void TransState::Pause() {

}

void TransState::Resume() {

}
