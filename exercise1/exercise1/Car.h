#pragma once
class Car
{


public:
	Car();
	Car(int x_pos, int y_pos, int width, int height,int speed);
	~Car();

	int x_pos;
	int y_pos;
	int width;
	int height;
	int speed;
	
};

