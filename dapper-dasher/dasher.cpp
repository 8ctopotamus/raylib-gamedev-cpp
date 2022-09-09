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
  
  AnimData nebulae[3]{};

  for (int i = 0; i < 3; i++) {
    nebulae[i].rec.x = 0.0;
    nebulae[i].rec.y = 0.0;
    nebulae[i].rec.width = nebula.width / 8;
    nebulae[i].rec.height = nebula.height / 8;
    nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
    nebulae[i].frame = 0;
    nebulae[i].runningTime = 0.0;
    nebulae[i].updateTime = 0.0;
  }
  nebulae[0].pos.x = windowDimensions[0];
  nebulae[1].pos.x = windowDimensions[0] + 300;
  nebulae[2].pos.x = windowDimensions[0] + 600;
  
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

    // update nebula position
    nebulae[0].pos.x += nebVelocity * dt;
    // update nebula2 position
    nebulae[1].pos.x += nebVelocity * dt;
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
    nebulae[0].runningTime += dt;
    if (nebulae[0].runningTime >= nebulae[0].updateTime) {
      nebulae[0].runningTime = 0.0;
      nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
      nebulae[0].frame++;
      if (nebulae[0].frame > 7) {
        nebulae[0].frame = 0;
      }
    }

    nebulae[1].runningTime += dt;
    if (nebulae[1].runningTime >= nebulae[1].updateTime) {
      nebulae[1].runningTime = 0.0;
      nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
      nebulae[1].frame++;
      if (nebulae[1].frame > 7) {
        nebulae[1].frame = 0;
      }
    }

    DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
    DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();

  return 0;
}