#include "PlayerCharacter.h"
#include <iostream>

using namespace std;
PlayerCharacter::PlayerCharacter(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions) :
        Character(sprite, startingPos, dimensions) {
}

PlayerCharacter::~PlayerCharacter() {

}

void PlayerCharacter::processInput(GameInput *playerInput) {
	this->velocity.x = 0;
	this->velocity.y = 0;

	if (playerInput->left) {
		this->velocity.x = -SHIP_VELOCITY_X;
	}

	if (playerInput->right) {
		this->velocity.x = SHIP_VELOCITY_X;
	}
}
