# Gobang

Play Online (WebAssembly): https://qiekn.itch.io/gobang  
Notes (WIP): https://qiekn.notion.site/gobang

## Screenshots

<img width="1200" height="928" alt=" 2025-09-09 at 13 22 24" src="https://github.com/user-attachments/assets/41c8bdfb-9f62-4361-a941-df60973af7cd" />

<img width="1200" height="928" alt=" 2025-09-09 at 13 21 04" src="https://github.com/user-attachments/assets/ab5c3c05-db22-4038-a5f9-4a8d29122d8b" />

<img width="1200" height="928" alt=" 2025-09-09 at 07 58 50" src="https://github.com/user-attachments/assets/b398c547-8284-4ad7-8b11-a70d55e9acb9" />


## Screenshots

<img width="1200" height="928" alt=" 2025-09-09 at 13 22 24" src="https://github.com/user-attachments/assets/41c8bdfb-9f62-4361-a941-df60973af7cd" />

<img width="1200" height="928" alt=" 2025-09-09 at 13 21 04" src="https://github.com/user-attachments/assets/ab5c3c05-db22-4038-a5f9-4a8d29122d8b" />

<img width="1200" height="928" alt=" 2025-09-09 at 07 58 50" src="https://github.com/user-attachments/assets/b398c547-8284-4ad7-8b11-a70d55e9acb9" />


## Build for Desktop

```bash
cmake -S . -B build && cmake --build build
./build/game
```

## Build for WebAssembly

Read [Raylib Docs](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))

Install [emscripten toolchain](https://emscripten.org/docs/getting_started/downloads.html).
If you are on macOS, you can install Emscripten using Homebrew: `brew install emscripten`


!change path to you emsdk

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/Users/leoua7/Apps/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM=Web
make
