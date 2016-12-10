#include "Character.h"

using namespace std;

Character::Character(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions) :
    characterSprite(sprite), pos(startingPos), bounds(dimensions) {
}

Character::~Character() {

}

Point Character::getPos() {
    return this->pos;
}

void Character::draw(){
    al_convert_mask_to_alpha(this->characterSprite, al_map_rgb(255, 0 , 255));
    al_draw_bitmap_region(this->characterSprite, 0, 0, 28, 20, this->pos.x, this->pos.y, 0);
}

void Character::setVelocity(Velocity v) {
    this->velocity = v;
}

void Character::updatePosition() {
    this->pos.x += this->velocity.x;
    this->pos.y += this->velocity.y;
}
