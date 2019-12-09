#pragma once
#include<allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>
class bomb {
private:
	double xpos;
	double ypos;
	double angle;
	double radius;
	bool alive = true;
	bool flash = false;
	int timer = 0;
	int timerMax = 30;
	bool shot = false;
	int ticker = 0;
	bool drawExplode = false;
	bool hit = false;
	ALLEGRO_BITMAP *boom = al_load_bitmap("bomb.png");
	ALLEGRO_BITMAP *explode = al_load_bitmap("explode.png");
public:
	bomb(int x, int y);
	void move();
	bool draw(bool draw);
	void kill();
	bool offScreen();
	bool isAlive();
	int getx();
	int gety();
	void shoot(int x, int y);
	int collide(bool collision);
	void flashTimer();
};