#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main() {
  int windowWidth{384};
  int windowHeight{384};
  InitWindow(windowWidth, windowHeight, "Classy Clash");
  
  SetTargetFPS(60);

  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0};
  
  Character knight{};
  knight.setScreenPos(windowWidth, windowHeight);

  while(!WindowShouldClose()) {
    float dT{ GetFrameTime() };
    BeginDrawing();
    ClearBackground(WHITE);
    
    // draw map
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
    // tick knight
    knight.tick(dT);    

    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}