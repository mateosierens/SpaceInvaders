//
// Created by mateo on 23.12.19.
//

#include "BulletController.h"


BulletController::BulletController(const std::shared_ptr<Entity> &entity) : Controller(entity) {}

BulletController::~BulletController() {

}

void BulletController::update() {
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(getEntity());
    if (bullet->getCoords().second - (bullet->getEntityHeight()/2) > 3) {
        setEntity(nullptr);
        bulletOutOfRange = true;
    } else {
        bullet->update();
    }
}

bool BulletController::isBulletOutOfRange() const {
    return bulletOutOfRange;
}

void BulletController::hitEnemy() {
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(getEntity());
    bullet->removeBullet();
    bulletOutOfRange = true;
}
