#include "raylib.h"

struct AnimData {
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main() {
  const int windowWidth{512};
  int windowHeight{380};
  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
  SetTargetFPS(60);

  // acceleraction due to gravity: (pixels/second) / second
  const int gravity{1'000};
  const int jumpVelocity{-600}; // px / second
  int nebVelocity{-600}; // nebula X velocity (px/sec)
  int velocity{-10};
  bool isInAir = false;

  // nebulas
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  AnimData nebulaData{ 
    {0.0, 0.0, nebula.width / 8, nebula.width / 8}, // Rectangle rec
    {windowWidth, windowHeight - nebula.height / 8}, // Vector2 pos
    0, // int frame
    1.0/12.0, // float updateTime
    0.0 // float runningTime
  };
  AnimData nebula2Data{ 
    {0.0, 0.0, nebula.width / 8, nebula.width / 8}, // Rectangle rec
    {windowWidth + 300, windowHeight - nebula.height / 8}, // Vector2 pos
    0, // int frame
    1.0/16.0, // float updateTime
    0.0 // float runningTime
  };

  // scarfy
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width / 6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowHeight - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = 1.0/12.0;
  scarfyData.runningTime = 0.0;

  while (!WindowShouldClose()) {
    // delta time (time since last frame)
    float dt{ GetFrameTime() };

    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check 
    if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height) {
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
    nebulaData.pos.x += nebVelocity * dt;
    // update nebula2 position
    nebula2Data.pos.x += nebVelocity * dt;
    // update scarfy position
    scarfyData.pos.y += velocity * dt;
    
    // update scarfy's animation
    if (!isInAir) {
      // update running time
      scarfyData.runningTime += dt;
      if (scarfyData.runningTime >= scarfyData.updateTime) {
        scarfyData.runningTime = 0.0;
        scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
        scarfyData.frame++;
        if (scarfyData.frame > 5) {
          scarfyData.frame = 0;
        }
      }
    }

    // update nebula's animation
    nebulaData.runningTime += dt;
    if (nebulaData.runningTime >= nebulaData.updateTime) {
      nebulaData.runningTime = 0.0;
      nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
      nebulaData.frame++;
      if (nebulaData.frame > 7) {
        nebulaData.frame = 0;
      }
    }

    nebula2Data.runningTime += dt;
    if (nebula2Data.runningTime >= nebula2Data.updateTime) {
      nebula2Data.runningTime = 0.0;
      nebula2Data.rec.x = nebula2Data.frame * nebula2Data.rec.width;
      nebula2Data.frame++;
      if (nebula2Data.frame > 7) {
        nebula2Data.frame = 0;
      }
    }

    DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
    DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, RED);
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();

  return 0;
}