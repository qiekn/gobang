#pragma once

#include <raylib.h>
#include "gobang/chess-board.h"
#include "scenes/scene.h"

class GameScene : public Scene {
public:
  GameScene();
  virtual ~GameScene();

  void Update() override;
  void Draw() override;

private:
  void DrawBackground();
  void LoadBackgroundShader();

  ChessBoard board_;

  Shader shader_;
  int time_loc_;
  int resolution_loc_;
};
