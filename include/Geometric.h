#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <cmath>
const double PI = 3.14159265359;



class Vec2 {
public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
    Vec2(int x, int y);

    virtual ~Vec2();

    float magnitude();
    Vec2 normalizado();
    float inclinacao(); // Retorna em radianos
    float inclinacao(Vec2 other); // Retorna em radianos
    float distF(Vec2 other);
    Vec2 rotacao(float radianos);

    Vec2 operator+(const Vec2& other);
    Vec2 operator-(const Vec2& other); 
    Vec2 operator*(const float& other) const;
    Vec2 operator/(const float& other);
    Vec2& operator=(const Vec2& other);
};

class Rect {
public:
    //float x;
    //float y;
    //float h;
    //float w;
    
    Vec2 pos;
    Vec2 size;

    Rect();
    Rect(float x, float y, float w, float h);
    Rect(const Vec2& pos, const Vec2& size);


    virtual ~Rect();

    Vec2 centro();
    void mudaCentro(Vec2 novo_centro);
    float distEntreCentros(Rect& other);
    //bool estaDentro(Point2 ponto); // talvez no futuro
    bool estaDentro(float x, float y);
    bool estaDentro(float x, float y, float x2, float y2);
    //Rect operator+(const Rect& other) const;
    Rect operator+(const Vec2& other);
    Rect operator-(const Vec2& other);
    //Rect operator-(const Rect& other);
    //Rect operator*(const Rect& other) const;

    Rect& operator=(const Rect& other);
};

float RadToDegrees(float rad);
float DegreesToRad(float degrees);

int verificaRange(Vec2 conjunto1, Vec2 conjunto2);


#endif