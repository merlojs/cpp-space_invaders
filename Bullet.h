#ifndef BULLET_H
#define BULLET_H

#include "Collidable.h"

class Bullet : public Collidable
{
protected:
	ALLEGRO_BITMAP* bulletSprite;
	Velocity velocity;

public: // Métodos
	Bullet(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds bounds, Velocity velocity);
	~Bullet();

	Point getPos();

	void updatePosition();
	void draw();
};

#endif // BULLET_H
