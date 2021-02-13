#include "Board.h"

Board::Board()
{
	srand(time(NULL));
	ballsGreed.resize(SIZE);
	for (size_t i = 0; i < SIZE; i++)
	{
		ballsGreed[i].resize(SIZE);
	}
}

void Board::mix()
{
	for (size_t y = 0; y < SIZE; y++)
	{
		for (size_t x = 0; x < SIZE; x++)
		{
			ballsGreed[y][x] = std::make_shared<Balls>(Vector2{ float(x + 1) * Balls::CELL,float(y + 1) * Balls::CELL }, Balls::TARGET_RADIUS, rand() % 6, y, x, Balls::State::INIT);
			if (y > 1)
			{
				if (ballsGreed[y][x]->getColor() == ballsGreed[y - 1][x]->getColor() && ballsGreed[y][x]->getColor() == ballsGreed[y - 2][x]->getColor())
				{
					size_t tColor = ballsGreed[y][x]->getColor();
					while (tColor == ballsGreed[y][x]->getColor())
					{
						tColor = rand() % 6;
					}
					ballsGreed[y][x]->setColor(tColor);
				}
			}
			if (x > 1)
			{
				if (ballsGreed[y][x]->getColor() == ballsGreed[y][x - 1]->getColor() && ballsGreed[y][x]->getColor() == ballsGreed[y][x - 2]->getColor())
				{
					size_t tColor = ballsGreed[y][x]->getColor();
					while (tColor == ballsGreed[y][x]->getColor())
					{
						tColor = rand() % 6;
					}
					ballsGreed[y][x]->setColor(tColor);
				}
			}
		}
	}

}

void Board::update()
{
	setStatus(NONE);
	for (auto& rowVector : ballsGreed)
	{
		for (auto& ball : rowVector)
		{
			ball->update();

			if (ball->getStatus() != Balls::NONE)setStatus(ACTIVE);

		}
	}
	switch (status)
	{
	case Board::NONE:

		if (!findPossibleMatch())
		{
			mix();
		}

		if (checkMatch3())
		{
			setMatch3();
		}
		else if (fallDown())
		{
			fallDown();
		}
		else
		{
			appearBalls();
		}
		break;

	case Board::ACTIVE:
		break;
	}
}


void Board::draw()
{

	DrawText(TextFormat("SCORE : %i",score), 650, 50,20,RED);

	for (auto& rowVector : ballsGreed)
	{
		for (auto& ball : rowVector)
		{
			ball->draw();
		}
	}
}

void Board::click()
{
	clicked++;
	if (clicked == 1)
	{
		for (auto& rowVector : ballsGreed)
		{
			for (auto& ball : rowVector)
			{
				if (CheckCollisionPointCircle(GetMousePosition(), ball->getPosition(), Balls::TARGET_RADIUS))
				{
					swap_ball_1 = ball;
					return;
				}
			}
		}
		clicked = 0;
	}
	if (clicked == 2)
	{
		for (auto& rowVector : ballsGreed)
		{
			for (auto& ball : rowVector)
			{
				if (CheckCollisionPointCircle(GetMousePosition(), ball->getPosition(), Balls::TARGET_RADIUS))
				{
					swap_ball_2 = ball;
					if (abs(int(swap_ball_1->getCol() - swap_ball_2->getCol())) + abs(int(swap_ball_1->getRow() - swap_ball_2->getRow())) == 1)
					{
						std::iter_swap(swap_ball_1, swap_ball_2);
						if (checkMatch3()) {
							clicked = 0;
							swap_ball_2->swap(swap_ball_1);
						}
						else
						{
							std::iter_swap(swap_ball_2, swap_ball_1);
						}
					}
					else clicked = 1;
				}
			}
		}
		clicked = 0;
	}
}

bool Board::findPossibleMatch()
{
	for (size_t y = 0; y < SIZE; y++)
	{
		for (size_t x = 0; x < SIZE; x++)
		{
			size_t color = ballsGreed[y][x]->getColor();
			if (y < SIZE - 1 && color == ballsGreed[y + 1][x]->getColor())
			{

				if (y < SIZE - 3 && ballsGreed[y + 3][x]->getColor() == color)return true;
				if (y < SIZE - 2 && x < SIZE - 1 && ballsGreed[y + 2][x + 1]->getColor() == color)return true;
				if (y < SIZE - 2 && x > 0 && ballsGreed[y + 2][x - 1]->getColor() == color)return true;
				if (y > 0 && x > 0 && ballsGreed[y - 1][x - 1]->getColor() == color)return true;
				if (y > 0 && x < SIZE - 1 && ballsGreed[y - 1][x + 1]->getColor() == color)return true;
				if (y > 1 && ballsGreed[y - 2][x]->getColor() == color)return true;
			}
			if (x < SIZE - 1 && color == ballsGreed[y][x + 1]->getColor())
			{
				if (x < SIZE - 3 && ballsGreed[y][x + 3]->getColor() == color)return true;
				if (x < SIZE - 2 && y> 0 && ballsGreed[y - 1][x + 2]->getColor() == color)return true;
				if (x < SIZE - 2 && y < SIZE - 1 && ballsGreed[y + 1][x + 2]->getColor() == color)return true;
				if (x > 0 && y > 0 && ballsGreed[y - 1][x - 1]->getColor() == color)return true;
				if (x > 0 && y < SIZE - 1 && ballsGreed[y + 1][x - 1]->getColor() == color)return true;
				if (x > 1 && ballsGreed[y][x - 2]->getColor() == color)return true;
			}
			if (y < SIZE - 2 && color == ballsGreed[y + 2][x]->getColor())
			{
				if (x < SIZE - 1 && ballsGreed[y + 1][x + 1]->getColor() == color)return true;
				if (x > 0 && ballsGreed[y + 1][x - 1]->getColor() == color)return true;
			}
			if (x < SIZE - 2 && color == ballsGreed[y][x + 2]->getColor())
			{
				if (y > 0 && ballsGreed[y - 1][x + 1]->getColor() == color)return true;
				if (y < SIZE - 1 && ballsGreed[y + 1][x + 1]->getColor() == color)return true;
			}
		}
	}
	return false;
}

bool Board::checkMatch3()
{
	for (size_t y = 0; y < SIZE; y++)
	{
		for (size_t x = 0; x < SIZE; x++)
		{
			size_t color = ballsGreed[y][x]->getColor();

			if (x < SIZE - 2 && color != 6)
			{
				if (color == ballsGreed[y][x + 1]->getColor() && color == ballsGreed[y][x + 2]->getColor() )
				{
					return true;
				}
			}
			if (y < SIZE - 2 && color != 6)
			{
				if (color == ballsGreed[y + 1][x]->getColor() && color == ballsGreed[y + 2][x]->getColor() )
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Board::setStatus(State state)
{
	status = state;
}

void Board::setMatch3()
{
	for (size_t y = 0; y < SIZE; y++)
	{
		for (size_t x = 0; x < SIZE; x++)
		{
			size_t colorX = ballsGreed[y][x]->getColor();
			size_t colorY = ballsGreed[y][x]->getColor();
			if (x < SIZE - 2 && colorX != 6)
			{
				if (colorX == ballsGreed[y][x + 1]->getColor() && colorX == ballsGreed[y][x + 2]->getColor() )
				{
					score += 10;
					ballsGreed[y][x]->setStatus(Balls::DELETING);
					while (x < SIZE - 1 && colorX == ballsGreed[y][++x]->getColor() )
					{
						ballsGreed[y][x]->setStatus(Balls::DELETING);
						score += 10;
					}
				}
			}
			if (y < SIZE - 2 && colorY != 6)
			{
				if (colorY == ballsGreed[y + 1][x]->getColor() && colorY == ballsGreed[y + 2][x]->getColor() )
				{
					score += 10;
					ballsGreed[y][x]->setStatus(Balls::DELETING);
					while (y < SIZE - 1 && colorY == ballsGreed[++y][x]->getColor())
					{
						ballsGreed[y][x]->setStatus(Balls::DELETING);
						score += 10;
					}
				}
			}
		}
	}
}

bool Board::fallDown()
{	
	bool flag = false;
	for (int y = SIZE-2; y >= 0; y--)
	{
		for (int x = SIZE-1; x >= 0; x--)
		{
			if (ballsGreed[y + 1][x]->getColor() == 6 && ballsGreed[y][x]->getColor() != 6)
			{
				flag = true;
				int t = y + 1;
				while (t < 10 && ballsGreed[t][x]->getColor() == 6 )
				{
					t++;
				}
				t--;
				std::iter_swap(ballsGreed[y][x], ballsGreed[t][x]);
				ballsGreed[y][x]->fall(ballsGreed[t][x]);
			}
		}
	}
	return flag;
}

void Board::appearBalls()
{
	for (size_t y = 0; y < SIZE; y++)
	{
		for (size_t x = 0; x < SIZE; x++)
		{
			if (ballsGreed[y][x]->getColor() == 6)
			{
				ballsGreed[y][x]->setColor(rand() % 6);
				ballsGreed[y][x]->setStatus(Balls::INIT);
			}
		}
	}
}


