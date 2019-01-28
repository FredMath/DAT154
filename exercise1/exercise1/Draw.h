#pragma once

#include "stdafx.h"
#include "Car.h"
#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

	void drawTrafficLight(HDC hdc, int pos_x, int pos_y, bool state[]);
	void drawRoad(HDC hdc);
	void drawCar(HDC hdc, Car &car);
#endif

