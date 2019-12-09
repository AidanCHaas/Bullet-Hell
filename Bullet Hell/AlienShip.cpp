#include "AlienShip.h"

/*class AlienShip {
private:
	int xpos;
	int ypos;
	int xdir;
	int ydir;
	int xvel;
	int yvel;
	int hp;
	ALLEGRO_BITMAP *ship = al_load_bitmap("mothership.png");
public:
	AlienShip(int x, int y);
	void move();
	void draw();
	void ouchie();
	int getx();
	int gety();
	int gethp();
};*/

AlienShip::AlienShip(int x, int y) {
	xdir = 0;
	ydir = 2;
	xpos = x;
	ypos = y;
	al_draw_bitmap(ship, xpos, ypos, NULL);
	
}

void AlienShip::move() {
	if (xpos + 128 > 1700 || xpos < 100){
		xvel *= -1;
	}
	xpos += xvel;
	ypos += yvel;
}

void AlienShip::draw() {
	al_draw_bitmap(ship, xpos, ypos, NULL);
}

void AlienShip::ouchie(int ouch) {
	hp -= ouch;
}

int AlienShip::getx() {
	return xpos;
}

int AlienShip::gety() {
	return ypos;
}

int AlienShip::gethp() {
	return hp;
}