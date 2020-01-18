//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_CONTROLLER_H
#define SPACEINVADERS_CONTROLLER_H

#include "../Entities/Entity.h"

namespace Controllers {
    class Controller {
    private:
        std::shared_ptr<Entities::Entity> entity;
    public:
        virtual ~Controller();

        explicit Controller(const std::shared_ptr<Entities::Entity> &entity);

        const std::shared_ptr<Entities::Entity> &getEntity() const;

        std::pair<float, float> getCoords();

        double getEntityWidth();

        double getEntityHeight();

        void setEntity(const std::shared_ptr<Entities::Entity> &entity);

        virtual void update() = 0;
    };
}




#endif //SPACEINVADERS_CONTROLLER_H
