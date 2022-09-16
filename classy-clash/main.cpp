#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main() {
  int windowWidth{384};
  int windowHeight{384};
  InitWindow(windowWidth, windowHeight, "Classy Clash");
  
  SetTargetFPS(60);

  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0};
  const float mapScale{4.0};
  
  Character knight{windowWidth, windowHeight};
  Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset/Rock.png")};

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    
    // draw map
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
    DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
    
    // draw rock
    rock.render(knight.getWorldPos());
    
    // tick knight
    knight.tick(GetFrameTime());
    
    // check map bounds
    if (
      knight.getWorldPos().x < 0.f ||
      knight.getWorldPos().y < 0.f ||
      knight.getWorldPos().x + windowWidth > map.width * mapScale ||
      knight.getWorldPos().y + windowHeight > map.height * mapScale 
    ) {
      knight.undoMovement();
    } 
    
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}