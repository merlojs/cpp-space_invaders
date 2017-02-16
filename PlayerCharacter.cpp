#include "PlayerCharacter.h"
#include <iostream>

using namespace std;
PlayerCharacter::PlayerCharacter(ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP *bulletSprite, Point startingPos, Bounds dimensions) :
        Character(sprite, bulletSprite, startingPos, dimensions) {
	this->shotDirection = UP;
}

PlayerCharacter::~PlayerCharacter() {

}

void PlayerCharacter::processInput(GameInput *playerInput, BulletManager *bulletManager) {
	this->velocity.x = 0;
	this->velocity.y = 0;

	if (playerInput->left) {
		this->velocity.x = -SHIP_VELOCITY_X;
	}

	if (playerInput->right) {
		this->velocity.x = SHIP_VELOCITY_X;
	}

	if (playerInput->action && !bulletManager->hasPlayerBullet()) {
		bulletManager->addPlayerBullet(this->shoot());
	}
}
