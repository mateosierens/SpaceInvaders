//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_PLAYERSHIP_H
#define SPACEINVADERS_PLAYERSHIP_H

#include "Entity.h"

class PlayerShip : public Entity {
public:
    PlayerShip(const double &x, const double &y);

    void moveLeft();

    void moveRight();
};


#endif //SPACEINVADERS_PLAYERSHIP_H
