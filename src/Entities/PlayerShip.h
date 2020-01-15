//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_PLAYERSHIP_H
#define SPACEINVADERS_PLAYERSHIP_H

#include "Entity.h"
#include "Bullet.h"
#include "../Controllers/BulletController.h"

class PlayerShip : public Entity {
private:
    // initialise bullet with nullptr for check if there is already a playerbullet on screen
    std::shared_ptr<BulletController> bullet = nullptr;
    std::vector<std::shared_ptr<BulletController>> enemyBullets;
    int lives = 3;
    bool alive = true;
public:
    PlayerShip(const double &x, const double &y);

    void moveLeft();

    void moveRight();

    const std::shared_ptr<BulletController> &getBullet() const;

    void setBullet(const std::shared_ptr<BulletController> &bullet);

    void addEnemyBullet(const std::shared_ptr<BulletController> &enemyBullet);

    const std::vector<std::shared_ptr<BulletController>> &getEnemyBullets() const;

    void removeEnemyBullet(const int &index);

    void decreaseLives();

    int getLives() const;

    bool isAlive() const;

    void kill();

};


#endif //SPACEINVADERS_PLAYERSHIP_H
