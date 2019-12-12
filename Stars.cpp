#include "Stars.h"

stars::stars() {
	x = rand() % 1920;
	y = rand() % 1080;
	rg = rand() % 200;
	b = rand() % 150 + 100;
	size = 2;
}

void stars::draw() {
	al_draw_filled_circle(x, y, size, al_map_rgb(rg, rg, b));
}

void stars::move() {
	y += 10;
}

void stars::preposition() {
	if (y > 1082) {
		y = -2;
	}
}