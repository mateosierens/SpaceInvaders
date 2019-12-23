//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_VIEW_H
#define SPACEINVADERS_VIEW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Observer.h"
#include "../Transformation.h"

class View : public ObserverPattern::Observer {
private:
    std::shared_ptr<Entity> entity;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    View(std::shared_ptr<Entity> &entity, const std::string &textureFile);

    virtual ~View() {};

    virtual void onNotify(const Entity &entity, std::string event) = 0;

    virtual void makeThisObserver(std::shared_ptr<Entity> &entity);

    const sf::Sprite &getSprite() const;

    void setSprite(const sf::Sprite &sprite);
};


#endif //SPACEINVADERS_VIEW_H
