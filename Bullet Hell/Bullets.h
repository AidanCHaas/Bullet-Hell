#pragma once
#include<allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>

class Bullets
{
private:
	double xpos=0;
	double ypos=0;
	double angle = 0;
	double radius = 10;
	bool alive;
public:
	Bullets(int x, int y);
	void move();
	void draw();
	void kill();
	bool offScreen();
	bool isAlive();
	int getx();
	int gety();
	void shoot(int x, int y);
	bool collide(double x, double y);
};