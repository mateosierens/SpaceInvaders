//
// Created by mateo on 24.12.19.
//

#ifndef SPACEINVADERS_ENEMYSHIPCONTROLLER_H
#define SPACEINVADERS_ENEMYSHIPCONTROLLER_H


#include "Controller.h"
#include "BulletController.h"

class EnemyShipController : public Controller {
private:
    std::shared_ptr<BulletController> playerBullet;
public:
    EnemyShipController(const std::shared_ptr<Entity> &entity);

    ~EnemyShipController() override;

    void update() override;

    const std::shared_ptr<BulletController> &getPlayerBullet() const;

    void setPlayerBullet(const std::shared_ptr<BulletController> &playerBullet);

    bool movingLeft();

    void setMovingLeft(bool direction);

    void moveDown();
};


#endif //SPACEINVADERS_ENEMYSHIPCONTROLLER_H
