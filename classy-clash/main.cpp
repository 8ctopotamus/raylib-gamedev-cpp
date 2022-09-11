#include "raylib.h"

int main() {
  int windowDimensions{384};
  InitWindow(windowDimensions, windowDimensions, "Classy Clash");
  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  SetTargetFPS(60);
  while(!WindowShouldClose()) {
    float dT{ GetFrameTime() };
    BeginDrawing();
    ClearBackground(WHITE);
    Vector2 mapPos{0.0, 0.0};
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}