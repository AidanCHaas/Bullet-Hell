#pragma once
#include<allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>
class stars {
private:
	int x;
	double y;
	int rg;
	int b;
	int size;
public:
	stars();
	void draw();
	void move();
	void preposition();
};