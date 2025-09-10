#include "game.h"
#include <raylib.h>
#include "constants.h"
#include "utils/font-cache.h"
#include "utils/singleton.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
Game* game = nullptr;
void MainLoopWrapper() { game->Loop(); }
#endif

void Game::Run() {
  Init();
  Start();

  // Main loop
#if defined(PLATFORM_WEB)
  game = this;
  emscripten_set_main_loop(MainLoopWrapper, 0, 1);
#else
  SetTargetFPS(kFPS);
  while (!WindowShouldClose()) {
    Loop();
  }
#endif

  CloseWindow();
}

void Game::Init() {
  SetTraceLogLevel(LOG_WARNING);
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  // SetConfigFlags(FLAG_WINDOW_UNDECORATED);

  // InitWindow create OpenGL context
  // Make sure this line is the last line of the function.
  InitWindow(kScreenWidth, kScreenHeight, "game");
}

void Game::Start() {
  CONSTRUCT_SINGLETON(FontCache);
  scene_manager_ = std::make_unique<SceneManager>();
}

void Game::Update() { scene_manager_->Update(); }

void Game::Draw() {
  BeginDrawing();
  scene_manager_.get()->Draw();
  EndDrawing();
}

void Game::Loop() {
  Update();
  Draw();
}
