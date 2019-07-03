
#include "Collider.h"
#include <iostream>
#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject &associated, const Vec2& scale, const Vec2& offset) : Component(associated), box(), scale(scale), offset(offset) {

}

void Collider::Update(float dt) {
	//this->box.pos = associated.box.pos;
    this->box.size.x = associated.box.size.x * scale.x;
    this->box.size.y = associated.box.size.y * scale.y;
    this->box.mudaCentro(associated.box.centro() + offset.rotacao(DegreesToRad(associated.anlgleDeg)));
	
}

void Collider::Render() {
#ifdef DEBUG
    Vec2 center( box.centro() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.pos.x, box.pos.y) - center).rotacao( associated.anlgleDeg / (180/PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	point = (Vec2(box.pos.x + box.size.x, box.pos.y) - center).rotacao( associated.anlgleDeg /(180/PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};

	point = (Vec2(box.pos.x + box.size.x, box.pos.y + box.size.y) - center).rotacao( associated.anlgleDeg/(180/PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};

	point = (Vec2(box.pos.x, box.pos.y + box.size.y) - center).rotacao( associated.anlgleDeg/(180/PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG

}

bool Collider::Is(std::string type) {
    return type == "Collider";
}

void Collider::SetScale(const Vec2& scale) {
    this->scale = scale;
}

void Collider::SetOffset(const Vec2& offset) {
    this->offset = offset;
}

