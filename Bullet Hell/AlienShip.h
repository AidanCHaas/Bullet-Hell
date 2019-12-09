#pragma once
#include<allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>

class AlienShip {
private:
	int xpos;
	int ypos;
	int xdir;
	int ydir;
	int xvel = 10;
	int yvel = 0;
	int hp = 1000;
	ALLEGRO_BITMAP *ship = al_load_bitmap("mothership.png");
public:
	AlienShip(int x, int y);
	void move();
	void draw();
	void ouchie(int ouch);
	int getx();
	int gety();
	int gethp();
};