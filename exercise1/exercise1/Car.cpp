#include "stdafx.h"
#include "Car.h"


Car::Car()
{
}

Car::Car(int x_pos, int y_pos, int width, int height, int speed) {
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->width = width;
	this->height = height;
	this->speed = speed;
}


Car::~Car()
{
}
