#include "Bullet.h"

using namespace std;

Bullet::Bullet(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions) :
	bulletSprite(sprite), pos(startingPos), bounds(dimensions) {
}

Bullet::~Bullet() {

}

Point Bullet::getPos() {
	return this->pos;
}

void Bullet::draw() {
	al_convert_mask_to_alpha(this->bulletSprite, al_map_rgb(255, 0, 255));
	al_draw_bitmap_region(this->bulletSprite, 0, 0, 28, 20, this->pos.x, this->pos.y, 0);
}

void Bullet::setVelocity(Velocity v) {
	this->velocity = v;
}

void Bullet::updatePosition() {
	this->pos.x += this->velocity.x;
	this->pos.y += this->velocity.y;
}
