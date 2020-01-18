//
// Created by mateo on 23.12.19.
//

#include "BulletController.h"

namespace Controllers {
    BulletController::BulletController(const std::shared_ptr<Entities::Entity> &entity) : Controller(entity) {}

    BulletController::~BulletController() {

    }

    void BulletController::update() {
        std::shared_ptr<Entities::Bullet> bullet = std::dynamic_pointer_cast<Entities::Bullet>(getEntity());
        if (bullet->getCoords().second - (bullet->getEntityHeight()/2) > 3 or
            bullet->getCoords().second + (bullet->getEntityHeight()/2) < -3) {
            setEntity(nullptr);
            bulletOutOfRange = true;
        } else {
            bullet->update();
        }
    }

    bool BulletController::isBulletOutOfRange() const {
        return bulletOutOfRange;
    }

    void BulletController::hitEnemyOrPlayer() {
        std::shared_ptr<Entities::Bullet> bullet = std::dynamic_pointer_cast<Entities::Bullet>(getEntity());
        bullet->removeBullet();
        bulletOutOfRange = true;
    }

    void BulletController::makeEnemyBullet() {
        std::shared_ptr<Entities::Bullet> bullet = std::dynamic_pointer_cast<Entities::Bullet>(getEntity());
        bullet->setEnemy(true);
    }
}


