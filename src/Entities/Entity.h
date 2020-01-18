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
        std::pair<float, float> coords; // coordinates of entity in game logic

        // width and height of entity in game logic
        float entityWidth;
        float entityHeight;

    public:
        virtual ~Entity();

        Entity();

        explicit Entity(const std::pair<float, float> &coords);

        const std::pair<float, float> &getCoords() const;

        void setCoords(const std::pair<float, float> &coords);

        float getEntityWidth() const;

        void setEntityWidth(float entityWidth);

        float getEntityHeight() const;

        void setEntityHeight(float entityHeight);

        bool collision(std::shared_ptr<Entity> otherEntity);
    };
}




#endif //SPACEINVADERS_ENTITY_H
