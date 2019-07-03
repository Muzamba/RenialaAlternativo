#include "Game.h"
#include "InputManager.h"
#include "TestState.h"

int main() {
    auto& game = Game::GetInstance();
    game.Push(new TestState());

    game.Run();

    return 0;
}