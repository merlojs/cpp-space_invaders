#ifndef HEADER_INC
#define HEADER_INC

// TODO: Separar en otro archivo?
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "allegro_inc.h"

using namespace std;

#define SCREEN_WIDTH 600   //ver si las voy a usar
#define SCREEN_HEIGHT 600

#define SHIP_VELOCITY_X 5

#define FPS 60

const int SCREEN_TOP = 5;
const int SCREEN_RIGHT = 550;
const int SCREEN_BOTTOM = 560;
const int SCREEN_LEFT = 50;

// TODO: Revisar valores
const int ENEMY_GRID_STARTING_X = 150;
const int ENEMY_GRID_STARTING_Y = 150;

const int ENEMY_GRID_WIDTH = 11;
const int ENEMY_GRID_HEIGHT = 5;

const int ENEMY_SPACING_H = 8;
const int ENEMY_SPACING_V =5;

const int ENEMY_WIDTH = 21;
const int ENEMY_HEIGHT = 16;

const int ENEMY_STEP_WIDTH = 10;
const int ENEMY_STEP_HEIGHT = 10;

const int TICS_PER_ENEMY_GRID_STEP = 50;

struct Point {
	int x;
	int y;
};

struct Velocity {
	int x;
	int y;
};

struct Bounds {
	int w;
	int h;
};

struct GameInput {
	bool up;
	bool right;
	bool down;
	bool left;
	bool action;
	bool escape;
};

enum MOVE_DIR {
	UP, RIGHT, DOWN, LEFT
};

void keyboardEventHandler(bool keyUp, int keyCode, GameInput *playerInput);

#endif // HEADER_INC
