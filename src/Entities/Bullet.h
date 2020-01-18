//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H


#include "Entity.h"
#include "EnemyShip.h"

namespace Entities {
    class Bullet : public Entity {
    private:
        bool enemy = false;
    public:
        Bullet(const float &x, const float &y);

        ~Bullet() override;

        void update();

        void removeBullet();

        void setEnemy(bool enemy);
    };
}



#endif //SPACEINVADERS_BULLET_H
