#include "Character.h"

using namespace std;

Character::Character(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions) :
	Collidable(startingPos, dimensions)/*, characterSprite(sprite)*/, previousPos(startingPos) {
	this->velocity.x = 0;
	this->velocity.y = 0;

	this->characterSprite = sprite;
}

Character::~Character() {

}

Point Character::getPreviousPos() {
	return this->previousPos;
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
/*
void Character::shoot() {

}
*/
