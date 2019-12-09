#include "Bullets.h"

#include <algorithm>

Bullets::Bullets(int x, int y) {
	xpos = x;
	ypos = y;
}

void Bullets::move() {
	angle += .01;
	xpos += 10*cos(angle);
	ypos++;
}

void Bullets::draw() {
	if (alive) {
		al_draw_filled_circle(xpos, ypos, radius, al_map_rgb(255, 0, 0));
	}
}

void Bullets::kill() {
	alive = false;
}

bool Bullets::offScreen() {
	if (ypos < 0) {
		return true;
	}
	else {
		return false;
	}
}

void Bullets::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool Bullets::isAlive() {
	return alive;
}

int Bullets::getx() {
	return xpos;
}

int Bullets::gety() {
	return ypos;
}

bool Bullets::collide(double x, double y) {
	if (sqrt(((x-16 - xpos)*(x+16 - xpos)) + ((y-16 - ypos)*(y+16 - ypos))) <= radius) {
		return true;
	}
	else {
		return false;
	}
}

