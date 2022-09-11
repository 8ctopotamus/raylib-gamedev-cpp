#include "raylib.h"
#include "raymath.h"

// c^2 = a^2 * + b^2

int main() {
  int windowDimensions{384};
  InitWindow(windowDimensions, windowDimensions, "Classy Clash");
  
  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  SetTargetFPS(60);
  
  Vector2 mapPos{0.0, 0.0};
  
  while(!WindowShouldClose()) {
    float dT{ GetFrameTime() };
    BeginDrawing();
    ClearBackground(WHITE);
    
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
    
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}