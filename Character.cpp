#include "Character.h"

using namespace std;

Character::Character(ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP *bulletSprite, Point startingPos, Bounds dimensions) :
	Collidable(startingPos, dimensions) {
	this->velocity.x = 0;
	this->velocity.y = 0;

	this->characterSprite = sprite;
	this->bulletSprite = bulletSprite;

	this->previousPos = startingPos;
}

Character::~Character() {

}

Point Character::getPreviousPos() {
	return this->previousPos;
}

bool Character::isAlive() {
	return this->alive;
}

void Character::draw(){
    al_draw_bitmap_region(this->characterSprite, 0, 0, 28, 20, this->pos.x, this->pos.y, 0);
}

void Character::setVelocity(Velocity v) {
    this->velocity = v;
}

void Character::updatePosition() {
	this->previousPos = this->pos;

	this->pos.x += this->velocity.x;
	this->pos.y += this->velocity.y;
}

void Character::resetPosition() {
	this->pos = this->previousPos;
}

void Character::kill() {
	this->alive = false;
}

void Character::explode() {

}

Bullet * Character::shoot() {
	Velocity bulletVelocity;

	if (shotDirection == UP) {
		bulletVelocity.y = -BULLET_SPEED;
	}
	else {
		bulletVelocity.y = BULLET_SPEED;
	}

	Point startingPos;
	startingPos.x = this->pos.x + this->bounds.w / 2;
	startingPos.y = this->pos.y;

	Bounds bulletBounds;
	bulletBounds.w = BULLET_WIDTH;
	bulletBounds.h = BULLET_HEIGHT;

	return new Bullet(this->bulletSprite, startingPos, bulletBounds, bulletVelocity);
}

