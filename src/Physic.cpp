#include "Physic.h"
#include "Collider.h"
#include "Gravidade.h"
#include "InputManager.h"

Physic::Physic(GameObject& associated, Type tipo) : Component(associated), tipo(tipo), dirMovimentoX(0), dirMovimentoY(0), jumps(0), posAnteriorPlayer({0, 0}) {}

Physic::~Physic() {}

void Physic::Update(float dt) {
    auto& im = InputManager::GetInstance();
    auto gravidade = (Gravidade*)associated.GetComponent("Gravidade");
    

    switch(tipo){
        case CHAO:
            break;
        
        case JOGADOR:
            if (im.IsKeyDown(D_KEY) or im.IsKeyDown(A_KEY) or im.KeyPress(W_KEY) or im.IsKeyDown(S_KEY)) {
		        if(im.IsKeyDown(D_KEY) or im.IsKeyDown(A_KEY)) {
                    float velo = 300;
                    if (im.IsKeyDown(D_KEY)) {
			            associated.box.pos.x = associated.box.pos.x + velo * dt;
                        dirMovimentoX = 1;
    
		            }
                    if (im.IsKeyDown(A_KEY)) {
			            associated.box.pos.x = associated.box.pos.x - velo * dt;
                        dirMovimentoX = -1;
		            }
                } else {
                    dirMovimentoX = 0;
                }
		        if (im.KeyPress(W_KEY) && jumps < 2) {
			    //if (gravidade->GetGrounded()) {
			        gravidade->SetVelocidade(-455);
			        gravidade->Jump();
                    dirMovimentoY = 1;

			    jumps++;
			    //}

		        }
		
	        }
            break;
    }
}

void Physic::Render() {}

bool Physic::Is(std::string type) {
    return type == "Physic";
}

void Physic::NotifyCollision(GameObject& other) {
    static bool mudarDir = true;
    auto otherPhysic = (Physic*)other.GetComponent("Physic"); 
    auto collider = (Collider*)associated.GetComponent("Collider");
    auto collider2 = (Collider*)other.GetComponent("Collider");
    auto gravidade =(Gravidade*)associated.GetComponent("Gravidade");
    std::pair<int,int> pontoES = {collider->box.centro().x - collider->box.size.x/2, collider->box.centro().y - collider->box.size.y/2};
    std::pair<int,int> pontoDS = {collider->box.centro().x + collider->box.size.x/2, collider->box.centro().y - collider->box.size.y/2};
    std::pair<int,int> pontoDI = {collider->box.centro().x + collider->box.size.x/2, collider->box.centro().y + collider->box.size.y/2};
    std::pair<int,int> pontoEI = {collider->box.centro().x - collider->box.size.x/2, collider->box.centro().y + collider->box.size.y/2};

    auto valorX = (associated.box.size.x - collider->box.size.x)/2;
    auto valorY = (associated.box.size.y - collider->box.size.y)/2 - 5;

    static std::pair<int,int> colDir = {0, 0};
    if(otherPhysic) {
        switch (tipo) {
        case CHAO:
            break;

        case JOGADOR:
            switch (otherPhysic->tipo) {
            case CHAO:
                
                    //if(mudarDir){
                        if(collider2->box.estaDentro(pontoES.first, pontoES.second)) {
                            if(collider2->box.estaDentro(pontoES.first + 5, pontoES.second)) {
                                colDir = {0,1};
                            } else {
                                colDir = {-1,0};
                            }
                        } else if(collider2->box.estaDentro(pontoEI.first, pontoEI.second)) {
                            if(collider2->box.estaDentro(pontoEI.first, pontoEI.second - 20)) {
                                colDir = {-1,0};
                            } else {
                                colDir = {0,-1};
                            }
                        } else if(collider2->box.estaDentro(pontoDS.first, pontoDS.second)) {
                            if(collider2->box.estaDentro(pontoDS.first, pontoDS.second + 20)) {
                                colDir = {1,0};
                            } else {
                                colDir = {0,1};
                            }
                        } else if(collider2->box.estaDentro(pontoDI.first, pontoDI.second)) {
                            if(collider2->box.estaDentro(pontoDI.first - 5, pontoDI.second)) {
                                colDir = {0,-1};
                            } else {
                                colDir = {1,0};
                            }
                        }
                        //mudarDir = false;
                    //}
               
                if(colDir.second == -1) {
                    
                    if(gravidade){
                        //gravidade->toggle = false;
                        if(gravidade->velocidade > 0)
                        gravidade->velocidade = 0;
                    }
                    //if(dirMovimentoY < 0) {
                        //if(!(jumps > 0)){

                        //}
                        if(dirMovimentoY != 1) {    
                            jumps = 0;
                            associated.box.mudaCentro({associated.box.centro().x, collider2->box.pos.y - collider->box.size.y/2 - 5});
                        }
                            dirMovimentoY = 0;
                       // touching = true;
                    //}
                } else if(colDir.second == 1) {
                    if(dirMovimentoY == 1) {
                        if(gravidade){
                            gravidade->velocidade = 50;
                        }
                        //associated.box.pos.y = collider2->box.pos.y + collider2->box.size.y - valorY;
                    }
                }
                if(colDir.first) {    
                    
                    if(colDir.first == 1) {
                        if(dirMovimentoX == 1) {
                            associated.box.pos.x = collider2->box.pos.x - collider->box.size.x - valorX + 2;
                        }
                    }
                    if(colDir.first == -1) {
                        if(dirMovimentoX == -1) {
                            associated.box.pos.x = collider->box.pos.x - valorX;
                        }
                    }
                    
                }
            
                //on = false;
                break;

            case JOGADOR:
                break;
            }
            break;
        }
    }
}