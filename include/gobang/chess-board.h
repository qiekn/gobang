#pragma once

#include <raylib.h>
#include <vector>
#include "utils/color.h"

enum class Order {
  kWhite = 0,
  kBlack = 1,
};

class ChessBoard {
public:
  ChessBoard();
  virtual ~ChessBoard();

  void Update();
  void Draw();

private:
  /* methods */
  void Place();  // Place a piece on the board
  void Restart();

  void SetOffset();
  void DrawBoard() const;
  void DrawPieces() const;
  void DrawPieceIndicator() const;
  void DrawStatus();

  Vector2 GetGridPos() const;  // Get the grid position of the mouse cursor
  Vector2 GetWorldPos(Vector2 pos) const;
  Vector2 GetWorldPos(int x, int y) const;
  Vector2 GetBoardSize() const;
  Rectangle GetBoardRect() const;

  bool IsHover() const;
  void CheckHover();
  void CheckWin(int x, int y);  // Use this after Place()

private:
  float alpha_{0.4f};  // Background alpha
  int steps_{0};
  bool is_hover_{false};  // Is mouse over board
  bool is_win_{false};
  bool is_check_win_{true};

  Vector2 offset_;  // Offset from the top-left corner of the window
  Color bg_color_{Hexc("#c4c4c4")};
  Color grid_bg_color_{Fade(BLACK, alpha_)};
  Color grid_border_color_{150, 150, 150, 255};

  int current_color_index_{0};  // used for gui color pick
  Color color_0_;
  Color color_1_;
  Color color_2_;

  // -1: empty, 0: white, 1: black
  std::vector<std::vector<int>> board_{kGridCount, std::vector<int>(kGridCount, -1)};

  Order order_{Order::kBlack};  // Current turn order

  constexpr static int kGridSize = 40;
  constexpr static int kGridCount = 20;
};
