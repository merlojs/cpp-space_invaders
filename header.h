#ifndef HEADER_INC
#define HEADER_INC

#include "allegro_inc.h"

#define SCREEN_WIDTH 600   //ver si las voy a usar
#define SCREEN_HEIGHT 600

#define SHIP_VELOCITY_X 5

#define FPS 60

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

void keyboardEventHandler(bool keyUp, int keyCode, GameInput *playerInput);

#endif // HEADER_INC
