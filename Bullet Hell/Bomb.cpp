#include "Bomb.h"
#include <algorithm>
#include <iostream>
using namespace std;

bomb::bomb(int x, int y) {
	xpos = x;
	ypos = y;
}

void bomb::move() {
	ypos -= 5;
}

bool bomb::draw(bool draw) {
	if (draw) {
		if (alive) {
			if (!flash) {
				al_draw_bitmap_region(boom, 0, 0, 32, 32, xpos, ypos, NULL);
			}
			else {
				al_draw_bitmap_region(boom, 0, 32, 32, 32, xpos, ypos, NULL);
			}
		}
		if (hit) {
			al_draw_bitmap_region(explode, 0, 64 * ticker, 64, 64, xpos - 16, ypos - 16, NULL);
			ticker++;
			if (ticker == 26) {
				ticker = 0;
				cout << "?????????" << endl;
				drawExplode = false;
				return false;
			}
		}
		return true;
	}
	return false;
}

void bomb::flashTimer() {
	if (shot) {
		timer++;
		if (timer > timerMax) {
			timer = 0;
			timerMax = 40;
		}
		if (timer == timerMax) {
			flash = !flash;
			timer = 0;
			timerMax -= 5;
			if (timerMax == 0) {
				kill();
			}
		}
	}
}

void bomb::kill() {
	alive = false;
	shot = false;
	drawExplode = true;
	timer = 0;
	timerMax = 30;
}

bool bomb::offScreen() {
	if (ypos < 0) {
		return true;
	}
	else {
		return false;
	}
}

void bomb::shoot(int x, int y) {
	cout << "Hey Hey Hey" << endl;
	alive = true;
	shot = true;
	xpos = x;
	ypos = y;
}

bool bomb::isAlive() {
	return alive;
}

int bomb::collide(bool collision) {
	if (collision && !hit) {
		kill();
		hit = true;
		return 75;
	}
	return 0;
}

int bomb::getx() {
	return xpos;
}

int bomb::gety() {
	return ypos;
}