//
// Created by mateo on 23.12.19.
//

#ifndef SPACEINVADERS_BULLETVIEW_H
#define SPACEINVADERS_BULLETVIEW_H

#include "../Entities/Entity.h"
#include "View.h"

class BulletView : public View {
public:
    BulletView(std::shared_ptr<Entity> &entity, const std::string &textureFile);

    ~BulletView() override;

    void onNotify(const Entity &entity, std::string event) override;
};


#endif //SPACEINVADERS_BULLETVIEW_H
