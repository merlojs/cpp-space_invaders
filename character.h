#ifndef CHARACTER_H
#define CHARACTER_H

#include "header.h"
#include "Collidable.h"
#include "Bullet.h"

class Character : public Collidable
{
    protected:
        ALLEGRO_BITMAP* characterSprite;
		ALLEGRO_BITMAP *bulletSprite;
		Point previousPos;
        Velocity velocity;

		int shotDirection;
		bool alive;
    public: // Métodos
		Character(ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP *bulletSprite, Point startingPos, Bounds bounds);
        ~Character();

		Point getPreviousPos();
		void resetPosition();

        void setVelocity(Velocity v);

        void updatePosition();
        void draw();

		bool isAlive();
		void kill();

		Bullet *shoot();
};

#endif // CHARACTER_H
	