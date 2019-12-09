#pragma once
#include<allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>
class missile {
private:
	double xpos;
	double ypos;
	double angle;
	double radius;
	bool alive;
public:
	missile(int x, int y);
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