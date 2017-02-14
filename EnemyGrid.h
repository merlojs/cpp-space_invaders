#ifndef ENEMY_GRID_H
#define ENEMY_GRID_H

#include "header.h"
#include "EnemyCharacter.h"

class EnemyGrid {
	private:
		Point pos;
		Bounds bounds;
		vector<vector<EnemyCharacter *> *> *enemies;

		int direction;
		int prevDirection;
		int framesSinceLastStep;
	public:
		EnemyGrid(int width, int height, ALLEGRO_BITMAP *enemySprite, ALLEGRO_BITMAP *bulletSprite);
		~EnemyGrid();

		vector<vector<EnemyCharacter *> *> *getEnemies();

		void updatePosition();

		void draw();
		void debugDraw();
};

#endif // ENEMY_GRID_H