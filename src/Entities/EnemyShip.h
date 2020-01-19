//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_ENEMYSHIP_H
#define SPACEINVADERS_ENEMYSHIP_H

#include "Entity.h"

namespace Entities {
class EnemyShip : public Entity
{
private:
        // enemies will first move left when they spawn, when they reach the border of the window
        // they will start moving right by setting the bool to false
        bool movingLeft = true;

public:
        EnemyShip(const float& x, const float& y);

        void moveLeft();

        void moveRight();

        void moveDown();

        void die();

        bool isMovingLeft() const;

        void setMovingLeft(bool movingLeft);
};
} // namespace Entities

#endif // SPACEINVADERS_ENEMYSHIP_H
