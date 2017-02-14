#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "header.h"

class Collidable
{
	protected:
		Point pos;
		Bounds bounds;

	public:
		Collidable(Point pos, Bounds bounds);
		~Collidable();

		bool isColliding(Collidable *collidable);

		void setPos(Point pos);
		void setPos(int x, int y);

		Bounds getBounds();
		Point getPos();
};


#endif // COLLIDABLE_H 