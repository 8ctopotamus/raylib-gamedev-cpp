#include "raylib.h"

int main(void)
{
	int width{350};
	int height{200};
	InitWindow(width, height, "Josh's raylib window");

	int circle_x{175};
	int circle_y{100};
	
	SetTargetFPS(60);
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		
		DrawCircle(circle_x, circle_y, 25, BLUE);
		
		if (IsKeyDown(KEY_D) && circle_x < width)
		{
			circle_x = circle_x + 10;
		} 
		else if (IsKeyDown(KEY_A) && circle_x > 0)
		{
			circle_x = circle_x - 10;
		} 
		else if (IsKeyDown(KEY_W))
		{
			circle_y = circle_y - 10;
		} 
		else if (IsKeyDown(KEY_S))
		{
			circle_y = circle_y + 10;
		} 
		
		EndDrawing();
	}
	return 0;
}