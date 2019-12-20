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
    sf::Texture playerTexture;

public:
    ~PlayerShipView() override;

    PlayerShipView(std::shared_ptr<Entity> &entity);

    void onNotify(const Entity &entity, std::string event) override;

    void makeThisObserver(std::shared_ptr<Entity> &entity);

    const sf::Sprite &getPlayerSprite() const;
};


#endif //SPACEINVADERS_PLAYERSHIPVIEW_H
