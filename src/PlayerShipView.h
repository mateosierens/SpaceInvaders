//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_PLAYERSHIPVIEW_H
#define SPACEINVADERS_PLAYERSHIPVIEW_H


#include "View.h"
#include <SFML/Graphics.hpp>

class PlayerShipView : public View {
private:
    sf::Sprite playerSprite;

public:
    ~PlayerShipView() override;

    void onNotify(const Entity &entity, std::string event) override;
};


#endif //SPACEINVADERS_PLAYERSHIPVIEW_H
