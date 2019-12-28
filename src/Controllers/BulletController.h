//
// Created by mateo on 23.12.19.
//

#ifndef SPACEINVADERS_BULLETCONTROLLER_H
#define SPACEINVADERS_BULLETCONTROLLER_H


#include "Controller.h"
#include "../Entities/Bullet.h"

class BulletController : public Controller {
private:
    bool bulletOutOfRange = false;

public:
    virtual ~BulletController();

    void update() override;

    BulletController(const std::shared_ptr<Entity> &entity);

    bool isBulletOutOfRange() const;

    void hitEnemy();
};


#endif //SPACEINVADERS_BULLETCONTROLLER_H
