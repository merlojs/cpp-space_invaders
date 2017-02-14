#ifndef CHARACTER_H
#define CHARACTER_H

#include "header.h"

class Character
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

		void setPos(Point pos);
		void setPos(int x, int y);

		Bounds getBounds();
		Point getPos();
		Point getPreviousPos();

		void resetPosition();

        void setVelocity(Velocity v);

        void updatePosition();
        void draw();

		/* los enemigos disparan? por las dudas lo dejo aca */
		void shoot();


};

#endif // CHARACTER_H
	