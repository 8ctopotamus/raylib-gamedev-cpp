#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main() {
  int windowWidth{384};
  int windowHeight{384};
  InitWindow(windowWidth, windowHeight, "Classy Clash");
  
  SetTargetFPS(60);

  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0};
  const float mapScale{4.0};
  
  Character knight{windowWidth, windowHeight};

  Prop props[2] {
    Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
    Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}, 
  };

  Enemy goblin{
    Vector2{},
    LoadTexture("characters/goblin_idle_spritesheet.png"),
    LoadTexture("characters/goblin_run_spritesheet.png")
  };
  
  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    
    // draw map
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
    DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
    
    // draw props
    for (auto prop : props) {
      prop.render(knight.getWorldPos());
    }
    
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

    // check prop collisions
    for (auto prop : props) {
      if ( CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()) ) {
        knight.undoMovement();
      }
    }

    goblin.tick(GetFrameTime());
    
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}