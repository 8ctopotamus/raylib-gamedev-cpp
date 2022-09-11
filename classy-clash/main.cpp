#include "raylib.h"
#include "raymath.h"

// c^2 = a^2 * + b^2

int main() {
  int windowWidth{384};
  int windowHeight{384};
  InitWindow(windowWidth, windowHeight, "Classy Clash");
  
  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  SetTargetFPS(60);

  Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
  Vector2 knightPos{
    (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
    (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height),
  };

  Vector2 mapPos{0.0, 0.0};
  float speed{4.0};
  
  while(!WindowShouldClose()) {
    float dT{ GetFrameTime() };
    BeginDrawing();
    ClearBackground(WHITE);
    
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    if (Vector2Length(direction) != 0.0) {
      mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
    } 
    // draw map
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
    // draw knight
    // DrawTexturePro(knight, knightPos);

    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}