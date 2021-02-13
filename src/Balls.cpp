#include "Balls.h"

void Balls::draw()
{

	DrawCircleV(pos, radius, ColorAlpha(intToColor(color),alpha));
	
}

void Balls::update()
{
	switch (status)
	{
	case Balls::NONE:

		break;

	case Balls::INIT:

		alpha += 0.05f;
		if (alpha > 1.0f)setStatus(NONE);

		break;

	case Balls::SWAP:

		if (this->pos.x > this->target.x)this->pos.x -= 2.0f;
		else if (this->pos.x < this->target.x)this->pos.x += 2.0f;
		else if (this->pos.y < this->target.y)this->pos.y += 2.0f;
		else if (this->pos.y > this->target.y)this->pos.y -= 2.0f;

		if ((int)this->pos.x == (int)this->target.x && (int)this->pos.y == (int)this->target.y)setStatus(NONE);

		break;

	case Balls::DELETING:

		alpha -= 0.05f;
		if (alpha < 0.0001f) {
			setStatus(NONE);
			setColor(6);
		}

		break;

	case Balls::FALL:

		pos.y += 4.0f;
		if((int)pos.y == (int)target.y)setStatus(NONE);

		break;
	}

}

size_t Balls::getColor()
{
    return this->color;
}

void Balls::setColor(size_t tColor)
{
    this->color = tColor;
}

Color Balls::intToColor(size_t randomValue)
{
	switch (randomValue)
	{
	case 0:
		return RED;
	case 1:
		return BEIGE;
	case 2:
		return GREEN;
	case 3:
		return BLUE;
	case 4:
		return DARKPURPLE;
	case 5:
		return ORANGE;
	case 6:
		return WHITE;
	}

}

void Balls::setStatus(State state)
{
	status = state;
}

Vector2 Balls::getPosition()
{
	return pos;
}

size_t Balls::getRow()
{
	return row;
}

size_t Balls::getCol()
{
	return col;
}

void Balls::swap(std::shared_ptr<Balls> other)
{
	std::swap(this->col, other->col);
	std::swap(this->row, other->row);
	

	this->target = other->pos;
	other->target = this->pos;

	this->setStatus(SWAP);
	other->setStatus(SWAP);
}

size_t Balls::getStatus()
{
	return this->status;
}

void Balls::fall(std::shared_ptr<Balls> other)
{
	std::swap(this->col, other->col);
	std::swap(this->row, other->row);


	other->target = Vector2{ this->pos.x,this->pos.y };
	this->pos = other->pos;

	other->setStatus(FALL);
}
