#include "raylib.h"

int main() {
  const int windowWidth{512};
  int windowHeight{380};
  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
  SetTargetFPS(60);

  // acceleraction due to gravity: (pixels/frame) / frame
  const int gravity{1};
  const int jumpVelocity{-22};

  const int width{50};
  const int height{80};
  
  bool isInAir = false;

  int posY{windowHeight - height};
  int velocity{-10};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check 
    if (posY >= windowHeight - height) {
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
    posY += velocity;
    
    DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

    EndDrawing();
  }
  CloseWindow();

  return 0;
}