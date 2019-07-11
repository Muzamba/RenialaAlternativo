#include "ArvoreComponent.h"
#include "Sprite.h"
#include "Game.h"
#include "Player.h"
#include "Dialogo.h"
#include "Wisp.h"

ArvoreComponent::ArvoreComponent(GameObject& associated) : Component(associated) {
    associated.AddComponent(this);
    ascendendo = new Sprite(associated, "assets/img/Arvore/arvore_acendendo.png", 0, 0, 0.1f, 12);
    ascendendo->SetScale(3, 3);
    idle = new Sprite(associated, "assets/img/Arvore/arvore_idle.png", 0, 0, 0.15f, 8);
    idle->SetScale(3, 3);
    atual = ascendendo;
    ligaRender = false;
    timer.Restart();
    associated.box.pos = {1280/2 - associated.box.size.x/2.0f, 160.0f};

    brilhoChao = new GameObject();
    auto brilho = new Sprite(*brilhoChao, "assets/img/cenarioArvore/brilhochão.png");
    brilhoChao->AddComponent(brilho);
    brilho->SetScale(2.872,12);
    brilhoChao->box.pos = {-10.0f, 624 - brilhoChao->box.size.y/2};

    timer2.Restart();

    

}

ArvoreComponent::~ArvoreComponent() {
    delete ascendendo;
    delete idle;
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
    }
    if(ligaRender){
        atual->Update(dt);
        if(timer.Get() < 1.2f) {
            timer.Update(dt);
            
        } else {
            atual = idle;
            if(timer2.Get() < 2.0f) {
                timer2.Update(dt);
            } else {
                static bool first = true;
                if(first) {
                    ((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("aaaaaaaaaaaAAAAAAAAAAaaaaaaaaaaaaaaaa", "arvore");
                    first = false;
                }
            }
        }
    }

    if (first) {
        if(Game::GetInstance().playerStatus.player->box.centro().x > 640) {
            ligaRender = true;
            first = false;
            Game::GetInstance().GetCurrentState().AddObject(brilhoChao);
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
