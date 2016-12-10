#include "PlayerCharacter.h"

using namespace std;
PlayerCharacter::PlayerCharacter(ALLEGRO_BITMAP* sprite, Point startingPos, Bounds dimensions) :
        Character(sprite, startingPos, dimensions) {
}

void PlayerCharacter::processInput(GameInput *playerInput) {
	if (playerInput->left) {
		this->velocity.x -= SHIP_VELOCITY_X;
	}

	if (playerInput->right) {
		this->velocity.x += SHIP_VELOCITY_X;
	}
}
