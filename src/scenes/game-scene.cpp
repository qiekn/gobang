#include "scenes/game-scene.h"
#include <raylib.h>

GameScene::GameScene() { LoadBackgroundShader(); }

GameScene::~GameScene() { UnloadShader(shader_); }

void GameScene::Update() { board_.Update(); }

void GameScene::Draw() {
  DrawBackground();
  /*
  const char* text = "Game Scene";

  int font_size = 32;
  Vector2 text_size = MeasureTextEx(NotoItlaic(), text, font_size, 1);
  Vector2 text_pos = {(GetScreenWidth() - text_size.x) / 2.0f, 150};
  DrawTextEx(NotoItlaic(), text, text_pos, font_size, 1, LIGHTGRAY);
  */
  board_.Draw();
}

void GameScene::DrawBackground() {
  // BeginShaderMode(shader_);
  // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);  // Color doesn't matter; shader overrides
  // EndShaderMode();
}

void GameScene::LoadBackgroundShader() {
  shader_ = LoadShader(0, "assets/shaders/balatro.fs");
  if (shader_.id == 0) {
    TraceLog(LOG_ERROR, "Failed to load shader: assets/shaders/balatro.fs");
    return;
  }
}
