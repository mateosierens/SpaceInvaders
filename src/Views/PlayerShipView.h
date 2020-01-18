//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_PLAYERSHIPVIEW_H
#define SPACEINVADERS_PLAYERSHIPVIEW_H

#include "View.h"

namespace Views {
    class PlayerShipView : public View {
    public:
        ~PlayerShipView() override;

        PlayerShipView(std::shared_ptr<Entities::Entity> &entity, const std::string &textureFile);

        void onNotify(const Entities::Entity &entity, std::string event) override;
    };
}




#endif //SPACEINVADERS_PLAYERSHIPVIEW_H
