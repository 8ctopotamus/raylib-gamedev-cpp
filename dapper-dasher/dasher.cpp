#include "raylib.h"

struct AnimData {
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

bool isOnGround(AnimData data, int windowHeight) {
  return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrames) {
  data.runningTime += deltaTime;
  if (data.runningTime >= data.updateTime) {
    data.runningTime = 0.0;
    data.rec.x = data.frame * data.rec.width;
    data.frame++;
    if (data.frame > maxFrames) {
      data.frame = 0;
    }
  }
  return data;
}

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

  Texture2D background = LoadTexture("textures/far-buildings.png");
  float bgX{};

  Texture2D midground = LoadTexture("textures/back-buildings.png");
  float mgX{};

  Texture2D foreground = LoadTexture("textures/foreground.png");
  float fgX{};

  while (!WindowShouldClose()) {
    // delta time (time since last frame)
    float dt{ GetFrameTime() };

    BeginDrawing();
    ClearBackground(WHITE);

    // draw background
    bgX -= 20 * dt;
    if (bgX <= -background.width*2) {
      bgX = 0.0;
    }
    Vector2 bgPos{bgX, 0.0};
    Vector2 bg2Pos{bgX + background.width*2, 0.0};
    DrawTextureEx(background, bgPos, 0.0, 2.0, WHITE);
    DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
    // draw midground
    mgX -= 40 * dt;
    if (mgX <= -midground.width*2) {
      mgX = 0.0;
    }
    Vector2 mgPos{mgX, 0.0};
    Vector2 mg2Pos{mgX + midground.width*2, 0.0};
    DrawTextureEx(midground, mgPos, 0.0, 2.0, WHITE);
    DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
    // draw foreground
    fgX -= 80 * dt;
    if (fgX <= -foreground.width*2) {
      fgX = 0.0;
    }
    Vector2 fgPos{fgX, 0.0};
    Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
    DrawTextureEx(foreground, fgPos, 0.0, 2.0, WHITE);
    DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

    // perform ground check 
    if (isOnGround(scarfyData, windowDimensions[1])) {
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
      scarfyData = updateAnimData(scarfyData, dt, 5);
    }

    // update nebula's animation
    for (int i = 0; i < sizeOfNebulae; i++) {
      nebulae[i] = updateAnimData(nebulae[i], dt, 8);
      DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
    }

    // draw scarfy 
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);
  CloseWindow();

  return 0;
}