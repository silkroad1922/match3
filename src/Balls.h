#pragma once

#include "raylib.h"
#include <iostream>

class Balls
{
public:

	enum State
	{
		NONE,INIT,SWAP,DELETING,FALL
	};

	Balls(Vector2 xy, size_t radius, size_t color, size_t row, size_t col, State stat) :pos(xy), radius(radius), color(color), row(row), col(col), status(stat) {};

	void draw();
	void update();
	void setColor(size_t);
	void setStatus(State);
	void fall(std::shared_ptr<Balls>);
	void swap(std::shared_ptr<Balls> other);

	size_t getColor();
	size_t getRow();
	size_t getCol();
	size_t getStatus();

	Color intToColor(size_t);
	Vector2 getPosition();
	
	const static size_t TARGET_RADIUS = 29;
	const static size_t SIZE = 10;
	const static size_t CELL = 60;

private:
	Vector2 pos;
	Vector2 target;
	size_t radius;
	size_t color;
	size_t row;
	size_t col;
	State status;
	float alpha = 0.0f;
};

