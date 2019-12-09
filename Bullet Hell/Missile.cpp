#include "Missile.h"
#include <algorithm>

missile::missile(int x, int y) {
	xpos = x;
	ypos = y;
}

void missile::move() {
	ypos -= 15;
}

void missile::draw() {
	if (alive) {
		//al_draw_filled_circle(xpos, ypos, 5, al_map_rgb(150, 150, 150));
		al_draw_line(xpos + 16, ypos, xpos + 16, ypos + 15, al_map_rgb(150, 150, 150), 2);
	}
}

void missile::kill() {
	alive = false;
}

bool missile::offScreen() {
	if (ypos < 0) {
		return true;
	}
	else {
		return false;
	}
}

void missile::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool missile::isAlive() {
	return alive;
}

bool missile::collide(double x, double y) {
	if (sqrt(((x - xpos)*(x - xpos)) + ((y - ypos)*(y - ypos))) <= radius) {
		return true;
	}
	else {
		return false;
	}
}

int missile::getx() {
	return xpos;
}

int missile::gety() {
	return ypos;
}