#include "utils/font.h"
#include <raylib.h>
#include "managers/font-manager.h"
#include "utils/font-cache.h"

void DrawTextUtil(const char* text, int x, int y, int fs, Color color);

void ck::DrawTextPixel(const char* text, int x, int y, int fs, Color color) {
  const auto& fd = FontManager::Get().GetPixelSCData();
  DrawTextUtil(text, x, y, fs, color);
}

void ck::DrawTextPixelCenter(const char* text, int x, int y, int fs, Color color) {
  Vector2Int size = MeasurePixelText(text, fs);
  DrawTextPixel(text, x - size.x / 2, y - size.y / 2, fs, color);
}

Vector2Int ck::MeasurePixelText(const char* text, int fs) {
  Vector2 size = MeasureTextEx(FontCache::Get().GetFont(fs, text), text, (float)fs, (float)TextStyle::kSpacing);
  int w = fs / 16;
  size.x -= w;
  size.y += w;
  return {size.x, size.y};
}

Vector2Int ck::MeasurePixelText(const std::string& text, int fs) { return MeasurePixelText(text.c_str(), fs); }

void DrawTextUtil(const char* text, int x, int y, int fs, Color color) {
  const Font& font = FontCache::Get().GetFont(fs, text);
  DrawTextEx(font, text, Vector2{(float)x, (float)y}, (float)fs, (float)TextStyle::kSpacing, color);
}
void ck::DrawTextExCenterV(const Font& font, const char* text, Vector2 pos, int fs, Color color) {
  DrawTextExCenter(font, text, (int)pos.x, (int)pos.y, fs, color);
}
void ck::DrawTextExCenter(const Font& font, const char* text, int x, int y, int fs, Color color) {
  Vector2 size = MeasureTextEx(font, text, (float)fs, (float)TextStyle::kSpacing);
  DrawTextEx(font, text, Vector2{(float)(x - size.x / 2), (float)(y - size.y / 2)}, (float)fs,
             (float)TextStyle::kSpacing, color);
}
