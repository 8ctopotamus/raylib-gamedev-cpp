#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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
    Vector2{800.f, 300.f},
    LoadTexture("characters/goblin_idle_spritesheet.png"),
    LoadTexture("characters/goblin_run_spritesheet.png")
  };

  Enemy slime{
    Vector2{500.f, 700.f},
    LoadTexture("characters/slime_idle_spritesheet.png"),
    LoadTexture("characters/slime_run_spritesheet.png")
  };

  Enemy* enemies[]{&goblin, &slime};
  for (auto enemy : enemies) {
    enemy->setTarget(&knight);
  }
  
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
    
    // draw text
    if (knight.getAlive()) {
      std::string knightsHealth = "Health: ";
      knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
      DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, WHITE);
    } else {
      DrawText("Game Over!", 55.f, 45.f, 40, RED);
      EndDrawing();
      continue;
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

    for (auto enemy : enemies) {
      enemy->tick(GetFrameTime());
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      for (auto enemy : enemies) {
        if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRect())) {
          enemy->setAlive(false);
        }
      }
    }
    
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}