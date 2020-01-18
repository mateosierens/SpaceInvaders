//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_PLAYERSHIPCONTROLLER_H
#define SPACEINVADERS_PLAYERSHIPCONTROLLER_H


#include "Controller.h"
#include "BulletController.h"
#include "../Entities/Entity.h"

namespace Controllers {
    class PlayerShipController : public Controller {
    public:
        PlayerShipController(const std::shared_ptr<Entities::Entity> &entity);

        void move(const char &c);

        bool shotBullet();

        void setBullet(std::shared_ptr<BulletController> &bullet);

        void addEnemyBullet(const std::shared_ptr<BulletController> &enemyBullet);

        void update();

        bool alive();

        void kill();

        int getLives();
    };
}




#endif //SPACEINVADERS_PLAYERSHIPCONTROLLER_H
