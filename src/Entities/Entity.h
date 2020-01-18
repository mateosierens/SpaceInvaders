//
// Created by mateo on 30.11.19.
//

#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

#include <utility>
#include "../Subject.h"

namespace Entities {
    class Entity : public ObserverPattern::Subject {
    private:
        std::pair<double, double> coords; // coordinates of entity in game logic

        // width and height of entity in game logic
        double entityWidth;
        double entityHeight;

    public:
        virtual ~Entity();

        Entity();

        Entity(const std::pair<double, double> &coords);

        const std::pair<double, double> &getCoords() const;

        void setCoords(const std::pair<double, double> &coords);

        double getEntityWidth() const;

        void setEntityWidth(double entityWidth);

        double getEntityHeight() const;

        void setEntityHeight(double entityHeight);

        bool collision(std::shared_ptr<Entity> otherEntity);
    };
}




#endif //SPACEINVADERS_ENTITY_H
