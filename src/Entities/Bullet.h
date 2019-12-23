//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H


#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(const double &x, const double &y);

    virtual ~Bullet();

    void update();
};


#endif //SPACEINVADERS_BULLET_H
