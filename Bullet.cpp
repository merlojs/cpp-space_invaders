#include "Bullet.h"

Bullet::Bullet(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions, Velocity velocity) :
	Collidable(startingPos.x - (dimensions.w / 2), startingPos.y, dimensions.w, dimensions.h) {
		this->bulletSprite = sprite;
		this->velocity = velocity;
}

Bullet::~Bullet() {

}

Point Bullet::getPos() {
	return this->pos;
}

void Bullet::draw() {
	al_draw_bitmap_region(this->bulletSprite, 0, 0, 28, 20, this->pos.x, this->pos.y, 0);
}

void Bullet::updatePosition() {
	this->pos.y += this->velocity.y;
}
