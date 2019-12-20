//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

#include <utility>
#include "Subject.h"

class Game;

class Entity : public ObserverPattern::Subject {
private:
    std::pair<double, double> coords;
public:
    virtual ~Entity();

    Entity();

    Entity(const std::pair<double, double> &coords);

    const std::pair<double, double> &getCoords() const;

    void setCoords(const std::pair<double, double> &coords);
};


#endif //SPACEINVADERS_ENTITY_H
