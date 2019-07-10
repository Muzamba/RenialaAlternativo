#include "Rect.h"

Rect::Rect()
{
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
}

Rect::Rect(int x, int y, int w, int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::~Rect()
{
}

bool Rect::Contains(int x, int y){
    return x >= this->x && x <= this->x+w && y>=this->y && y<= this->y+h;
}

bool Rect::Contains(Vec2d a){
    return a.x >= this->x && a.x <= this->x+w && a.y>=this->y && a.y<= this->y+h;
}

void Rect::SetCentro(float x, float y) {
	this->x = x - w / 2;
	this->y = y - h / 2;
}

void Rect::SetCentro(Vec2d v) {
	this->x = v.x - w / 2;
	this->y = v.y - h / 2;
}

Vec2d Rect::GetVec() {
	return Vec2d(x, y);
}
Vec2d Rect::GetCentro() {
	return Vec2d(x + w / 2, y + h / 2);
}