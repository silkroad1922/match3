#pragma once

#include "raylib.h"
#include "Balls.h"
#include <vector>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <memory>


class Board
{
public:
	
	enum State
	{
		NONE,ACTIVE
	};

	Board();

	void mix();
	void update();
	void draw();
	void click();
	void setStatus(State);
	void setMatch3();
	void appearBalls();

	bool findPossibleMatch();
	bool checkMatch3();
	bool fallDown();
	
	const size_t SIZE = 10;
	size_t clicked = 0;

private:
	std::vector<std::vector<std::shared_ptr<Balls>>> ballsGreed;
	std::shared_ptr<Balls> swap_ball_1;
	std::shared_ptr<Balls> swap_ball_2;
	State status;
	size_t score = 0;
};

