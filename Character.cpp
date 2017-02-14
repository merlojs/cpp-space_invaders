#include "Character.h"

using namespace std;

Character::Character(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions) :
    characterSprite(sprite), pos(startingPos), bounds(dimensions), previousPos(startingPos) {
	this->velocity.x = 0;
	this->velocity.y = 0;
}

Character::~Character() {

}
Bounds Character::getBounds() {
	return this->bounds;
}

Point Character::getPos() {
    return this->pos;
}

Point Character::getPreviousPos() {
	return this->previousPos;
}

void Character::setPos(Point pos) {
	this->pos = pos;
}

void Character::setPos(int x, int y) {
	this->pos.x = x;
	this->pos.y = y;
}

void Character::draw(){
   // al_convert_mask_to_alpha(this->characterSprite, al_map_rgb(255, 0 , 255));
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

void Character::shoot() {

}
