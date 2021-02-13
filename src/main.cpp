#include<iostream>
#include <string>
#include "raylib.h"
#include <vector>
#include "Board.h"

int main()
{
	Board board;
	board.mix();
	const int WW = 900;
	const int HW = 720;
	InitWindow(WW, HW, "Match3");
	
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		
		board.update();
		BeginDrawing();
		

			board.draw();
			ClearBackground(WHITE);
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				board.click();
			}

		EndDrawing();
	}

	return 0;
}