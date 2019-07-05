#include "Geometric.h"
#include <cmath>

//---------------------------------------------------------Vec2
Vec2::Vec2() : x(0), y(0){
}

Vec2::Vec2(float p_x,float p_y) : x(p_x), y(p_y){
}

Vec2::Vec2(int p_x, int p_y) : x(p_x), y(p_y){
}

float Vec2::magnitude() {
    float resultado = sqrt((x * x) + (y * y));
    return resultado;
}

Vec2 Vec2::normalizado() {
    Vec2 resultado;
    if(this->magnitude()!= 0){
        resultado.x = x / this->magnitude();
        resultado.y = y / this->magnitude();
    }
    return resultado;
}

float Vec2::inclinacao() {
    auto temp = atan2(y, x);
    return temp;
}//retorna em radianos;

float Vec2::inclinacao(Vec2 other) {
    auto temp =  other - *this;
    return temp.inclinacao();
}

Vec2 Vec2::rotacao(float radianos) {
    Vec2 resultado;

    resultado.x = (x * cos(radianos)) - (y * sin(radianos));
    resultado.y = ((x * sin(radianos))) + (y* cos(radianos));

    return resultado;
}

float Vec2::distF(Vec2 other) {
    Vec2 temp;
    temp = other - (*this);
    return temp.magnitude();
}

Vec2 Vec2::operator*(const float& other) const{
    Vec2 temp;
    temp.x = x * other;
    temp.y = y * other;
    return temp;
}

Vec2 Vec2::operator/(const float& other) {
    Vec2 temp;
    temp.x = x / other;
    temp.y = y / other;
    return temp;
}

Vec2 Vec2::operator+(const Vec2& other) {
    Vec2 temp;
    temp.x = this->x + other.x;
    temp.y = this->y + other.y;
    return temp;
}

Vec2 Vec2::operator-(const Vec2& other) {
    Vec2 temp;
    temp.x = this->x - other.x;
    temp.y = this->y - other.y;
    return temp;
}

Vec2& Vec2::operator=(const Vec2& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}


Vec2::~Vec2() = default;

//---------------------------------------------------------------Vec2

//---------------------------------------------------------------Rect

float Rect::distEntreCentros(Rect& other) {
    Vec2 centro1 = this->centro();
    Vec2 centro2 = other.centro();

    return centro1.distF(centro2);
}

Rect::Rect() : pos(0, 0), size(0, 0) {
}

Rect::Rect(float p_x, float p_y, float p_w, float p_h) : pos(p_x, p_y), size(p_w, p_h) {
}

Rect::Rect(const Vec2& pos, const Vec2& size) : pos(pos), size(size) {
}

bool Rect::estaDentro(float x, float y) {
    if((x > this->pos.x) && (x < (this->pos.x + this->size.x))){
        if((y > this->pos.y) && (y < (this->pos.y + this->size.y))) {
            return true;
        }
    }
    return false;
}

bool Rect::estaDentro(float x, float y, float x2, float y2) {
    
    int X = x,X2 = x2, Y = y, Y2 = y2;


    if(X == X2) {
        int maxY = std::fmax(Y, Y2);
        int minY = std::fmin(Y, Y2);
        for(int i = 0; i < maxY - minY; ++i) {
            if(estaDentro(X, minY + i)) {
                return true;
            }
        }
    } else {
        int maxX = std::fmax(X, X2);
        int minX = std::fmin(X, X2);
        for(int i = 0; i < maxX - minX; ++i) {
            if(estaDentro(minX + i, Y)) {
                return true;
            }
        }
    }
    return false;
    
}



Rect::~Rect() = default;

Vec2 Rect::centro() {
    Vec2 temp = Vec2(this->pos.x + (this->size.x / 2), this->pos.y + (this->size.y / 2));
    return temp;
}

void Rect::mudaCentro(Vec2 novo_centro) {
    pos = novo_centro - (size / 2);
}

Rect Rect::operator+(const Vec2& other) {
    Rect temp;
    temp.pos = pos + other;
    
    return temp;
}

Rect Rect::operator-(const Vec2& other) {
    Rect temp;
    temp.pos = pos - other;
    
    return temp;
}

Rect& Rect::operator=(const Rect& other) {
    this->pos = other.pos;
    this->size = other.size;

    return *this;
}


//-----------------------------------------------------------------Rect

float RadToDegrees(float rad) {
    return rad * (180 / PI);
}

float DegreesToRad(float degrees) {
    return degrees * (PI / 180);
}

// Formatodo vec2 = {min,max};
int verificaRange(Vec2 conjunto1, Vec2 conjunto2) {
    if(conjunto1.x < conjunto2.x) {
        if(conjunto1.y < conjunto2.x) {
            return 0;
        } else if(conjunto1.y > conjunto2.y) {
            return floor(conjunto2.y - conjunto2.x);
        } else {
            return floor(conjunto1.y - conjunto2.x);
        }
    } else if(conjunto1.x < conjunto2.y) {
        if(conjunto1.y < conjunto2.y) {
            return floor(conjunto1.y - conjunto1.x);
        } else {
            return floor(conjunto2.y - conjunto1.x);
        }
    } else {
        return 0;
    }
}
