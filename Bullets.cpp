#include "Bullets.h"

#include <algorithm>
#include<iostream>
using namespace std;

Bullets::Bullets(int x, int y) {
	xpos = x;
	ypos = y;
}

void Bullets::move(int health) {
	if (health > 800) {
		pattern = 1;
	}
	else if (health <= 800 && health > 400) {
		pattern = 2;
	}
	else if (health < 400) {
		pattern = 3;
	}
	if (pattern == 1) {
		angle += .01;
		xpos += 10 * cos(angle);
		ypos++;
	}
	if (pattern == 2) {
		angle += .01;
		xpos += 3 * sin(angle);
		ypos += 2;
	}
	if (pattern == 3) {
		angle += .05;
		xpos += 5 * sin(angle);
		ypos += 5;
	}
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

bool Bullets::collide(double x, double y, double w) {
	if (sqrt(((x+16 - xpos)*(x+16 - xpos)) + ((y+16 - ypos)*(y+16 - ypos))) <= radius+w) {
		return true;
	}
	else {
		return false;
	}
}

