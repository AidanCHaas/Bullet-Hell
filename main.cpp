#include "Stars.h"
#include "Bomb.h"
#include "Missile.h"
#include "AlienShip.h"
#include "Bullets.h"

#include<vector>
#include<allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<ctime>
#include<iostream>
using namespace std;


//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 1920;
const int SCREEN_H = 1080;
const bool doIntro = true;

const int ALIEN_W = 128;
const int ALIEN_H = 64;

bool collision(int x1, int y1, int x2, int y2, int w, int h);

//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_B, KEY_SHIFT, KEY_CTRL
};

enum DIRECTIONS {
	UP, DOWN, LEFT, RIGHT
};

int main()
{
	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	srand(time(NULL));

	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP *shipPic = al_load_bitmap("ship.png");
	ALLEGRO_BITMAP *dinopic = al_load_bitmap("dino.png");
	ALLEGRO_BITMAP *boom = al_load_bitmap("bomb.png");

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(SCREEN_W, SCREEN_H);

	al_hide_mouse_cursor(display);

	al_start_timer(timer);

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	if (doIntro) {
		//start dark for a second
		for (float i = 0; i < 1; i += .0005) {
			al_clear_to_color(al_map_rgb(255, 255, 255));
		}
		//fade in
		for (float i = 0; i < 1; i += .0008) {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, i), SCREEN_W / 2 - 400, SCREEN_H / 2 - 400, NULL);
			al_flip_display();
		}
		//stay solid for a second
		for (float i = 0; i < 1; i += .001) {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, 1), SCREEN_W / 2 - 400, SCREEN_H / 2 - 400, NULL);
			al_flip_display();
		}
		//fade out
		for (float i = 1; i > 0; i -= .0005) {
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_tinted_bitmap(dinopic, al_map_rgba_f(i, 1, 1, i), SCREEN_W / 2 - 400, SCREEN_H / 2 - 400, NULL);
			al_flip_display();
		}
	}

	al_destroy_bitmap(dinopic);

	//star vector
	vector<stars *> starfield;
	vector<stars *>::iterator iter3;
	for (int i = 1; i < 100; i++) {
		stars *newStar = new stars();
		starfield.push_back(newStar);
	}

	//position of player
	double xPos = 400;
	double yPos = 700;

	//missile vector
	vector<missile *> missiles;
	vector<missile *>::iterator iter2;
	for (int i = 0; i < 40; i++) {
		missile *newMissile = new missile(0, 0);
		missiles.push_back(newMissile);
	}

	//bomb vector
	vector<bomb *> bombs;
	vector<bomb *>::iterator iter4;
	for (int i = 0; i < 4; i++) {
		bomb *newBomb = new bomb(0, 0);
		bombs.push_back(newBomb);
	}

	//another bomb vector (weird solution to a weird problem)
	vector<bool> bombas;
	vector<bool>::iterator iter5;
	for (int i = 0; i < 4; i++) {
		bombas.push_back(true);
	}

	//bullets vector
	vector <Bullets *> bullets;
	vector <Bullets *>::iterator iter6;

	//declare ship
	AlienShip mothership(SCREEN_W / 2, 100);

	//game variables
	bool key[8] = { false, false, false, false, false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop
	int ticker = 0;
	int cellNum = 0;
	int dir = 0;
	int justShot = 0;
	int bombShot = 0;
	int bombsRemaining = 3;
	float speedmod = 1;
	int counter = 0;
	double minBullets = 60;
	int lives = 3;

	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (!doexit)//game loop!
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			ticker++;
			if (ticker > 10) {
				ticker = 0;
			}

			if (ticker == 0) {
				cellNum++;
			}
			
			if (dir == UP || dir == DOWN) {
				if (cellNum > 4) {
					cellNum = 0;
				}
			}
			if (dir == LEFT || dir == RIGHT) {
				if (cellNum < 5) {
					cellNum = 5;
				}
				if (cellNum > 9) {
					cellNum = 5;
				}
			}

			mothership.move();

			//instantiate bullets
			counter++;
			if (minBullets > 10) {
				minBullets -= .1;
			}
			if (counter > minBullets) {
				Bullets *newBullets = new Bullets(mothership.getx(), mothership.gety());
				bullets.push_back(newBullets);
				counter = 0;
			}

			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP]) {
				yPos -= 8.0*speedmod;
			}

			if (key[KEY_DOWN]) {
				yPos += 8.0*speedmod;
			}

			if (key[KEY_LEFT]) {
				xPos -= 8.0*speedmod;
			}

			if (key[KEY_RIGHT]) {
				xPos += 8.0*speedmod;
			}

			if (key[KEY_SHIFT]) {
				speedmod = .5;
			}

			if (!key[KEY_SHIFT]) {
				speedmod = 1;
			}			

			justShot++;
			bombShot++;

			if (key[KEY_SPACE]) {
				for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
					if (((*iter2)->isAlive()) == false && justShot > 5) {
						(*iter2)->shoot(xPos, yPos);
						justShot = 0;
					}
				}
			}

			if (key[KEY_B] && bombsRemaining > 0) {
				for (iter4 = bombs.begin(); iter4 != bombs.end(); iter4++) {
					if (((*iter4)->isAlive()) == false && bombShot > 300) {
						(*iter4)->shoot(xPos, yPos);
						bombShot = 0;
						bombsRemaining--;
					}
				}
			}

			for (iter4 = bombs.begin(); iter4 != bombs.end(); iter4++) {
				(*iter4)->flashTimer();	
			}

			if (key[KEY_RIGHT]) {
				dir = RIGHT;
			}
			else if (key[KEY_LEFT]) {
				dir = LEFT;
			}
			else {
				dir = UP;
			}

			//move the missiles
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				if ((*iter2)->isAlive()) {
					(*iter2)->move();
				}
			}

			//missile collision
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				if (collision((*iter2)->getx(), (*iter2)->gety(), mothership.getx(), mothership.gety(), ALIEN_W, ALIEN_H) && (*iter2)->isAlive()) {
					cout << "got em" << endl;
					(*iter2)->kill();
					mothership.ouchie(5);
				}
			}

			//cull the missiles
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				if ((*iter2)->offScreen()) {
					(*iter2)->kill();
				}
			}

			//move the bombs
			for (iter4 = bombs.begin(); iter4 != bombs.end(); iter4++) {
				if ((*iter4)->isAlive()) {
					(*iter4)->move();
				}
			}

			//collision
			for (iter4 = bombs.begin(); iter4 != bombs.end(); iter4++) {
				mothership.ouchie((*iter4)->collide(collision((*iter4)->getx(), (*iter4)->gety(), mothership.getx(), mothership.gety(), ALIEN_W, ALIEN_H)));
			}

			//cull the bombs
			for (iter4 = bombs.begin(); iter4 != bombs.end(); iter4++) {
				if ((*iter4)->offScreen()) {
					(*iter4)->kill();
				}
			}

			//Move the Bullets
			for (iter6 = bullets.begin(); iter6 != bullets.end(); iter6++) {
				if ((*iter6)->isAlive()) {
					(*iter6)->move(mothership.gethp());
				}
			}

			//collision
			for (iter6 = bullets.begin(); iter6 != bullets.end(); iter6++) {
				if ((*iter6)->collide(xPos+16, yPos+16, 8)) {
					lives--;
					xPos = SCREEN_W / 2;
					yPos = SCREEN_H / 2;
					for (iter6 = bullets.begin(); iter6 != bullets.end(); iter6++) {
						(*iter6)->kill();
						(*iter6)->~Bullets();
					}
					bullets.erase(bullets.begin(), bullets.end());
					break;
				}
			}

			//cull the bullets
			for (iter6 = bullets.begin(); iter6 != bullets.end(); iter6++) {
				if ((*iter6)->offScreen()) {
					(*iter6)->kill();
					(*iter6)->~Bullets();
					iter6 = bullets.erase(iter6);
				}
			}

			//win condition
			if (mothership.gethp() <= 0) {
				break;
			}
			if (lives < 0) {
				break;
			}

			redraw = true;
		}
		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_W:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_S:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_A:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_D:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;

			case ALLEGRO_KEY_B:
				key[KEY_B] = true;
				break;

			case ALLEGRO_KEY_LSHIFT:
				key[KEY_SHIFT] = true;
				break;

			case ALLEGRO_KEY_RSHIFT:
				key[KEY_SHIFT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_W:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_S:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_A:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_D:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;

			case ALLEGRO_KEY_B:
				key[KEY_B] = false;
				break;

			case ALLEGRO_KEY_LSHIFT:
				key[KEY_SHIFT] = false;
				break;

			case ALLEGRO_KEY_RSHIFT:
				key[KEY_SHIFT] = false;
				break;
			}
		}
		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing (without this things smear)

			//move and draw stars
			for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
				(*iter3)->preposition();
				(*iter3)->move();
				(*iter3)->draw();
			}

			//draw mothership
			mothership.draw();

			//draw missiles
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				(*iter2)->draw();
			}

			for (iter6 = bullets.begin(); iter6 != bullets.end(); iter6++) {
				(*iter6)->draw();
			}

			//draw bombs
			iter5 = bombas.begin();
			for (iter4 = bombs.begin(); iter4 != bombs.end(); iter4++) {
				*iter5 = (*iter4)->draw(*iter5);
				if (!*iter5) {
					bombs.erase(iter4);
					bombas.erase(iter5);
					iter5 = bombas.begin();
					iter4 = bombs.begin();
				}
				if (iter5 != bombas.end()) {
					iter5++;
				}
			}

			for (int i = 0; i < bombsRemaining; i++) {
				al_draw_bitmap_region(boom, 0, 0, 32, 32, 20, 20 + (52 * i), NULL);
			}
			al_draw_rectangle(15, 15, 57, 166, al_map_rgb(255, 255, 255), 5);

			for (int i = 0; i < lives; i++) {
				al_draw_bitmap_region(shipPic, 0, 0, 32, 32, 20, 250 + (52 * i), NULL);
			}
			al_draw_rectangle(15, 245, 57, 396, al_map_rgb(255, 255, 255), 5);

			if (dir == LEFT) {
			al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, ALLEGRO_FLIP_HORIZONTAL); //draw the player
			}
			else {
				al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, NULL);
			}

			al_draw_rectangle(1800, 30, 1840, 1050, al_map_rgb(255, 255, 255), 10);
			al_draw_line(1820, 40, 1820, mothership.gethp() + 40, al_map_rgb(255, 0, 0), 20);

			al_flip_display(); //flip everything from memory to gamescreen
		}//end render
	}//end game loop

	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

bool collision(int x1, int y1, int x2, int y2, int w, int h) {
	if (x1 > x2 &&
		x1 < x2 + w &&
		y1 > y2 &&
		y1 < y2 + h) {
		return true;
	}
	else {
		return false;
	}
}