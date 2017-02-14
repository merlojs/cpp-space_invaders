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

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

#define SHIP_VELOCITY_X 5

#define FPS 60

// Bordes del area de juego
const int SCREEN_TOP = 110;
const int SCREEN_RIGHT = 550;
const int SCREEN_BOTTOM = 560;
const int SCREEN_LEFT = 50;

// Constantes para la grilla de enemigos
const int ENEMY_GRID_STARTING_X = 150;
const int ENEMY_GRID_STARTING_Y = 150;

const int ENEMY_GRID_WIDTH = 11;
const int ENEMY_GRID_HEIGHT = 5;

const int ENEMY_SPACING_H = 8;
const int ENEMY_SPACING_V =5;

// Constantes de enemigos
const int ENEMY_WIDTH = 21;
const int ENEMY_HEIGHT = 16;

// Constantes de movimiento de enemigos
const int ENEMY_STEP_WIDTH = 10;
const int ENEMY_STEP_HEIGHT = 10;

const int TICS_PER_ENEMY_GRID_STEP = 50;

// Scores
const int SCORE_ENEMY = 50;

// Constantes para las balas
const int BULLET_WIDTH = 6;
const int BULLET_HEIGHT = 12;

const int BULLET_SPEED = 5;

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
