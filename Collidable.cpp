#include "Collidable.h"

Collidable::Collidable(Point position, Bounds bounds) :
	pos(position), bounds(bounds)
{
}

Collidable::Collidable(int x, int y, int w, int h) {
	this->pos.x = x;
	this->pos.y = y;

	this->bounds.w = w;
	this->bounds.h = h;
}

Collidable::~Collidable() {

}

Bounds Collidable::getBounds() {
	return this->bounds;
}

Point Collidable::getPos() {
	return this->pos;
}

void Collidable::setPos(Point pos) {
	this->pos = pos;
}

void Collidable::setPos(int x, int y) {
	this->pos.x = x;
	this->pos.y = y;
}

bool Collidable::isColliding(Collidable *collidable) {
	if (this->pos.y > collidable->pos.y + collidable->bounds.h
		|| this->pos.y + this->bounds.h < collidable->pos.y
		|| this->pos.x + this->bounds.w < collidable->pos.x
		|| this->pos.x > collidable->pos.x + collidable->bounds.w) {
		return false;
	}
	else {
		return true;
	}
}