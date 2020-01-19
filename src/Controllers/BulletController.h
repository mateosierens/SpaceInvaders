//
// Created by mateo on 23.12.19.
//

#ifndef SPACEINVADERS_BULLETCONTROLLER_H
#define SPACEINVADERS_BULLETCONTROLLER_H

#include "../Entities/Bullet.h"
#include "Controller.h"

namespace Controllers {
class BulletController : public Controller
{
private:
        bool bulletOutOfRange = false;

public:
        ~BulletController() override;

        void update() override;

        explicit BulletController(const std::shared_ptr<Entities::Entity>& entity);

        bool isBulletOutOfRange() const;

        void hitEnemyOrPlayer();

        void makeEnemyBullet();
};
} // namespace Controllers

#endif // SPACEINVADERS_BULLETCONTROLLER_H
