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
        Bullet(const double &x, const double &y);

        virtual ~Bullet();

        void update();

        void removeBullet();

        void setEnemy(bool enemy);
    };
}



#endif //SPACEINVADERS_BULLET_H
