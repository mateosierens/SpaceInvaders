//
// Created by mateo on 24.12.19.
//

#ifndef SPACEINVADERS_ENEMYSHIPVIEW_H
#define SPACEINVADERS_ENEMYSHIPVIEW_H


#include "View.h"

namespace Views {
    class EnemyShipView : public View {
    public:
        ~EnemyShipView() override;

        void onNotify(const Entities::Entity &entity, std::string event) override;

        EnemyShipView(std::shared_ptr<Entities::Entity> &entity, const std::string &textureFile);
    };
}



#endif //SPACEINVADERS_ENEMYSHIPVIEW_H
