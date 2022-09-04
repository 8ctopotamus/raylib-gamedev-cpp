#include "raylib.h"

int main() {
  const int windowWidth{512};
  int windowHeight{380};
  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
  SetTargetFPS(60);

  // acceleraction due to gravity: (pixels/second) / second
  const int gravity{1'000};
  const int jumpVelocity{-600}; // px / second

  // nebula
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.width / 8};
  Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
  int nebVelocity{-600}; // nebula X velocity (px/sec)

  // scarfy
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  Rectangle scarfyRec{0, 0, scarfy.width / 6, scarfy.height};
  Vector2 scarfyPos{windowWidth / 2 - scarfyRec.width / 2, windowHeight - scarfyRec.height};

  bool isInAir = false;
  int velocity{-10};
  int frame{0};

  const float updateTime{1.0/12.0};
  float runningTime{0};

  while (!WindowShouldClose()) {
    // delta time (time since last frame)
    float dt{ GetFrameTime() };

    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check 
    if (scarfyPos.y >= windowHeight - scarfyRec.height) {
      // rectangle is on ground
      velocity = 0;
      isInAir = false;
    } else {
      // apply gravity if in air
      velocity += gravity * dt;
      isInAir = true;
    }

    // jump
    if (IsKeyPressed(KEY_SPACE) && !isInAir) {
      velocity += jumpVelocity;
    }

    // update nebula position
    nebPos.x += nebVelocity * dt;

    // update scarfy position
    scarfyPos.y += velocity * dt;
    
    if (!isInAir) {
      // update running time
      runningTime += dt;
      if (runningTime >= updateTime) {
        runningTime = 0;
        // update animation frame
        scarfyRec.x = frame * scarfyRec.width;
        nebRec.x = frame * nebRec.width;
        frame++;
        if (frame > 5) {
          frame = 0;
        }
      }
    }

    DrawTextureRec(nebula, nebRec, nebPos, WHITE);
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();

  return 0;
}