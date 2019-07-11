#include "Game.h"
#include "InputManager.h"
#include "MenuState.h"
#include "TransState.h"

int main() {
    auto& game = Game::GetInstance();
    game.Push(new MenuState());

    game.Run();

    return 0;
}