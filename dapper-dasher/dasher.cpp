#include "raylib.h"

int main() 
{
  const int windowWidth{512};
  int windowHeight{380};
  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
  SetTargetFPS(60);

  const int width{50};
  const int height{80};
  
  int posY{windowHeight - height};
  int velocity{-10};

  while (!WindowShouldClose()) 
  {
    BeginDrawing();
    ClearBackground(WHITE);

    if (IsKeyPressed(KEY_SPACE)) 
    {
      velocity -= 10;
    }

    posY += velocity;
    
    DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

    EndDrawing();
  }
  CloseWindow();

  return 0;
}