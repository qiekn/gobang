#include "gobang/chess-board.h"
#include <raylib.h>
#include <algorithm>
#include <format>
#include <ios>
#include <string>
#include "constants.h"
#include "raygui.h"
#include "utils/font.h"

ChessBoard::ChessBoard() {
  SetOffset();
  color_0_ = bg_color_;
  color_1_ = grid_bg_color_;
  color_2_ = grid_border_color_;
}

ChessBoard::~ChessBoard() {}

void ChessBoard::DrawBoard() const {
  ClearBackground(bg_color_);
  // Draw background
  int sz = kGridSize, cnt = kGridCount + 1;
  DrawRectangle(offset_.x, offset_.y, sz * cnt, sz * cnt, grid_bg_color_);

  // Draw grid lines
  for (int i = 0; i <= cnt; ++i) {
    // Vertical lines
    DrawLine(offset_.x + i * sz, offset_.y, offset_.x + i * sz, offset_.y + sz * cnt, grid_border_color_);
    // Horizontal lines
    DrawLine(offset_.x, offset_.y + i * sz, offset_.x + sz * cnt, offset_.y + i * sz, grid_border_color_);
  }
}

Vector2 ChessBoard::GetGridPos() const {
  Vector2 mouse_pos = GetMousePosition();
  // range: [0, kGridCount - 1]
  float x = (mouse_pos.x - offset_.x - 0.5f * kGridSize) / kGridSize;
  float y = (mouse_pos.y - offset_.y - 0.5f * kGridSize) / kGridSize;
  x = std::clamp(x, 0.0f, kGridCount - 1.0f);
  y = std::clamp(y, 0.0f, kGridCount - 1.0f);
  return {x, y};
}

void ChessBoard::Update() {
  if (is_check_win_ && is_win_) return;
  CheckHover();
  // if (is_hover_)
  //   HideCursor();
  // else
  //   ShowCursor();
  if (is_hover_ && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Place();
  }
}

void ChessBoard::Draw() {
  DrawBoard();
  DrawPieces();
  DrawPieceIndicator();
  DrawStatus();
}

void ChessBoard::Place() {
  Vector2 pos = GetGridPos();
  int x = pos.x, y = pos.y;
  if (x < 0 || y < 0) return;
  if (board_[x][y] != -1) {
    // already placed
    return;
  } else if (order_ == Order::kWhite) {
    board_[x][y] = 0;
    order_ = Order::kBlack;
  } else if (order_ == Order::kBlack) {
    board_[x][y] = 1;
    order_ = Order::kWhite;
  }
  CheckWin(x, y);
  steps_++;
}

void ChessBoard::SetOffset() {
  offset_.y = (kScreenHeight - kGridSize * (kGridCount + 1)) / 2;
  offset_.x = offset_.y;
}

void ChessBoard::DrawPieces() const {
  for (int x = 0; x < kGridCount; x++) {
    for (int y = 0; y < kGridCount; y++) {
      // 获取格子中心世界坐标
      Vector2 pos = GetWorldPos(x, y);

      float scale = 0.8f;
      // 根据 board_ 的值画棋子
      if (board_[x][y] == 0) {  // 白子
        DrawCircleV(pos, kGridSize / 2 * scale, WHITE);
      } else if (board_[x][y] == 1) {  // 黑子
        DrawCircleV(pos, kGridSize / 2 * scale, BLACK);
      }
      // -1 表示空格，不画棋子
    }
  }
}

void ChessBoard::DrawStatus() {
  // Draw backgorund;
  Vector2 size = GetBoardSize();
  float x = offset_.x + size.x + offset_.x;
  float y = offset_.y;
  float w = kScreenWidth - x - offset_.x;
  float h = size.y;
  Rectangle rect = {x, y, w, h};
  DrawRectangleRec(rect, Fade(BLACK, alpha_));

  float padding = 10.0f;

  // Title
  const char* title = "Game Status";
  Vector2 title_size = MeasureTextEx(NotoItlaic(), title, FontSize::kSubtitle, 1);
  Vector2 center_pos = {x + w / 2, y + title_size.y / 2 + padding};
  ck::DrawTextExCenterV(NotoItlaic(), title, center_pos, FontSize::kSubtitle, RAYWHITE);

  // Grid Pos
  Vector2 grid_pos{0, 0};
  if (IsHover()) grid_pos = GetGridPos();

  std::string player;
  if (order_ == Order::kWhite)
    player = "白棋(White)";
  else if (order_ == Order::kBlack)
    player = "黑棋(Black)";

  std::string grid_info = std::format("位置(GridPos): ({},{})", (int)grid_pos.x + 1, (int)grid_pos.y + 1);
  std::string step_info = std::format("步数(Steps): {}", steps_);
  std::string order_info = std::format("玩家(Player): {}", player);
  if (is_win_) {
    if (order_ == Order::kWhite)
      order_info = "黑棋获胜";
    else if (order_ == Order::kBlack)
      order_info = "白棋获胜";
  }

  GuiStatusBar({940, 100, 190, 24}, grid_info.c_str());
  GuiStatusBar({940, 130, 190, 24}, step_info.c_str());
  GuiStatusBar({940, 160, 190, 24}, order_info.c_str());

  // Color Change
  Color* p;
  switch (current_color_index_) {
    case 0:
      p = &color_0_;
      bg_color_ = color_0_;
      break;
    case 1:
      p = &color_1_;
      grid_bg_color_ = Fade(color_1_, alpha_);
      break;
    case 2:
      p = &color_2_;
      grid_border_color_ = color_2_;
      break;
    default:
      break;
  }
  GuiToggleGroup((Rectangle){940, 200, 62, 24}, "背景;棋盘;格线", &current_color_index_);
  GuiColorPicker((Rectangle){940, 200 + 32, 180, 180}, NULL, p);

  if (GuiButton({940, 425, 190, 24}, "重新开始(Restart)")) {
    Restart();
  }
}

Vector2 ChessBoard::GetBoardSize() const {
  float w = kGridSize * (kGridCount + 1);
  float h = kGridSize * (kGridCount + 1);
  return {w, h};
}

Vector2 ChessBoard::GetWorldPos(Vector2 pos) const { return GetWorldPos(pos.x, pos.y); }

Vector2 ChessBoard::GetWorldPos(int x, int y) const {
  if (x < 0 || x > kGridCount || y < 0 || y > kGridCount) {
    TraceLog(LOG_WARNING, "GetWorldPos: Out of range!");
    return {};
  }
  float res_x = offset_.x + kGridSize * (x + 1);
  float res_y = offset_.y + kGridSize * (y + 1);
  return {res_x, res_y};
}

Rectangle ChessBoard::GetBoardRect() const {
  auto size = GetBoardSize();
  return {offset_.x, offset_.y, size.x, size.y};
}

bool ChessBoard::IsHover() const { return is_hover_; }

void ChessBoard::CheckHover() { is_hover_ = CheckCollisionPointRec(GetMousePosition(), GetBoardRect()); }

void ChessBoard::DrawPieceIndicator() const {
  if (!is_hover_) return;
  if (is_check_win_ && is_win_) return;
  float radius = kGridSize * 0.4f;  // 16px
  float thickness = 2.0f;
  Color color = order_ == Order::kBlack ? BLACK : WHITE;
  DrawRing(GetWorldPos(GetGridPos()), radius, radius + thickness, 0, 360, 64, color);
}

void ChessBoard::CheckWin(int a, int b) {
  // 总之，就是下完一步棋，就检查一次
  int flag = -1, size = 16;
  if (order_ == Order::kWhite)
    flag = 1;  // 黑棋刚下完，就检查黑棋
  else if (order_ == Order::kBlack)
    flag = 0;  // 白棋刚下完，就检查白棋是否获胜

  // 方向数组
  static const int dirs[4][2] = {
      {1, 0},  // 横向
      {0, 1},  // 竖向
      {1, 1},  // 右下
      {1, -1}  // 左下
  };

  for (auto& d : dirs) {
    int dx = d[0], dy = d[1];

    // 遍历该方向上可能的起点
    for (int i = -4; i <= 0; i++) {
      int start_x = a + i * dx;
      int start_y = b + i * dy;

      // 检查该方向的连续5 格
      bool ok = true;
      for (int k = 0; k < 5; k++) {
        int x = start_x + k * dx;
        int y = start_y + k * dy;
        if (x < 0 || x >= size || y < 0 || y >= size || board_[x][y] != flag) {
          ok = false;
          break;
        }
      }

      // 找到一个起点开始的5连，结束
      if (ok) {
        is_win_ = true;
        return;
      }
    }
  }
  is_win_ = false;
}

void ChessBoard::Restart() {
  for (auto& x : board_) {
    for (auto& g : x) {
      g = -1;
    }
  }
  steps_ = 0;
  is_win_ = false;
}
