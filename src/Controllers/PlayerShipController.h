//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_PLAYERSHIPCONTROLLER_H
#define SPACEINVADERS_PLAYERSHIPCONTROLLER_H

#include "../Entities/Entity.h"
#include "BulletController.h"
#include "Controller.h"

namespace Controllers {
class PlayerShipController : public Controller
{
public:
        explicit PlayerShipController(const std::shared_ptr<Entities::Entity>& entity);

        void move(const char& c);

        bool shotBullet();

        void setBullet(std::shared_ptr<BulletController>& bullet);

        void addEnemyBullet(const std::shared_ptr<BulletController>& enemyBullet);

        void update() override;

        bool alive();

        void kill();

        int getLives();
};
} // namespace Controllers

#endif // SPACEINVADERS_PLAYERSHIPCONTROLLER_H
