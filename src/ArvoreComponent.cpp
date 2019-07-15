#include "ArvoreComponent.h"
#include "Sprite.h"
#include "Game.h"
#include "Player.h"
#include "Dialogo.h"
#include "Wisp.h"
#include "InputManager.h"
#include "HUD.h"
#include "Cutscene.h"

ArvoreComponent::ArvoreComponent(GameObject& associated) : Component(associated) {
    associated.AddComponent(this);
    ascendendo = new Sprite(associated, "assets/img/Arvore/arvore_acendendo.png", 0, 0, 0.131944444f, 12);
    ascendendo->SetScale(3, 3);
    idle = new Sprite(associated, "assets/img/Arvore/arvore_idle.png", 0, 0, 0.19791666f, 8);//0.098958333, 8);
    idle->SetScale(3, 3);
    atual = ascendendo;
    ligaRender = false;
    timer.Restart();
    associated.box.pos = {1280/2 - associated.box.size.x/2.0f, 160.0f};

    brilhoChao = new GameObject();
    auto brilho = new Sprite(*brilhoChao, "assets/img/cenarioArvore/brilhochão.png");
    brilhoChao->AddComponent(brilho);
    brilho->SetScale(3.8,12);
    brilhoChao->box.pos = {-10.0f, 624 - brilhoChao->box.size.y/2};

    timer2.Restart();

    //musica = new Music("assets/sound/Reniala-fase-final-_95bpm_.ogg");

}

ArvoreComponent::~ArvoreComponent() {
    delete ascendendo;
    delete idle;
    //musica->Stop(0);
    //delete musica;
    //delete brilhoChao;
    //delete wisp;
}


void ArvoreComponent::Update(float dt) {
    static bool first = true;
    //brilhoChao->Update(dt);
    if(!Game::GetInstance().playerStatus.criarVariaveis) {
        first = false;
        ligaRender = false;
        atual = idle;
        atual->Update(dt);
        if(associated.box.estaDentro(Game::GetInstance().playerStatus.player->box.centro().x, Game::GetInstance().playerStatus.player->box.centro().y)) {
            if(InputManager::GetInstance().KeyPress(SDLK_x)){
                int a = ((HUD*)Game::GetInstance().playerStatus.hud->GetComponent("HUD"))->faltaQuantos();
                if(a != 3){
                    ((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Preciso de mais !!!!!", "arvore");
                } else {
                    Game::GetInstance().Push(new Cutscene(false));
                }
            }
        }

    }
        static bool second = true;
    if(ligaRender){
        atual->Update(dt);
        if(timer.Get() < 1.58333f) {
            timer.Update(dt);
            
        } else {
            atual = idle;
            if(timer2.Get() < 1.0f) {
                timer2.Update(dt);
            } else {
                static bool first = true;
                if(first) {
                    first = false;
                }
            }
        }
    }

    if (first) {
        if(Game::GetInstance().playerStatus.player->box.centro().x > 340 and second){
            ligaRender = true;
            second = false;
            ((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Socoooorrro!!! Preciso dos tres talismas para continuar vivendo", "arvore");
                    
            Game::GetInstance().GetCurrentState().AddObject(brilhoChao);
        }
        if(Game::GetInstance().playerStatus.player->box.centro().x > 640) {
            first = false;
            //musica->Play();
            //((Dialogo*)Game::GetInstance().playerStatus.player.lock()->GetComponent("Dialogo"))->Begin("oi", "arvore");
            //((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Bom dia grupo", "wisp");
            //auto go = new GameObject();
            //auto o = new Wisp(*go, Game::GetInstance().playerStatus.player);
            if(Game::GetInstance().playerStatus.criarVariaveis) {
                Game::GetInstance().playerStatus.wisp = Game::GetInstance().GetCurrentState().AddObject(wisp).lock();
            } else {
                //Game::GetInstance().playerStatus.wisp = Game::GetInstance().GetCurrentState().AddObject(Game::GetInstance().playerStatus.wisp.get()).lock();
            }
        }
    }
}

void ArvoreComponent::Render() {
    //if(ligaRender) {
        atual->Render();
        //brilhoChao->Render();
    //}
}

bool ArvoreComponent::Is(std::string type) {
    return type == "ArvoreComponent";
}

void ArvoreComponent::Start() {
    if(Game::GetInstance().playerStatus.criarVariaveis){
        wisp = new GameObject();
        new Wisp(*wisp, Game::GetInstance().playerStatus.player);
    }

}
