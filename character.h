#ifndef CHARACTER_H
#define CHARACTER_H

#include "header.h"
#include "Collidable.h"

class Character : public Collidable
{
    protected:
        ALLEGRO_BITMAP* characterSprite;
        Point pos;
		Point previousPos;
        Bounds bounds;
        Velocity velocity;

    public: // Métodos
        Character(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds bounds);
        ~Character();

		Point getPreviousPos();
		void resetPosition();

        void setVelocity(Velocity v);

        void updatePosition();
        void draw();

		/* los enemigos disparan? por las dudas lo dejo aca */
//		void shoot();
};

#endif // CHARACTER_H
	