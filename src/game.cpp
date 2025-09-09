#include "game.h"
#include <raylib.h>
#include "constants.h"
#include "utils/font-cache.h"
#include "utils/singleton.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void Game::Run() {
  Init();

  InitWindow(kScreenWidth, kScreenHeight, "game");

  Start();

  // Main loop
#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(Loop, 0, 1);
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
