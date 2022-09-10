#include "raylib.h"

struct AnimData {
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main() {
  int windowDimensions[2];
  windowDimensions[0] = 512;
  windowDimensions[1] = 380;

  InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");
  SetTargetFPS(60);

  // acceleraction due to gravity: (pixels/second) / second
  const int gravity{1'000};
  const int jumpVelocity{-600}; // px / second
  int nebVelocity{-600}; // nebula X velocity (px/sec)
  int velocity{-10};
  bool isInAir = false;

  // nebulas
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  const int initialNebXSpacing = 300;
  const int sizeOfNebulae{10};
  AnimData nebulae[sizeOfNebulae]{};
  for (int i = 0; i < sizeOfNebulae; i++) {
    nebulae[i].rec.x = 0.0;
    nebulae[i].rec.y = 0.0;
    nebulae[i].rec.width = nebula.width / 8;
    nebulae[i].rec.height = nebula.height / 8;
    nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
    nebulae[i].frame = 0;
    nebulae[i].runningTime = 0.0;
    nebulae[i].updateTime = 0.0;
    nebulae[i].pos.x = windowDimensions[0] + i * initialNebXSpacing;
  }
  
  // scarfy
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width / 6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = 1.0/12.0;
  scarfyData.runningTime = 0.0;

  while (!WindowShouldClose()) {
    // delta time (time since last frame)
    float dt{ GetFrameTime() };

    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check 
    if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height) {
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

    // update nebulae position
    for (int i = 0; i < sizeOfNebulae; i++) {
      nebulae[i].pos.x += nebVelocity * dt;
    }

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
    for (int i = 0; i < sizeOfNebulae; i++) {
      nebulae[i].runningTime += dt;
      if (nebulae[i].runningTime >= nebulae[i].updateTime) {
        nebulae[i].runningTime = 0.0;
        nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
        nebulae[i].frame++;
        if (nebulae[i].frame > 7) {
          nebulae[i].frame = 0;
        }
      }
      DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
    }

    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();

  return 0;
}