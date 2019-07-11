#include "Game.h"
Game* Game::instance = nullptr;

#include "InputManager.h"
#include "Camera.h"
#include "Resources.h"



Game& Game::GetInstance() {
    if(!instance) {
        instance = new Game("Reniala", 1280, 720);
    }
    return *instance;
}


Game::Game(const std::string& title,int width, int height) : frameStart(0), dt(0), storedState(nullptr), window(nullptr), renderer(nullptr) {
    if(instance != nullptr) {
        std::cout << "Game iniciado mais de uma vez!\n";
        exit(0);
    }
    instance = this;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << SDL_GetError();
        exit(1);
    }
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cout << "Não consegui carregar nenhum setup de imagem!\n";
        exit(2);
    }

    if(Mix_Init(MIX_INIT_OGG == 0)){
        std::cout << "Falha ao iniciar o áudio!\n";
        exit(3);
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cout << "Falha no OpenAudio!\n";
        exit(4);
    }

    Mix_AllocateChannels(32);

    if(TTF_Init()) {
        std::cout << "Erro no TTF_Init!\n";
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr) {
        std::cout << "Erro ao criar a Janela!";
        exit(5);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Erro ao criar renderer!\n";
        exit(6);
    }
}


Game::~Game() {
    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    if(storedState != nullptr) {
        delete storedState;
    }
    while(!stateStack.empty()) {
        stateStack.pop();
    }
}

State& Game::GetCurrentState() {
    return *stateStack.top();
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}


void Game::Run() {

    if(storedState == nullptr) {
        std::cout << "Jogo finalizado pois não possui estado inicial" <<std::endl;
        return;
    }
    auto& im = InputManager::GetInstance();
    //std::cout << "Aqui\n";
    stateStack.push(std::unique_ptr<State>(storedState));
    storedState = nullptr;

    stateStack.top()->Start();
    while(!stateStack.empty()) {
        //printf("0\n");
        if(stateStack.top()->QuitRequested()) {
            break;
        }
        //printf("1\n");
        if(stateStack.top()->PopRequested()) {
            //printf("Aqui\n");
            stateStack.pop();
            Resources::ClearImages();
            Resources::ClearMusics();
            Resources::ClearSounds();
            Resources::ClearFonts();
            Resources::ClearTileSets();
            if(stateStack.empty()) {
                if(!storedState) {
                    break;
                }
            } else {
                stateStack.top()->Resume();
            }
        }
        //printf("2\n");
        if(storedState) {
            if(!stateStack.empty()) {
                stateStack.top()->Pause();
            }
            stateStack.push(std::unique_ptr<State>(storedState));
            stateStack.top()->Start();
            storedState = nullptr;

        }
        //printf("3\n");

        CalculateDeltaTime();
        //printf("1\n");
        im.Update();
        //printf("2\n");
        stateStack.top()->Update(dt);
        //printf("3\n");
        stateStack.top()->Render();
        //printf("4\n");


        SDL_RenderPresent(renderer);
        //printf("5\n");
        SDL_Delay(33);
    }
    while(!stateStack.empty()){
        stateStack.pop();
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();
    Resources::ClearTileSets();
    
}

void Game::CalculateDeltaTime() {
    int temp = SDL_GetTicks();
    dt = temp - frameStart;
    frameStart = temp;
    dt = dt / 1000;
    //std::cout << "dt: " << dt << std::endl;
}

void Game::Push(State *state) {
    storedState = state;
}

float Game::GetDeltaTime() {
    return dt;
}
