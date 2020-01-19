//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "EnemyShip.h"
#include "Entity.h"

namespace Entities {
class Bullet : public Entity
{
private:
        bool enemy = false;

public:
        Bullet(const float& x, const float& y);

        ~Bullet() override;

        void update();

        void removeBullet();

        void setEnemy(bool enemy);
};
} // namespace Entities

#endif // SPACEINVADERS_BULLET_H
