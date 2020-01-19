//
// Created by mateo on 24.12.19.
//

#ifndef SPACEINVADERS_ENEMYSHIPCONTROLLER_H
#define SPACEINVADERS_ENEMYSHIPCONTROLLER_H

#include "BulletController.h"
#include "Controller.h"

namespace Controllers {
class EnemyShipController : public Controller
{
private:
        std::shared_ptr<BulletController> playerBullet;

public:
        explicit EnemyShipController(const std::shared_ptr<Entities::Entity>& entity);

        ~EnemyShipController() override;

        void update() override;

        const std::shared_ptr<BulletController>& getPlayerBullet() const;

        void setPlayerBullet(const std::shared_ptr<BulletController>& playerBullet);

        bool movingLeft();

        void setMovingLeft(bool direction);

        void moveDown();
};
} // namespace Controllers

#endif // SPACEINVADERS_ENEMYSHIPCONTROLLER_H
