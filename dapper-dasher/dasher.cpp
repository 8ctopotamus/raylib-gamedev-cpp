#include "raylib.h"

int main() {
  const int windowWidth{512};
  int windowHeight{380};
  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
  SetTargetFPS(60);

  // acceleraction due to gravity: (pixels/frame) / frame
  const int gravity{1};
  const int jumpVelocity{-22};

  // scarfy
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  Rectangle scarfyRec;
  scarfyRec.width = scarfy.width / 6;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;
  Vector2 scarfyPos;
  scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
  scarfyPos.y = windowHeight - scarfyRec.height;

  bool isInAir = false;
  int velocity{-10};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check 
    if (scarfyPos.y >= windowHeight - scarfyRec.height) {
      // rectangle is on ground
      velocity = 0;
      isInAir = false;
    } else {
      // apply gravity if in air
      velocity += gravity;
      isInAir = true;
    }

    // jump
    if (IsKeyPressed(KEY_SPACE) && !isInAir) {
      velocity += jumpVelocity;
    }

    // update position
    scarfyPos.y += velocity;
    
    // TODO: https://www.udemy.com/course/cpp-fundamentals/learn/lecture/26327620#overview
    // DrawTextureRec(scarfy, scarfyRec, scarfyPos, w)

    EndDrawing();
  }
  CloseWindow();

  return 0;
}