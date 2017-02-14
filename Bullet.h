#ifndef BULLET_H
#define BULLET_H

#include "Character.h"

class Bullet
{
protected:
	ALLEGRO_BITMAP* bulletSprite;
	Point pos;
	Bounds bounds;
	Velocity velocity;

public: // Métodos
	Bullet(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds bounds);
	~Bullet();

	Point getPos();
	void setVelocity(Velocity v);

	void updatePosition();
	void draw();
};

#endif // BULLET_H
