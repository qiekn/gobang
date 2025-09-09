#pragma once

#include <filesystem>

const std::filesystem::path kAssets = ASSETS;
const std::filesystem::path kFontPath = kAssets / "fonts";
const std::filesystem::path kImagePath = kAssets / "images";

const int kScreenWidth = 1200;
const int kScreenHeight = 900;

const int kFPS = 120;
