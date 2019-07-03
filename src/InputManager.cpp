#include "InputManager.h"
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>

InputManager& InputManager::GetInstance() {
    static InputManager inputManager;
    return inputManager;
}

InputManager::InputManager() : mouseState(), mouseUpdate(), quitRequested(false), updateCounter(0), mouseX(0), mouseY(0) {
    for(int i = 0;i < 6;++i) {

        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager::~InputManager() {
    keyState.clear();
    keyUpdate.clear();
}

void InputManager::Update() {
    SDL_Event evento;
    quitRequested = false;
    updateCounter++;
    // Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

    while(SDL_PollEvent(&evento)) {
            switch (evento.type) {

                case SDL_KEYDOWN:  //Pressionamento de tecla
                    if(!evento.key.repeat) {
                        keyState[evento.key.keysym.sym] = true;
                        keyUpdate[evento.key.keysym.sym] = updateCounter;
                    }
                    break;


                case SDL_KEYUP: //Uma tecla foi solta
                    if(!evento.key.repeat) {
                        keyState[evento.key.keysym.sym] = false;
                        keyUpdate[evento.key.keysym.sym] = updateCounter;
                    }
                    break;


                case SDL_MOUSEBUTTONDOWN:  //Pressionamento de botão do mouse
                    mouseState[evento.button.button] = true;
                    mouseUpdate[evento.button.button] = updateCounter;
                    break;


                case SDL_MOUSEBUTTONUP:  //Botão do mouse foi solto
                    mouseState[evento.button.button]= false;
                    mouseUpdate[evento.button.button] = updateCounter;
                    break;

                case SDL_QUIT:  //Sair
                    quitRequested = true;
                    break;

                default:
                    break;
            }
        }
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::KeyPress(int key) {
    auto it = keyUpdate.find(key);
    if(it == keyUpdate.end()){
        return false;
    }
    if(keyUpdate[key] == updateCounter) {
        return keyState[key];
    }
    return false;
}
bool InputManager::KeyRelease(int key) {
    auto it = keyUpdate.find(key);
    if(it == keyUpdate.end()){
        return false;
    }
    if(keyUpdate[key] == updateCounter) {
        return !keyState[key];
    }
    return false;
}
bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}
bool InputManager::MousePress(int button) {
    if(mouseUpdate[button] == updateCounter) {
        return mouseState[button];
    }
    return false;
}
bool InputManager::MouseRelease(int button) {
    if(mouseUpdate[button] == updateCounter) {
        return !mouseState[button];
    }
    return false;
}
bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

bool InputManager::QuitRequested() {
        return quitRequested;
}



