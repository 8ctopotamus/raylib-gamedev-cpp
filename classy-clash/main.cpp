#include "raylib.h"
#include "raymath.h"

// c^2 = a^2 * + b^2

int main() {
  int windowWidth{384};
  int windowHeight{384};
  InitWindow(windowWidth, windowHeight, "Classy Clash");
  
  SetTargetFPS(60);
  Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
  Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
  Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
  Vector2 knightPos{
    (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
    (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height),
  };
  // 1 = facing right, 2 = facing left
  float rightLeft{1.f};
  // animation variables
  float runningTime{};
  int frame{};
  const int maxFrames{6};
  const float updateTime{1.f/12.f};

  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
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
      rightLeft = direction.x < 0.f ? -1 : 1;
      knight = knight_run;
    } else {
      knight = knight_idle;
    }
    // draw map
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // update animation frame
    runningTime += GetFrameTime();
    if (runningTime >= updateTime) {
      frame++;
      runningTime = 0.f;
      if (frame > maxFrames) frame = 0;
    }

    // draw knight
    Rectangle source{frame * (float)knight.width/6.f, 0.f, (float)knight.width/6.f, (float)knight.height};
    Rectangle dest{knightPos.x, knightPos.y, 4.0f*(float)knight.width/6.0f, 4.0f*(float)knight.height};
    DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}