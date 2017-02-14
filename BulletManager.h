#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "header.h"

#include "ScoreBoard.h"
#include "Bullet.h"
#include "EnemyGrid.h"

class BulletManager
{
private:
	Bullet *playerBullet;
	vector<Bullet *> *enemyBullets;

public:
	BulletManager();
	~BulletManager();

	void addPlayerBullet(Bullet *bullet);
	void addEnemyBullet(Bullet *bullet);

	bool hasPlayerBullet();
	Bullet *getPlayerBullet();

	void checkPlayerBulletCollisions(EnemyGrid *enemyGrid, ScoreBoard *scoreBoard);
	void updateBulletsPosition();

	void draw();
};

#endif // BULLET_MANAGER_H