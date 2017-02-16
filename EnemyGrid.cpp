#include "EnemyGrid.h"
#include <iostream>

EnemyGrid::EnemyGrid(int width, int height, ALLEGRO_BITMAP *enemySprite, ALLEGRO_BITMAP *bulletSprite) {
	this->pos.x = ENEMY_GRID_STARTING_X;
	this->pos.y = ENEMY_GRID_STARTING_Y;

	this->bounds.w = (ENEMY_WIDTH + ENEMY_SPACING_H) * width;
	this->bounds.h = (ENEMY_HEIGHT + ENEMY_SPACING_V) * height;

	this->direction = RIGHT;
	this->prevDirection = this->direction;

	this->framesSinceLastStep = 0;
	this->framesSinceLastShot = 0;

	Bounds enemyBounds = {};
	enemyBounds.w = ENEMY_WIDTH;
	enemyBounds.h = ENEMY_HEIGHT;

	this->enemies = new vector<vector<EnemyCharacter *> *>();

	for (int i = 0; i < height; i++) {
		vector<EnemyCharacter *> *enemyRow = new vector < EnemyCharacter * > ;
		Point enemyPos = {};
		enemyPos.y = ENEMY_GRID_STARTING_Y + i * (ENEMY_SPACING_V + ENEMY_HEIGHT);

		for (int j = 0; j < width; j++) {
			enemyPos.x = ENEMY_GRID_STARTING_X + j * (ENEMY_SPACING_H + ENEMY_WIDTH);
			enemyRow->push_back(new EnemyCharacter(enemySprite, bulletSprite, enemyPos, enemyBounds, SCORE_ENEMY));
		}

		this->enemies->push_back(enemyRow);
	}
}

EnemyGrid::~EnemyGrid() {

}

void EnemyGrid::resetEnemyPositions() {
	this->pos.x = ENEMY_GRID_STARTING_X;
	this->pos.y = ENEMY_GRID_STARTING_Y;

	this->prevDirection = RIGHT;
	this->direction = RIGHT;

	int i = 0, j = 0;
	Point newPos;
	for (vector<vector<EnemyCharacter *> *>::iterator it = this->enemies->begin(); it != this->enemies->end(); it++, i++) {
		vector<EnemyCharacter *> *enemyRow = (*it);

		j = 0;
		for (vector<EnemyCharacter *>::iterator it2 = enemyRow->begin(); it2 != enemyRow->end(); it2++, j++) {
			newPos.x = this->pos.x + j * (ENEMY_SPACING_H + ENEMY_WIDTH);
			newPos.y = this->pos.y + i * (ENEMY_SPACING_V + ENEMY_HEIGHT);

			(*it2)->setPos(newPos);
		}
	}
}

void EnemyGrid::updatePosition() {
	if (this->framesSinceLastStep < TICS_PER_ENEMY_GRID_STEP) {
		this->framesSinceLastShot++;

		this->framesSinceLastStep++;
	}
	else {
		this->framesSinceLastStep = 0;

		if (this->direction == DOWN) {
			this->pos.y += ENEMY_STEP_HEIGHT;

			this->direction = (this->prevDirection == LEFT ? RIGHT : LEFT);
		} 
		else if (this->direction == LEFT) {
			this->pos.x -= ENEMY_STEP_WIDTH;

			if (this->pos.x <= SCREEN_LEFT) {
				this->prevDirection = LEFT;
				this->direction = DOWN;
			}
		}
		else {
			this->pos.x += ENEMY_STEP_WIDTH;
			if (this->pos.x + this->bounds.w >= SCREEN_RIGHT) {
				this->prevDirection = RIGHT;
				this->direction = DOWN;
			}
		}

		Point newPos;
		int i = 0, j = 0;
		for (vector<vector<EnemyCharacter *> *>::iterator it = this->enemies->begin(); it != this->enemies->end(); it++, i++) {
			vector<EnemyCharacter *> *enemyRow = (*it);

			j = 0;
			for (vector<EnemyCharacter *>::iterator it2 = enemyRow->begin(); it2 != enemyRow->end(); it2++, j++) {
				newPos.x = this->pos.x + j * (ENEMY_SPACING_H + ENEMY_WIDTH);
				newPos.y = this->pos.y + i * (ENEMY_SPACING_V + ENEMY_HEIGHT);

				(*it2)->setPos(newPos);
			}
		}
	}
}

void EnemyGrid::draw() {
	for (vector<vector<EnemyCharacter *> *>::iterator it = this->enemies->begin(); it != this->enemies->end(); it++) {
		vector<EnemyCharacter *> *enemyRow = (*it);

		for (vector<EnemyCharacter *>::iterator it2 = enemyRow->begin(); it2 != enemyRow->end(); it2++) {
			if ((*it2)->isAlive()) {
				(*it2)->draw();
			}
		}
	}
}

EnemyCharacter *EnemyGrid::getShooter() {
	// Determinar si dispara (tope de balas en vuelo, tiempo)
	srand(time(NULL));

	int yIndex = rand() % ENEMY_GRID_HEIGHT;
	int xIndex = rand() % ENEMY_GRID_WIDTH;

	return this->enemies->at(yIndex)->at(xIndex);
}

void EnemyGrid::debugDraw() {
	al_draw_rectangle(this->pos.x, this->pos.y, this->pos.x + this->bounds.w, this->pos.y + this->bounds.h, al_map_rgb(255, 0, 0), 3);
}

vector<vector<EnemyCharacter *> *> *EnemyGrid::getEnemies() {
	return this->enemies;
}