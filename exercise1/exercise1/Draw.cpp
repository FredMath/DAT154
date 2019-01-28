#include "stdafx.h"
#include "Draw.h"

COLORREF red = RGB(255, 0, 0);
COLORREF yellow = RGB(255, 255, 0);
COLORREF green = RGB(0, 255, 0);
COLORREF grey = RGB(192, 192, 192);
COLORREF black = RGB(0, 0, 0);



void drawTrafficLight(HDC hdc, int pos_x, int pos_y, bool state[])
{
	HBRUSH hBrush = CreateSolidBrush(black);
	HGDIOBJ hOrg = SelectObject(hdc, hBrush);

	int left = pos_x - 20;
	int right = pos_x + 20;
	int top = pos_y - 55;
	int bottom = pos_y + 55;
	int lightLeft = left + 5;
	int lightRight = right - 5;
	int distanceBetweenLights = 3;
	int redTop = top + distanceBetweenLights;
	int redBottom = redTop + 30;
	int yellowTop = redBottom + distanceBetweenLights;
	int yellowBottom = yellowTop + 30;
	int greenTop = yellowBottom + distanceBetweenLights;
	int greenBottom = greenTop + 30;

	Rectangle(hdc, left, top, right, bottom);
	

	if (state[0] == 1) {
		hBrush = CreateSolidBrush(red);
	}
	else
		hBrush = CreateSolidBrush(grey);

	hOrg = SelectObject(hdc, hBrush);
	Ellipse(hdc, lightLeft, redTop, lightRight, redBottom);

	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);

	if (state[1] == 1) {
		hBrush = CreateSolidBrush(yellow);
	}
	else
		hBrush = CreateSolidBrush(grey);

	hOrg = SelectObject(hdc, hBrush);
	Ellipse(hdc, lightLeft, yellowTop, lightRight, yellowBottom);

	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);
	DeleteObject(hOrg);
	if (state[2] == 1)
		hBrush = CreateSolidBrush(green);
	else
		hBrush = CreateSolidBrush(grey);

	hOrg = SelectObject(hdc, hBrush);
	Ellipse(hdc, lightLeft, greenTop, lightRight, greenBottom);

	SelectObject(hdc, hOrg);
	DeleteObject(hBrush);

	int rectWidth = right - left;
	
	MoveToEx(hdc, left + rectWidth / 2, bottom, 0);
	LineTo(hdc, left + rectWidth / 2, bottom + 100);

}

void drawRoad(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(grey);
	HGDIOBJ hOrg = SelectObject(hdc, hBrush);
	HGDIOBJ hPen;
	HGDIOBJ hPenOld;
	LOGBRUSH lb;
	lb.lbColor = yellow;
	lb.lbStyle = PS_SOLID;

	Rectangle(hdc, 0, 250, 1300, 350);
	Rectangle(hdc, 550, 0, 650, 1300);

	hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 15, &lb, 0, NULL);
	hPenOld = SelectObject(hdc, hPen);

	MoveToEx(hdc, 0, 300, 0);
	LineTo(hdc, 1300, 300);

	MoveToEx(hdc, 600, 0, 0);
	LineTo(hdc, 600, 1300);


	SelectObject(hdc, hOrg);
	DeleteObject(hOrg);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}



void drawCar(HDC hdc, Car &car) {
	HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HGDIOBJ hOrg = SelectObject(hdc, hBrush);

	int rectLeft = car.x_pos - 20;
	int rectRight = car.x_pos + 20;
	int rectTop = car.y_pos -20;
	int rectBottom = car.y_pos + 20;

	Rectangle(hdc, rectLeft, rectTop, rectRight, rectBottom);

	SelectObject(hdc, hOrg);
	DeleteObject(hOrg);
}




