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
#include "TransState.h"
#include "Gravidade.h"
#include "PauseState.h"



ArvoreState::ArvoreState() : State() {
    fadeOut = new GameObject();
    fadeOut->AddComponent(new FadeOut(*fadeOut, 0.25f));

    fadeIn = new GameObject();
    if(Game::GetInstance().playerStatus.criarVariaveis){
        fadeIn->AddComponent(new FadeIn(*fadeIn, 5.0f));
    }else {
        fadeIn->AddComponent(new FadeIn(*fadeIn, 0.25f));
    }
}


ArvoreState::~ArvoreState() {
    //delete arvore;
    delete fadeOut;
    delete fadeIn;
    delete musica;
}
    


void ArvoreState::LoadAssets() {
    GameObject* bg = new GameObject();

    auto bgS = new Sprite(*bg, "assets/img/cenarioArvore/fundo_arvore.png");
    bgS->SetScale(3.742690f,3.75f);
    bg->AddComponent(bgS);
    bg->AddComponent(new CameraFollower(*bg));
    AddObject(bg);

    Camera::pos = {0,0};
    Camera::SetFase(Camera::ARVORE);
    
    arvore = new GameObject();
    auto component = new ArvoreComponent(*arvore);
    AddObject(arvore);
    
    GameObject* goPlat = new GameObject();
	TileSet* tile = new TileSet(32, 32, "assets/img/chao1.png");
	PlataformaFixa* plat = new PlataformaFixa(*goPlat,tile, "assets/map/Arvore/plat1.txt");
	goPlat->box.pos.y = 624;
	goPlat->box.pos.x = 0;
	AddObject(goPlat);

     musica = new Music("assets/sound/Reniala-fase-final-_95bpm_.ogg");

    if(Game::GetInstance().playerStatus.criarVariaveis) {
        GameObject* goplayer = new GameObject();
	    Player* player = new Player(*goplayer);
	    goplayer->box.pos.x = 0;//300;
	    goplayer->box.pos.y = 530;
	    Camera::Fallow(goplayer);
	    Game::GetInstance().playerStatus.player = AddObject(goplayer).lock();

        GameObject* goDia = new GameObject();
        new Dialogo(*goDia);
        Game::GetInstance().playerStatus.dialogo = AddObject(goDia).lock();
        

        GameObject* goHUD = new GameObject();
        new HUD(*goHUD);
        Game::GetInstance().playerStatus.hud = AddObject(goHUD).lock();

        GameObject* talismaFolha = new GameObject();
		Talisma *talisma1 = new Talisma(*talismaFolha, "assets/text/talisma1.txt", "assets/img/talismans/talisma_folha(1).png","assets/img/talismans/talisma_folha.png","assets/img/talismans/folha.png", Camera::BONITA, 0);
		talismaFolha->box.pos.x = 8850 + 220;//11000; 8900 - 50, 632 
		talismaFolha->box.pos.y = 550 ;//550;
		((HUD*)Game::GetInstance().playerStatus.hud->GetComponent("HUD"))->AddTalisma(talismaFolha);
        
        GameObject* talismaFlor = new GameObject();
		Talisma *talisma2 = new Talisma(*talismaFlor, "assets/text/talisma2.txt", "assets/img/talismans/talisma_flor(1).png","assets/img/talismans/talisma_flor.png","assets/img/talismans/flor.png", Camera::CAVERNA, 1);
		talismaFlor->box.pos.x = 40 * 32;//definir posicao do talisma na fase correspondente
		talismaFlor->box.pos.y = -7008 + 32 * 218;//
		((HUD*)Game::GetInstance().playerStatus.hud->GetComponent("HUD"))->AddTalisma(talismaFlor);

        GameObject* talismaPedra = new GameObject();
		Talisma *talisma3 = new Talisma(*talismaPedra, "assets/text/talisma3.txt", "assets/img/talismans/talisma_pedra(1).png","assets/img/talismans/talisma_pedra.png","assets/img/talismans/pedra.png", Camera::FEIA, 2);
		talismaPedra->box.pos.x = 1280 + 32;//definir posicao do talisma na fase correspondente
		talismaPedra->box.pos.y = 550 ;//
		((HUD*)Game::GetInstance().playerStatus.hud->GetComponent("HUD"))->AddTalisma(talismaPedra);


    } else {
        //Game::GetInstance().playerStatus.player = AddObject(Game::GetInstance().playerStatus.player.get()).lock();
        Game::GetInstance().playerStatus.player->box.pos = {1280 + 32, 720};
        ((Gravidade*)Game::GetInstance().playerStatus.player->GetComponent("Gravidade"))->SetVelocidade(-670);
        musica->Play();
    }

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
    limiteDir->box.pos = {44* 32, 0} ;
    AddObject(limiteDir); 

   


    

}


void ArvoreState::Update(float dt) {
    Camera::Update(dt);
    UpdateArray(dt);
    
    static bool first = true;
    if(Game::GetInstance().playerStatus.player->box.centro().x > 340 && first) {
        musica->Play();
        first = false;
    }

    if(!Game::GetInstance().playerStatus.criarVariaveis) {
        auto& playerStatus = Game::GetInstance().playerStatus;
        playerStatus.player->Update(dt);
        playerStatus.wisp->Update(dt);
        playerStatus.hud->Update(dt);
        playerStatus.dialogo->Update(dt);

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
    }else {

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






    if(Game::GetInstance().playerStatus.player->box.pos.y > 740) {
        static bool first = true;
        if(first) {
            ((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
            first = false;
            musica->Stop(250);
        }
        if( ((FadeOut*)fadeOut->GetComponent("FadeOut"))->timer.Get() > 0.25f){
            popRequested = true;
            Game::GetInstance().Push(new TransState(0));
            first = true;
            Game::GetInstance().playerStatus.criarVariaveis = false;
        }
    }
    

	if (InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) ){
		Game::GetInstance().Push(new PauseState());
	}
    
        fadeIn->Update(dt);
        fadeOut->Update(dt);

    static bool one = true;
    if(one){
        ((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Use as teclas WASD para andar e barra de espaco para pular dialogos", "boneco");
        one = false;
    }
}


void ArvoreState::Render() {
    //arvore->Render();
    RenderArray();
    Game::GetInstance().playerStatus.dialogo->Render();
    if(!Game::GetInstance().playerStatus.criarVariaveis) {
        auto& playerStatus = Game::GetInstance().playerStatus;
        playerStatus.player->Render();
        playerStatus.wisp->Render();
        playerStatus.hud->Render();
        playerStatus.dialogo->Render();
    }
    fadeIn->Render();
    fadeOut->Render();
}



void ArvoreState::Start() {
    LoadAssets();
	StartArray();
    ((FadeIn*)fadeIn->GetComponent("FadeIn"))->Begin();
}


void ArvoreState::Pause() {

}


void ArvoreState::Resume() {

}