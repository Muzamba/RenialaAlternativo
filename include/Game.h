#ifndef GAME_H
#define GAME_H
class Game;
#include <iostream>
#include <string>
#include <stack>
#include <memory>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
//class Game;
#include "State.h"
#include "GameData.h"


class Game{
public:

    ~Game();
    static Game& GetInstance();

    SDL_Renderer* GetRenderer();
    State& GetCurrentState();
    void Push(State* state);

    void Run();

    float GetDeltaTime();

    GameData playerStatus;

private:

    Game(const std::string& title,int width, int height);
    void CalculateDeltaTime();

    int frameStart;
    float dt;

    static Game* instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::stack<std::unique_ptr<State>> stateStack;

};

#endif

