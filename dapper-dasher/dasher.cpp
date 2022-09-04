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

  Rectangle nebRec2{0.0, 0.0, nebula.width / 8, nebula.width / 8};
  Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec2.height};

  // scarfy
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  Rectangle scarfyRec{0, 0, scarfy.width / 6, scarfy.height};
  Vector2 scarfyPos{windowWidth / 2 - scarfyRec.width / 2, windowHeight - scarfyRec.height};

  // scarfy animation vars
  int frame{0};
  const float updateTime{1.0/12.0};
  float runningTime{0.0};
  
  // nebula animation vars
  int nebFrame{0};
  const float nebUpdateTime(1.0/12.0);
  float nebRunningTime{0.0};

  int neb2Frame{0};
  const float neb2UpdateTime(1.0/16.0);
  float neb2RunningTime{0.0};

  int nebVelocity{-600}; // nebula X velocity (px/sec)
  int velocity{-10};
  bool isInAir = false;

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

    // update nebula2 position
    neb2Pos.x += nebVelocity * dt;

    // update scarfy position
    scarfyPos.y += velocity * dt;
    
    // update scarfy's animation
    if (!isInAir) {
      // update running time
      runningTime += dt;
      if (runningTime >= updateTime) {
        runningTime = 0.0;
        scarfyRec.x = frame * scarfyRec.width;
        frame++;
        if (frame > 5) {
          frame = 0;
        }
      }
    }

    // update nebula's animation
    nebRunningTime += dt;
    if (nebRunningTime >= nebUpdateTime) {
      nebRunningTime = 0.0;
      nebRec.x = nebFrame * nebRec.width;
      nebFrame++;
      if (nebFrame > 7) {
        nebFrame = 0;
      }
    }

    neb2RunningTime += dt;
    if (neb2RunningTime >= neb2UpdateTime) {
      neb2RunningTime = 0.0;
      nebRec2.x = neb2Frame * nebRec2.width;
      neb2Frame++;
      if (neb2Frame > 7) {
        neb2Frame = 0;
      }
    }

    DrawTextureRec(nebula, nebRec, nebPos, WHITE);
    DrawTextureRec(nebula, nebRec2, neb2Pos, RED);
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();

  return 0;
}