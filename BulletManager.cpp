#include "BulletManager.h"


BulletManager::BulletManager()
{
	this->enemyBullets = new vector < Bullet * > ;
	this->playerBullet = 0;
}


BulletManager::~BulletManager()
{
}

void BulletManager::addPlayerBullet(Bullet *bullet)
{
	this->playerBullet = bullet;
}

void BulletManager::addEnemyBullet(Bullet *bullet)
{
	this->enemyBullets->push_back(bullet);
}

bool BulletManager::hasPlayerBullet() {
	return (this->playerBullet != 0 ? true : false);
}

void BulletManager::updateBulletsPosition()
{
	if (this->hasPlayerBullet()) {
		this->playerBullet->updatePosition();
		if (this->playerBullet->getPos().y < SCREEN_TOP) {
			this->playerBullet = 0;
		}
	}
	//TODO: Loopear balas de enemigos llamando al método de update
}

void BulletManager::draw() {
	if (this->hasPlayerBullet()) {
		this->playerBullet->draw();
	}
	//TODO: Loopear balas de enemigos llamando al método de dibujado
}

Bullet *BulletManager::getPlayerBullet() {
	return this->playerBullet;
}



void BulletManager::checkPlayerBulletCollisions(EnemyGrid *enemyGrid, ScoreBoard *scoreBoard) {
	if (this->playerBullet) {
		for (vector<vector<EnemyCharacter *> *>::iterator it = enemyGrid->getEnemies()->begin(); it != enemyGrid->getEnemies()->end(); it++) {
			vector<EnemyCharacter *> *enemyRow = (*it);

			for (vector<EnemyCharacter *>::iterator it2 = enemyRow->begin(); it2 != enemyRow->end(); it2++) {
				if ((*it2)->isAlive() && (*it2)->isColliding(playerBullet)) {
					(*it2)->kill();
					// TODO: Animar explosion y esas cosas
					scoreBoard->addPoints((*it2)->getKillScore());
					this->playerBullet = 0;
					return;
				}
			}
		}
	}
}